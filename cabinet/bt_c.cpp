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

/* Kyoto Includes */
#include <kcdirdb.h>
#include <kchashdb.h>

using namespace std;
using namespace kyotocabinet;

// define error constants
const int NO_ERROR				=  0;
const int META_OPEN_ERROR 		=  1;
const int META_INSERT_ERROR 	=  2;
const int META_READ_ERROR		=  3;
const int META_CLOSE_ERROR 		=  4;
const int DB_OPEN_ERROR			=  5;
const int DB_CLOSE_ERROR		=  6;
const int INVALID_ARGUMENTS		=  7;

const int NO_RESULTS			=  8;
const int NO_SUCH_HANDLE		=  9;

const int DATA_INSERT_ERROR		= 10;

// other constants
#define MAXLINE 				4096

// structure for holding pointers to the open lists
struct open_d
{
	char *dbname;
	char *predname;
	int arity;
	int indexon;
	int handle;
	ForestDB *db;

	size_t buffer_size;
	unsigned long current_position;
	char *current_location;
	char *result_buffer;

	struct open_d *next;
};

struct open_d *list_head = NULL;
int nextHandle = 0;


/** Look up a database structure based on handle number **/
struct open_d *find(int index)
{
	struct open_d *trav = list_head;

	while(trav != NULL)
	{
		// check the handle number here
		if(trav->handle == index)
			return trav;
		// advance the traveller
		trav = trav->next;
	}

	return NULL;
}

///////// C_BT_CREATE /////////////////////////////////////////////////////////////
extern "C" int c_bt_create(CTXTdecl char *dbname, char *predname, int arity, int indexon)
{
	char buff[MAXLINE];
	printf("CREATE: %s, %s/%d on %d\n", dbname, predname, arity, indexon);

	// check that the indexon is not greater than the arity
	if( indexon > arity)
	{
		cerr << "error: indexon cannot exceed the predicate arity." << endl;
		return INVALID_ARGUMENTS;
	}

	// first create the directory to hold the database and the meta-db
	if(mkdir(dbname, S_IRWXU | S_IRWXG | S_IRWXO) < 0)
	{
		cerr << "unable to create database directory." << endl;
		return META_OPEN_ERROR;
	}

	// now, in that directory create a HashDB to store the meta data
	HashDB hashdb;
	sprintf(buff, "%s/meta", dbname);

	// create the meta database
	if (!hashdb.open(buff, HashDB::OWRITER | HashDB::OCREATE)) {
	  cerr << "open error: " << hashdb.error().name() << endl;
	  return META_OPEN_ERROR;
	}

	// store the meta values
	// DBNAME
	if (!hashdb.set("dbname", 6, dbname, strlen(dbname))) {
		cerr << "insert meta error: " << hashdb.error().name() << endl;
		return META_INSERT_ERROR;
	}

	// PREDNAME
	if (!hashdb.set("predname", 8, predname, strlen(predname))) {
		cerr << "insert meta error: " << hashdb.error().name() << endl;
		return META_INSERT_ERROR;
	}

	// ARITY
	bzero(buff, MAXLINE);
	sprintf(buff, "%d", arity);
	if (!hashdb.set("arity", 5, buff, strlen(buff))) {
		cerr << "insert meta error: " << hashdb.error().name() << endl;
		return META_INSERT_ERROR;
	}

	// INDEXON
	bzero(buff, MAXLINE);
	sprintf(buff, "%d", indexon);
	if (!hashdb.set("indexon", 7, buff, strlen(buff))) {
		cerr << "insert meta error: " << hashdb.error().name() << endl;
		return META_INSERT_ERROR;
	}

	// close the meta db
	if (!hashdb.close()) {
	  cerr << "close error: " << hashdb.error().name() << endl;
	  return META_CLOSE_ERROR;
	}

	// now create the B+ tree (simpler process)
	bzero(buff, MAXLINE);
	sprintf(buff, "%s/db", dbname);

	ForestDB db;

	// open the database
	if (!db.open(buff, ForestDB::OWRITER | ForestDB::OCREATE)) {
	  cerr << "open error: " << db.error().name() << endl;
	  return DB_OPEN_ERROR;
	}

	// close it so it is written to disk
	if (!db.close()) {
	  cerr << "close error: " << db.error().name() << endl;
	  return DB_CLOSE_ERROR;
	}	

	return NO_ERROR;
}

///////// C_BT_INIT /////////////////////////////////////////////////////////////
extern "C" int c_bt_init(CTXTdecl char *dbname, int *t)
{
	char buff[MAXLINE];
	// open the meta database
	HashDB hashdb;
	sprintf(buff, "%s/meta", dbname);

	// open the meta database
	if (!hashdb.open(buff, HashDB::OWRITER | HashDB::OCREATE)) {
	  cerr << "open error: " << hashdb.error().name() << endl;
	  return META_OPEN_ERROR;
	}

	// read the predicate name
	size_t size;
	char *predname = hashdb.get("predname", 8, &size);

	if(predname == NULL)
	{
		//cerr << "read error: " << hashdb.error().name() << endl;
		printf("READ ERROR: %s.\n", hashdb.error().name());
		return META_READ_ERROR;
	}

	// read the arity
	char *arity_s = hashdb.get("arity", 5, &size);
	int arity = std::atoi(arity_s);

	if(arity_s == NULL)
	{
		cerr << "read error: " << hashdb.error().name() << endl;
		return META_READ_ERROR;
	}

	// read the indexon
	char *indexon_s = hashdb.get("indexon", 7, &size);
	int indexon = std::atoi(indexon_s);
	
	if(indexon_s == NULL)
	{
		cerr << "read error: " << hashdb.error().name() << endl;
		return META_READ_ERROR;
	}

	// close the meta database
	if (!hashdb.close()) {
	  cerr << "close error: " << hashdb.error().name() << endl;
	  return META_CLOSE_ERROR;
	}	

	// open the forest
	ForestDB *db = new ForestDB();
	sprintf(buff, "%s/db", dbname);

	// open the database
	if (!db->open(buff, ForestDB::OWRITER | ForestDB::OCREATE)) {
	  cerr << "open error: " << db->error().name() << endl;
	  return DB_OPEN_ERROR;
	}

	// build the structure
	struct open_d *h = (struct open_d *)malloc(sizeof(struct open_d));
	h->dbname = dbname;
	h->predname = predname;
	h->arity = arity;
	h->indexon = indexon;
	h->handle = nextHandle++;
	h->db = db;

	h->next = list_head;
	list_head = h;

	// set the handle number
	(*t) = h->handle;

	return NO_ERROR;
}

///////// C_BT_CLOSE //////////////////////////////////////////////////////////
extern "C" int c_bt_close(int handle)
{
	// find the handle	
	struct open_d *db = find(handle);

	if(db == NULL)
		return NO_SUCH_HANDLE;

	if(!db->db->close())
		return DB_CLOSE_ERROR;

	// TODO: Free the handles and remove the struct from the list

	return NO_ERROR;
}

///////// C_BT_INSERT /////////////////////////////////////////////////////////
extern "C" int c_bt_insert(int handle, prolog_term val)
{
	// find the handle	
	struct open_d *db = find(handle);

	if(db == NULL)
		return NO_SUCH_HANDLE;

	prolog_term key = p2p_arg(val, db->indexon);
	char *buff = canonical_term(CTXTdecl key, 1);
	int size = cannonical_term_size(CTXTdecl) + 1;
	char keystr[size];
	strncpy(keystr, buff, size);

	buff = canonical_term(CTXTdecl val, 1);
	size = cannonical_term_size(CTXTdecl) + 1;
	char valstr[size];
	strncpy(valstr, buff, size);

	if(!db->db->append(keystr, strlen(keystr)+1, valstr, strlen(valstr)))
		return DATA_INSERT_ERROR; 

	return NO_ERROR;
}

///////// C_BT_QUERY_INIT /////////////////////////////////////////////////////
extern "C" int c_bt_query_init(int handle, char *keystr)
{
	// find the handle	
	struct open_d *db = find(handle);

	if(db == NULL)
		return NO_SUCH_HANDLE;

	// send the query to the database
	db->result_buffer = db->db->get(keystr, strlen(keystr), &db->buffer_size);
	db->current_location = db->result_buffer;
	db->current_position = 0;

	if(db->result_buffer == NULL)
		return NO_RESULTS;

	return NO_ERROR;
}

///////// C_BT_QUERY_NEXT /////////////////////////////////////////////////////
extern "C" int c_bt_query_next(int handle, char **valstr)
{
	// find the handle	
	struct open_d *db = find(handle);

	if(db == NULL)
		return NO_SUCH_HANDLE;

	// if the buffer size is 0, there are no results queued
	if(db->buffer_size == db->current_position)
	{
		// free the space
		if(db->result_buffer != NULL)
		{
			delete(db->result_buffer);
			db->result_buffer = NULL;
			db->current_location = NULL;
			db->current_position = 0;
		}		
		return NO_RESULTS;
	}

	if(db->result_buffer == NULL)
		return NO_RESULTS;
	
	// find out how long the next string is
	int rlen = strlen(db->result_buffer);

	// allocate enough space to return it
	char *buff = (char *)malloc(sizeof(char) * rlen);

	// copy the bytes
	strcpy(buff, db->current_location);

	// advance the buffer and update the size
	db->current_location += rlen * sizeof(char);
	db->current_position += rlen;

	// point the valstr to the new space
	(*valstr) = buff;

	return NO_ERROR;
}