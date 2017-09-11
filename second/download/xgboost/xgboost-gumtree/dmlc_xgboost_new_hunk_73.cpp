 limitations under the License.
 */

#include "../wrapper/xgboost_wrapper.h"
#include "xgboost4j_wrapper.h"
#include <cstring>

//helper functions
//set handle
void setHandle(JNIEnv *jenv, jlongArray jhandle, void* handle) {
    long out[1];
    out[0] = (long) handle;
    jenv->SetLongArrayRegion(jhandle, 0, 1, (const jlong*) out);
}

JNIEXPORT jstring JNICALL Java_org_dmlc_xgboost4j_wrapper_XgboostJNI_XGBGetLastError
  (JNIEnv *jenv, jclass jcls) {
    jstring jresult = 0 ;
    const char* result = XGBGetLastError();
    if (result) jresult = jenv->NewStringUTF(result);
    return jresult;
}

JNIEXPORT jint JNICALL Java_org_dmlc_xgboost4j_wrapper_XgboostJNI_XGDMatrixCreateFromFile
  (JNIEnv *jenv, jclass jcls, jstring jfname, jint jsilent, jlongArray jout) {
    DMatrixHandle result;
    const char* fname = jenv->GetStringUTFChars(jfname, 0);
    int ret = XGDMatrixCreateFromFile(fname, jsilent, &result);
    if (fname) jenv->ReleaseStringUTFChars(jfname, fname);    
    setHandle(jenv, jout, result);
    return ret;
}

/*
