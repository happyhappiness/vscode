}

/*
 * Class:     ml_dmlc_xgboost4j_java_XGBoostJNI
 * Method:    XGBGetLastError
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_ml_dmlc_xgboost4j_java_XGBoostJNI_XGBGetLastError
  (JNIEnv *jenv, jclass jcls) {
  jstring jresult = 0;
  const char* result = XGBGetLastError();
