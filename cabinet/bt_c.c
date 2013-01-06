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
 **/
int c_bt_close(int handle);
DllExport int call_conv bt_close(CTXTdecl) 
{
	prolog_term handle_term = reg_term(CTXTdecl 1);
	if(!is_int(handle_term))
	{
		// unify the error
		ctop_int(2, HANDLE_NOT_INT);
		return TRUE;
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
		// unify the error
		ctop_int(3, HANDLE_NOT_INT);
		return TRUE;
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
		// unify the error
		ctop_int(5, HANDLE_NOT_INT);
		return TRUE;
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
		// unify the error
		ctop_int(3, HANDLE_NOT_INT);
		return TRUE;
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
		// unify the error
		ctop_int(2, HANDLE_NOT_INT);
		return TRUE;
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
		ctop_int(3, error);
		return TRUE;
	}

	// now confirm the pred name and arity for this predicate
	prolog_term value = reg_term(CTXTdeclc 2);

	if(!is_functor(value))
	{
		ctop_int(3, INSERT_NON_FUNCTOR);
		return TRUE;
	}

	int in_arity = p2c_arity(value);
	char *in_predname = p2c_functor(value);

	if(in_arity != arity)
	{
		ctop_int(3, ARITY_MISMATCH);
		return TRUE;
	}

	if(strcmp(in_predname, predname) != 0)
	{
		ctop_int(3, PREDNAME_MISMATCH);
		return TRUE;
	}

	// This check may be redundant...indexon < arity is checked in INIT and the indexon argument is taken
	// from the IndexTable.
	if(indexon > arity)
	{
		ctop_int(3, INVALID_INDEXON);
		return TRUE;
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
		// unify the error
		ctop_int(2, HANDLE_NOT_INT);
		return TRUE;
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
		// unify the error
		ctop_int(2, HANDLE_NOT_INT);
		return TRUE;
	} 

	int handle_index = p2c_int(tree_term);
	char *value;
	int error = c_bt_query_next(handle_index, &value);

	// unify the error
	ctop_int(3,error);	

	if(error == 0)
	{
		// unify the string and return
		STRFILE strfile;
		strfile.strcnt = strlen(value);
		strfile.strptr = value; strfile.strbase = value;

		read_canonical_term(CTXTdecl NULL, &strfile, 1);
	}

	return TRUE;
}

/**
 * bt_query_prev/3. Retrieve the previous value from an active key query handle.
 * bt_query_prev(+TreeHandle, -Value, -Error).
 **/
int c_bt_query_prev(int handle, char **valstr);
DllExport int call_conv bt_query_prev(CTXTdecl)
{
	// the first argument is the handle to the tree
	prolog_term tree_term = reg_term(CTXTdecl 1);
	if(!is_int(tree_term))
	{
		// unify the error
		ctop_int(2, HANDLE_NOT_INT);
		return TRUE;
	} 

	int handle_index = p2c_int(tree_term);
	char *value;
	int error = c_bt_query_prev(handle_index, &value);

	// unify the error
	ctop_int(3,error);	

	if(error == 0)
	{
		// unify the string and return
		STRFILE strfile;
		strfile.strcnt = strlen(value);
		strfile.strptr = value; strfile.strbase = value;

		read_canonical_term(CTXTdecl NULL, &strfile, 1);
	}

	return TRUE;
}

/** 
 * bt_get_predname/3 returns the predicate name used to store the data in the b+ tree. 
 * bt_get_predname(+Handle, -Name, -Error).
 **/
DllExport int call_conv bt_get_predname(CTXTdecl)
{
	// Find the IndexTable associated with the handle.
	prolog_term handle_term = reg_term(CTXTdecl 1);
	if(!is_int(handle_term))
	{
		ctop_int(3, HANDLE_NOT_INT);
		return TRUE;
	}

	int handle_index = p2c_int(handle_term);
	char *predname;
	int sink;
	int error = c_bt_get_info(handle_index, &predname, &sink, &sink);

	extern_ctop_string(CTXTdecl 2, predname);
	ctop_int(3,error);

	return TRUE;
}

/** bt_get_arity/2 returns the predicate arity stored in the b+ tree. **/
DllExport int call_conv bt_get_arity(CTXTdecl)
{
	// Find the IndexTable associated with the handle.
	prolog_term handle_term = reg_term(CTXTdecl 1);
	if(!is_int(handle_term))
	{
		ctop_int(3, HANDLE_NOT_INT);
		return TRUE;
	}

	int handle_index = p2c_int(handle_term);
	char *predname;
	int arity;
	int indexon;
	int error = c_bt_get_info(handle_index, &predname, &arity, &indexon);

	ctop_int(2,arity);
	ctop_int(3,error);

	return TRUE;
}

/** bt_get_arity/2 returns the index on number stored in the b+ tree. **/
DllExport int call_conv bt_get_indexon(CTXTdecl)
{
	// Find the IndexTable associated with the handle.
	prolog_term handle_term = reg_term(CTXTdecl 1);
	if(!is_int(handle_term))
	{
		ctop_int(3, HANDLE_NOT_INT);
		return TRUE;
	}

	int handle_index = p2c_int(handle_term);
	char *predname;
	int arity;
	int indexon;
	int error = c_bt_get_info(handle_index, &predname, &arity, &indexon);

	ctop_int(2,indexon);
	ctop_int(3,error);

	return TRUE;
}

/** Start a transaction on the DB **/
int c_bt_trans_start(int handle);
DllExport int call_conv bt_trans_start(CTXTdecl)
{
	// Find the IndexTable associated with the handle.
	prolog_term handle_term = reg_term(CTXTdecl 1);
	if(!is_int(handle_term))
	{
		ctop_int(2, HANDLE_NOT_INT);
		return TRUE;
	}

	int handle_index = p2c_int(handle_term);

	int error = c_bt_trans_start(handle_index);

	ctop_int(2,error);

	return TRUE;
}

int c_bt_trans_end(int handle, int commit);
DllExport int call_conv bt_trans_commit(CTXTdecl)
{
	// Find the IndexTable associated with the handle.
	prolog_term handle_term = reg_term(CTXTdecl 1);
	if(!is_int(handle_term))
	{
		ctop_int(2, HANDLE_NOT_INT);
		return TRUE;
	}

	int handle_index = p2c_int(handle_term);

	int error = c_bt_trans_end(handle_index, 1);

	ctop_int(2,error);

	return TRUE;
}

DllExport int call_conv bt_trans_abort(CTXTdecl)
{
	// Find the IndexTable associated with the handle.
	prolog_term handle_term = reg_term(CTXTdecl 1);
	if(!is_int(handle_term))
	{
		ctop_int(2, HANDLE_NOT_INT);
		return TRUE;
	}

	int handle_index = p2c_int(handle_term);

	int error = c_bt_trans_end(handle_index, 0);

	ctop_int(2,error);

	return TRUE;
}

/**************************
 * MANUAL CURSOR MODE 
 * This mode allows the programmer to manipulate a trees cursor.
 **************************/
 /* bt_mcm_init/2. Sets the cursorMode of the given tree to MCM. */
int c_bt_mcm_init(int handle);
DllExport int call_conv bt_mcm_init(CTXTdecl)
{
	// the first argument is the handle to the tree
	prolog_term tree_term = reg_term(CTXTdecl 1);
	if(!is_int(tree_term))
	{
		ctop_int(2, HANDLE_NOT_INT);
		return TRUE;	
	} 
	int handle_index = p2c_int(tree_term);
	
	int error = c_bt_mcm_init(handle_index);

	ctop_int(2,error);

	return TRUE;
}

/** bt_cm_first/1. Jump the cursor to the first record in the tree. **/
int c_bt_mcm_first(int handle);
DllExport int call_conv bt_mcm_first(CTXTdecl)
{ 
	// the first argument is the handle to the tree
	prolog_term tree_term = reg_term(CTXTdecl 1);
	if(!is_int(tree_term))
	{
		ctop_int(2, HANDLE_NOT_INT);
		return TRUE;	
	} 
	int handle_index = p2c_int(tree_term);
	
	int error = c_bt_mcm_first(handle_index);

	ctop_int(2,error);

	return TRUE;
}

/** bt_cm_last/1. Jump the cursor to the last record in the tree. **/
int c_bt_mcm_last(int handle);
DllExport int call_conv bt_mcm_last(CTXTdecl)
{ 
	// the first argument is the handle to the tree
	prolog_term tree_term = reg_term(CTXTdecl 1);
	if(!is_int(tree_term))
	{
		ctop_int(2, HANDLE_NOT_INT);
		return TRUE;	
	} 
	int handle_index = p2c_int(tree_term);
	
	int error = c_bt_mcm_last(handle_index);

	ctop_int(2,error);

	return TRUE;
}

/** bt_mcm_next/1. Jump the cursor to the next successive record in the tree. **/
int c_bt_mcm_next(int handle);
DllExport int call_conv bt_mcm_next(CTXTdecl) 
{ 
	// the first argument is the handle to the tree
	prolog_term tree_term = reg_term(CTXTdecl 1);
	if(!is_int(tree_term))
	{
		ctop_int(2, HANDLE_NOT_INT);
		return TRUE;	
	} 
	int handle_index = p2c_int(tree_term);
	
	int error = c_bt_mcm_next(handle_index);

	ctop_int(2,error);

	return TRUE;
}


/** bt_mcm_next/1. Jump the cursor to the next successive record in the tree. **/
int c_bt_mcm_prev(int handle);
DllExport int call_conv bt_mcm_prev(CTXTdecl) 
{ 
	// the first argument is the handle to the tree
	prolog_term tree_term = reg_term(CTXTdecl 1);
	if(!is_int(tree_term))
	{
		ctop_int(2, HANDLE_NOT_INT);
		return TRUE;	
	} 
	int handle_index = p2c_int(tree_term);
	
	int error = c_bt_mcm_prev(handle_index);

	ctop_int(2,error);

	return TRUE;
}

/** bt_mcm_key/3. returns the key and the current point. **/
int c_bt_mcm_val(int handle, char **valstr);
DllExport int call_conv bt_mcm_val(CTXTdecl) 
{ 
	// the first argument is the handle to the tree
	prolog_term tree_term = reg_term(CTXTdecl 1);
	if(!is_int(tree_term))
	{
		ctop_int(2, HANDLE_NOT_INT);
		return TRUE;	
	} 
	int handle_index = p2c_int(tree_term);
	
	char *valstr;
	int error = c_bt_mcm_val(handle_index, &valstr);

	ctop_int(3,error);

	if(error == 0)
	{
		// unify the string and return
		STRFILE strfile;
		strfile.strcnt = strlen(valstr);
		strfile.strptr = valstr; strfile.strbase = valstr;

		read_canonical_term(CTXTdecl NULL, &strfile, 1);
	}

	return TRUE;
}

int c_bt_mcm_key(int handle, char **keystr);
/** bt_mcm_val/2. returns the key and the current point. **/
DllExport int call_conv bt_mcm_key(CTXTdecl) 
{ 
	// the first argument is the handle to the tree
	prolog_term tree_term = reg_term(CTXTdecl 1);
	if(!is_int(tree_term))
	{
		ctop_int(2, HANDLE_NOT_INT);
		return TRUE;	
	} 
	int handle_index = p2c_int(tree_term);
	
	char *keystr;
	int error = c_bt_mcm_key(handle_index, &keystr);

	ctop_int(3,error);

	if(error == 0)
	{
		// unify the string and return
		STRFILE strfile;
		strfile.strcnt = strlen(keystr);
		strfile.strptr = keystr; strfile.strbase = keystr;

		read_canonical_term(CTXTdecl NULL, &strfile, 1);
	}

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


int c_bt_errmsg(int handle, char **message);
DllExport int call_conv bt_error_message(CTXTdecl)
{
	// Find the IndexTable associated with the handle.
	prolog_term handle_term = reg_term(CTXTdecl 1);
	if(!is_int(handle_term))
	{
		// unify the error
		ctop_int(3, HANDLE_NOT_INT);
		return TRUE;
	}

	int handle_index = p2c_int(handle_term);
	char *message;
	//int error = c_bt_errmsg(handle_index, &message);
	c_bt_errmsg(handle_index, &message);

	// set the results
	//ctop_int(3, error);
	extern_ctop_string(2, message);

	return TRUE;
}