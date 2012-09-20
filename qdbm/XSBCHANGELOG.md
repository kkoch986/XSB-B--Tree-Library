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
