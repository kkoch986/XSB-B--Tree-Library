CHANGELOG
=========

## B+ Tree Library

Still a major work in progress, using this file to keep track of changes to XSB system files as i make them.

### XSB System Changes

These are changes that need to be made to XSB and compiled using ./makexsb.

1. __emu/io_builtins_xsb.c__ \[Line 836\] or \[871\]

Change:

	} else return (Cell)NULL;

To:

	} else if(code == 3) { /** B+ Trees (bt_get/3) **/
    	return (Cell)ptoc_tag(CTXTc 3);
 	} 
  	else if(code == 4) { /** B+ Trees (bt_getnext/2) **/
    	return (Cell)ptoc_tag(CTXTc 2);
  	} 
  	else return (Cell)NULL;

1. __emu/io_builtins_xsb.c__ \[Line 1898\]

Add:

    /** BT Library, need to get the actual size of the last call to cannonical term **/
    int cannonical_term_size(CTXTdeclc) { return wcan_string->length; }

1. __emu/io_builtins_xsb.h__ \[End Of File\]

Add:

    ////////
    char *canonical_term(CTXTdeclc Cell prologterm, int letter_flag);
    int cannonical_term_size(CTXTdeclc);


### Building QDBM

In order to use the B+ Tree library, the QDBM librarys must be build and installed on your machine. The process is pretty straightforward, and more information can be found [here](http://fallabs.com/qdbm/spex.html#installation).

#### Linux Users:

To build on linux, use the following commands from the qdbm directory:

  `./configure`

  `make`

  `make check`
  
  `make install`

#### MAC Users:

Follow a similiar process:

To build on linux, use the following commands from the qdbm directory:

  `./configure`

  `make mac`

  `make check-mac`
  
  `make install-mac`

#### Windows and other systems 
See the [installation page](http://fallabs.com/qdbm/spex.html#installation).

### Usage

This section describes the basic usage tutorial for the library. Currently the work must be done from a working directory in the folder with the library files. Also note that QDBM libraries must be installed on you machine (see above).

#### Initializing a B+ Tree Index

To initialize a B+ Tree Index, you can use the bt_init/3 predicate. The call mode for bt_init/3 is:
    
    bt_init(+Predicate/Arity, +ArgumentNumber, -IndexHandle).

For example, to create an index on the second argument of the word/2 predicate, use:

    ?- bt_init(word/2, 2, X).
    B+ Tree (db_2_2_word) Size: 0

    X = 0;

The value returned in X will be used later to make queries against this index later.

#### Inserting Values into a B+ Tree.

Once you have initialized a B+ Tree for a given predicate, you can insert values into it using bt_insert/2. bt_insert/2 is called with the following mode:
    
    bt_insert(+Handle, +Predicate).

__Note the predicate name and arity must match that which the tree was created.__

You can explicity pass the integer value returned from init, or chain it together into a query or rule:

    ?- bt_init(word/2, 1, _Handle), bt_insert(_Handle, word(noun, computer)).
    B+ Tree (db_1_2_word) Size: 3
    Insert Term: (Key: noun, Value: word(noun,computer))
    B+ Tree (word) Size: 4

#### Closing a B+ Tree

You _MUST_ close a B+ Tree when inserting values to ensure that the values are written to disk safely. You close a B+ Tree by using bt_close/1. The only argument is the tree handle number. For example, a complete process from opening a tree, inserting a value and closing the tree would look like this:

    ?- bt_init(word/2,1,Handle), bt_insert(Handle, word(noun, computer)), bt_close(Handle).
    B+ Tree (db_1_2_word) Size: 8
    Insert Term: (Key: noun, Value: word(noun,computer))

    Handle = 0;

This would open the tree, insert the term of word/2 and close the tree to ensure changes are written to disk. __Note: Once a tree is closed, that handle is no longer valid.__ Changes can be made to the same tree, but another call to bt_init will be required.

#### Querying the Tree

Argueably the most important functionality in the b+ Tree is the types of queries that can be made. Read below to find the different calls that can be made to query the B+ Tree.


