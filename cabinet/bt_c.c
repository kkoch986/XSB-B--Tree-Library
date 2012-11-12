#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <sys/stat.h>

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

#include "bterrs.h"

static const int DEBUG = 0;
void debugprintf(char *message, ... )
{
	if(DEBUG == 1)
	{
		va_list args;
		va_start(args, message);
		printf(message, args);
		va_end(args);
	}
}

// predefine functions
//char *pt2str(prolog_term term);
char *pt2dbname(char *predname, int arity, int arg);

// stats regarding prefix or range query.
static const int NOT_INITIALIZED = 10, PREFIX_MODE = 1, RANGE_MODE = 2, MANUAL_CURSOR_MODE = 3;

// a structure to hold information about the b+ tree table.
struct IndexTable
{
	VILLA *villa;
	char *predname;
	char *dbname;
	int arity;
	int argnum;
	int open;

	// stats for prefix and range queries
	int cursorMode;
	char *prefix;
	char *upperBound;

	// for btgetl type queries
	CBLIST *activeList;
};

// pointer to our B+ trees.
static struct IndexTable *villas;
static int nextIndex = 0;

/** 
 * bt_create/5.
 * Creates the necessary stucture to hold a database for the given predicate.
 * Call with: bt_create(+DBName, +Pred, +Arity, +Argument, -Error) 
 *
 * NOTE: a call to this does not do any intitalzion or loading, 
 * just creates the blank databases on disk and returns yes if it
 * can do so with no conflicts.
 **/
int c_bt_create(char *dbname, char *predname, int arity, int indexon);
DllExport int call_conv bt_create(CTXTdecl)
{
	// get the arguments passed in
    prolog_term db_name_t 	= reg_term(CTXTdecl 1);
    prolog_term predicate   = reg_term(CTXTdecl 2);
    prolog_term arity_term   = reg_term(CTXTdecl 3);
    prolog_term indexon     = reg_term(CTXTdecl 4);

    // TODO: Sanity checking on input args
    char *db_name           = p2c_string(db_name_t);
    char *predname          = p2c_string(predicate);
    int arity               = p2c_int(arity_term);
    int index_arg           = p2c_int(indexon);

	int result = c_bt_create(db_name, predname, arity, index_arg);

	// unify result with the error code
	ctop_int(5,result);	

	// success
	return TRUE;
}

/**
 * bt_init/3. 
 * Initializes the B+ Tree.
 * Should be called with the following args:
 * bt_init(+dbname, -Handle, -Error)
 *
 * The value returned in Handle can be used to insert
 * values directly into an index table later on.
 **/
int c_bt_init(CTXTdecl char *dbname, int *t);
DllExport int call_conv bt_init(CTXTdecl)
{
	/* compute the DB name */
	/* as db_predname_arity_indexargnum */
	prolog_term db_name = reg_term(CTXTdecl 1);
	char *db_name_str = p2c_string(db_name);

	int handle = -1;
	int error = c_bt_init(db_name_str, &handle); 

	// unify the handle and error code
	ctop_int(2, handle);
	ctop_int(3, error);

	// return true
	return TRUE;
}

/**
 * bt_close/2
 * Close a BTree
 * TODO: Clean up error handling 
 **/
int c_bt_close(int handle);
DllExport int call_conv bt_close(CTXTdecl) 
{
	prolog_term handle_term = reg_term(CTXTdecl 1);
	if(!is_int(handle_term))
	{
		fprintf(stderr, "Close Error: Handle Non-Integer Type.\n");
		return FALSE;
	}
	int handle_index = p2c_int(handle_term);

	int error = c_bt_close(handle_index);

	// unify the error and return
	ctop_int(2,error);

	return TRUE;
}

/** bt_size/3 returns the current size of the tree **/
// TODO: ERROR HANDLING CLEANUP
int c_bt_size(int handle, int *size);
DllExport int call_conv bt_size(CTXTdecl)
{
	// Find the IndexTable associated with the handle.
	prolog_term handle_term = reg_term(CTXTdecl 1);
	if(!is_int(handle_term))
	{
		fprintf(stderr, "Insert Error: Handle Non-Integer Type.\n");
		return FALSE;
	}
	int handle_index = p2c_int(handle_term);

	int size = 0;

	int error = c_bt_size(handle_index, &size);

	// unify the size and the error
	ctop_int(2, size);
	ctop_int(3, error);

	return TRUE;
}

/** 
 * bt_getinfo/5 returns information aboutthe database
 * bt_getinfo(+Handle, -Predname, -Arity, -Indexon, -Error)
 **/
int c_bt_get_info(int handle, char **predname_in, int *arity_in, int *indexon_in);
DllExport int call_conv bt_getinfo(CTXTdecl)
{
	prolog_term handle_term = reg_term(CTXTdecl 1);
	if(!is_int(handle_term))
	{
		fprintf(stderr, "Insert Error: Handle Non-Integer Type.\n");
		return FALSE;
	}
	int handle_index = p2c_int(handle_term);

	char *predname;
	int arity = -1;
	int indexon = -1;

	int error = c_bt_get_info(handle_index, &predname, &arity, &indexon);

	// unify and return
	extern_ctop_string(2, predname);
	ctop_int(3, arity);
	ctop_int(4, indexon);
	ctop_int(5, error);

	return TRUE;
}

/**
 * bt_db_name/3 gets the name of the given database handle
 * bt_db_name(+Handle, -Name, -Error)
 **/
int c_bt_dbname(int handle, char **treename);
DllExport int call_conv bt_dbname(CTXTdecl)
{
	// Find the IndexTable associated with the handle.
	prolog_term handle_term = reg_term(CTXTdecl 1);
	if(!is_int(handle_term))
	{
		fprintf(stderr, "Insert Error: Handle Non-Integer Type.\n");
		return FALSE;
	}

	int handle_index = p2c_int(handle_term);
	char *treename;
	int error = c_bt_dbname(handle_index, &treename);

	// set the results
	ctop_int(3, error);
	extern_ctop_string(2, treename);

	return TRUE;
}

/**
 * bt_insert/3.
 * Inserts the given term into the B+ Tree given by the second argument.
 * The B+ Tree must match on predicate symbol and arity and will be indexed on 
 * the same argument as others in that table.
 *
 * bt_insert(+Handle, +Term, -Error).
 **/
int c_bt_insert(int handle, char *keystr, char *valstr);
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

	// Get the indexon, predname and arity fro mthe DB
	char *predname;
	int arity = -1;
	int indexon = -1;
	int error = -1;

	error = c_bt_get_info(handle_index, &predname, &arity, &indexon);

	// check fi there was an error
	if(error != 0)
	{
		fprintf(stderr, "GET INFO ERROR %d", error);
		return FALSE;
	}

	// now confirm the pred name and arity for this predicate
	prolog_term value = reg_term(CTXTdeclc 2);

	if(!is_functor(value))
	{
		fprintf(stderr, "Insert Error: Insert Argument Is Not A Functor.\n");
		return FALSE;
	}

	int in_arity = p2c_arity(value);
	char *in_predname = p2c_functor(value);

	if(in_arity != arity)
	{
		fprintf(stderr, "Insert Error: Arity Mismatch (Got %i, Expecting %i).\n", in_arity, arity);
		return FALSE;
	}

	if(strcmp(in_predname, predname) != 0)
	{
		fprintf(stderr, "Insert Error: Functor Mismatch (Got '%s', Expecting '%s').\n", predname, in_predname);
		return FALSE;	
	}

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
	char key_str[size];
	strncpy(key_str, buff, size);

	buff = canonical_term(CTXTdecl value, 1);
	size = cannonical_term_size(CTXTdecl) + 1;
	char val_str[size];
	strncpy(val_str, buff, size);

	error = c_bt_insert(handle_index, key_str, val_str);

	// unify the error
	ctop_int(3, error);

	return TRUE;
}

/**
 *	bt_query_init/2. Used to initialze a bucket of values that match the current query key
 *  bt_query_init(+TreeHandle, +Key, -Error)
 */
int c_bt_query_init(int handle, char *keystr);
DllExport int call_conv bt_query_init(CTXTdecl)
{
	// the first argument is the handle to the tree
	prolog_term tree_term = reg_term(CTXTdecl 1);
	if(!is_int(tree_term))
	{
		fprintf(stderr, "Get Error: Tree Handle Not Integer.\n");
		return FALSE;	
	} 

	int handle_index = p2c_int(tree_term);

	// the second argument is the key
	prolog_term key = reg_term(CTXTdecl 2);
	char *buff = canonical_term(CTXTdecl key, 1);
	int size = cannonical_term_size(CTXTdecl) + 1;
	char key_str[size];
	strncpy(key_str, buff, size);

	// perform the lookup
	int error = c_bt_query_init(handle_index, key_str);

	// unify the error code
	ctop_int(3,error);

	return TRUE;
}

/**
 * bt_query_next/3. Retrieve the next value from an active key query handle.
 * bt_query_next(+TreeHandle, -Value, -Error).
 **/
int c_bt_query_next(int handle, char **valstr);
DllExport int call_conv bt_query_next(CTXTdecl)
{
	// the first argument is the handle to the tree
	prolog_term tree_term = reg_term(CTXTdecl 1);
	if(!is_int(tree_term))
	{
		fprintf(stderr, "Get Error: Tree Handle Not Integer.\n");
		return FALSE;	
	} 

	int handle_index = p2c_int(tree_term);
	char *value;
	int error = c_bt_query_next(handle_index, &value);

	// unify the error
	ctop_int(3,error);	

	// unify the string and return
	STRFILE strfile;
	strfile.strcnt = strlen(value);
	strfile.strptr = value; strfile.strbase = value;

	read_canonical_term(CTXTdecl NULL, &strfile, 1);
	return TRUE;
}



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/** bt_get_predname/2 returns the predicate name used to store the data in the b+ tree. **/
DllExport int call_conv bt_get_predname(CTXTdecl)
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

	extern_ctop_string(CTXTdecl 2, handle.predname);

	return TRUE;
}

/** bt_get_arity/2 returns the predicate arity stored in the b+ tree. **/
DllExport int call_conv bt_get_arity(CTXTdecl)
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

	ctop_int(CTXTdecl 2, handle.arity);

	return TRUE;
}

/** bt_get_indexon/2 returns the predicate argument number used for indexing in the b+ tree. **/
DllExport int call_conv bt_get_indexon(CTXTdecl)
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

	ctop_int(CTXTdecl 2, handle.argnum);

	return TRUE;
}

/**
 * bt_drop/1.
 * This will delete a database file.
 * CAll with: bt_drop(+DBName).
 **/
DllExport int call_conv bt_drop(CTXTdecl) 
{
	/* compute the DB name */
	/* as db_predname_arity_indexargnum */
	prolog_term db_name_t = reg_term(CTXTdecl 1);
	char *db_name = p2c_string(db_name_t);

	// Do a quick search to make sure this table was not opened in
	// a handle
	int x ;
	for(x = 0; x < nextIndex; x++)
	{
		struct IndexTable i = villas[x];
		if(i.open == TRUE)
		{
			if(strcmp(i.dbname, db_name) == 0)
			{
				// match, fails
				printf("This Tree has an open handle(%i), please close all handles before dropping the tree.\n", x);
				return FALSE;
			}
		}
	}

	// actually drop the tree.
	char buff[MAXLINE];
	sprintf(buff, "%s/db", db_name);

	if(!vlremove(buff))
	{
		debugprintf("WARNING: Unable to drop tree (%s), maybe it is missing?\n", db_name);
	}

	// delete the meta file
	sprintf(buff, "%s/meta", db_name);

	if(!dpremove(buff))
	{
		debugprintf("WARNING: Unable to drop meta data file (%s), maybe it is missing?\n", db_name);
	}

	// delete the whole directory
	if(rmdir(db_name) >= 0)
	{
		return TRUE;
	}

	return FALSE;
}


char *pt2dbname(char *predname, int arity, int arg)
{
	/* dbname is of the format db_arg_arity_predname */
	char *buff = malloc(sizeof(char) * (5 + sizeof(predname) + 12 + 12));	
	sprintf(buff, "db_%i_%i_%s", arg, arity, predname);
	return buff;
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

	if(villas[tree_index].open == FALSE)
	{
		fprintf(stderr, "Error: Handle has been closed.\n");
		return FALSE;
	}

	// make sure to free up any old search keys
	if(villas[tree_index].cursorMode == PREFIX_MODE)
	{
		free(villas[tree_index].prefix);
	}
	else if(villas[tree_index].cursorMode == RANGE_MODE)
	{
		free(villas[tree_index].prefix);
		free(villas[tree_index].upperBound);
	}

	struct IndexTable tree = villas[tree_index];

	prolog_term key = reg_term(CTXTdecl 2);
	char *buff = canonical_term(CTXTdecl key, 1);
	int size = cannonical_term_size(CTXTdecl) + 1;

	char key_str[size];
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

	if(villas[tree_index].open == FALSE)
	{
		fprintf(stderr, "Error: Handle has been closed.\n");
		return FALSE;
	}

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
		debugprintf("PREFIX: vlcurkey Error\n");
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
	strfile.strptr = value; strfile.strbase = value;

	vlcurnext(tree.villa);

	read_canonical_term(CTXTdecl NULL, &strfile, 1);
	return TRUE;
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
		fprintf(stderr, "RANGE INIT Error: Tree Handle Not Integer.\n");
		return FALSE;	
	} 

	int tree_index = p2c_int(tree_term);
	// check that we can find an IndexTable in this range
	if(tree_index >= nextIndex)
	{
		fprintf(stderr, "RANGE INIT Error: Handle Exceeds Range of Loaded Tables.\n");
		return FALSE;
	}

	if(villas[tree_index].open == FALSE)
	{
		fprintf(stderr, "Error: Handle has been closed.\n");
		return FALSE;
	}

	// make sure to free up any old search keys
	if(villas[tree_index].cursorMode == PREFIX_MODE)
	{
		free(villas[tree_index].prefix);
	}
	else if(villas[tree_index].cursorMode == RANGE_MODE)
	{
		free(villas[tree_index].prefix);
		free(villas[tree_index].upperBound);
	}


	struct IndexTable tree = villas[tree_index];

	prolog_term key = reg_term(CTXTdecl 2);
	char *buff = canonical_term(CTXTdecl key, 1);
	int size = cannonical_term_size(CTXTdecl) + 1;
	char *key_str = malloc(sizeof(char) * size);
	//char key_str[size];
	strncpy(key_str, buff, size);

	villas[tree_index].prefix = key_str;
	villas[tree_index].cursorMode = RANGE_MODE;

	// now set the cursor on the villa.
	vlcurjump(tree.villa, key_str, -1, VL_JFORWARD);

	// now load the upper bound 
	prolog_term bound = reg_term(CTXTdecl 3);
	buff = canonical_term(CTXTdecl bound, 1);
	size = cannonical_term_size(CTXTdecl) + 1;
	key_str = malloc(sizeof(char) * size);
	strncpy(key_str, buff, size);

	villas[tree_index].upperBound = key_str;

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
		fprintf(stderr, "RANGE Error: Tree Handle Not Integer.\n");
		return FALSE;	
	} 

	int tree_index = p2c_int(tree_term);
	// check that we can find an IndexTable in this range
	if(tree_index >= nextIndex)
	{
		fprintf(stderr, "RANGE Error: Handle Exceeds Range of Loaded Tables.\n");
		return FALSE;
	}

	if(villas[tree_index].open == FALSE)
	{
		fprintf(stderr, "Error: Handle has been closed.\n");
		return FALSE;
	}

	struct IndexTable tree = villas[tree_index];

	// verify the tree is in prefix mode
	if(tree.cursorMode != RANGE_MODE)
	{
		fprintf(stderr, "RANGE Error: Tree is not currently in RANGE mode (%i, %s).\n", tree.cursorMode, tree.prefix);
		return FALSE;
	}

	// now look up the next cursor value
	char *key = vlcurkey(tree.villa, NULL);
	if(key == NULL)
	{
		debugprintf("RANGE: vlcurkey Error\n");
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
	strfile.strptr = value; strfile.strbase = value;

	vlcurnext(tree.villa);

	read_canonical_term(CTXTdecl NULL, &strfile, 1);
	return TRUE;
}



/**************************
 * MANUAL CURSOR MODE 
 * This mode allows the programmer to manipulate a trees cursor.
 **************************/
 /* bt_mcm_init/1. Sets the cursorMode of the given tree to MCM. */

DllExport int call_conv bt_mcm_init(CTXTdecl)
{
	// the first argument is the handle to the tree
	prolog_term tree_term = reg_term(CTXTdecl 1);
	if(!is_int(tree_term))
	{
		fprintf(stderr, "MCM INIT Error: Tree Handle Not Integer.\n");
		return FALSE;	
	} 

	int tree_index = p2c_int(tree_term);
	// check that we can find an IndexTable in this range
	if(tree_index >= nextIndex)
	{
		fprintf(stderr, "MCM INIT Error: Handle Exceeds Range of Loaded Tables.\n");
		return FALSE;
	}

	if(villas[tree_index].open == FALSE)
	{
		fprintf(stderr, "Error: Handle has been closed.\n");
		return FALSE;
	}

	// make sure to free up any old search keys
	if(villas[tree_index].cursorMode == PREFIX_MODE)
	{
		free(villas[tree_index].prefix);
	}
	else if(villas[tree_index].cursorMode == RANGE_MODE)
	{
		free(villas[tree_index].prefix);
		free(villas[tree_index].upperBound);
	}

	villas[tree_index].cursorMode = MANUAL_CURSOR_MODE;		

	return TRUE;
}

/* Performs the basic cursor operation functions */
/* NOT CALLED DIRECTLY from prolog. **/
int mcm_cur_ops(CTXTdecl int operation)
{
	prolog_term key;
	char *buff;
	int size;
	//char *key_str;
	char key_str[MAXLINE];
	char *value;
	STRFILE strfile;
	int proposedSize;
	int actualSize;
	int changed = 0;

	// for cur enc repair:
	char fone = 1;

	// the first argument is the handle to the tree
	prolog_term tree_term = reg_term(CTXTdecl 1);
	if(!is_int(tree_term))
	{
		fprintf(stderr, "MCM FIRST Error: Tree Handle Not Integer.\n");
		return FALSE;	
	} 

	int tree_index = p2c_int(tree_term);
	// check that we can find an IndexTable in this range
	if(tree_index >= nextIndex)
	{
		fprintf(stderr, "MCM FIRST Error: Handle Exceeds Range of Loaded Tables.\n");
		return FALSE;
	}

	if(villas[tree_index].open == FALSE)
	{
		fprintf(stderr, "Error: Handle has been closed.\n");
		return FALSE;
	}

	// verify the tree is in prefix mode
	if(villas[tree_index].cursorMode != MANUAL_CURSOR_MODE && operation != 11 && operation != 10)
	{
		fprintf(stderr, "MCM Error: Tree is not currently in MCM mode (%i).\n", villas[tree_index].cursorMode);
		return FALSE;
	}

	switch(operation)
	{
		case 0: 		// first
			if(!vlcurfirst(villas[tree_index].villa))
			{
				debugprintf("MCM FIRST Error: vlcurfirst Error.\n");
				return FALSE;	
			}		

			return TRUE;
		case 1:			// last
			if(!vlcurlast(villas[tree_index].villa))
			{
				debugprintf("MCM FIRST Error: vlcurlast Error.\n");
				return FALSE;	
			}		

			return TRUE;
		case 2:			// next
			if(!vlcurnext(villas[tree_index].villa))
			{
				debugprintf("MCM FIRST Error: vlcurnext Error.\n");
				return FALSE;	
			}		

			return TRUE;
		case 3:			// prev
			if(!vlcurprev(villas[tree_index].villa))
			{
				debugprintf("MCM FIRST Error: vlcurprev Error.\n");
				return FALSE;	
			}		

			return TRUE;

		case 4: 		// jump
			// get the key term
			key = reg_term(CTXTdecl 2);
			buff = canonical_term(CTXTdecl key, 1);
			size = cannonical_term_size(CTXTdecl) + 1;
			strncpy(key_str, buff, size);

			if(!vlcurjump(villas[tree_index].villa, key_str, -1, VL_JFORWARD))
			{
				fprintf(stderr, "MCM JUMP Error: vlcurjump Error.\n");
				return FALSE;	
			}
			
			return TRUE;
		case 5: 		// jump_rev
			// get the key term
			key = reg_term(CTXTdecl 2);
			buff = canonical_term(CTXTdecl key, 1);
			size = cannonical_term_size(CTXTdecl) + 1;
			strncpy(key_str, buff, size);

			if(!vlcurjump(villas[tree_index].villa, key_str, -1, VL_JBACKWARD))
			{
				fprintf(stderr, "MCM JUMP REV Error: vlcurjump Error.\n");
				return FALSE;	
			}
			
			return TRUE;

		case 6:		// mcm_key
		    value = vlcurkey(villas[tree_index].villa, NULL);
			strfile.strcnt = strlen(value);
			strfile.strptr = value; strfile.strbase = value;

			read_canonical_term(CTXTdecl NULL, &strfile, 1);
			return TRUE;

		case 7:		// mcm_val
		    value = vlcurval(villas[tree_index].villa, NULL);
			strfile.strcnt = strlen(value);
			
			strfile.strptr = value; strfile.strbase = value;
			read_canonical_term(CTXTdecl NULL, &strfile, 1);
			return TRUE;
		case 8: // mcm_next_key
			value = vlcurkey(villas[tree_index].villa, NULL);
			char *local = "";
			do
			{
				if(!vlcurnext(villas[tree_index].villa))
				{
					debugprintf("MCM FIRST Error: vlcurnext Error.\n");
					return FALSE;	
				}
				
				local = vlcurkey(villas[tree_index].villa, NULL);

			} while( strcmp(local, value) == 0 );

			return TRUE;
		case 9: // mcm_cur_out
			if(!vlcurout(villas[tree_index].villa))
			{
				fprintf(stderr, "MCM CUR OUT Error: vlcurout Error.\n");
				return FALSE;	
			}
			return TRUE;

		case 10: // export

			// get the filename
			key = reg_term(CTXTdecl 2);
			buff = canonical_term(CTXTdecl key, 1);
			size = cannonical_term_size(CTXTdecl) + 1;
			strncpy(key_str, buff, size);

			if(!vlexportdb(villas[tree_index].villa, buff))
			{
				fprintf(stderr, "BT EXPORT DB Error: vlexportdb Error.\n");
				return FALSE;	
			}
			return TRUE;

		case 11: // import
			// get the filename
			key = reg_term(CTXTdecl 2);
			buff = canonical_term(CTXTdecl key, 1);
			size = cannonical_term_size(CTXTdecl) + 1;
			strncpy(key_str, buff, size);

			if(!vlimportdb(villas[tree_index].villa, buff))
			{
				fprintf(stderr, "BT IMPORT DB Error: vlimportdb Error.\n");
				return FALSE;	
			}
			return TRUE;

		case 12: // bt_cur_enc_repair
			fone = 0;
		case 13: // bt_cur_enc_repair_fone

			// get the value at the curso
			value = vlcurval(villas[tree_index].villa, &proposedSize);
			actualSize = strlen(value);

			printf("Proposed Value Size: %i (actual size %i)\n", proposedSize, actualSize);

			int x;
			for(x = 0; x < proposedSize; x++)
			{
				if(value[x] == 0)
				{
					changed++;
					value[x] = '?';
				}
			}

			if(changed > 0)
			{
				printf("%i Bad Character(s) replaced, saving back to DB.\n", changed);
				if(!vlcurput(villas[tree_index].villa, value, -1, VL_CPCURRENT))
				{
					fprintf(stderr, "BT Cursor Value Repair Error: vlcurput Error.\n");
					return FALSE;	
				}
			}
			else
			{
				printf("No Bad Characters Found in: %s.\n", value);
				if(fone == 1)
					return FALSE;
			}

			return TRUE;

		default:
			fprintf(stderr, "MCM ERROR: Unknown Operation (%i)\n", operation);
			return FALSE;
	}
}

/** bt_cm_first/1. Jump the cursor to the first record in the tree. **/
DllExport int call_conv bt_mcm_first(CTXTdecl){ return mcm_cur_ops(CTXTdecl 0);  }
/** bt_mcm_last/1. Jump the cursor to the last record in the tree. **/
DllExport int call_conv bt_mcm_last(CTXTdecl) { return mcm_cur_ops(CTXTdecl 1);  }
/** bt_mcm_next/1. Jump the cursor to the next successive record in the tree. **/
DllExport int call_conv bt_mcm_next(CTXTdecl) { return mcm_cur_ops(CTXTdecl 2);	 }
/** bt_mcm_prev/1. Jump the cursor to the previous successive record in the tree. **/
DllExport int call_conv bt_mcm_prev(CTXTdecl) { return mcm_cur_ops(CTXTdecl 3);	 }
/** bt_mcm_jump/1. Jump the cursor to the first entry matching the key (or closest match). **/
DllExport int call_conv bt_mcm_jump(CTXTdecl) { return mcm_cur_ops(CTXTdecl 4);	 }
/** bt_mcm_jump_rev/1. Jump the cursor to the last entry matching the key (or closest match). **/
DllExport int call_conv bt_mcm_jump_rev(CTXTdecl) { return mcm_cur_ops(CTXTdecl 5);	 }

/** bt_mcm_key/2. returns the key and the current point. **/
DllExport int call_conv bt_mcm_key(CTXTdecl) { return mcm_cur_ops(CTXTdecl 6);	 }
/** bt_mcm_val/2. returns the key and the current point. **/
DllExport int call_conv bt_mcm_val(CTXTdecl) { return mcm_cur_ops(CTXTdecl 7);	 }
/** bt_mcm_next_key/1. Jump the cursor to the next record with a unique key in the tree. **/
DllExport int call_conv bt_mcm_next_key(CTXTdecl) { return mcm_cur_ops(CTXTdecl 8);	 }

/** bt_mcm_out/1. Deletes the current record indicated by the cursor. **/
DllExport int call_conv bt_mcm_out(CTXTdecl) { return mcm_cur_ops(CTXTdecl 9);	 }

/** Functions for backup and restoring databases **/
/** bt_export/2. Exports the given database to the given filename. **/
/** bt_export(TreeHandle, DestinationFileName).		**/
// DllExport int call_conv bt_export(CTXTdecl) { return mcm_cur_ops(CTXTdecl 10);	 }

/** bt_import/2. Imports all of the facts from the given database export to **/
/** the given databse. NOTE: the file must have been generated using bt_export/2. **/
/** bt_import(TreeHandle, SourceFileName).		**/
// DllExport int call_conv bt_import(CTXTdecl) { return mcm_cur_ops(CTXTdecl 11);	 }

/** Attempts to repair a record which encounters EOF characters or other encoding **/
/** errors on read_canonical calls. Succeeds if a repair is made without error, or no repair is made**/
// DllExport int call_conv bt_cur_enc_repair(CTXTdecl) { return mcm_cur_ops(CTXTdecl 12);	 }

/* same as bt_cur_enc_repair, but fails if no repair is made. */
// DllExport int call_conv bt_cur_enc_repair_fone(CTXTdecl) { return mcm_cur_ops(CTXTdecl 13);	 }



/*
 The function `vlcurput' is used in order to insert a record around the cursor.

int vlcurput(VILLA *villa, const char *vbuf, int vsiz, int cpmode);
`villa' specifies a database handle connected as a writer. `vbuf' specifies the pointer to the region of a value. `vsiz' specifies the size of the region of the value. If it is negative, the size is assigned with `strlen(vbuf)'. `cpmode' specifies detail adjustment: `VL_CPCURRENT', which means that the value of the current record is overwritten, `VL_CPBEFORE', which means that a new record is inserted before the current record, `VL_CPAFTER', which means that a new record is inserted after the current record. If successful, the return value is true, else, it is false. False is returned when no record corresponds to the cursor. After insertion, the cursor is moved to the inserted record.
The function `vlcurout' is used in order to delete the record where the cursor is.

*/

/** bt_tree_name/2 Returns the name of the B+ Tree which also identirfies the name of the **/
/** Directory which holds the tree.	**/
DllExport int call_conv bt_tree_name(CTXTdecl)
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

	if(villas[handle_index].open == FALSE)
	{
		fprintf(stderr, "Error: Handle has been closed.\n");
		return FALSE;
	}

	extern_ctop_string(CTXTdecl 2, villas[handle_index].dbname);
	
	return TRUE;
}

/**********************************************/
/**** TRANSACTIONS ****************************/
/**********************************************/
DllExport int call_conv bt_trans_start(CTXTdecl)
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

	if(villas[handle_index].open == FALSE)
	{
		fprintf(stderr, "Error: Handle has been closed.\n");
		return FALSE;
	}

	if(!vltranbegin(villas[handle_index].villa))
	{
		fprintf(stderr, "TRANSACTION Error: vltranbegin Error.\n");
		return FALSE;	
	}

	return TRUE;
}

DllExport int call_conv bt_trans_commit(CTXTdecl)
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

	if(villas[handle_index].open == FALSE)
	{
		fprintf(stderr, "Error: Handle has been closed.\n");
		return FALSE;
	}

	if(!vltrancommit(villas[handle_index].villa))
	{
		fprintf(stderr, "TRANSACTION Error: vltrancommit Error (%s).\n", dperrmsg(dpecode));
		return FALSE;	
	}

	return TRUE;
}

DllExport int call_conv bt_trans_abort(CTXTdecl)
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

	if(villas[handle_index].open == FALSE)
	{
		fprintf(stderr, "Error: Handle has been closed.\n");
		return FALSE;
	}

	if(!vltranabort(villas[handle_index].villa))
	{
		fprintf(stderr, "TRANSACTION Error: vltranabort Error.\n");
		return FALSE;	
	}

	return TRUE;
}


/** bt_repair/1 attempts to repair corrupted databases **/
DllExport int call_conv bt_repair(CTXTdecl)
{
	// Find the IndexTable associated with the handle.
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

	if(!vlrepair(db_name, VL_CMPLEX))
	{
		fprintf(stderr, "Repair Unsuccessful: vlrepair Error.\n");
		free(db_name);
		return FALSE;	
	}

	free(db_name);
	return TRUE;
}
