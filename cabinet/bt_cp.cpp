// gcc -s -o ./bt_cp.so -shared ./bt_cp.cpp -lkyotocabinet -lstdc++ -lz -lrt -lpthread -lm -lc -B/usr/local/lib -fPIC


#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <sys/stat.h>

/* Kyoto Includes */
#include <kcdirdb.h>
#include <kchashdb.h>

using namespace std;
using namespace kyotocabinet;

#include "bterrs.h"

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
extern "C" int c_bt_create(char *dbname, char *predname, int arity, int indexon)
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
extern "C" int c_bt_init(char *dbname, int *t)
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

///////// C_BT_SIZE ///////////////////////////////////////////////////////////
extern "C" int c_bt_size(int handle, int *size)
{
	// find the handle	
	struct open_d *db = find(handle);

	if(db == NULL)
		return NO_SUCH_HANDLE;

	(*size) = db->db->count();
	if((*size) == -1)
		return SIZE_ERROR;

	return NO_ERROR;
}

///////// C_BT_GET_INFO /////////////////////////////////////////////////////////
extern "C" int c_bt_get_info(int handle, char **predname_in, int *arity_in, int *indexon_in)
{
	// find the handle	
	struct open_d *db = find(handle);

	if(db == NULL)
		return NO_SUCH_HANDLE;

	// line up the pointers and return
    (*predname_in)  = db->predname;
    (*arity_in)     = db->arity;
    (*indexon_in)   = db->indexon;

	return NO_ERROR;
}

extern "C" int c_bt_dbname(int handle, char **treename)
{
	// find the handle	
	struct open_d *db = find(handle);

	if(db == NULL)
		return NO_SUCH_HANDLE;

	// set the tree name 
	(*treename) = db->dbname;

	// return 
	return NO_ERROR;
}

///////// C_BT_INSERT /////////////////////////////////////////////////////////
extern "C" int c_bt_insert(int handle, char *keystr, char *valstr)
{
	// find the handle	
	struct open_d *db = find(handle);

	if(db == NULL)
		return NO_SUCH_HANDLE;

	if(!db->db->append(keystr, strlen(keystr), valstr, strlen(valstr)+1))
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
	if(db->buffer_size <= db->current_position)
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
	db->current_location += rlen * sizeof(char) + 1;
	db->current_position += rlen + 1;

	// point the valstr to the new space
	(*valstr) = buff;

	return NO_ERROR;
}