:- ldoption('-lkyotocabinet -lstdc++ -lz -lrt -lpthread -lm -lc -B/usr/local/lib').

%% Creates a new B+ Tree
%% the last value is an error code (or 0 if no error)
:- foreign_pred bt_create(+dbname, +predname, +arity, +indexon, -retval) from c_bt_create(dbname:string, predname:string, arity:int, indexon:int):int.

%% Loads a B+ Tree and returns a handle
%% the last value is an error code (or 0 if no error)
:- foreign_pred bt_init(+dbname, -h, -retval) from c_bt_init(dbname:string, h:intptr):int.

%% Closes a B+ Tree handle
:- foreign_pred bt_close(+handle, -retval) from c_bt_close(handle:int):int.

%% Inserts a value into the tree.
:- foreign_pred bt_insert(+handle, +valstr, -retval) from c_bt_insert(handle:int, valstr:term):int.

%% Initializes a query
%% this should be called to load the query results into the buffer for this handle
%% NO_ERROR is returned in the error field (final argument) if at least one result is found
%% NO_RESULTS is returned in the error field if no results are found
:- foreign_pred bt_query_init(+handle, +keystr, -retval) from c_bt_query_init(handle:int, keystr:string):int.

%% returns the next result in the query results queue
:- foreign_pred bt_query_next(+handle, -valstr, -retval) from c_bt_query_next(handle:int, valstr:stringptr):int.



%% gcc -s -o ./bt_c.so -shared ./bt_c.c   -Wall -fPIC -I/home/ken/XSB/emu -I/home/ken/XSB/config/x86_64-unknown-linux-gnu  -O3 -fno-strict-aliasing  -Wall -pipe  -lqdbm -B/usr/local/lib 
%% gcc -s -o ./bt_c.so -shared ./bt_c.cpp xsb_wrap_bt_c.c  -Wall -fPIC -I/home/ken/XSB/emu -I/home/ken/XSB/config/x86_64-unknown-linux-gnu  -O3 -fno-strict-aliasing  -Wall -pipe  -lkyotocabinet -lstdc++ -lz -lrt -lpthread -lm -lc -B/usr/local/lib 