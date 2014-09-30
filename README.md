CHANGELOG
=========

## B+ Tree Library

Still a major work in progress, using this file to keep track of changes to XSB system files as i make them.

### XSB System Changes

These are changes that need to be made to XSB and compiled using ./makexsb.

1. __emu/io_builtins_xsb.c__ \[Above `int call_conv write_canonical_term_rec(CTXTdeclc Cell prologterm, int letter_flag)`\]

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

You can rebuild the parser once the changes have been put in place by issueing the query:

    ?- consult(parse, [sysmod]).

To add this capability, simply add the contents of `src/cmplib_parse_code.P` near the top of `<XSB INSTALL DIR>/cmplib/parse` 
and rebuild parse (`?- consult(parse, [sysmod])`).
