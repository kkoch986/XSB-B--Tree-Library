// Copyright (c) 1994 Darren Erik Vengroff
//
// File: scan_count.cpp
// Author: Darren Erik Vengroff <darrenv@eecs.umich.edu>
// Created: 10/6/94
//
// A scan object to generate a stream of intergers in ascending order.
//


static char scan_count_id[] = "$Id: scan_count.cpp,v 1.4 2004/08/12 15:15:11 jan Exp $";

#include "app_config.h"
#include "scan_count.h"

AMI_err scan_count::initialize(void)
{
    called = 0;
    ii = 0;
    return AMI_ERROR_NO_ERROR;
};

scan_count::scan_count(TPIE_OS_OFFSET max) :
        maximum(max),
        ii(0)
{
};

AMI_err scan_count::operate(TPIE_OS_OFFSET *out1, AMI_SCAN_FLAG *sf)
{
    called++;
    *out1 = ++ii;
    return (*sf = (ii <= maximum)) ? AMI_SCAN_CONTINUE : AMI_SCAN_DONE;
};

