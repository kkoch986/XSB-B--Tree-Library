// Copyright (c) 1995 Darren Vengroff
//
// File: scan_inner_product.h
// Author: Darren Vengroff <darrenv@eecs.umich.edu>
// Created: 3/23/95
//
// $Id: scan_inner_product.h,v 1.2 1999/02/03 22:07:09 tavi Exp $
//
#ifndef _SCAN_INNER_PRODUCT_H
#define _SCAN_INNER_PRODUCT_H

template<class T>
class scan_inner_product : AMI_scan_object {
private:
    T running_sum;
public:
    scan_inner_product() {};
    virtual ~scan_inner_product() {};
    T result(void)
    {
        return running_sum;
    };
    AMI_err initialize(void)
    {
        running_sum = 0;
        return AMI_ERROR_NO_ERROR;
    };
    inline AMI_err operate(const T &in1, const T &in2, AMI_SCAN_FLAG *sf)
    {
        if (sf[0]) {
            running_sum += in1 * in2;
            return AMI_SCAN_CONTINUE;
        } else {
            return AMI_SCAN_DONE;
        }
    };
};

#endif // _SCAN_INNER_PRODUCT_H 
