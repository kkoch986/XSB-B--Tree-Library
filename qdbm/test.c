//#include "xsb_config.h"
#include <depot.h>
#include <cabin.h>
#include <villa.h>
#include <stdlib.h>
#include <stdio.h>

#define NAME     "mikio"
#define NUMBER   "000-1234-5678"
#define DBNAME   "xsbdb_a_2"

int main(int argc, char **argv){
  VILLA *villa;
  CBLIST *val;

  /* open the database */
  if(!(villa = vlopen(DBNAME, VL_OWRITER | VL_OCREAT, VL_CMPLEX))){
    fprintf(stderr, "vlopen: %s\n", dperrmsg(dpecode));
    return 1;
  }

  /* store the record */
  if(!vlput(villa, NAME, -1, NUMBER, -1, VL_DDUP)){
    fprintf(stderr, "vlput: %s\n", dperrmsg(dpecode));
  }

  /* retrieve the record */
  if(!(val = vlgetlist(villa, NAME, -1))) {
    fprintf(stderr, "vlget: %s\n", dperrmsg(dpecode)); 
  } else {
    printf("Found %i Entries: \n", cblistnum(val));

    int *sp;
    char *element = cblistpop(val, sp);
    while(element != NULL)
    {      
      printf("Number: %s\n", element);
      free(element);
      element = cblistpop(val, sp);
    }

    cblistclose(val);
  }


  /* close the database */
  if(!vlclose(villa)){
    fprintf(stderr, "vlclose: %s\n", dperrmsg(dpecode));
    return 1;
  }

  return 0;
}