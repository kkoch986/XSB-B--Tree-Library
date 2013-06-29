%% :-  %xsb_configuration(packagesdir,PkgPath),
%% 	PkgPath = '.',
%% 	atom_concat(' -lkyotocabinet -B/usr/local/lib', PkgPath, Part1),
%% 	atom_concat(Part1, '/bt_cp.so ', Part2),
%% 	atom_concat(Part2, PkgPath, Part3),
%% 	atom_concat(Part3, '/bt_cp.cpp', Part4),
%% 	write('test: '), writeln(Part4),
%% 	ldoption(Part4).
:- ldoption(' -lkyotocabinet -B/usr/local/lib -lbtc -L ./ ').


%% new create stuff
:- export bt_create/5.

%% bt_init/0. Initializes a B+ Villa DB
:- export bt_init/3, bt_close/2, bt_size/3. %% BT_SIZE needs to be revamped to account for multiples in a bucket
:- export bt_insert/3.
:- export bt_query_init/3, bt_query_next/3, bt_query_prev/3.
%TODO :- export bt_drop/2.

%% prefix and range queries
%TODO :- export bt_prefix_jump/2, bt_prefix_next/2.
%TODO :- export bt_range_init/3, bt_range_next/2.

% manual cursor mode
:- export bt_mcm_init/2.
:- export bt_mcm_first/2, bt_mcm_last/2.
:- export bt_mcm_next/2, bt_mcm_prev/2.
%TODO :- export bt_mcm_jump/2, bt_mcm_jump_rev/2.
:- export bt_mcm_key/3, bt_mcm_val/3.
%TODO :- export bt_mcm_next_key/1.
%TODO :- export bt_mcm_out/1.

% get info about a tree
:- export bt_dbname/3, bt_getinfo/5.

% transactions
:- export bt_trans_start/2, bt_trans_commit/2, bt_trans_abort/2.

% meta data
:- export bt_get_predname/3, bt_get_arity/3, bt_get_indexon/3. 
:- export bt_error_message/2.