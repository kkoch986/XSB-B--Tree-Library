:- ldoption('-lkyotocabinet -lstdc++ -lz -lrt -lpthread -lm -lc').

:- foreign_pred test(-retval) from btest(void):int.

%% Creates a new B+ Tree
%% the last value is an error code (or 0 if no error)
:- foreign_pred bt_create(+dbname, +predname, +arity, +indexon, -retval) from c_bt_create(dbname:string, predname:string, arity:int, indexon:int):int.


%% Loads a B+ Tree and returns a handle
%% the last value is an error code (or 0 if no error)
:- foreign_pred bt_init(+dbname, -handle, -retval) from c_bt_init(dbname:string, handle:int):int.