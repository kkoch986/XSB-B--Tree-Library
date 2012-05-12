#include "xsb_config.h"
#include "cinterf.h"
#ifdef CYGWIN
#include "../../emu/context.h"
#else
#include "context.h"
#endif
#include <stdio.h>
#include <functional>
#include <algorithm>
#include <stack>
#include <ami_btree.h>

/** Prints out a prolog term in a readable way. **/
extern "C" void printTerm(prolog_term entry)
{
	if(is_attv(entry))
		printf("Attrv");
	if(is_functor(entry))
	{
		int arity = p2c_arity(entry);
		char *functor = p2c_functor(entry);
		//printf("functor: %s/%d", functor, arity, functor);		
		printf("%s(", functor, arity, functor);		
			for(int x = 1 ; x <= arity ; x++)
			{
				printTerm(p2p_arg(entry, x));
				if(x != arity) printf(",");
			}
		printf(")");
	}
	if(is_string(entry))
		printf("%s", p2c_string(entry));
	if(is_list(entry))
		printf("list");
	if(is_var(entry))
		printf("VAR");
	if(is_int(entry))
		printf("%i", (int)p2c_int(entry));
}


struct int_key {
  const int operator()(const int t) const { printf("key %d\n", t); return t + 1; }
};

struct pt_key {
	prolog_term operator()(prolog_term t)
	{ 
		printf("key: "); 
		printTerm(t); 
		printf("\n"); 
		return t; 
	}
};

/* The B+ Tree Type Definition. KEY: prolog_term, VALUE: clause_bucket_node */
//typedef AMI_btree<int, int, less<int>, int_key > IndexTree;
typedef AMI_btree<prolog_term, prolog_term, less<prolog_term>, pt_key > IndexTree;
IndexTree *btree;

/**
 * Deleting the reference to the tree will cause it to be removed.
 */
extern "C" bool cbt_close(CTXTdecl)
{
	delete btree;
	return 0;
}


/**
 * bool cbt_init() -- <bt_init/0>.
 *
 * Initializes the B+ Tree. if you are creating a new tree for the first time, 
 * for some reason you need to call init, close, init. TODO: look into that....
 **/
extern "C" bool cbt_init(CTXTdecl)
{
	AMI_btree_params params;
	params.node_block_factor 	= 1;
	params.leaf_block_factor 	= 1;
	params.leaf_cache_size 		= 32;
	params.node_cache_size 		= 32;
	params.node_size_max 		= 3; // default.
	params.leaf_size_max 		= 100;

	btree = new IndexTree("index_tree", AMI_READ_WRITE_COLLECTION, params) ;
	btree->persist(PERSIST_PERSISTENT);

	if (!btree->is_valid()) 
	{
	    delete btree;
	    printf("Error encountered while opening B-tree.\n");
	    return false;
	}
	else
	{
		TPIE_OS_OFFSET input_size = btree->size();
		printf("BTree Loaded (Size: %d)\n", (int)btree->size());
		return true;
	}
}

/**
 * bool cbt_insert(prolog_term entry) -- <bt_insert(+value)>
 *
 * Attempts to insert the term into the B+ Tree.
 **/
 static prolog_term last_term = NULL;

extern "C" bool cbt_insert(CTXTdecl prolog_term entry)
{
	printf("COMP: %d", last_term == entry);
	last_term = entry;

	if(is_attv(entry))
		printf("Attrv");
	if(is_functor(entry))
	{
		printf("FUNCTOR: ");
		printTerm(entry);
		printf("\n");

		bool insert = btree->insert(entry);
		if(!insert)
		{
			printf("Couldn't insert the term, duplicate Key detected.");
			// TODO: Here we will push it into the bucket instead.
		}
	}
	if(is_string(entry))
	{
		printf("STRING: %s\n", p2c_string(entry));

		bool insert = btree->insert(entry);
		if(!insert)
		{
			printf("Couldn't insert the term, duplicate Key detected.");
			// TODO: Here we will push it into the bucket instead.
		}
	}
	if(is_list(entry))
		printf("list");
	if(is_var(entry))
		printf("VAR");
	if(is_int(entry))
	{
		printf("INT");
		bool insert = btree->insert(p2c_int(entry));
		if(!insert)
		{
			printf("Couldn't insert the term, duplicate Key detected.");
			// TODO: Here we will push it into the bucket instead.
		}
	}
		

	// char *repr = p2c_string(entry);
	// printf("Insert row: %s\n", repr);
	// bool insert = btree->insert(repr);
	// if(!insert)
	// 	printf("Couldn't insert the string, duplicate Key detected.");

	return FALSE;
}

prolog_term result ;
extern "C" prolog_term cbt_get(CTXTdecl prolog_term key)
{
	printf("start");
	printTerm(key);

	if(btree->find(key, result))
	{
		printf("Result:");
		printTerm(result);
		printf("\n");

		return result;
	}
	else
		printf("Unable to find any results.");


	printf("ret NULL");
	return NULL;
}



