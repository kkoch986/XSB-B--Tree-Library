/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class qdbm_Depot */

#ifndef _Included_qdbm_Depot
#define _Included_qdbm_Depot
#ifdef __cplusplus
extern "C" {
#endif
#undef qdbm_Depot_ENOERR
#define qdbm_Depot_ENOERR 0L
#undef qdbm_Depot_EFATAL
#define qdbm_Depot_EFATAL 1L
#undef qdbm_Depot_EMODE
#define qdbm_Depot_EMODE 2L
#undef qdbm_Depot_EBROKEN
#define qdbm_Depot_EBROKEN 3L
#undef qdbm_Depot_EKEEP
#define qdbm_Depot_EKEEP 4L
#undef qdbm_Depot_ENOITEM
#define qdbm_Depot_ENOITEM 5L
#undef qdbm_Depot_EALLOC
#define qdbm_Depot_EALLOC 6L
#undef qdbm_Depot_EMAP
#define qdbm_Depot_EMAP 7L
#undef qdbm_Depot_EOPEN
#define qdbm_Depot_EOPEN 8L
#undef qdbm_Depot_ECLOSE
#define qdbm_Depot_ECLOSE 9L
#undef qdbm_Depot_ETRUNC
#define qdbm_Depot_ETRUNC 10L
#undef qdbm_Depot_ESYNC
#define qdbm_Depot_ESYNC 11L
#undef qdbm_Depot_ESTAT
#define qdbm_Depot_ESTAT 12L
#undef qdbm_Depot_ESEEK
#define qdbm_Depot_ESEEK 13L
#undef qdbm_Depot_EREAD
#define qdbm_Depot_EREAD 14L
#undef qdbm_Depot_EWRITE
#define qdbm_Depot_EWRITE 15L
#undef qdbm_Depot_ELOCK
#define qdbm_Depot_ELOCK 16L
#undef qdbm_Depot_EUNLINK
#define qdbm_Depot_EUNLINK 17L
#undef qdbm_Depot_EMKDIR
#define qdbm_Depot_EMKDIR 18L
#undef qdbm_Depot_ERMDIR
#define qdbm_Depot_ERMDIR 19L
#undef qdbm_Depot_EMISC
#define qdbm_Depot_EMISC 20L
#undef qdbm_Depot_OREADER
#define qdbm_Depot_OREADER 1L
#undef qdbm_Depot_OWRITER
#define qdbm_Depot_OWRITER 2L
#undef qdbm_Depot_OCREAT
#define qdbm_Depot_OCREAT 4L
#undef qdbm_Depot_OTRUNC
#define qdbm_Depot_OTRUNC 8L
#undef qdbm_Depot_ONOLCK
#define qdbm_Depot_ONOLCK 16L
#undef qdbm_Depot_OLCKNB
#define qdbm_Depot_OLCKNB 32L
#undef qdbm_Depot_OSPARSE
#define qdbm_Depot_OSPARSE 64L
#undef qdbm_Depot_DOVER
#define qdbm_Depot_DOVER 0L
#undef qdbm_Depot_DKEEP
#define qdbm_Depot_DKEEP 1L
#undef qdbm_Depot_DCAT
#define qdbm_Depot_DCAT 2L
/* Inaccessible static: class_00024qdbm_00024ADBM */
/*
 * Class:     qdbm_Depot
 * Method:    dpinit
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_qdbm_Depot_dpinit
  (JNIEnv *, jclass);

/*
 * Class:     qdbm_Depot
 * Method:    dpversion
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_qdbm_Depot_dpversion
  (JNIEnv *, jclass);

/*
 * Class:     qdbm_Depot
 * Method:    dpecode
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_qdbm_Depot_dpecode
  (JNIEnv *, jclass);

/*
 * Class:     qdbm_Depot
 * Method:    dperrmsg
 * Signature: (I)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_qdbm_Depot_dperrmsg
  (JNIEnv *, jclass, jint);

/*
 * Class:     qdbm_Depot
 * Method:    dpopen
 * Signature: (Ljava/lang/String;II)I
 */
JNIEXPORT jint JNICALL Java_qdbm_Depot_dpopen
  (JNIEnv *, jclass, jstring, jint, jint);

/*
 * Class:     qdbm_Depot
 * Method:    dpclose
 * Signature: (I)I
 */
JNIEXPORT jint JNICALL Java_qdbm_Depot_dpclose
  (JNIEnv *, jclass, jint);

/*
 * Class:     qdbm_Depot
 * Method:    dpput
 * Signature: (I[BI[BII)I
 */
JNIEXPORT jint JNICALL Java_qdbm_Depot_dpput
  (JNIEnv *, jclass, jint, jbyteArray, jint, jbyteArray, jint, jint);

/*
 * Class:     qdbm_Depot
 * Method:    dpout
 * Signature: (I[BI)I
 */
JNIEXPORT jint JNICALL Java_qdbm_Depot_dpout
  (JNIEnv *, jclass, jint, jbyteArray, jint);

/*
 * Class:     qdbm_Depot
 * Method:    dpget
 * Signature: (I[BIII)[B
 */
JNIEXPORT jbyteArray JNICALL Java_qdbm_Depot_dpget
  (JNIEnv *, jclass, jint, jbyteArray, jint, jint, jint);

/*
 * Class:     qdbm_Depot
 * Method:    dpvsiz
 * Signature: (I[BI)I
 */
JNIEXPORT jint JNICALL Java_qdbm_Depot_dpvsiz
  (JNIEnv *, jclass, jint, jbyteArray, jint);

/*
 * Class:     qdbm_Depot
 * Method:    dpiterinit
 * Signature: (I)I
 */
JNIEXPORT jint JNICALL Java_qdbm_Depot_dpiterinit
  (JNIEnv *, jclass, jint);

/*
 * Class:     qdbm_Depot
 * Method:    dpiternext
 * Signature: (I)[B
 */
JNIEXPORT jbyteArray JNICALL Java_qdbm_Depot_dpiternext
  (JNIEnv *, jclass, jint);

/*
 * Class:     qdbm_Depot
 * Method:    dpsetalign
 * Signature: (II)I
 */
JNIEXPORT jint JNICALL Java_qdbm_Depot_dpsetalign
  (JNIEnv *, jclass, jint, jint);

/*
 * Class:     qdbm_Depot
 * Method:    dpsetfbpsiz
 * Signature: (II)I
 */
JNIEXPORT jint JNICALL Java_qdbm_Depot_dpsetfbpsiz
  (JNIEnv *, jclass, jint, jint);

/*
 * Class:     qdbm_Depot
 * Method:    dpsync
 * Signature: (I)I
 */
JNIEXPORT jint JNICALL Java_qdbm_Depot_dpsync
  (JNIEnv *, jclass, jint);

/*
 * Class:     qdbm_Depot
 * Method:    dpoptimize
 * Signature: (II)I
 */
JNIEXPORT jint JNICALL Java_qdbm_Depot_dpoptimize
  (JNIEnv *, jclass, jint, jint);

/*
 * Class:     qdbm_Depot
 * Method:    dpname
 * Signature: (I)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_qdbm_Depot_dpname
  (JNIEnv *, jclass, jint);

/*
 * Class:     qdbm_Depot
 * Method:    dpfsiz
 * Signature: (I)I
 */
JNIEXPORT jint JNICALL Java_qdbm_Depot_dpfsiz
  (JNIEnv *, jclass, jint);

/*
 * Class:     qdbm_Depot
 * Method:    dpbnum
 * Signature: (I)I
 */
JNIEXPORT jint JNICALL Java_qdbm_Depot_dpbnum
  (JNIEnv *, jclass, jint);

/*
 * Class:     qdbm_Depot
 * Method:    dpbusenum
 * Signature: (I)I
 */
JNIEXPORT jint JNICALL Java_qdbm_Depot_dpbusenum
  (JNIEnv *, jclass, jint);

/*
 * Class:     qdbm_Depot
 * Method:    dprnum
 * Signature: (I)I
 */
JNIEXPORT jint JNICALL Java_qdbm_Depot_dprnum
  (JNIEnv *, jclass, jint);

/*
 * Class:     qdbm_Depot
 * Method:    dpwritable
 * Signature: (I)I
 */
JNIEXPORT jint JNICALL Java_qdbm_Depot_dpwritable
  (JNIEnv *, jclass, jint);

/*
 * Class:     qdbm_Depot
 * Method:    dpfatalerror
 * Signature: (I)I
 */
JNIEXPORT jint JNICALL Java_qdbm_Depot_dpfatalerror
  (JNIEnv *, jclass, jint);

/*
 * Class:     qdbm_Depot
 * Method:    dpinode
 * Signature: (I)I
 */
JNIEXPORT jint JNICALL Java_qdbm_Depot_dpinode
  (JNIEnv *, jclass, jint);

/*
 * Class:     qdbm_Depot
 * Method:    dpmtime
 * Signature: (I)J
 */
JNIEXPORT jlong JNICALL Java_qdbm_Depot_dpmtime
  (JNIEnv *, jclass, jint);

/*
 * Class:     qdbm_Depot
 * Method:    dpremove
 * Signature: (Ljava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_qdbm_Depot_dpremove
  (JNIEnv *, jclass, jstring);

/*
 * Class:     qdbm_Depot
 * Method:    dpsnaffle
 * Signature: (Ljava/lang/String;[BI)[B
 */
JNIEXPORT jbyteArray JNICALL Java_qdbm_Depot_dpsnaffle
  (JNIEnv *, jclass, jstring, jbyteArray, jint);

#ifdef __cplusplus
}
#endif
#endif
