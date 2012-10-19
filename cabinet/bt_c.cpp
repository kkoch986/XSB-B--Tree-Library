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
const int META_CLOSE_ERROR 		=  3;
const int DB_OPEN_ERROR			=  4;
const int DB_CLOSE_ERROR		=  5;
const int INVALID_ARGUMENTS		=  6;

// other constants
#define MAXLINE 				4096

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

extern "C" int btest()
{
	ForestDB db;

	// open the database
	if (!db.open("casket.kch", ForestDB::OWRITER | ForestDB::OCREATE)) {
	  cerr << "open error: " << db.error().name() << endl;
	}

	// try adding a record
	if (!db.append("hello", 5, "world\0", 6)) {
		cerr << "insert error: " << db.error().name() << endl;
	}

	if (!db.append("hello", 5, "this rocks\0", 11)) {
		cerr << "insert error: " << db.error().name() << endl;
	}

	// retrieve the record
	size_t sizeptr;
	char *val;
	if((val = db.get("hello", 5, &sizeptr)) == NULL) {
		cerr << "get error: " << db.error().name() << endl;
	}
	
	printf("Retrieved: %s (length %lu)\n", val, sizeptr);


	// close the dfatabase
	if (!db.close()) {
	  cerr << "close error: " << db.error().name() << endl;
	}	

	return FALSE;
}