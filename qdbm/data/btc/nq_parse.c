/*************************************/
/* To Build:				
 	gcc nqparse.c -o nqp `pkg-config raptor2 --cflags --libs`
	NOTE: You may have to add the path to raptor2.pc into the var: PKG_CONFIG_PATH
/*************************************/

#include <stdio.h>
#include <stdarg.h>
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

/* Raptor Includes */
#include <raptor2.h>


struct raptor_node_item
{
	int type;
	unsigned char* arg1;
	unsigned char* arg2;
	unsigned char* arg3;
};

struct raptor_node
{
	struct raptor_node *next;
	struct raptor_node * prev;
	struct raptor_node_item subject;
	struct raptor_node_item predicate;
	struct raptor_node_item object;
	struct raptor_node_item graph;
};

static struct raptor_node *head = NULL;
static struct raptor_node *tail = NULL;
static char *prefix = "quad";

static struct raptor_node_item build_term(raptor_term *triple)
{
	struct raptor_node_item n;
	n.type = triple->type;

	switch(triple->type)
	{
	  	case RAPTOR_TERM_TYPE_UNKNOWN:
	  		//printf("BUILD: (UKNOWN)" );
	  		break ;

	  	case RAPTOR_TERM_TYPE_URI:
	  		//printf("uri( %s )", raptor_uri_as_string(triple->value.uri));

	  		if(triple->value.uri == NULL)
	  			n.arg1 = "";
	  		else 
	  		{
	  			int size = strlen(raptor_uri_as_string(triple->value.uri));
	  			n.arg1 = malloc(sizeof(char) * size);
    			strncpy(n.arg1, raptor_uri_as_string(triple->value.uri), size);
	  		}

	  		break ;

	  	case RAPTOR_TERM_TYPE_LITERAL:
	  		//printf("literal( %s, %s, %s )", triple->value.literal.string, raptor_uri_as_string(triple->value.literal.datatype), triple->value.literal.language);

	  		// literal string
	  		if(triple->value.literal.string == NULL)
	  			n.arg1 = "";
	  		else 
	  		{
	  			int size = strlen(triple->value.literal.string);
	  			n.arg1 = malloc(sizeof(char) * size);
    			strncpy(n.arg1, triple->value.literal.string, size);
	  		}

	  		// datatype string
	  		if(triple->value.literal.datatype == NULL)
	  			n.arg2 = "";
	  		else 
	  		{
	  			int size = strlen(raptor_uri_as_string(triple->value.literal.datatype));
	  			n.arg2 = malloc(sizeof(char) * size);
    			strncpy(n.arg2, raptor_uri_as_string(triple->value.literal.datatype), size);
	  		}

	  		// language string
	  		if(triple->value.literal.language == NULL)
	  			n.arg3 = "";
	  		else 
	  		{
	  			int size = strlen(triple->value.literal.language);
	  			n.arg3 = malloc(sizeof(char) * size);
    			strncpy(n.arg1, triple->value.literal.language, size);
	  		}

	  		break ;

	  	case RAPTOR_TERM_TYPE_BLANK:
	  		 //printf("blank( %s )", triple->value.blank.string);

	  		if(triple->value.blank.string == NULL)
	  			n.arg1 = "";
	  		else 
	  		{
	  			int size = strlen(triple->value.blank.string);
	  			n.arg1 = malloc(sizeof(char) * size);
    			strncpy(n.arg1, triple->value.blank.string, size);
	  		}

	  		 break ;
	}

	return n;
}

static void c2p_raptor_term(CTXTdecl struct raptor_node_item triple, prolog_term t)
{
	switch(triple.type)
	{
	  	case RAPTOR_TERM_TYPE_UNKNOWN:
	  		// printf("BUILD: (UKNOWN)" );
	  		c2p_nil(CTXTdecl t);

	  		break ;

	  	case RAPTOR_TERM_TYPE_URI:

	  		// printf("uri( %s )", raptor_uri_as_string(triple->value.uri));

	  		c2p_functor(CTXTdecl "url", 1, t);
	  		prolog_term uri_str = p2p_arg(CTXTdecl t, 1); 
	  		c2p_string(CTXTdecl (char *)triple.arg1, uri_str);

	  		break ;

	  	case RAPTOR_TERM_TYPE_LITERAL:
	  		//printf("literal( %s, %s, %s )", triple->value.literal.string, raptor_uri_as_string(triple->value.literal.datatype), triple->value.literal.language);

	  		c2p_functor(CTXTdecl "literal", 3, t);

	  		// the actual string
	  		prolog_term lit_str = p2p_arg(CTXTdecl t, 1); 
	  		c2p_string(CTXTdecl (char *)triple.arg1, lit_str);

	  		// the datatype
			prolog_term dt_str = p2p_arg(CTXTdecl t, 2); 
			if(triple.arg2 != NULL)
	  			c2p_string(CTXTdecl (char *)triple.arg2, dt_str);	  		
	  		else
	  			c2p_string(CTXTdecl "", dt_str);	  		

	  		// the language
	  		prolog_term lang_str = p2p_arg(CTXTdecl t, 3); 
			if(triple.arg3 != NULL)
	  			c2p_string(CTXTdecl (char *)triple.arg3, lang_str);	  		
	  		else
	  			c2p_string(CTXTdecl "", lang_str);

	  		break ;

	  	case RAPTOR_TERM_TYPE_BLANK:
	  		// printf("blank( %s )", triple->value.blank.string);
	  		
	  		c2p_functor(CTXTdecl "blank", 1, t);
	  		prolog_term blank_str = p2p_arg(CTXTdecl t, 1); 
	  		c2p_string(CTXTdecl (char *)triple.arg1, blank_str);

	  		break ;

	  	default:
			c2p_nil(CTXTdecl t);
			break ;
	}

	//return t;
}

static void handle_term(CTXTdecl void* user_data, raptor_statement* quad)
{
	struct raptor_node *node = malloc(sizeof(struct raptor_node));
	
	// build a prolog term
	node->subject = build_term(quad->subject);
	node->predicate = build_term(quad->predicate);
	node->object = build_term(quad->object);
	node->graph = build_term(quad->graph);

	if(tail == NULL)
	{
		node->prev = NULL;
		node->next = NULL;
		tail = node;
		head = node;
	}
	else
	{
		node->next = tail;
		node->prev = NULL;
		tail->prev = node;
		tail = node;
	}
}


raptor_world *world = NULL;
raptor_parser* rdf_parser = NULL;

DllExport int call_conv load_nquad_file(CTXTdecl)
{
	char *filename = p2c_string(reg_term(CTXTdecl 1));

	unsigned char *uri_string;
	raptor_uri *uri, *base_uri;

	world = raptor_new_world();

	rdf_parser = raptor_new_parser(world, "nquads");

	raptor_parser_set_statement_handler(rdf_parser, NULL, handle_term);

	uri_string = raptor_uri_filename_to_uri_string(filename);
	uri = raptor_new_uri(world, uri_string);
	base_uri = raptor_uri_copy(uri);

	raptor_parser_parse_file(rdf_parser, uri, base_uri);

	raptor_free_parser(rdf_parser);

	raptor_free_uri(base_uri);
	raptor_free_uri(uri);
	raptor_free_memory(uri_string);

	raptor_free_world(world);

	return 1;
}

DllExport int call_conv set_nq_prefix(CTXTdecl)	
{
	prolog_term arg = reg_term(CTXTdecl 1);
	prefix = p2c_string(CTXTdecl arg);

	return 1;
}

DllExport int call_conv get_next_result(CTXTdecl)	
{
	if(head == NULL) return 0;

	// process the head raptor-term and build a term
	prolog_term return_term = reg_term(CTXTdecl 1);
	prolog_term t = p2p_new();
	c2p_functor(CTXTdecl prefix, 4, t);
	c2p_raptor_term(CTXTdecl head->subject, p2p_arg(CTXTdecl t, 1));
	c2p_raptor_term(CTXTdecl head->predicate, p2p_arg(CTXTdecl t, 2));
	c2p_raptor_term(CTXTdecl head->object, p2p_arg(CTXTdecl t, 3));
	c2p_raptor_term(CTXTdecl head->graph, p2p_arg(CTXTdecl t, 4));

	p2p_unify(return_term, t);

	// pop the head off the queue
	struct raptor_node *old_head = head;

	if(tail == head)
	{
		tail = NULL;
		head = NULL;
	}
	else
		head = head->prev;

	// free up the strings
	// free_node(old_head->subject);
	// free_node(old_head->predicate);
	// free_node(old_head->object);
	// free_node(old_head->graph);

	// return
	return 1;
}


