@@ -24,15 +24,15 @@ void setHandle(JNIEnv *jenv, jlongArray jhandle, void* handle) {
     jenv->SetLongArrayRegion(jhandle, 0, 1, (const jlong*) out);
 }
 
-JNIEXPORT jstring JNICALL Java_org_dmlc_xgboost4j_XgboostJNI_XGBGetLastError
+JNIEXPORT jstring JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_XGBGetLastError
   (JNIEnv *jenv, jclass jcls) {
     jstring jresult = 0 ;
     const char* result = XGBGetLastError();
     if (result) jresult = jenv->NewStringUTF(result);
     return jresult;
 }
 
-JNIEXPORT jint JNICALL Java_org_dmlc_xgboost4j_XgboostJNI_XGDMatrixCreateFromFile
+JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_XGDMatrixCreateFromFile
   (JNIEnv *jenv, jclass jcls, jstring jfname, jint jsilent, jlongArray jout) {
     DMatrixHandle result;
     const char* fname = jenv->GetStringUTFChars(jfname, 0);
@@ -43,11 +43,11 @@ JNIEXPORT jint JNICALL Java_org_dmlc_xgboost4j_XgboostJNI_XGDMatrixCreateFromFil
 }
 
 /*
- * Class:     org_dmlc_xgboost4j_XgboostJNI
+ * Class:     ml_dmlc_xgboost4j_XgboostJNI
  * Method:    XGDMatrixCreateFromCSR
  * Signature: ([J[J[F)J
  */
-JNIEXPORT jint JNICALL Java_org_dmlc_xgboost4j_XgboostJNI_XGDMatrixCreateFromCSR
+JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_XGDMatrixCreateFromCSR
   (JNIEnv *jenv, jclass jcls, jlongArray jindptr, jintArray jindices, jfloatArray jdata, jlongArray jout) {
     DMatrixHandle result;
     jlong* indptr = jenv->GetLongArrayElements(jindptr, 0);
@@ -65,11 +65,11 @@ JNIEXPORT jint JNICALL Java_org_dmlc_xgboost4j_XgboostJNI_XGDMatrixCreateFromCSR
 }
 
 /*
- * Class:     org_dmlc_xgboost4j_XgboostJNI
+ * Class:     ml_dmlc_xgboost4j_XgboostJNI
  * Method:    XGDMatrixCreateFromCSC
  * Signature: ([J[J[F)J
  */
-JNIEXPORT jint JNICALL Java_org_dmlc_xgboost4j_XgboostJNI_XGDMatrixCreateFromCSC
+JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_XGDMatrixCreateFromCSC
   (JNIEnv *jenv, jclass jcls, jlongArray jindptr, jintArray jindices, jfloatArray jdata, jlongArray jout) {
     DMatrixHandle result;  
     jlong* indptr = jenv->GetLongArrayElements(jindptr, NULL);
@@ -89,11 +89,11 @@ JNIEXPORT jint JNICALL Java_org_dmlc_xgboost4j_XgboostJNI_XGDMatrixCreateFromCSC
 }
 
 /*
- * Class:     org_dmlc_xgboost4j_XgboostJNI
+ * Class:     ml_dmlc_xgboost4j_XgboostJNI
  * Method:    XGDMatrixCreateFromMat
  * Signature: ([FIIF)J
  */
-JNIEXPORT jint JNICALL Java_org_dmlc_xgboost4j_XgboostJNI_XGDMatrixCreateFromMat
+JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_XGDMatrixCreateFromMat
   (JNIEnv *jenv, jclass jcls, jfloatArray jdata, jint jnrow, jint jncol, jfloat jmiss, jlongArray jout) {
     DMatrixHandle result;
     jfloat* data = jenv->GetFloatArrayElements(jdata, 0);
@@ -107,11 +107,11 @@ JNIEXPORT jint JNICALL Java_org_dmlc_xgboost4j_XgboostJNI_XGDMatrixCreateFromMat
 }
 
 /*
- * Class:     org_dmlc_xgboost4j_XgboostJNI
+ * Class:     ml_dmlc_xgboost4j_XgboostJNI
  * Method:    XGDMatrixSliceDMatrix
  * Signature: (J[I)J
  */
-JNIEXPORT jint JNICALL Java_org_dmlc_xgboost4j_XgboostJNI_XGDMatrixSliceDMatrix
+JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_XGDMatrixSliceDMatrix
   (JNIEnv *jenv, jclass jcls, jlong jhandle, jintArray jindexset, jlongArray jout) {
     DMatrixHandle result;
     DMatrixHandle handle = (DMatrixHandle) jhandle; 
@@ -128,23 +128,23 @@ JNIEXPORT jint JNICALL Java_org_dmlc_xgboost4j_XgboostJNI_XGDMatrixSliceDMatrix
 }
 
 /*
- * Class:     org_dmlc_xgboost4j_XgboostJNI
+ * Class:     ml_dmlc_xgboost4j_XgboostJNI
  * Method:    XGDMatrixFree
  * Signature: (J)V
  */
-JNIEXPORT jint JNICALL Java_org_dmlc_xgboost4j_XgboostJNI_XGDMatrixFree
+JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_XGDMatrixFree
   (JNIEnv *jenv, jclass jcls, jlong jhandle) {    
     DMatrixHandle handle = (DMatrixHandle) jhandle;
     int ret = XGDMatrixFree(handle);
     return ret;
 }
 
 /*
- * Class:     org_dmlc_xgboost4j_XgboostJNI
+ * Class:     ml_dmlc_xgboost4j_XgboostJNI
  * Method:    XGDMatrixSaveBinary
  * Signature: (JLjava/lang/String;I)V
  */
-JNIEXPORT jint JNICALL Java_org_dmlc_xgboost4j_XgboostJNI_XGDMatrixSaveBinary
+JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_XGDMatrixSaveBinary
   (JNIEnv *jenv, jclass jcls, jlong jhandle, jstring jfname, jint jsilent) {
     DMatrixHandle handle = (DMatrixHandle) jhandle;
     const char* fname = jenv->GetStringUTFChars(jfname, 0);
@@ -154,11 +154,11 @@ JNIEXPORT jint JNICALL Java_org_dmlc_xgboost4j_XgboostJNI_XGDMatrixSaveBinary
 }
 
 /*
- * Class:     org_dmlc_xgboost4j_XgboostJNI
+ * Class:     ml_dmlc_xgboost4j_XgboostJNI
  * Method:    XGDMatrixSetFloatInfo
  * Signature: (JLjava/lang/String;[F)V
  */
-JNIEXPORT jint JNICALL Java_org_dmlc_xgboost4j_XgboostJNI_XGDMatrixSetFloatInfo
+JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_XGDMatrixSetFloatInfo
   (JNIEnv *jenv, jclass jcls, jlong jhandle, jstring jfield, jfloatArray jarray) {
     DMatrixHandle handle = (DMatrixHandle) jhandle;
     const char*  field = jenv->GetStringUTFChars(jfield, 0);
@@ -173,11 +173,11 @@ JNIEXPORT jint JNICALL Java_org_dmlc_xgboost4j_XgboostJNI_XGDMatrixSetFloatInfo
 }
 
 /*
- * Class:     org_dmlc_xgboost4j_XgboostJNI
+ * Class:     ml_dmlc_xgboost4j_XgboostJNI
  * Method:    XGDMatrixSetUIntInfo
  * Signature: (JLjava/lang/String;[I)V
  */
-JNIEXPORT jint JNICALL Java_org_dmlc_xgboost4j_XgboostJNI_XGDMatrixSetUIntInfo
+JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_XGDMatrixSetUIntInfo
   (JNIEnv *jenv, jclass jcls, jlong jhandle, jstring jfield, jintArray jarray) {
     DMatrixHandle handle = (DMatrixHandle) jhandle;
     const char*  field = jenv->GetStringUTFChars(jfield, 0);   
@@ -192,11 +192,11 @@ JNIEXPORT jint JNICALL Java_org_dmlc_xgboost4j_XgboostJNI_XGDMatrixSetUIntInfo
 }
 
 /*
- * Class:     org_dmlc_xgboost4j_XgboostJNI
+ * Class:     ml_dmlc_xgboost4j_XgboostJNI
  * Method:    XGDMatrixSetGroup
  * Signature: (J[I)V
  */
-JNIEXPORT jint JNICALL Java_org_dmlc_xgboost4j_XgboostJNI_XGDMatrixSetGroup
+JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_XGDMatrixSetGroup
   (JNIEnv * jenv, jclass jcls, jlong jhandle, jintArray jarray) {
     DMatrixHandle handle = (DMatrixHandle) jhandle;
     jint* array = jenv->GetIntArrayElements(jarray, NULL);
@@ -208,11 +208,11 @@ JNIEXPORT jint JNICALL Java_org_dmlc_xgboost4j_XgboostJNI_XGDMatrixSetGroup
 }
 
 /*
- * Class:     org_dmlc_xgboost4j_XgboostJNI
+ * Class:     ml_dmlc_xgboost4j_XgboostJNI
  * Method:    XGDMatrixGetFloatInfo
  * Signature: (JLjava/lang/String;)[F
  */
-JNIEXPORT jint JNICALL Java_org_dmlc_xgboost4j_XgboostJNI_XGDMatrixGetFloatInfo
+JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_XGDMatrixGetFloatInfo
   (JNIEnv *jenv, jclass jcls, jlong jhandle, jstring jfield, jobjectArray jout) {
     DMatrixHandle handle = (DMatrixHandle) jhandle;
     const char*  field = jenv->GetStringUTFChars(jfield, 0);
@@ -230,11 +230,11 @@ JNIEXPORT jint JNICALL Java_org_dmlc_xgboost4j_XgboostJNI_XGDMatrixGetFloatInfo
 }
 
 /*
- * Class:     org_dmlc_xgboost4j_XgboostJNI
+ * Class:     ml_dmlc_xgboost4j_XgboostJNI
  * Method:    XGDMatrixGetUIntInfo
  * Signature: (JLjava/lang/String;)[I
  */
-JNIEXPORT jint JNICALL Java_org_dmlc_xgboost4j_XgboostJNI_XGDMatrixGetUIntInfo
+JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_XGDMatrixGetUIntInfo
   (JNIEnv *jenv, jclass jcls, jlong jhandle, jstring jfield, jobjectArray jout) {
     DMatrixHandle handle = (DMatrixHandle) jhandle;
     const char*  field = jenv->GetStringUTFChars(jfield, 0);
@@ -251,11 +251,11 @@ JNIEXPORT jint JNICALL Java_org_dmlc_xgboost4j_XgboostJNI_XGDMatrixGetUIntInfo
 }
 
 /*
- * Class:     org_dmlc_xgboost4j_XgboostJNI
+ * Class:     ml_dmlc_xgboost4j_XgboostJNI
  * Method:    XGDMatrixNumRow
  * Signature: (J)J
  */
-JNIEXPORT jint JNICALL Java_org_dmlc_xgboost4j_XgboostJNI_XGDMatrixNumRow
+JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_XGDMatrixNumRow
   (JNIEnv *jenv, jclass jcls, jlong jhandle, jlongArray jout) {
     DMatrixHandle handle = (DMatrixHandle) jhandle;
     bst_ulong result[1];
@@ -265,11 +265,11 @@ JNIEXPORT jint JNICALL Java_org_dmlc_xgboost4j_XgboostJNI_XGDMatrixNumRow
 }
 
 /*
- * Class:     org_dmlc_xgboost4j_XgboostJNI
+ * Class:     ml_dmlc_xgboost4j_XgboostJNI
  * Method:    XGBoosterCreate
  * Signature: ([J)J
  */
-JNIEXPORT jint JNICALL Java_org_dmlc_xgboost4j_XgboostJNI_XGBoosterCreate
+JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_XGBoosterCreate
   (JNIEnv *jenv, jclass jcls, jlongArray jhandles, jlongArray jout) {
     DMatrixHandle* handles;
     bst_ulong len = 0;
@@ -298,23 +298,23 @@ JNIEXPORT jint JNICALL Java_org_dmlc_xgboost4j_XgboostJNI_XGBoosterCreate
 }
 
 /*
- * Class:     org_dmlc_xgboost4j_XgboostJNI
+ * Class:     ml_dmlc_xgboost4j_XgboostJNI
  * Method:    XGBoosterFree
  * Signature: (J)V
  */
-JNIEXPORT jint JNICALL Java_org_dmlc_xgboost4j_XgboostJNI_XGBoosterFree
+JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_XGBoosterFree
   (JNIEnv *jenv, jclass jcls, jlong jhandle) {
     BoosterHandle handle = (BoosterHandle) jhandle;
     return XGBoosterFree(handle);
 }
 
 
 /*
- * Class:     org_dmlc_xgboost4j_XgboostJNI
+ * Class:     ml_dmlc_xgboost4j_XgboostJNI
  * Method:    XGBoosterSetParam
  * Signature: (JLjava/lang/String;Ljava/lang/String;)V
  */
-JNIEXPORT jint JNICALL Java_org_dmlc_xgboost4j_XgboostJNI_XGBoosterSetParam
+JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_XGBoosterSetParam
   (JNIEnv *jenv, jclass jcls, jlong jhandle, jstring jname, jstring jvalue) {
     BoosterHandle handle = (BoosterHandle) jhandle;    
     const char* name = jenv->GetStringUTFChars(jname, 0);
@@ -327,23 +327,23 @@ JNIEXPORT jint JNICALL Java_org_dmlc_xgboost4j_XgboostJNI_XGBoosterSetParam
 }
 
 /*
- * Class:     org_dmlc_xgboost4j_XgboostJNI
+ * Class:     ml_dmlc_xgboost4j_XgboostJNI
  * Method:    XGBoosterUpdateOneIter
  * Signature: (JIJ)V
  */
-JNIEXPORT jint JNICALL Java_org_dmlc_xgboost4j_XgboostJNI_XGBoosterUpdateOneIter
+JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_XGBoosterUpdateOneIter
   (JNIEnv *jenv, jclass jcls, jlong jhandle, jint jiter, jlong jdtrain) {
     BoosterHandle handle = (BoosterHandle) jhandle;
     DMatrixHandle dtrain = (DMatrixHandle) jdtrain;
     return XGBoosterUpdateOneIter(handle, jiter, dtrain);
 }
 
 /*
- * Class:     org_dmlc_xgboost4j_XgboostJNI
+ * Class:     ml_dmlc_xgboost4j_XgboostJNI
  * Method:    XGBoosterBoostOneIter
  * Signature: (JJ[F[F)V
  */
-JNIEXPORT jint JNICALL Java_org_dmlc_xgboost4j_XgboostJNI_XGBoosterBoostOneIter
+JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_XGBoosterBoostOneIter
   (JNIEnv *jenv, jclass jcls, jlong jhandle, jlong jdtrain, jfloatArray jgrad, jfloatArray jhess) {
     BoosterHandle handle = (BoosterHandle) jhandle;
     DMatrixHandle dtrain = (DMatrixHandle) jdtrain;
@@ -358,11 +358,11 @@ JNIEXPORT jint JNICALL Java_org_dmlc_xgboost4j_XgboostJNI_XGBoosterBoostOneIter
 }
 
 /*
- * Class:     org_dmlc_xgboost4j_XgboostJNI
+ * Class:     ml_dmlc_xgboost4j_XgboostJNI
  * Method:    XGBoosterEvalOneIter
  * Signature: (JI[J[Ljava/lang/String;)Ljava/lang/String;
  */
-JNIEXPORT jint JNICALL Java_org_dmlc_xgboost4j_XgboostJNI_XGBoosterEvalOneIter
+JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_XGBoosterEvalOneIter
   (JNIEnv *jenv, jclass jcls, jlong jhandle, jint jiter, jlongArray jdmats, jobjectArray jevnames, jobjectArray jout) {
     BoosterHandle handle = (BoosterHandle) jhandle;
     DMatrixHandle* dmats = 0;
@@ -406,11 +406,11 @@ JNIEXPORT jint JNICALL Java_org_dmlc_xgboost4j_XgboostJNI_XGBoosterEvalOneIter
 }
 
 /*
- * Class:     org_dmlc_xgboost4j_XgboostJNI
+ * Class:     ml_dmlc_xgboost4j_XgboostJNI
  * Method:    XGBoosterPredict
  * Signature: (JJIJ)[F
  */
-JNIEXPORT jint JNICALL Java_org_dmlc_xgboost4j_XgboostJNI_XGBoosterPredict
+JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_XGBoosterPredict
   (JNIEnv *jenv, jclass jcls, jlong jhandle, jlong jdmat, jint joption_mask, jint jntree_limit, jobjectArray jout) {
     BoosterHandle handle = (BoosterHandle) jhandle;
     DMatrixHandle dmat = (DMatrixHandle) jdmat;
@@ -426,11 +426,11 @@ JNIEXPORT jint JNICALL Java_org_dmlc_xgboost4j_XgboostJNI_XGBoosterPredict
 }
 
 /*
- * Class:     org_dmlc_xgboost4j_XgboostJNI
+ * Class:     ml_dmlc_xgboost4j_XgboostJNI
  * Method:    XGBoosterLoadModel
  * Signature: (JLjava/lang/String;)V
  */
-JNIEXPORT jint JNICALL Java_org_dmlc_xgboost4j_XgboostJNI_XGBoosterLoadModel
+JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_XGBoosterLoadModel
   (JNIEnv *jenv, jclass jcls, jlong jhandle, jstring jfname) {
     BoosterHandle handle = (BoosterHandle) jhandle;
     const char* fname = jenv->GetStringUTFChars(jfname, 0);
@@ -441,11 +441,11 @@ JNIEXPORT jint JNICALL Java_org_dmlc_xgboost4j_XgboostJNI_XGBoosterLoadModel
 }
 
 /*
- * Class:     org_dmlc_xgboost4j_XgboostJNI
+ * Class:     ml_dmlc_xgboost4j_XgboostJNI
  * Method:    XGBoosterSaveModel
  * Signature: (JLjava/lang/String;)V
  */
-JNIEXPORT jint JNICALL Java_org_dmlc_xgboost4j_XgboostJNI_XGBoosterSaveModel
+JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_XGBoosterSaveModel
   (JNIEnv *jenv, jclass jcls, jlong jhandle, jstring jfname) {
     BoosterHandle handle = (BoosterHandle) jhandle;
     const char*  fname = jenv->GetStringUTFChars(jfname, 0);
@@ -457,23 +457,23 @@ JNIEXPORT jint JNICALL Java_org_dmlc_xgboost4j_XgboostJNI_XGBoosterSaveModel
 }
 
 /*
- * Class:     org_dmlc_xgboost4j_XgboostJNI
+ * Class:     ml_dmlc_xgboost4j_XgboostJNI
  * Method:    XGBoosterLoadModelFromBuffer
  * Signature: (JJJ)V
  */
-JNIEXPORT jint JNICALL Java_org_dmlc_xgboost4j_XgboostJNI_XGBoosterLoadModelFromBuffer
+JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_XGBoosterLoadModelFromBuffer
   (JNIEnv *jenv, jclass jcls, jlong jhandle, jlong jbuf, jlong jlen) {
     BoosterHandle handle = (BoosterHandle) jhandle;
     void *buf = (void*) jbuf;
     return XGBoosterLoadModelFromBuffer(handle, (void const *)buf, (bst_ulong) jlen);
 }
 
 /*
- * Class:     org_dmlc_xgboost4j_XgboostJNI
+ * Class:     ml_dmlc_xgboost4j_XgboostJNI
  * Method:    XGBoosterGetModelRaw
  * Signature: (J)Ljava/lang/String;
  */
-JNIEXPORT jint JNICALL Java_org_dmlc_xgboost4j_XgboostJNI_XGBoosterGetModelRaw
+JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_XGBoosterGetModelRaw
   (JNIEnv * jenv, jclass jcls, jlong jhandle, jobjectArray jout) {
     BoosterHandle handle = (BoosterHandle) jhandle;
     bst_ulong len = 0;
@@ -488,11 +488,11 @@ JNIEXPORT jint JNICALL Java_org_dmlc_xgboost4j_XgboostJNI_XGBoosterGetModelRaw
 }
 
 /*
- * Class:     org_dmlc_xgboost4j_XgboostJNI
+ * Class:     ml_dmlc_xgboost4j_XgboostJNI
  * Method:    XGBoosterDumpModel
  * Signature: (JLjava/lang/String;I)[Ljava/lang/String;
  */
-JNIEXPORT jint JNICALL Java_org_dmlc_xgboost4j_XgboostJNI_XGBoosterDumpModel
+JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_XGBoosterDumpModel
   (JNIEnv *jenv, jclass jcls, jlong jhandle, jstring jfmap, jint jwith_stats, jobjectArray jout) {
     BoosterHandle handle = (BoosterHandle) jhandle;
     const char *fmap = jenv->GetStringUTFChars(jfmap, 0);