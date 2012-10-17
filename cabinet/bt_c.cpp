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
#include <kcpolydb.h>

using namespace std;
using namespace kyotocabinet;

#define DBNAME "xsbdb"
#define BNUM 10
#define MAXLINE 4096

extern "C" int c_bt_create(CTXTdecl char *dbname, char *predname, int arity, int indexon)
{
	printf("CREATE: %s, %s/%d on %d\n", dbname, predname, arity, indexon);

	return 0;
}

extern "C" void btest()
{
	TreeDB db;

	// open the database
	if (!db.open("casket.kch", TreeDB::OWRITER | TreeDB::OCREATE)) {
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

}