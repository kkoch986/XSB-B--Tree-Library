:- ldoption('-lqdbm -B/usr/local/lib ./bt_cp.so ./bt_cp.cpp').

%% new create stuff
:- export bt_create/5.

%% bt_init/0. Initializes a B+ Villa DB
:- export bt_init/3, bt_close/2, bt_size/3.
:- export bt_insert/3.
:- export bt_query_init/3, bt_query_next/3.
%TODO :- export bt_drop/1.

%% prefix and range queries
%TODO :- export bt_prefix_jump/2, bt_prefix_next/2.
%TODO :- export bt_range_init/3, bt_range_next/2.

% manual cursor mode
%TODO :- export bt_mcm_init/1.
%TODO :- export bt_mcm_first/1, bt_mcm_last/1.
%TODO :- export bt_mcm_next/1, bt_mcm_prev/1.
%TODO :- export bt_mcm_jump/2, bt_mcm_jump_rev/2.
%TODO :- export bt_mcm_key/2, bt_mcm_val/2.
%TODO :- export bt_mcm_next_key/1.
%TODO :- export bt_mcm_out/1.

% get info about a tree
:- export bt_dbname/3, bt_getinfo/5.

% transactions
%TODO :- export bt_trans_start/1, bt_trans_commit/1, bt_trans_abort/1.

% meta data
%TODO :- export bt_get_predname/2, bt_get_arity/2, bt_get_indexon/2.
