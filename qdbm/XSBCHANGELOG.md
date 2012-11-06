CHANGELOG
=========

## B+ Tree Library

Still a major work in progress, using this file to keep track of changes to XSB system files as i make them.

### XSB System Changes

These are changes that need to be made to XSB and compiled using ./makexsb.

1. __emu/io_builtins_xsb.c__ \[Line 1898\]

Add:

    /** BT Library, need to get the actual size of the last call to cannonical term **/
    int cannonical_term_size(CTXTdeclc) { return wcan_string->length; }

1. __emu/io_builtins_xsb.h__ \[End Of File\]

Add:

    ////////
    char *canonical_term(CTXTdeclc Cell prologterm, int letter_flag);
    int cannonical_term_size(CTXTdeclc);


### For indexing implementation:
Using the built in indexing stuff you can create statements like:

    :- import test/2 from dbfile as btree(2).
or 
    :- import test/2 from dbfile as btree.

and then access the clauses of the database using:

    ?- test(X,Y).

just as if it were an indexed clause. The indexing code will determine if the call is bound on the
indexed argument and make calls accordingly.

## add to cmplib/parse.P
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    %% CONCERNS:
    %% in the event that the user doesnt fail all the way through the options, tree handles may be left open
    %% this is obviosuly bad, it would be better to either have one handle always open per index (really ideal) or
    %% have the handle close after each call is finished (impossible? and less ideal)
    parse_directive(import(as(from(PredIn/ArityIn, DBName),btree), _QrList,SymTab,ModName,ModStruct) :-
      parse_directive(import(as(from(PredIn/ArityIn, DBName),btree(1))), _QrList,SymTab,ModName,ModStruct). 
    parse_directive(import(as(from(PredIn/ArityIn, DBName),btree(IndexonIn))), _QrList,SymTab,ModName,ModStruct) :- !,
      consult:consult(bt),
      %% initialize the B+ Tree
      (
        bt:btinit(DBName, Handle) 
        ; (
          bt:btcreate(DBName, PredIn/ArityIn, IndexonIn),
          bt:btinit(DBName, Handle)
        )
      ),
      %% check that the arity is a match
      bt:btarity(Handle, Arity),
      (
        ArityIn = Arity 
          -> true 
          ; misc_error(('Arity Mismatch (Expecting: ', Arity, ' got ', ArityIn, ')'))
      ),
      %% check the indexon is a match
      bt:btindexon(Handle, Indexon),
      (
        IndexonIn = Indexon
          -> true 
          ; misc_error(('Indexon Mismatch (Expecting: ', Indexon, ' got ', IndexonIn, ')'))
      ),
      %% get the real name it is stored with
      bt:btpredname(Handle, PredName),
      %% we can close this handle, unfortunetly at this time we have to reopen a connection everytime we query
      bt:btclose(Handle),
      %% create a blank list of variables
      basics:length(ArgList, Arity),
      % get the index on argument
      basics:ith(Indexon, ArgList, IndexVar),
      %% create the head of the rule
      RuleHead =.. [PredIn|ArgList],
      %% assert a predicate to respond to queries against this variable.
      Rule = 
      (
        RuleHead :- 
          % determine if its bound or not
          var(IndexVar) ->
          (
            %% UNBOUNDED CALL, USE BT_GETALL
            %% open a database connection
            bt:btinit(DBName, Handle2),
            (
              (
                bt:btgetall(Handle2, Result),
                Result =.. [PredName|ArgList]
              )
              ; (
                standard:writeln(close),
                bt:btclose(Handle2), !, fail
              )
            )
          )  ;
          (
            %% BOUNDED CALL, USE BT_GET
            %% open a database connection
            bt:btinit(DBName, Handle2),
            (
              bt:btget(Handle2, IndexVar, Result) 
              ; (
                standard:writeln(close),
                bt:btclose(Handle2), !, fail
              )
            ),
            Result =.. [PredName|ArgList]
          )
      ),
      parse_clause(Rule, ModStruct, ModName).
    
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%