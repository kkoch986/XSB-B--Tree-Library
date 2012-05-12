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
#include "io_builtins_xsb.h"
#ifdef WIN_NT
#define XSB_DLL
#endif

/* QDBM Includes */
#include <depot.h>
#include <cabin.h>
//#include <vista.h>
#include <villa.h>

#define DBNAME "xsbdb"

// predefine functions
char *pt2str(prolog_term term);
char *pt2dbname(char *predname, int arity, int arg);

// a structure to hold information about the b+ tree table.
struct IndexTable
{
	VILLA *villa;
	char *predname;
	int arity;
	int argnum;
};

// pointer to our B+ trees.
static struct IndexTable *villas;
static int currentSize = 10;
static int nextIndex = 0;

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
		printf("First Initialization\n");
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
	/* open the database */
	if(!(villas[nextIndex].villa = vlopen(db_name, VL_OWRITER | VL_OCREAT, VL_CMPLEX))){
		fprintf(stderr, "vlopen: %s\n", dperrmsg(dpecode));
		return FALSE;
	}

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
 * bt_insert(+Term, +Handle).
 **/
DllExport int call_conv bt_insert(CTXTdecl)
{
	// Find the IndexTable associated with the handle.
	prolog_term handle_term = reg_term(CTXTdecl 2);
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
	prolog_term value = reg_term(CTXTdeclc 1);

	if(!is_functor(value))
	{
		fprintf(stderr, "Insert Error: Insert Argument Is Not A Functor.\n");
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
	char *val_str = pt2str(value);
	char *key_str = pt2str(key);

	if(!vlput(handle.villa, key_str, -1, val_str, -1, VL_DDUP))
	{
    	fprintf(stderr, "Insert Error (DB): %s\n", dperrmsg(dpecode));
    	return FALSE;
	}

	// ---------------------------------------------
	// -- DEBUG -- PRINT OUT THE TERM --------------
	// ---------------------------------------------
	printf("Insert Term: (Key: %s, Value: %s)\n", key_str, val_str);
	int size = vlrnum(handle.villa);
	printf("B+ Tree (%s) Size: %i\n", handle.predname, size);
	// ---------------------------------------------
	// ---------------------------------------------

	return TRUE;
}


DllExport int call_conv bt_close(CTXTdecl) 
{
	prolog_term handle_term = reg_term(CTXTdecl 2);
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

	return TRUE;
}


/** note: buff is created with malloc here, may need to be freed? */
char *pt2str(prolog_term entry)
{
	if(is_attv(entry))
		printf("Attrv");
	if(is_functor(entry))
	{
		char *buff = malloc(sizeof(char) * 1000);
		int arity = p2c_arity(entry);
		char *functor = p2c_functor(entry);
		sprintf(buff, "%s(", functor);		
			int x;
			for(x = 1 ; x <= arity ; x++)
			{
				strcat(buff, pt2str(p2p_arg(entry, x)));
				if(x != arity) buff = strcat(buff, ",");
			}
		buff = strcat(buff, ")");
		return buff;
	}
	if(is_string(entry))
		return p2c_string(entry);
	if(is_list(entry))
		printf("list");
	if(is_var(entry))
		printf("VAR");
	if(is_int(entry))
	{
		char *buff = malloc(sizeof(char) * 12);
		sprintf(buff, "%i", (int)p2c_int(entry));
		return buff;
	}

	return "";
}


char *pt2dbname(char *predname, int arity, int arg)
{
	/* dbname is of the format db_arg_arity_predname */
	char *buff = malloc(sizeof(char) * (5 + sizeof(predname) + 12 + 12));
	sprintf(buff, "db_%i_%i_%s", arg, arity, predname);
	return buff;
}


DllExport int call_conv bt_test(CTXTdecl)
{
	STRFILE strfile;
	
	char *st = "a(b,c)";
	strfile.strcnt = strlen(st);
	strfile.strptr = st;

	read_canonical_term(CTXTdecl NULL, &strfile, 1);
	return TRUE;
}




