@@ -16,21 +16,34 @@
 #include "../wrapper/xgboost_wrapper.h"
 #include "xgboost4j_wrapper.h"
 
-JNIEXPORT jlong JNICALL Java_org_dmlc_xgboost4j_wrapper_XgboostJNI_XGDMatrixCreateFromFile
-  (JNIEnv *jenv, jclass jcls, jstring jfname, jint jsilent) {
-    jlong jresult = 0 ;
+JNIEXPORT jstring JNICALL Java_org_dmlc_xgboost4j_wrapper_XgboostJNI_XGBGetLastError
+  (JNIEnv *jenv, jclass jcls) {
+    jstring jresult = 0 ;
+    char* result = 0;
+    result = (char *)XGBGetLastError();
+    if (result) jresult = jenv->NewStringUTF((const char *)result);
+    return jresult;
+}
+
+JNIEXPORT jint JNICALL Java_org_dmlc_xgboost4j_wrapper_XgboostJNI_XGDMatrixCreateFromFile
+  (JNIEnv *jenv, jclass jcls, jstring jfname, jint jsilent, jlongArray jout) {
+    jint jresult = 0 ;
     char *fname = (char *) 0 ;
     int silent;
-    void *result = 0 ;
-    fname = 0;
-    if (jfname) {
-        fname = (char *)jenv->GetStringUTFChars(jfname, 0);
-        if (!fname) return 0;
-    }
+    void* result[1];
+    unsigned long out[1];
+    
+    fname = (char *)jenv->GetStringUTFChars(jfname, 0);
+    
     silent = (int)jsilent; 
-    result = (void *)XGDMatrixCreateFromFile((char const *)fname, silent);
-    *(void **)&jresult = result; 
+    jresult = (jint) XGDMatrixCreateFromFile((char const *)fname, silent, result);
+    
+    
+    *(void **)&out[0] = *result;
+
     if (fname) jenv->ReleaseStringUTFChars(jfname, (const char *)fname);
+    
+    jenv->SetLongArrayRegion(jout, 0, 1, (const jlong *) out);
     return jresult;
 }
 
@@ -39,21 +52,23 @@ JNIEXPORT jlong JNICALL Java_org_dmlc_xgboost4j_wrapper_XgboostJNI_XGDMatrixCrea
  * Method:    XGDMatrixCreateFromCSR
  * Signature: ([J[J[F)J
  */
-JNIEXPORT jlong JNICALL Java_org_dmlc_xgboost4j_wrapper_XgboostJNI_XGDMatrixCreateFromCSR
-  (JNIEnv *jenv, jclass jcls, jlongArray jindptr, jintArray jindices, jfloatArray jdata) {
-    jlong jresult = 0 ;
+JNIEXPORT jint JNICALL Java_org_dmlc_xgboost4j_wrapper_XgboostJNI_XGDMatrixCreateFromCSR
+  (JNIEnv *jenv, jclass jcls, jlongArray jindptr, jintArray jindices, jfloatArray jdata, jlongArray jout) {
+    jint jresult = 0 ;
     bst_ulong nindptr ;
     bst_ulong nelem;
-    void *result = 0 ;
+    void *result[1];
+    unsigned long out[1];
   
     jlong* indptr = jenv->GetLongArrayElements(jindptr, 0);
     jint* indices = jenv->GetIntArrayElements(jindices, 0);
     jfloat* data = jenv->GetFloatArrayElements(jdata, 0); 
     nindptr = (bst_ulong)jenv->GetArrayLength(jindptr); 
     nelem = (bst_ulong)jenv->GetArrayLength(jdata); 
 
-    result = (void *)XGDMatrixCreateFromCSR((unsigned long const *)indptr, (unsigned int const *)indices, (float const *)data, nindptr, nelem);
-    *(void **)&jresult = result; 
+    jresult = (jint) XGDMatrixCreateFromCSR((unsigned long const *)indptr, (unsigned int const *)indices, (float const *)data, nindptr, nelem, result);    
+    *(void **)&out[0] = *result;
+    jenv->SetLongArrayRegion(jout, 0, 1, (const jlong *) out);
     
     //release
     jenv->ReleaseLongArrayElements(jindptr, indptr, 0);
@@ -68,21 +83,23 @@ JNIEXPORT jlong JNICALL Java_org_dmlc_xgboost4j_wrapper_XgboostJNI_XGDMatrixCrea
  * Method:    XGDMatrixCreateFromCSC
  * Signature: ([J[J[F)J
  */
-JNIEXPORT jlong JNICALL Java_org_dmlc_xgboost4j_wrapper_XgboostJNI_XGDMatrixCreateFromCSC
-  (JNIEnv *jenv, jclass jcls, jlongArray jindptr, jintArray jindices, jfloatArray jdata) {
-    jlong jresult = 0 ;
+JNIEXPORT jint JNICALL Java_org_dmlc_xgboost4j_wrapper_XgboostJNI_XGDMatrixCreateFromCSC
+  (JNIEnv *jenv, jclass jcls, jlongArray jindptr, jintArray jindices, jfloatArray jdata, jlongArray jout) {
+    jint jresult = 0;
     bst_ulong nindptr ;
     bst_ulong nelem;
-    void *result = 0 ;
+    void *result[1];
+    unsigned long out[1];
   
     jlong* indptr = jenv->GetLongArrayElements(jindptr, NULL);
     jint* indices = jenv->GetIntArrayElements(jindices, 0);
     jfloat* data = jenv->GetFloatArrayElements(jdata, NULL);
     nindptr = (bst_ulong)jenv->GetArrayLength(jindptr); 
     nelem = (bst_ulong)jenv->GetArrayLength(jdata); 
 
-    result = (void *)XGDMatrixCreateFromCSC((unsigned long const *)indptr, (unsigned int const *)indices, (float const *)data, nindptr, nelem);  
-    *(void **)&jresult = result; 
+    jresult = (jint) XGDMatrixCreateFromCSC((unsigned long const *)indptr, (unsigned int const *)indices, (float const *)data, nindptr, nelem, result);  
+    *(void **)&out[0] = *result;
+    jenv->SetLongArrayRegion(jout, 0, 1, (const jlong *) out);
     
     //release
     jenv->ReleaseLongArrayElements(jindptr, indptr, 0);
@@ -97,21 +114,24 @@ JNIEXPORT jlong JNICALL Java_org_dmlc_xgboost4j_wrapper_XgboostJNI_XGDMatrixCrea
  * Method:    XGDMatrixCreateFromMat
  * Signature: ([FIIF)J
  */
-JNIEXPORT jlong JNICALL Java_org_dmlc_xgboost4j_wrapper_XgboostJNI_XGDMatrixCreateFromMat
-  (JNIEnv *jenv, jclass jcls, jfloatArray jdata, jint jnrow, jint jncol, jfloat jmiss) {
-    jlong jresult = 0 ;
+JNIEXPORT jint JNICALL Java_org_dmlc_xgboost4j_wrapper_XgboostJNI_XGDMatrixCreateFromMat
+  (JNIEnv *jenv, jclass jcls, jfloatArray jdata, jint jnrow, jint jncol, jfloat jmiss, jlongArray jout) {
+    jint jresult = 0 ;
     bst_ulong nrow ;
     bst_ulong ncol ;
     float miss ;
-    void *result = 0 ;
+    void *result[1];
+    unsigned long out[1];
   
 
     jfloat* data = jenv->GetFloatArrayElements(jdata, 0);
     nrow = (bst_ulong)jnrow; 
     ncol = (bst_ulong)jncol; 
     miss = (float)jmiss; 
-    result = (void *)XGDMatrixCreateFromMat((float const *)data, nrow, ncol, miss);
-    *(void **)&jresult = result; 
+    
+    jresult = (jint) XGDMatrixCreateFromMat((float const *)data, nrow, ncol, miss, result);
+    *(void **)&out[0] = *result;
+    jenv->SetLongArrayRegion(jout, 0, 1, (const jlong *) out);
   
     //release
     jenv->ReleaseFloatArrayElements(jdata, data, 0);
@@ -124,19 +144,21 @@ JNIEXPORT jlong JNICALL Java_org_dmlc_xgboost4j_wrapper_XgboostJNI_XGDMatrixCrea
  * Method:    XGDMatrixSliceDMatrix
  * Signature: (J[I)J
  */
-JNIEXPORT jlong JNICALL Java_org_dmlc_xgboost4j_wrapper_XgboostJNI_XGDMatrixSliceDMatrix
-  (JNIEnv *jenv, jclass jcls, jlong jhandle, jintArray jindexset) {
-    jlong jresult = 0 ;
+JNIEXPORT jint JNICALL Java_org_dmlc_xgboost4j_wrapper_XgboostJNI_XGDMatrixSliceDMatrix
+  (JNIEnv *jenv, jclass jcls, jlong jhandle, jintArray jindexset, jlongArray jout) {
+    jint jresult = 0 ;
     void *handle = (void *) 0 ;
     bst_ulong len;
-    void *result = 0 ;
+    void *result[1];
+    unsigned long out[1];
 
     jint* indexset = jenv->GetIntArrayElements(jindexset, 0);
     handle = *(void **)&jhandle; 
     len = (bst_ulong)jenv->GetArrayLength(jindexset); 
 
-    result = (void *)XGDMatrixSliceDMatrix(handle, (int const *)indexset, len);
-    *(void **)&jresult = result;
+    jresult = (jint) XGDMatrixSliceDMatrix(handle, (int const *)indexset, len, result);
+    *(void **)&out[0] = *result;
+    jenv->SetLongArrayRegion(jout, 0, 1, (const jlong *) out);
     
     //release
     jenv->ReleaseIntArrayElements(jindexset, indexset, 0);
@@ -149,136 +171,146 @@ JNIEXPORT jlong JNICALL Java_org_dmlc_xgboost4j_wrapper_XgboostJNI_XGDMatrixSlic
  * Method:    XGDMatrixFree
  * Signature: (J)V
  */
-JNIEXPORT void JNICALL Java_org_dmlc_xgboost4j_wrapper_XgboostJNI_XGDMatrixFree
+JNIEXPORT jint JNICALL Java_org_dmlc_xgboost4j_wrapper_XgboostJNI_XGDMatrixFree
   (JNIEnv *jenv, jclass jcls, jlong jhandle) {
+    jint jresult = 0;
     void *handle = (void *) 0 ;
     handle = *(void **)&jhandle; 
-    XGDMatrixFree(handle);
+    jresult = (jint) XGDMatrixFree(handle);
+    return jresult;
 }
 
 /*
  * Class:     org_dmlc_xgboost4j_wrapper_XgboostJNI
  * Method:    XGDMatrixSaveBinary
  * Signature: (JLjava/lang/String;I)V
  */
-JNIEXPORT void JNICALL Java_org_dmlc_xgboost4j_wrapper_XgboostJNI_XGDMatrixSaveBinary
+JNIEXPORT jint JNICALL Java_org_dmlc_xgboost4j_wrapper_XgboostJNI_XGDMatrixSaveBinary
   (JNIEnv *jenv, jclass jcls, jlong jhandle, jstring jfname, jint jsilent) {
+    jint jresult = 0;
     void *handle = (void *) 0 ;
     char *fname = (char *) 0 ;
     int silent ;
     handle = *(void **)&jhandle; 
     fname = 0;
-    if (jfname) {
-        fname = (char *)jenv->GetStringUTFChars(jfname, 0);
-        if (!fname) return ;
-    }
+    fname = (char *)jenv->GetStringUTFChars(jfname, 0);
+
     silent = (int)jsilent; 
-    XGDMatrixSaveBinary(handle, (char const *)fname, silent);
+    jresult = (jint) XGDMatrixSaveBinary(handle, (char const *)fname, silent);
     if (fname) jenv->ReleaseStringUTFChars(jfname, (const char *)fname);
+    
+    return jresult;
 }
 
 /*
  * Class:     org_dmlc_xgboost4j_wrapper_XgboostJNI
  * Method:    XGDMatrixSetFloatInfo
  * Signature: (JLjava/lang/String;[F)V
  */
-JNIEXPORT void JNICALL Java_org_dmlc_xgboost4j_wrapper_XgboostJNI_XGDMatrixSetFloatInfo
+JNIEXPORT jint JNICALL Java_org_dmlc_xgboost4j_wrapper_XgboostJNI_XGDMatrixSetFloatInfo
   (JNIEnv *jenv, jclass jcls, jlong jhandle, jstring jfield, jfloatArray jarray) {
+    jint jresult = 0;
     void *handle = (void *) 0 ;
     char *field = (char *) 0 ;
     bst_ulong len;
 
 
     handle = *(void **)&jhandle; 
-    field = 0;
-    if (jfield) {
-        field = (char *)jenv->GetStringUTFChars(jfield, 0);
-        if (!field) return ;
-    }
+
+    field = (char *)jenv->GetStringUTFChars(jfield, 0);
+
     
     jfloat* array = jenv->GetFloatArrayElements(jarray, NULL);
     len = (bst_ulong)jenv->GetArrayLength(jarray); 
-    XGDMatrixSetFloatInfo(handle, (char const *)field, (float const *)array, len);
+    jresult = (jint) XGDMatrixSetFloatInfo(handle, (char const *)field, (float const *)array, len);
     
     //release
     if (field) jenv->ReleaseStringUTFChars(jfield, (const char *)field);
     jenv->ReleaseFloatArrayElements(jarray, array, 0);
+    
+    return jresult;
 }
 
 /*
  * Class:     org_dmlc_xgboost4j_wrapper_XgboostJNI
  * Method:    XGDMatrixSetUIntInfo
  * Signature: (JLjava/lang/String;[I)V
  */
-JNIEXPORT void JNICALL Java_org_dmlc_xgboost4j_wrapper_XgboostJNI_XGDMatrixSetUIntInfo
+JNIEXPORT jint JNICALL Java_org_dmlc_xgboost4j_wrapper_XgboostJNI_XGDMatrixSetUIntInfo
   (JNIEnv *jenv, jclass jcls, jlong jhandle, jstring jfield, jintArray jarray) {
+    jint jresult = 0;
     void *handle = (void *) 0 ;
     char *field = (char *) 0 ;
     bst_ulong len ;
     handle = *(void **)&jhandle; 
     field = 0;
-    if (jfield) {
-        field = (char *)jenv->GetStringUTFChars(jfield, 0);
-        if (!field) return ;
-    }
+    field = (char *)jenv->GetStringUTFChars(jfield, 0);
+
     
     jint* array = jenv->GetIntArrayElements(jarray, NULL);
     len = (bst_ulong)jenv->GetArrayLength(jarray);
 
-    XGDMatrixSetUIntInfo(handle, (char const *)field, (unsigned int const *)array, len);
+    jresult = (jint) XGDMatrixSetUIntInfo(handle, (char const *)field, (unsigned int const *)array, len);
     //release
     if (field) jenv->ReleaseStringUTFChars(jfield, (const char *)field);
     jenv->ReleaseIntArrayElements(jarray, array, 0);
+    
+    return jresult;
 }
 
 /*
  * Class:     org_dmlc_xgboost4j_wrapper_XgboostJNI
  * Method:    XGDMatrixSetGroup
  * Signature: (J[I)V
  */
-JNIEXPORT void JNICALL Java_org_dmlc_xgboost4j_wrapper_XgboostJNI_XGDMatrixSetGroup
+JNIEXPORT jint JNICALL Java_org_dmlc_xgboost4j_wrapper_XgboostJNI_XGDMatrixSetGroup
   (JNIEnv * jenv, jclass jcls, jlong jhandle, jintArray jarray) {
+    jint jresult = 0;
     void *handle = (void *) 0 ;
     bst_ulong len ;
 
     handle = *(void **)&jhandle;
     jint* array = jenv->GetIntArrayElements(jarray, NULL);
     len = (bst_ulong)jenv->GetArrayLength(jarray); 
 
-    XGDMatrixSetGroup(handle, (unsigned int const *)array, len);
+    jresult = (jint) XGDMatrixSetGroup(handle, (unsigned int const *)array, len);
     
     //release
     jenv->ReleaseIntArrayElements(jarray, array, 0);
-
+    
+    return jresult;
 }
 
 /*
  * Class:     org_dmlc_xgboost4j_wrapper_XgboostJNI
  * Method:    XGDMatrixGetFloatInfo
  * Signature: (JLjava/lang/String;)[F
  */
-JNIEXPORT jfloatArray JNICALL Java_org_dmlc_xgboost4j_wrapper_XgboostJNI_XGDMatrixGetFloatInfo
-  (JNIEnv *jenv, jclass jcls, jlong jhandle, jstring jfield) {
+JNIEXPORT jint JNICALL Java_org_dmlc_xgboost4j_wrapper_XgboostJNI_XGDMatrixGetFloatInfo
+  (JNIEnv *jenv, jclass jcls, jlong jhandle, jstring jfield, jobjectArray jout) {
+    jint jresult = 0;
     void *handle = (void *) 0 ;
     char *field = (char *) 0 ;
     bst_ulong len[1];
     *len = 0;
-    float *result = 0 ;
+    float *result[1];
 
-      handle = *(void **)&jhandle; 
+    handle = *(void **)&jhandle; 
     field = 0;
     if (jfield) {
         field = (char *)jenv->GetStringUTFChars(jfield, 0);
         if (!field) return 0;
     }
     
-    result = (float *)XGDMatrixGetFloatInfo((void const *)handle, (char const *)field, len);
+    jresult = (jint) XGDMatrixGetFloatInfo(handle, (char const *)field, len, (const float **) result);
  
     if (field) jenv->ReleaseStringUTFChars(jfield, (const char *)field);
   
     jsize jlen = (jsize)*len;
-    jfloatArray jresult = jenv->NewFloatArray(jlen);
-    jenv->SetFloatArrayRegion(jresult, 0, jlen, (jfloat *)result);
+    jfloatArray jarray = jenv->NewFloatArray(jlen);
+    jenv->SetFloatArrayRegion(jarray, 0, jlen, (jfloat *) *result);
+    jenv->SetObjectArrayElement(jout, 0, (jobject) jarray);
+    
     return jresult;
 }
 
@@ -287,28 +319,26 @@ JNIEXPORT jfloatArray JNICALL Java_org_dmlc_xgboost4j_wrapper_XgboostJNI_XGDMatr
  * Method:    XGDMatrixGetUIntInfo
  * Signature: (JLjava/lang/String;)[I
  */
-JNIEXPORT jintArray JNICALL Java_org_dmlc_xgboost4j_wrapper_XgboostJNI_XGDMatrixGetUIntInfo
-  (JNIEnv *jenv, jclass jcls, jlong jhandle, jstring jfield) {
+JNIEXPORT jint JNICALL Java_org_dmlc_xgboost4j_wrapper_XgboostJNI_XGDMatrixGetUIntInfo
+  (JNIEnv *jenv, jclass jcls, jlong jhandle, jstring jfield, jobjectArray jout) {
+    jint jresult = 0;
     void *handle = (void *) 0 ;
     char *field = (char *) 0 ;
     bst_ulong len[1];
     *len = 0;
-    unsigned int *result = 0 ;
+    unsigned int *result[1];
 
     handle = *(void **)&jhandle; 
-    field = 0;
-    if (jfield) {
-        field = (char *)jenv->GetStringUTFChars(jfield, 0);
-        if (!field) return 0;
-    }
+    field = (char *)jenv->GetStringUTFChars(jfield, 0);
     
-    result = (unsigned int *)XGDMatrixGetUIntInfo((void const *)handle, (char const *)field, len);
+    jresult = (jint) XGDMatrixGetUIntInfo(handle, (char const *)field, len, (const unsigned int **) result);
  
     if (field) jenv->ReleaseStringUTFChars(jfield, (const char *)field);
   
     jsize jlen = (jsize)*len;
-    jintArray jresult = jenv->NewIntArray(jlen);
-    jenv->SetIntArrayRegion(jresult, 0, jlen, (jint *)result);
+    jintArray jarray = jenv->NewIntArray(jlen);
+    jenv->SetIntArrayRegion(jarray, 0, jlen, (jint *) *result);
+    jenv->SetObjectArrayElement(jout, 0, jarray);
     return jresult;
 }
 
@@ -317,14 +347,14 @@ JNIEXPORT jintArray JNICALL Java_org_dmlc_xgboost4j_wrapper_XgboostJNI_XGDMatrix
  * Method:    XGDMatrixNumRow
  * Signature: (J)J
  */
-JNIEXPORT jlong JNICALL Java_org_dmlc_xgboost4j_wrapper_XgboostJNI_XGDMatrixNumRow
-  (JNIEnv *jenv, jclass jcls, jlong jhandle) {
-    jlong jresult = 0 ;
+JNIEXPORT jint JNICALL Java_org_dmlc_xgboost4j_wrapper_XgboostJNI_XGDMatrixNumRow
+  (JNIEnv *jenv, jclass jcls, jlong jhandle, jlongArray jout) {
+    jint jresult = 0 ;
     void *handle = (void *) 0 ;
-    bst_ulong result;
+    bst_ulong result[1];
     handle = *(void **)&jhandle; 
-    result = (bst_ulong)XGDMatrixNumRow((void const *)handle);
-    jresult = (jlong)result; 
+    jresult = (jint) XGDMatrixNumRow(handle, result);
+    jenv->SetLongArrayRegion(jout, 0, 1, (const jlong *) result);
     return jresult;
 }
 
@@ -333,13 +363,14 @@ JNIEXPORT jlong JNICALL Java_org_dmlc_xgboost4j_wrapper_XgboostJNI_XGDMatrixNumR
  * Method:    XGBoosterCreate
  * Signature: ([J)J
  */
-JNIEXPORT jlong JNICALL Java_org_dmlc_xgboost4j_wrapper_XgboostJNI_XGBoosterCreate
-  (JNIEnv *jenv, jclass jcls, jlongArray jhandles) {
-    jlong jresult = 0 ;
+JNIEXPORT jint JNICALL Java_org_dmlc_xgboost4j_wrapper_XgboostJNI_XGBoosterCreate
+  (JNIEnv *jenv, jclass jcls, jlongArray jhandles, jlongArray jout) {
+    jint jresult = 0;
     void **handles = 0;
     bst_ulong len = 0;
-    void *result = 0 ;
+    void *result[1];
     jlong* cjhandles = 0;
+    unsigned long out[1];
     
     if(jhandles) {
         len = (bst_ulong)jenv->GetArrayLength(jhandles);
@@ -351,15 +382,17 @@ JNIEXPORT jlong JNICALL Java_org_dmlc_xgboost4j_wrapper_XgboostJNI_XGBoosterCrea
         }
     }
     
-    result = (void *)XGBoosterCreate(handles, len);
+    jresult = (jint) XGBoosterCreate(handles, len, result);
     
     //release
     if(jhandles) {
         delete[] handles;
         jenv->ReleaseLongArrayElements(jhandles, cjhandles, 0);
     }
     
-    *(void **)&jresult = result; 
+    *(void **)&out[0] = *result; 
+    jenv->SetLongArrayRegion(jout, 0, 1, (const jlong *) out);
+    
     return jresult;
 }
 
@@ -368,11 +401,11 @@ JNIEXPORT jlong JNICALL Java_org_dmlc_xgboost4j_wrapper_XgboostJNI_XGBoosterCrea
  * Method:    XGBoosterFree
  * Signature: (J)V
  */
-JNIEXPORT void JNICALL Java_org_dmlc_xgboost4j_wrapper_XgboostJNI_XGBoosterFree
+JNIEXPORT jint JNICALL Java_org_dmlc_xgboost4j_wrapper_XgboostJNI_XGBoosterFree
   (JNIEnv *jenv, jclass jcls, jlong jhandle) {
     void *handle = (void *) 0 ;
     handle = *(void **)&jhandle; 
-    XGBoosterFree(handle);
+    return (jint) XGBoosterFree(handle);
 }
 
 
@@ -381,52 +414,48 @@ JNIEXPORT void JNICALL Java_org_dmlc_xgboost4j_wrapper_XgboostJNI_XGBoosterFree
  * Method:    XGBoosterSetParam
  * Signature: (JLjava/lang/String;Ljava/lang/String;)V
  */
-JNIEXPORT void JNICALL Java_org_dmlc_xgboost4j_wrapper_XgboostJNI_XGBoosterSetParam
+JNIEXPORT jint JNICALL Java_org_dmlc_xgboost4j_wrapper_XgboostJNI_XGBoosterSetParam
   (JNIEnv *jenv, jclass jcls, jlong jhandle, jstring jname, jstring jvalue) {
+    jint jresult = -1;
     void *handle = (void *) 0 ;
     char *name = (char *) 0 ;
     char *value = (char *) 0 ;
     handle = *(void **)&jhandle; 
     
-    name = 0;
-    if (jname) {
-        name = (char *)jenv->GetStringUTFChars(jname, 0);
-        if (!name) return ;
-    }
-    
-    value = 0;
-    if (jvalue) {
-        value = (char *)jenv->GetStringUTFChars(jvalue, 0);
-        if (!value) return ;
-    }
-    XGBoosterSetParam(handle, (char const *)name, (char const *)value);
+    name = (char *)jenv->GetStringUTFChars(jname, 0);
+    value = (char *)jenv->GetStringUTFChars(jvalue, 0);
+
+    jresult = (jint) XGBoosterSetParam(handle, (char const *)name, (char const *)value);
     if (name) jenv->ReleaseStringUTFChars(jname, (const char *)name);
     if (value) jenv->ReleaseStringUTFChars(jvalue, (const char *)value);
+    
+    return jresult;
 }
 
 /*
  * Class:     org_dmlc_xgboost4j_wrapper_XgboostJNI
  * Method:    XGBoosterUpdateOneIter
  * Signature: (JIJ)V
  */
-JNIEXPORT void JNICALL Java_org_dmlc_xgboost4j_wrapper_XgboostJNI_XGBoosterUpdateOneIter
+JNIEXPORT jint JNICALL Java_org_dmlc_xgboost4j_wrapper_XgboostJNI_XGBoosterUpdateOneIter
   (JNIEnv *jenv, jclass jcls, jlong jhandle, jint jiter, jlong jdtrain) {
     void *handle = (void *) 0 ;
     int iter ;
     void *dtrain = (void *) 0 ;
     handle = *(void **)&jhandle; 
     iter = (int)jiter; 
     dtrain = *(void **)&jdtrain; 
-    XGBoosterUpdateOneIter(handle, iter, dtrain);
+    return (jint) XGBoosterUpdateOneIter(handle, iter, dtrain);
 }
 
 /*
  * Class:     org_dmlc_xgboost4j_wrapper_XgboostJNI
  * Method:    XGBoosterBoostOneIter
  * Signature: (JJ[F[F)V
  */
-JNIEXPORT void JNICALL Java_org_dmlc_xgboost4j_wrapper_XgboostJNI_XGBoosterBoostOneIter
+JNIEXPORT jint JNICALL Java_org_dmlc_xgboost4j_wrapper_XgboostJNI_XGBoosterBoostOneIter
   (JNIEnv *jenv, jclass jcls, jlong jhandle, jlong jdtrain, jfloatArray jgrad, jfloatArray jhess) {
+    jint jresult = 0;
     void *handle = (void *) 0 ;
     void *dtrain = (void *) 0 ;
     bst_ulong len ;
@@ -436,27 +465,29 @@ JNIEXPORT void JNICALL Java_org_dmlc_xgboost4j_wrapper_XgboostJNI_XGBoosterBoost
     jfloat* grad = jenv->GetFloatArrayElements(jgrad, 0);
     jfloat* hess = jenv->GetFloatArrayElements(jhess, 0);
     len = (bst_ulong)jenv->GetArrayLength(jgrad);
-    XGBoosterBoostOneIter(handle, dtrain, grad, hess, len);
+    jresult = (jint) XGBoosterBoostOneIter(handle, dtrain, grad, hess, len);
     
     //release
     jenv->ReleaseFloatArrayElements(jgrad, grad, 0);
     jenv->ReleaseFloatArrayElements(jhess, hess, 0);
+    
+    return jresult;
 }
 
 /*
  * Class:     org_dmlc_xgboost4j_wrapper_XgboostJNI
  * Method:    XGBoosterEvalOneIter
  * Signature: (JI[J[Ljava/lang/String;)Ljava/lang/String;
  */
-JNIEXPORT jstring JNICALL Java_org_dmlc_xgboost4j_wrapper_XgboostJNI_XGBoosterEvalOneIter
-  (JNIEnv *jenv, jclass jcls, jlong jhandle, jint jiter, jlongArray jdmats, jobjectArray jevnames) {
-    jstring jresult = 0 ;
+JNIEXPORT jint JNICALL Java_org_dmlc_xgboost4j_wrapper_XgboostJNI_XGBoosterEvalOneIter
+  (JNIEnv *jenv, jclass jcls, jlong jhandle, jint jiter, jlongArray jdmats, jobjectArray jevnames, jobjectArray jout) {
+    jint jresult = 0 ;
     void *handle = (void *) 0 ;
     int iter ;
     void **dmats = 0;
     char **evnames = 0;
     bst_ulong len ;
-    char *result = 0 ;
+    char *result[1];
     
     handle = *(void **)&jhandle; 
     iter = (int)jiter; 
@@ -480,7 +511,7 @@ JNIEXPORT jstring JNICALL Java_org_dmlc_xgboost4j_wrapper_XgboostJNI_XGBoosterEv
         evnames[i] = (char *)jenv->GetStringUTFChars(jevname, 0);
     }
     
-    result = (char *)XGBoosterEvalOneIter(handle, iter, dmats, (char const *(*))evnames, len);
+    jresult = (jint) XGBoosterEvalOneIter(handle, iter, dmats, (char const *(*))evnames, len, (const char **) result);
     
     if(len > 0) {
         delete[] dmats;
@@ -493,7 +524,9 @@ JNIEXPORT jstring JNICALL Java_org_dmlc_xgboost4j_wrapper_XgboostJNI_XGBoosterEv
         jenv->ReleaseLongArrayElements(jdmats, cjdmats, 0);
     }
     
-    if (result) jresult = jenv->NewStringUTF((const char *)result);
+    jstring jinfo = 0;
+    if (*result) jinfo = jenv->NewStringUTF((const char *) *result);
+    jenv->SetObjectArrayElement(jout, 0, jinfo);
   
     return jresult;
 }
@@ -503,26 +536,29 @@ JNIEXPORT jstring JNICALL Java_org_dmlc_xgboost4j_wrapper_XgboostJNI_XGBoosterEv
  * Method:    XGBoosterPredict
  * Signature: (JJIJ)[F
  */
-JNIEXPORT jfloatArray JNICALL Java_org_dmlc_xgboost4j_wrapper_XgboostJNI_XGBoosterPredict
-  (JNIEnv *jenv, jclass jcls, jlong jhandle, jlong jdmat, jint joption_mask, jlong jntree_limit) {
+JNIEXPORT jint JNICALL Java_org_dmlc_xgboost4j_wrapper_XgboostJNI_XGBoosterPredict
+  (JNIEnv *jenv, jclass jcls, jlong jhandle, jlong jdmat, jint joption_mask, jlong jntree_limit, jobjectArray jout) {
+    jint jresult = 0;
     void *handle = (void *) 0 ;
     void *dmat = (void *) 0 ;
     int option_mask ;
     unsigned int ntree_limit ;
     bst_ulong len[1];
     *len = 0;
-    float *result = 0 ;
+    float *result[1];
     
     handle = *(void **)&jhandle; 
     dmat = *(void **)&jdmat; 
     option_mask = (int)joption_mask; 
     ntree_limit = (unsigned int)jntree_limit; 
 
-    result = (float *)XGBoosterPredict(handle, dmat, option_mask, ntree_limit, len);
+    jresult = (jint) XGBoosterPredict(handle, dmat, option_mask, ntree_limit, len, (const float **) result);
     
     jsize jlen = (jsize)*len;
-    jfloatArray jresult = jenv->NewFloatArray(jlen);
-    jenv->SetFloatArrayRegion(jresult, 0, jlen, (jfloat *)result);
+    jfloatArray jarray = jenv->NewFloatArray(jlen);
+    jenv->SetFloatArrayRegion(jarray, 0, jlen, (jfloat *) *result);
+    jenv->SetObjectArrayElement(jout, 0, jarray);
+    
     return jresult;
 }
 
@@ -531,71 +567,78 @@ JNIEXPORT jfloatArray JNICALL Java_org_dmlc_xgboost4j_wrapper_XgboostJNI_XGBoost
  * Method:    XGBoosterLoadModel
  * Signature: (JLjava/lang/String;)V
  */
-JNIEXPORT void JNICALL Java_org_dmlc_xgboost4j_wrapper_XgboostJNI_XGBoosterLoadModel
+JNIEXPORT jint JNICALL Java_org_dmlc_xgboost4j_wrapper_XgboostJNI_XGBoosterLoadModel
   (JNIEnv *jenv, jclass jcls, jlong jhandle, jstring jfname) {
+    jint jresult = 0;
     void *handle = (void *) 0 ;
     char *fname = (char *) 0 ;
     handle = *(void **)&jhandle; 
-    fname = 0;
-    if (jfname) {
-        fname = (char *)jenv->GetStringUTFChars(jfname, 0);
-        if (!fname) return ;
-    }
-    XGBoosterLoadModel(handle,(char const *)fname);
+    
+    fname = (char *)jenv->GetStringUTFChars(jfname, 0);
+
+    
+    jresult = (jint) XGBoosterLoadModel(handle,(char const *)fname);
     if (fname) jenv->ReleaseStringUTFChars(jfname, (const char *)fname);
+    
+    return jresult;
 }
 
 /*
  * Class:     org_dmlc_xgboost4j_wrapper_XgboostJNI
  * Method:    XGBoosterSaveModel
  * Signature: (JLjava/lang/String;)V
  */
-JNIEXPORT void JNICALL Java_org_dmlc_xgboost4j_wrapper_XgboostJNI_XGBoosterSaveModel
+JNIEXPORT jint JNICALL Java_org_dmlc_xgboost4j_wrapper_XgboostJNI_XGBoosterSaveModel
   (JNIEnv *jenv, jclass jcls, jlong jhandle, jstring jfname) {
+    jint jresult = 0;
     void *handle = (void *) 0 ;
     char *fname = (char *) 0 ;
     handle = *(void **)&jhandle; 
     fname = 0;
-    if (jfname) {
-        fname = (char *)jenv->GetStringUTFChars(jfname, 0);
-        if (!fname) return ;
-    }
-    XGBoosterSaveModel(handle, (char const *)fname);
+    fname = (char *)jenv->GetStringUTFChars(jfname, 0);
+
+    jresult = (jint) XGBoosterSaveModel(handle, (char const *)fname);
     if (fname) jenv->ReleaseStringUTFChars(jfname, (const char *)fname);
+    
+    return jresult;
 }
 
 /*
  * Class:     org_dmlc_xgboost4j_wrapper_XgboostJNI
  * Method:    XGBoosterLoadModelFromBuffer
  * Signature: (JJJ)V
  */
-JNIEXPORT void JNICALL Java_org_dmlc_xgboost4j_wrapper_XgboostJNI_XGBoosterLoadModelFromBuffer
+JNIEXPORT jint JNICALL Java_org_dmlc_xgboost4j_wrapper_XgboostJNI_XGBoosterLoadModelFromBuffer
   (JNIEnv *jenv, jclass jcls, jlong jhandle, jlong jbuf, jlong jlen) {
     void *handle = (void *) 0 ;
     void *buf = (void *) 0 ;
     bst_ulong len ;
     handle = *(void **)&jhandle; 
     buf = *(void **)&jbuf; 
     len = (bst_ulong)jlen; 
-    XGBoosterLoadModelFromBuffer(handle, (void const *)buf, len);
+    return (jint) XGBoosterLoadModelFromBuffer(handle, (void const *)buf, len);
 }
 
 /*
  * Class:     org_dmlc_xgboost4j_wrapper_XgboostJNI
  * Method:    XGBoosterGetModelRaw
  * Signature: (J)Ljava/lang/String;
  */
-JNIEXPORT jstring JNICALL Java_org_dmlc_xgboost4j_wrapper_XgboostJNI_XGBoosterGetModelRaw
-  (JNIEnv * jenv, jclass jcls, jlong jhandle) {
-    jstring jresult = 0 ;
+JNIEXPORT jint JNICALL Java_org_dmlc_xgboost4j_wrapper_XgboostJNI_XGBoosterGetModelRaw
+  (JNIEnv * jenv, jclass jcls, jlong jhandle, jobjectArray jout) {
+    jint jresult = 0 ;
+    jstring jinfo = 0;
     void *handle = (void *) 0 ;
     bst_ulong len[1];
     *len = 0;
-    char *result = 0 ;
+    char *result[1];
     handle = *(void **)&jhandle; 
 
-    result = (char *)XGBoosterGetModelRaw(handle, len);
-    if (result) jresult = jenv->NewStringUTF((const char *)result);
+    jresult = (jint)XGBoosterGetModelRaw(handle, len, (const char **) result);
+    if (*result){
+        jinfo = jenv->NewStringUTF((const char *) *result);
+        jenv->SetObjectArrayElement(jout, 0, jinfo);
+    }
     return jresult;
 }
 
@@ -604,15 +647,16 @@ JNIEXPORT jstring JNICALL Java_org_dmlc_xgboost4j_wrapper_XgboostJNI_XGBoosterGe
  * Method:    XGBoosterDumpModel
  * Signature: (JLjava/lang/String;I)[Ljava/lang/String;
  */
-JNIEXPORT jobjectArray JNICALL Java_org_dmlc_xgboost4j_wrapper_XgboostJNI_XGBoosterDumpModel
-  (JNIEnv *jenv, jclass jcls, jlong jhandle, jstring jfmap, jint jwith_stats) {    
+JNIEXPORT jint JNICALL Java_org_dmlc_xgboost4j_wrapper_XgboostJNI_XGBoosterDumpModel
+  (JNIEnv *jenv, jclass jcls, jlong jhandle, jstring jfmap, jint jwith_stats, jobjectArray jout) {
+    jint jresult = 0;
     void *handle = (void *) 0 ;
     char *fmap = (char *) 0 ;
     int with_stats ;
     bst_ulong len[1];
     *len = 0;
     
-    char **result = 0 ;
+    char **result[1];
     handle = *(void **)&jhandle; 
     fmap = 0;
     if (jfmap) {
@@ -621,14 +665,16 @@ JNIEXPORT jobjectArray JNICALL Java_org_dmlc_xgboost4j_wrapper_XgboostJNI_XGBoos
     }
     with_stats = (int)jwith_stats;
 
-    result = (char **)XGBoosterDumpModel(handle, (char const *)fmap, with_stats, len);
+    jresult = (jint) XGBoosterDumpModel(handle, (const char *)fmap, with_stats, len, (const char ***) result);
     
     jsize jlen = (jsize)*len;
-    jobjectArray jresult = jenv->NewObjectArray(jlen, jenv->FindClass("java/lang/String"), jenv->NewStringUTF(""));
+    jobjectArray jinfos = jenv->NewObjectArray(jlen, jenv->FindClass("java/lang/String"), jenv->NewStringUTF(""));
     for(int i=0 ; i<jlen; i++) {
-        jenv->SetObjectArrayElement(jresult, i, jenv->NewStringUTF((const char*)result[i]));
+        jenv->SetObjectArrayElement(jinfos, i, jenv->NewStringUTF((const char*) result[0][i]));
     }
+    jenv->SetObjectArrayElement(jout, 0, jinfos);
     
     if (fmap) jenv->ReleaseStringUTFChars(jfmap, (const char *)fmap);
+    
     return jresult;
 }
\ No newline at end of file