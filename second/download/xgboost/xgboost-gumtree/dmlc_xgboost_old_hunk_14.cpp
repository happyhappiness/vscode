#include <vector>
#include <string>

//helper functions
//set handle
void setHandle(JNIEnv *jenv, jlongArray jhandle, void* handle) {
  long out = (long) handle;
  jenv->SetLongArrayRegion(jhandle, 0, 1, &out);
}

JNIEXPORT jstring JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_XGBGetLastError
  (JNIEnv *jenv, jclass jcls) {
  jstring jresult = 0;
