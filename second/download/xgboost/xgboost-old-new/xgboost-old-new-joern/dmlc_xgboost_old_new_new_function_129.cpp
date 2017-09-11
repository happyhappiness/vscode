JNIEXPORT jstring JNICALL Java_org_dmlc_xgboost4j_wrapper_XgboostJNI_XGBGetLastError
  (JNIEnv *jenv, jclass jcls) {
    jstring jresult = 0 ;
    char* result = 0;
    result = (char *)XGBGetLastError();
    if (result) jresult = jenv->NewStringUTF((const char *)result);
    return jresult;
}