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