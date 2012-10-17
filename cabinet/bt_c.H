:- ldoption('-lkyotocabinet -lstdc++ -lz -lrt -lpthread -lm -lc').

:- foreign_pred test() from btest(void):void.
:- foreign_pred bt_create(+dbname, +predname, +arity, +indexon, -retval) from c_bt_create(dbname:string, predname:string, arity:int, indexon:int):int.