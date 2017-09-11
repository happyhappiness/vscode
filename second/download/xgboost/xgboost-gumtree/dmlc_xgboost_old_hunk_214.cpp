#include "../wrapper/xgboost_wrapper.h"
#include "xgboost4j_wrapper.h"

JNIEXPORT jlong JNICALL Java_org_dmlc_xgboost4j_wrapper_XgboostJNI_XGDMatrixCreateFromFile
  (JNIEnv *jenv, jclass jcls, jstring jfname, jint jsilent) {
    jlong jresult = 0 ;
    char *fname = (char *) 0 ;
    int silent;
    void *result = 0 ;
    fname = 0;
    if (jfname) {
        fname = (char *)jenv->GetStringUTFChars(jfname, 0);
        if (!fname) return 0;
    }
    silent = (int)jsilent; 
    result = (void *)XGDMatrixCreateFromFile((char const *)fname, silent);
    *(void **)&jresult = result; 
    if (fname) jenv->ReleaseStringUTFChars(jfname, (const char *)fname);
    return jresult;
}

