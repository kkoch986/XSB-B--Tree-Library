//
// File: parse_args.cpp
// Author: Darren Erik Vengroff <darrenv@eecs.umich.edu>
// Created: 10/7/94
//

static char parse_args_id[] = "$Id: parse_args.cpp,v 1.13 2003/09/11 17:50:57 jan Exp $";

#include <portability.h>

#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <iostream>

#include "app_config.h"
#include "parse_args.h"

static size_t parse_number(char *s) {
  size_t n; 
  size_t mult = 1;
  size_t len = strlen(s);
  if(isalpha(s[len-1])) {
    switch(s[len-1]) {
    case 'M':
      mult = 1 << 20;
      break;
    case 'K':
      mult = 1 << 10;
      break;
    default:
      cerr << "bad number format: " << s << "\n";
      exit(-1);
      break;
    }
    s[len-1] = '\0';
  }
  n = atol(s);
  return n * mult;
}


void parse_args(int argc, char **argv, const char *as_opts,
                void (*parse_app_opt)(char opt, char *optarg))
{
  static char standard_opts[] = "m:t:z:v";
  
  // All options, standard and application specific.
  char *all_opts;

  if (as_opts != NULL) {
    unsigned int l_aso;
    
    all_opts = new char[sizeof(standard_opts) + (l_aso = strlen(as_opts))]; 
    strncpy(all_opts, standard_opts, sizeof(standard_opts));
    strncat(all_opts, as_opts, l_aso);
  } else {
    all_opts = standard_opts;
  }
  
  char c;
  
  optarg = NULL;
  while((c = getopt(argc, argv, all_opts)) != -1) {
    switch (c) {
    case 'v':
      verbose = true;
      break;
    case 'm':
      test_mm_size = parse_number(optarg);
      break;                
    case 't':
      test_size = parse_number(optarg);
      break;
    case 'z':
      random_seed = atol(optarg);
      break;
    default:
      parse_app_opt(c, optarg);
      break;
    }
  }
}

