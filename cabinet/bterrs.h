#define MAXLINE 				4096

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
const int SIZE_ERROR			= 11;
const int HANDLE_NOT_INT		= 12;
const int INSERT_NON_FUNCTOR	= 13;
const int ARITY_MISMATCH		= 14;
const int PREDNAME_MISMATCH		= 15;
const int INVALID_INDEXON 		= 16;
const int CANNOT_DELETE			= 17;
const int TRANS_ERROR			= 18;
const int NOT_MCM_MODE			= 19;
const int NO_VALUE				= 20;