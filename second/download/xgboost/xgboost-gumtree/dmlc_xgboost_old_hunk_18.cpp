    jenv->SetLongArrayRegion(jhandle, 0, 1, (const jlong*) out);
}

JNIEXPORT jstring JNICALL Java_org_dmlc_xgboost4j_XgboostJNI_XGBGetLastError
  (JNIEnv *jenv, jclass jcls) {
    jstring jresult = 0 ;
    const char* result = XGBGetLastError();
    if (result) jresult = jenv->NewStringUTF(result);
    return jresult;
}

JNIEXPORT jint JNICALL Java_org_dmlc_xgboost4j_XgboostJNI_XGDMatrixCreateFromFile
  (JNIEnv *jenv, jclass jcls, jstring jfname, jint jsilent, jlongArray jout) {
    DMatrixHandle result;
    const char* fname = jenv->GetStringUTFChars(jfname, 0);
