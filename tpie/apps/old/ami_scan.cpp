// Copyright (c) 1994 Darren Erik Vengroff
//
// File: ami_scan.cpp
// Author: Darren Erik Vengroff <dev@cs.duke.edu>
// Created: 5/26/94
//

static char ami_scan_id[] = "$Id: ami_scan.cpp,v 1.6 2003/04/20 23:51:40 tavi Exp $";

#define BTE_STREAM_MMAP_BLOCK_FACTOR 32

#include <iostream>
using std::cout;

// Use logs.
//#define TPL_LOGGING 1
#include <tpie_log.h>

#define BTE_STREAM_IMP_MMAP	// Use the MMAP version of BTE streams.

#include <ami_scan.h>

// A scan object to generate output.
template<int MAX> class count_scan : AMI_scan_object {
private:
    int ii;
public:    
    AMI_err initialize(void);
    inline AMI_err operate(int *out1, AMI_SCAN_FLAG *sf);
};

template<int MAX>
AMI_err count_scan<MAX>::initialize(void)
{
    ii = 0;
    return AMI_ERROR_NO_ERROR;
};

template<int MAX>
AMI_err count_scan<MAX>::operate(int *out1, AMI_SCAN_FLAG *sf)
{
    *out1 = ii++;
    return (*sf = (ii <= MAX)) ? AMI_SCAN_CONTINUE : AMI_SCAN_DONE;
};


// A scan object to square numeric types.
template<class T> class square_scan : AMI_scan_object {
public:    
    AMI_err initialize(void);
    inline AMI_err operate(const T &in, AMI_SCAN_FLAG *sfin,
                    T *out, AMI_SCAN_FLAG *sfout);
};

template<class T>
AMI_err square_scan<T>::initialize(void)
{
    return AMI_ERROR_NO_ERROR;
};

template<class T>
AMI_err square_scan<T>::operate(const T &in, AMI_SCAN_FLAG *sfin,
                                T *out, AMI_SCAN_FLAG *sfout)
{
    if (*sfout = *sfin) {
        *out = in * in;
        return AMI_SCAN_CONTINUE;
    } else {
        return AMI_SCAN_DONE;
    }
};


int main(int argc, char **argv)
{
    AMI_err ae;

    AMI_STREAM<int> amis1;
    AMI_STREAM<int> amis2;
        
    // Write some ints.
    {
        count_scan<1000> cs;
    
        ae = AMI_scan(&cs, (AMI_STREAM<int> *)&amis1);
    }

    cout << "Wrote them.\n";
        
    // Square them.
    {
        square_scan<int> ss;
        
        ae = AMI_scan((AMI_STREAM<int> *)&amis1, &ss, 
		      (AMI_STREAM<int> *)&amis2);
    }
    
    cout << "Squared them.\n";

    return 0;
}
