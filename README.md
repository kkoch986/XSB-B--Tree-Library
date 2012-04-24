XSB-B--Tree-Library
===================

My work in progress B+Tree Library for XSB Prolog


To Use:
=======

Open xsb and consult the make script:

```?- [make].```

Now run the ```make``` command:

```?- make.```

You can also run ```nuke``` which will delete any build files as well as any b+ tree files generated (you will lose your b+ tree data this way).

```?- nuke. ```

If you have a build and don't need to rebuild, you can simply consult ```bt```:

```?- [bt].```


B+ Tree Commands
================

You must always initialize and close the tree when you are working, to start call the init:

```?- bt_init.```

You can now insert entries like so: 

_NOTE: currently this only works with atoms_

```
?- bt_insert(a).
?- bt_insert(b).
?- bt_insert(c).
```

To retrieve the atoms, use ```bt_get/2```:

```
?- bt_get(a, X).
X = a;
```

Finally, to close the tree and save all the data to disk:

```?- bt_close.```
