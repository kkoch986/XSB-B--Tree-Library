:- ldoption('-lqdbm -lxqdbm -B/usr/local/lib').

%% bt_init/0. Initializes a B+ Villa DB
:- export bt_init/3, bt_close/1.
:- export bt_insert/1, bt_insert/2.
:- export bt_test/1, bt_test/2.