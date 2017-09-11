 limitations under the License.
 */

#include "../wrapper/xgboost_wrapper.h"
#include "xgboost4j_wrapper.h"

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
    long out[1];
    const char* fname = jenv->GetStringUTFChars(jfname, 0);
    int ret = XGDMatrixCreateFromFile(fname, jsilent, &result);
    out[0] = (long) result;
    if (fname) jenv->ReleaseStringUTFChars(jfname, fname);    
    jenv->SetLongArrayRegion(jout, 0, 1, (const jlong *) out);
    return ret;
}

/*
