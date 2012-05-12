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

/**
 * struct clause_bucket_node -- this struct will pair a prolog term and potentially 
 * a link to another clause_bucket_node which holds another prolog term in this bucket.
 * 
 * Chose a linked list structure here since you will likely traverse the entire bucket of 
 * clauses sequentially. New nodes are pushed at the head of the list.
 **/
struct clause_bucket_node 
{
	struct clause_bucket_node *next;
	prolog_term term;
};

/**
 * struct prolog_term_key : extracts a prolog_term to be used as a key. 
 * currently this structure can only extract keys from functor terms with
 * arity > 0. The current key extracted is the prolog term represented by
 * the first argument to the functor.
 */
struct prolog_term_key {
  prolog_term operator()(clause_bucket_node cbn) 
  { 
  	printf("extract key\n");
  	prolog_term t = (cbn.term);
  	if(is_functor(t))
  	{
  		int arity = p2c_arity(t);
		if(arity == 0)
			printf("Non-Indexable Term Exception ( 0-ary predicate )");

		char *functor = p2c_functor(t);
		printf("key functor: %s/%d\n", functor, arity);

		// get the first argument for now...
		// later i might make a struct to wrap a prolog term and the number
		// of its indexed argument
		prolog_term ret = p2p_arg(t, 1);

		return ret;
  	}
  	else
  		printf("Non-Indexable Term Exception (not a functor)");
  }
};

struct prolog_term_cmp {
  int operator()(prolog_term t1, prolog_term t2) 
  { 
  	printf("CMP");
  	return -1;
  }
};

/* The B+ Tree Type Definition. KEY: prolog_term, VALUE: clause_bucket_node */
typedef AMI_btree<prolog_term, struct clause_bucket_node, prolog_term_cmp, prolog_term_key > IndexTree;
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
extern "C" bool cbt_insert(CTXTdecl prolog_term entry)
{
	if(is_attv(entry))
		printf("Attrv");
	if(is_functor(entry))
	{
		int arity = p2c_arity(entry);
		if(arity == 0)
		{
			printf("WARNING: Cannot index /0 predicates.");
			return false;
		}

		char *functor = p2c_functor(entry);
		printf("functor: %s/%d\n", functor, arity);

		clause_bucket_node node;
		node.term = entry;
		node.next = NULL;

		bool insert = btree->insert(node);
		if(!insert)
		{
			printf("Couldn't insert the term, duplicate Key detected.");
			// TODO: Here we will push it into the bucket instead.
		}
			
	}
	if(is_string(entry))
		printf("string");
	if(is_list(entry))
		printf("list");
	if(is_var(entry))
		printf("VAR");
	if(is_int(entry))
		printf("INT");

	// char *repr = p2c_string(entry);
	// printf("Insert row: %s\n", repr);
	// bool insert = btree->insert(repr);
	// if(!insert)
	// 	printf("Couldn't insert the string, duplicate Key detected.");

	return FALSE;
}


extern "C" prolog_term cbt_get(CTXTdecl prolog_term key)
{
	struct clause_bucket_node result;

	printf("start");

	if(btree->find(key, result))
	{
		printf("start2");
		prolog_term t =  (result.term);
		return t;
	}
	else
		printf("Unable to find any results.");

	return NULL;
}


/** Prints out a prolog term in a readable way. **/
void printTerm(prolog_term entry)
{
	if(is_attv(entry))
		printf("Attrv");
	if(is_functor(entry))
	{
		int arity = p2c_arity(entry);
		char *functor = p2c_functor(entry);
		printf("functor: %s/%d\n", functor, arity);		
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


