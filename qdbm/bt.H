:- ldoption('-lqdbm -B/usr/local/lib').

%% bt_init/0. Initializes a B+ Villa DB
:- export bt_init/3, bt_close/1, bt_size/2.
:- export bt_insert/2.
:- export bt_get/3, bt_getl/2, bt_getnext/2.
:- export bt_drop/2.

%% prefix and range queries
:- export bt_prefix_jump/2, bt_prefix_next/2.
:- export bt_range_init/3, bt_range_next/2.

% manual cursor mode
:- export bt_mcm_init/1.
:- export bt_mcm_first/1, bt_mcm_last/1.
:- export bt_mcm_next/1, bt_mcm_prev/1.
:- export bt_mcm_jump/2, bt_mcm_jump_rev/2.
:- export bt_mcm_key/2, bt_mcm_val/2.