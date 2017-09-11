 limitations under the License.
 */

#include <jni.h>
#include "../wrapper/xgboost_wrapper.h"
#include "xgboost4j_wrapper.h"

JNIEXPORT jstring JNICALL Java_org_dmlc_xgboost4j_wrapper_XgboostJNI_XGBGetLastError
  (JNIEnv *jenv, jclass jcls) {
    jstring jresult = 0 ;
    char* result = 0;
    result = (char *)XGBGetLastError();
    if (result) jresult = jenv->NewStringUTF((const char *)result);
    return jresult;
}

JNIEXPORT jint JNICALL Java_org_dmlc_xgboost4j_wrapper_XgboostJNI_XGDMatrixCreateFromFile
  (JNIEnv *jenv, jclass jcls, jstring jfname, jint jsilent, jlongArray jout) {
    jint jresult = 0 ;
    char *fname = (char *) 0 ;
    int silent;
    void* result[1];
    unsigned long out[1];
    
    fname = (char *)jenv->GetStringUTFChars(jfname, 0);
    
    silent = (int)jsilent; 
    jresult = (jint) XGDMatrixCreateFromFile((char const *)fname, silent, result);
    
    
    *(void **)&out[0] = *result;

    if (fname) jenv->ReleaseStringUTFChars(jfname, (const char *)fname);
    
    jenv->SetLongArrayRegion(jout, 0, 1, (const jlong *) out);
    return jresult;
}

/*
