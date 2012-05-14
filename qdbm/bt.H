:- ldoption('-lqdbm -lxqdbm -B/usr/local/lib').

%% bt_init/0. Initializes a B+ Villa DB
:- export bt_init/3, bt_close/1.
:- export bt_insert/2.
:- export bt_get/3, bt_getl/3, bt_getnext/2.
:- export bt_test/3.