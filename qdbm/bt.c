#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

/* XSB Includes */
#include "xsb_config.h"
#include "auxlry.h"
/* context.h is necessary for the type of a thread context. */
#include "context.h"
#include "cinterf.h"
#include "cell_xsb.h"
#include "io_builtins_xsb.h"
#ifdef WIN_NT
#define XSB_DLL
#endif

/* QDBM Includes */
#include <depot.h>
#include <cabin.h>
#include <vista.h>
//#include <villa.h>

#define DBNAME "xsbdb"

// predefine functions
//char *pt2str(prolog_term term);
char *pt2dbname(char *predname, int arity, int arg);

// stats regarding prefix or range query.
static const int NOT_INITIALIZED = 10, PREFIX_MODE = 1, RANGE_MODE = 2;

// a structure to hold information about the b+ tree table.
struct IndexTable
{
	VILLA *villa;
	char *predname;
	int arity;
	int argnum;
	int open;

	// stats for prefix and range queries
	int cursorMode;
	char *prefix;
	char *upperBound;
};

struct ActiveLookupListNode
{
	int index;
	CBLIST *list;
	struct ActiveLookupListNode *next;
	struct ActiveLookupListNode *prev;
};

// pointer to our B+ trees.
static struct IndexTable *villas;
static int currentSize = 10;
static int nextIndex = 0;

// pointer to active CBLISTS being used to return results.
static struct ActiveLookupListNode *cblHead;
static int nextCBLIndex = 0;

/**
 * bt_init/3. 
 * Initializes the B+ Tree.
 * Should be called with the following args:
 * bt_init(+predname/arity, +index_arg_num, -Handle)
 *
 * The value returned in Handle can be used to insert
 * values directly into an index table later on.
 **/
DllExport int call_conv bt_init(CTXTdecl)
{
	if(villas == NULL)
	{
		villas = malloc(sizeof(struct IndexTable) * currentSize);
		//printf("First Initialization\n");
	}
	if(nextIndex >= currentSize)
	{
		// expand the tables
		currentSize = currentSize * 2;
		struct IndexTable *newtable = malloc(sizeof(struct IndexTable) * currentSize);
		memcpy(newtable, villas, sizeof(villas));
		free(villas);
		villas = newtable;

		printf("Expanding Villa Table Size to: %i\n", currentSize);
	}

	/* compute the DB name */
	/* as db_predname_arity_indexargnum */
	prolog_term predicate = reg_term(CTXTdecl 1);
	prolog_term indexon = reg_term(CTXTdecl 2);
	prolog_term handle = reg_term(CTXTdecl 3);
	int index_arg = p2c_int(indexon);
	// TODO: Sanity checking on input args
	char *predname = p2c_string(p2p_arg(predicate, 1));
	int arity = p2c_int(p2p_arg(predicate, 2));

	if(index_arg > arity)
	{
		fprintf(stderr, "Error: Index on Argument Number Greater Than Predicate Arity (Arity %i, index on: %i).\n", arity, index_arg);
		return FALSE;
	}

	char *db_name = pt2dbname(predname, arity, index_arg);

	villas[nextIndex].arity = arity;
	villas[nextIndex].predname = predname;
	villas[nextIndex].argnum = index_arg;
	villas[nextIndex].open = 0;
	villas[nextIndex].cursorMode = NOT_INITIALIZED;
	/* open the database */
	if(!(villas[nextIndex].villa = vlopen(db_name, VL_OWRITER | VL_OCREAT, VL_CMPLEX))){
		fprintf(stderr, "vlopen: %s\n", dperrmsg(dpecode));
		return FALSE;
	}
	villas[nextIndex].open = 1;

	int size = vlrnum(villas[nextIndex].villa);
	printf("B+ Tree (%s) Size: %i\n", db_name, size);

	c2p_int(CTXTdecl nextIndex, handle);

	nextIndex++;

	return TRUE;
}

/**
 * bt_insert/2.
 * Inserts the given term into the B+ Tree given by the second argument.
 * The B+ Tree must match on predicate symbol and arity and will be indexed on 
 * the same argument as others in that table.
 *
 * bt_insert(+Handle, +Term).
 **/
DllExport int call_conv bt_insert(CTXTdecl)
{
	// Find the IndexTable associated with the handle.
	prolog_term handle_term = reg_term(CTXTdecl 1);
	if(!is_int(handle_term))
	{
		fprintf(stderr, "Insert Error: Handle Non-Integer Type.\n");
		return FALSE;
	}

	int handle_index = p2c_int(handle_term);

	if(handle_index >= nextIndex)
	{
		fprintf(stderr, "Insert Error: Handle Exceeds Range of Loaded Tables.\n");
		return FALSE;
	}

	struct IndexTable handle = villas[handle_index];

	// now confirm the pred name and arity for this predicate
	prolog_term value = reg_term(CTXTdeclc 2);

	if(!is_functor(value))
	{
		fprintf(stderr, 
			"Insert Error: Insert Argument Is Not A Functor.\n");
		return FALSE;
	}

	int arity = p2c_arity(value);
	char *predname = p2c_functor(value);

	if(arity != handle.arity)
	{
		fprintf(stderr, "Insert Error: Arity Mismatch (Got %i, Expecting %i).\n", arity, handle.arity);
		return FALSE;
	}

	if(strcmp(predname, handle.predname) != 0)
	{
		fprintf(stderr, "Insert Error: Functor Mismatch (Got '%s', Expecting '%s').\n", predname, handle.predname);
		return FALSE;	
	}

	int indexon = handle.argnum;

	// This check may be redundant...indexon < arity is checked in INIT and the indexon argument is taken
	// from the IndexTable.
	if(indexon > arity)
	{
		fprintf(stderr, "Insert Error: Index on Argument Number Greater Than Predicate Arity.\n");
		return FALSE;
	}

	// Now do the actual insert...
	prolog_term key = p2p_arg(value, indexon);
	char *buff = canonical_term(CTXTdecl key, 1);
	int size = cannonical_term_size(CTXTdecl) + 1;
	char *key_str = malloc(sizeof(char) * size);
	strncpy(key_str, buff, size);

	buff = canonical_term(CTXTdecl value, 1);
	size = cannonical_term_size(CTXTdecl) + 1;
	char *val_str = malloc(sizeof(char) * size);
	strncpy(val_str, buff, size);
	//char *val_str = pt2str(value);
	//char *key_str = pt2str(key);

	if(!vlput(handle.villa, key_str, -1, val_str, -1, VL_DDUPR))
	{
    	fprintf(stderr, "Insert Error (DB): %s\n", dperrmsg(dpecode));
    	return FALSE;
	}

	//free(val_str);
	//free(key_str);

	// ---------------------------------------------
	// -- DEBUG -- PRINT OUT THE TERM --------------
	// ---------------------------------------------
	//printf("Insert Term: (Key: %s, Value: %s)\n", key_str, val_str);
	//int size = vlrnum(handle.villa);
	//printf("B+ Tree (%s) Size: %i\n", handle.predname, size);
	// ---------------------------------------------
	// ---------------------------------------------

	return TRUE;
}


DllExport int call_conv bt_close(CTXTdecl) 
{
	prolog_term handle_term = reg_term(CTXTdecl 1);
	if(!is_int(handle_term))
	{
		fprintf(stderr, "Close Error: Handle Non-Integer Type.\n");
		return FALSE;
	}

	int handle_index = p2c_int(handle_term);

	if(handle_index >= nextIndex)
	{
		fprintf(stderr, "Close Error: Handle Exceeds Range of Loaded Tables.\n");
		return FALSE;
	}

	struct IndexTable handle = villas[handle_index];
	
	/* close the database */
	if(!vlclose(handle.villa)){
		fprintf(stderr, "vlclose: %s\n", dperrmsg(dpecode));
		return FALSE;
	}

	// mark this index table as closed.
	handle.open = 0;

	return TRUE;
}

/**
 * bt_drop/2.
 * This will delete a database file.
 * CAll with: bt_drop(+Predname/Arity, +IndexOn).
 **/
DllExport int call_conv bt_drop(CTXTdecl) 
{
	/* compute the DB name */
	/* as db_predname_arity_indexargnum */
	prolog_term predicate = reg_term(CTXTdecl 1);
	prolog_term indexon = reg_term(CTXTdecl 2);
	int index_arg = p2c_int(indexon);
	// TODO: Sanity checking on input args
	char *predname = p2c_string(p2p_arg(predicate, 1));
	int arity = p2c_int(p2p_arg(predicate, 2));

	if(index_arg > arity)
	{
		fprintf(stderr, "Error: Index on Argument Number Greater Than Predicate Arity (Arity %i, index on: %i).\n", arity, index_arg);
		return FALSE;
	}

	char *db_name = pt2dbname(predname, arity, index_arg);

	// Do a quick search to make sure this table was not opened in
	// a handle
	int x ;
	for(x = 0; x < nextIndex; x++)
	{
		struct IndexTable i = villas[x];
		if(i.open == TRUE)
		{
			if(strcmp(i.predname, predname) == 0)
			{
				if(i.arity == arity && i.argnum == indexon)
				{
					// match, fails
					printf("This Tree has an open handle(%i), please close all handles before dropping the tree.\n", x);
					return FALSE;
				}
			}
		}
	}

	// actually drop the tree.
	if(vlremove(db_name))
		return TRUE;
	else
	{
		printf("WARNING: Unable to drop tree (%s), maybe it is missing?\n", db_name);
		return TRUE;
	}
}


char *pt2dbname(char *predname, int arity, int arg)
{
	/* dbname is of the format db_arg_arity_predname */
	char *buff = malloc(sizeof(char) * (5 + sizeof(predname) + 12 + 12));
	sprintf(buff, "db_%i_%i_%s", arg, arity, predname);
	return buff;
}

/**
 *	bt_get/3. Used to get a single value from a tree
 *  bt_Get(+Handle, +Key, -Value)
 */
DllExport int call_conv bt_get(CTXTdecl)
{
	// the first argument is the handle to the tree
	prolog_term tree_term = reg_term(CTXTdecl 1);
	if(!is_int(tree_term))
	{
		fprintf(stderr, "Get Error: Tree Handle Not Integer.\n");
		return FALSE;	
	} 

	int tree_index = p2c_int(tree_term);
	// check that we can find an IndexTable in this range
	if(tree_index >= nextIndex)
	{
		fprintf(stderr, "Insert Error: Handle Exceeds Range of Loaded Tables.\n");
		return FALSE;
	}

	struct IndexTable tree = villas[tree_index];

	// the second argument is the key
	prolog_term key = reg_term(CTXTdecl 2);
	char *buff = canonical_term(CTXTdecl key, 1);
	int size = cannonical_term_size(CTXTdecl) + 1;
	char *key_str = malloc(sizeof(char) * size);
	strncpy(key_str, buff, size);

	// perform the lookup
	int valsize;
	char *value = vlget(tree.villa, key_str, -1, &valsize);
	STRFILE strfile;
	strfile.strcnt = valsize;
	strfile.strptr = value;

	printf("Found Value: %s\n", value);

	// unify with the return argument
	return read_canonical_term(CTXTdecl NULL, &strfile, 3);
}

/**
 *	bt_getl/3. Used to get a handle to a list of values from a tree
 *  bt_Get(+TreeHandle, +Key, -ValueHandle)
 */
DllExport int call_conv bt_getl(CTXTdecl)
{
	// the first argument is the handle to the tree
	prolog_term tree_term = reg_term(CTXTdecl 1);
	if(!is_int(tree_term))
	{
		fprintf(stderr, "Get Error: Tree Handle Not Integer.\n");
		return FALSE;	
	} 

	int tree_index = p2c_int(tree_term);
	// check that we can find an IndexTable in this range
	if(tree_index >= nextIndex)
	{
		fprintf(stderr, "Insert Error: Handle Exceeds Range of Loaded Tables.\n");
		return FALSE;
	}

	struct IndexTable tree = villas[tree_index];

	// the second argument is the key
	prolog_term key = reg_term(CTXTdecl 2);
	char *buff = canonical_term(CTXTdecl key, 1);
	int size = cannonical_term_size(CTXTdecl) + 1;
	char *key_str = malloc(sizeof(char) * size);
	strncpy(key_str, buff, size);

	// perform the lookup
	CBLIST *value = vlgetlist(tree.villa, key_str, -1);

	// wrap this CBList into a node and return its index
	struct ActiveLookupListNode *node = malloc(sizeof(struct ActiveLookupListNode));
	node->index = nextCBLIndex++;
	node->next = NULL;
	node->prev = NULL;
	node->list = value;

	if(cblHead != NULL)
	{
		cblHead->next = node;
		node->prev = cblHead;
	}
	
	cblHead = node;
	
	// return the result in Handle
	prolog_term handle = reg_term(CTXTdecl 3);
	c2p_int(CTXTdecl cblHead->index, handle);

	return TRUE;
}

/**
 * bt_getnext/2. Retrieve the next value from the CBList handle.
 * bt_getnext(+CBLHandle, -Value).
 **/
DllExport int call_conv bt_getnext(CTXTdecl)
{
	// First get the handle and find if that CBL still exists.
	prolog_term cbl_term = reg_term(CTXTdecl 1);
	if(!is_int(cbl_term))
	{
		fprintf(stderr, "Get Next Error: CBL Handle Not Integer.\n");
		return FALSE;	
	} 

	int handle = p2c_int(cbl_term);

	// search for the cbl term
	struct ActiveLookupListNode *traveller = cblHead;

	int found = 0;
	while(traveller != NULL)
	{
		if(traveller->index == handle)
		{
			found = 1;
			break ;
		}

		if(traveller->prev == NULL) break ;
		traveller = traveller->prev;
	}

	if(found == 0)
	{
		printf("Unable to find CBL %i\n", handle);
		return FALSE;
	}

	//printf("FOUND CBL: %i\n", traveller->index);

	// retrieve the next value from the CBL
	if(traveller->list == NULL) 
	{
		printf("List Empty (never full).\n");
		return FALSE;
	}
	char *value = cblistpop(traveller->list, NULL);

	if(value == NULL)
	{
		printf("List empty.\n");
		// this list is now empty, remove it
		if(traveller->prev != NULL)
			traveller->prev->next = traveller->next;

		if(traveller->next != NULL)
			traveller->next->prev = traveller->prev;

		if(cblHead == traveller)
			cblHead = traveller->prev;

		free(traveller);
		return FALSE;
	}

	// unify the string and return
	STRFILE strfile;
	strfile.strcnt = strlen(value);
	strfile.strptr = value;

	return read_canonical_term(CTXTdecl NULL, &strfile, 4);
}

/*********************************************************/
/** RANGE/PREFIX Queries		**************************/
/*********************************************************/
/** bt_prefix_jump/2.
 ** Jumps the tree cursor to the nearest point with the given suffix.
 ** Call Mode:
 ** bt_prefix_jump(+TreeHandle, +Prefix).
 ** NOTE: This, unlink bt_getl cannot be used concurrently. That is,
 ** once a call to bt_prefix_jump is made, it will disrupt the cursor
 ** and cause unpredicatble results on previous calls to bt_prefix_next.
 **********************************************************/
DllExport int call_conv bt_prefix_jump(CTXTdecl)
{
	// the first argument is the handle to the tree
	prolog_term tree_term = reg_term(CTXTdecl 1);
	if(!is_int(tree_term))
	{
		fprintf(stderr, "Get Error: Tree Handle Not Integer.\n");
		return FALSE;	
	} 

	int tree_index = p2c_int(tree_term);
	// check that we can find an IndexTable in this range
	if(tree_index >= nextIndex)
	{
		fprintf(stderr, "Insert Error: Handle Exceeds Range of Loaded Tables.\n");
		return FALSE;
	}

	struct IndexTable tree = villas[tree_index];

	prolog_term key = reg_term(CTXTdecl 2);
	char *buff = canonical_term(CTXTdecl key, 1);
	int size = cannonical_term_size(CTXTdecl) + 1;
	char *key_str = malloc(sizeof(char) * size);
	strncpy(key_str, buff, size);

	villas[tree_index].prefix = key_str;
	villas[tree_index].cursorMode = PREFIX_MODE;

	// now set the cursor on the villa.
	vlcurjump(tree.villa, key_str, -1, VL_JFORWARD);

	return TRUE;
}

/**
 * bt_prefix_next/2.
 * Returns the next entry in the current prefix or range query.
 * Call Mode:
 * bt_prefix_next(+TreeHandle, -Value).
 **/
DllExport int call_conv bt_prefix_next(CTXTdecl)
{
	// the first argument is the handle to the tree
	prolog_term tree_term = reg_term(CTXTdecl 1);
	if(!is_int(tree_term))
	{
		fprintf(stderr, "PREFIX Error: Tree Handle Not Integer.\n");
		return FALSE;	
	} 

	int tree_index = p2c_int(tree_term);
	// check that we can find an IndexTable in this range
	if(tree_index >= nextIndex)
	{
		fprintf(stderr, "PREFIX Error: Handle Exceeds Range of Loaded Tables.\n");
		return FALSE;
	}

	struct IndexTable tree = villas[tree_index];

	// verify the tree is in prefix mode
	if(tree.cursorMode != PREFIX_MODE)
	{
		fprintf(stderr, "PREFIX Error: Tree is not currently in PREFIX mode (%i, %s).\n", tree.cursorMode, tree.prefix);
		return FALSE;
	}

	// now look up the next cursor value
	char *key = vlcurkey(tree.villa, NULL);
	if(key == NULL)
	{
		printf("PREFIX: vlcurkey Error\n");
		return FALSE;
	}

	// now verify the prefix condition
	if(strstr(key, tree.prefix) != key)
	{
    	// no more values
		villas[tree_index].cursorMode = NOT_INITIALIZED;
		free(tree.prefix);
		villas[tree_index].prefix = NULL;
		return FALSE;
    }

    // we are still in the prefix range, unify and return
    free(key);

    STRFILE strfile;
    char *value = vlcurval(tree.villa, NULL);
	strfile.strcnt = strlen(value);
	strfile.strptr = value;

	vlcurnext(tree.villa);

	return read_canonical_term(CTXTdecl NULL, &strfile, 4);
}


/********************************
 ** bt_range_init/3
 ** bt_range_init(+TreeHandle, +LowerBound, +UpperBound)
 ********************************/
DllExport int call_conv bt_range_init(CTXTdecl)
{
	// the first argument is the handle to the tree
	prolog_term tree_term = reg_term(CTXTdecl 1);
	if(!is_int(tree_term))
	{
		fprintf(stderr, "Get Error: Tree Handle Not Integer.\n");
		return FALSE;	
	} 

	int tree_index = p2c_int(tree_term);
	// check that we can find an IndexTable in this range
	if(tree_index >= nextIndex)
	{
		fprintf(stderr, "Insert Error: Handle Exceeds Range of Loaded Tables.\n");
		return FALSE;
	}

	struct IndexTable tree = villas[tree_index];

	prolog_term key = reg_term(CTXTdecl 2);
	char *buff = canonical_term(CTXTdecl key, 1);
	int size = cannonical_term_size(CTXTdecl) + 1;
	char *key_str = malloc(sizeof(char) * size);
	strncpy(key_str, buff, size);

	villas[tree_index].prefix = key_str;
	villas[tree_index].cursorMode = RANGE_MODE;

	prolog_term bound = reg_term(CTXTdecl 3);
	buff = canonical_term(CTXTdecl bound, 1);
	size = cannonical_term_size(CTXTdecl) + 1;
	key_str = malloc(sizeof(char) * size);
	strncpy(key_str, buff, size);

	villas[tree_index].upperBound = key_str;

	// now set the cursor on the villa.
	vlcurjump(tree.villa, key_str, -1, VL_JFORWARD);

	return TRUE;
}

/**
 * bt_range_next/2.
 * Returns the next entry in the current range query.
 * Call Mode:
 * bt_prefix_next(+TreeHandle, -Value).
 **/
DllExport int call_conv bt_range_next(CTXTdecl)
{
	// the first argument is the handle to the tree
	prolog_term tree_term = reg_term(CTXTdecl 1);
	if(!is_int(tree_term))
	{
		fprintf(stderr, "PREFIX Error: Tree Handle Not Integer.\n");
		return FALSE;	
	} 

	int tree_index = p2c_int(tree_term);
	// check that we can find an IndexTable in this range
	if(tree_index >= nextIndex)
	{
		fprintf(stderr, "PREFIX Error: Handle Exceeds Range of Loaded Tables.\n");
		return FALSE;
	}

	struct IndexTable tree = villas[tree_index];

	// verify the tree is in prefix mode
	if(tree.cursorMode != PREFIX_MODE)
	{
		fprintf(stderr, "PREFIX Error: Tree is not currently in PREFIX mode (%i, %s).\n", tree.cursorMode, tree.prefix);
		return FALSE;
	}

	// now look up the next cursor value
	char *key = vlcurkey(tree.villa, NULL);
	if(key == NULL)
	{
		printf("PREFIX: vlcurkey Error\n");
		return FALSE;
	}

	// now verify the prefix condition
	if(strcmp(key, tree.upperBound) >= 1)
	{
    	// no more values
		villas[tree_index].cursorMode = NOT_INITIALIZED;
		free(tree.prefix);
		free(tree.upperBound);
		villas[tree_index].prefix = NULL;
		return FALSE;
    }

    // we are still in the prefix range, unify and return
    free(key);

    STRFILE strfile;
    char *value = vlcurval(tree.villa, NULL);
	strfile.strcnt = strlen(value);
	strfile.strptr = value;

	vlcurnext(tree.villa);

	return read_canonical_term(CTXTdecl NULL, &strfile, 4);
}