@@ -134,11 +134,11 @@ XGB_EXTERN_C int XGBoost4jCallbackDataIterNext(
 }
 
 /*
- * Class:     ml_dmlc_xgboost4j_XgboostJNI
+ * Class:     ml_dmlc_xgboost4j_java_XGBoostJNI
  * Method:    XGBGetLastError
  * Signature: ()Ljava/lang/String;
  */
-JNIEXPORT jstring JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_XGBGetLastError
+JNIEXPORT jstring JNICALL Java_ml_dmlc_xgboost4j_java_XGBoostJNI_XGBGetLastError
   (JNIEnv *jenv, jclass jcls) {
   jstring jresult = 0;
   const char* result = XGBGetLastError();
@@ -149,11 +149,11 @@ JNIEXPORT jstring JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_XGBGetLastError
 }
 
 /*
- * Class:     ml_dmlc_xgboost4j_XgboostJNI
+ * Class:     ml_dmlc_xgboost4j_java_XGBoostJNI
  * Method:    XGDMatrixCreateFromDataIter
  * Signature: (Ljava/util/Iterator;Ljava/lang/String;[J)I
  */
-JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_XGDMatrixCreateFromDataIter
+JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_java_XGBoostJNI_XGDMatrixCreateFromDataIter
   (JNIEnv *jenv, jclass jcls, jobject jiter, jstring jcache_info, jlongArray jout) {
   DMatrixHandle result;
   const char* cache_info = nullptr;
@@ -170,11 +170,11 @@ JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_XGDMatrixCreateFromData
 }
 
 /*
- * Class:     ml_dmlc_xgboost4j_XgboostJNI
+ * Class:     ml_dmlc_xgboost4j_java_XGBoostJNI
  * Method:    XGDMatrixCreateFromFile
  * Signature: (Ljava/lang/String;I[J)I
  */
-JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_XGDMatrixCreateFromFile
+JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_java_XGBoostJNI_XGDMatrixCreateFromFile
   (JNIEnv *jenv, jclass jcls, jstring jfname, jint jsilent, jlongArray jout) {
   DMatrixHandle result;
   const char* fname = jenv->GetStringUTFChars(jfname, 0);
@@ -187,11 +187,11 @@ JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_XGDMatrixCreateFromFile
 }
 
 /*
- * Class:     ml_dmlc_xgboost4j_XgboostJNI
+ * Class:     ml_dmlc_xgboost4j_java_XGBoostJNI
  * Method:    XGDMatrixCreateFromCSR
  * Signature: ([J[J[F)J
  */
-JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_XGDMatrixCreateFromCSR
+JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_java_XGBoostJNI_XGDMatrixCreateFromCSR
   (JNIEnv *jenv, jclass jcls, jlongArray jindptr, jintArray jindices, jfloatArray jdata, jlongArray jout) {
   DMatrixHandle result;
   jlong* indptr = jenv->GetLongArrayElements(jindptr, 0);
@@ -209,11 +209,11 @@ JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_XGDMatrixCreateFromCSR
 }
 
 /*
- * Class:     ml_dmlc_xgboost4j_XgboostJNI
+ * Class:     ml_dmlc_xgboost4j_java_XGBoostJNI
  * Method:    XGDMatrixCreateFromCSC
  * Signature: ([J[J[F)J
  */
-JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_XGDMatrixCreateFromCSC
+JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_java_XGBoostJNI_XGDMatrixCreateFromCSC
   (JNIEnv *jenv, jclass jcls, jlongArray jindptr, jintArray jindices, jfloatArray jdata, jlongArray jout) {
   DMatrixHandle result;
   jlong* indptr = jenv->GetLongArrayElements(jindptr, NULL);
@@ -233,11 +233,11 @@ JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_XGDMatrixCreateFromCSC
 }
 
 /*
- * Class:     ml_dmlc_xgboost4j_XgboostJNI
+ * Class:     ml_dmlc_xgboost4j_java_XGBoostJNI
  * Method:    XGDMatrixCreateFromMat
  * Signature: ([FIIF)J
  */
-JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_XGDMatrixCreateFromMat
+JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_java_XGBoostJNI_XGDMatrixCreateFromMat
   (JNIEnv *jenv, jclass jcls, jfloatArray jdata, jint jnrow, jint jncol, jfloat jmiss, jlongArray jout) {
   DMatrixHandle result;
   jfloat* data = jenv->GetFloatArrayElements(jdata, 0);
@@ -251,11 +251,11 @@ JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_XGDMatrixCreateFromMat
 }
 
 /*
- * Class:     ml_dmlc_xgboost4j_XgboostJNI
+ * Class:     ml_dmlc_xgboost4j_java_XGBoostJNI
  * Method:    XGDMatrixSliceDMatrix
  * Signature: (J[I)J
  */
-JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_XGDMatrixSliceDMatrix
+JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_java_XGBoostJNI_XGDMatrixSliceDMatrix
   (JNIEnv *jenv, jclass jcls, jlong jhandle, jintArray jindexset, jlongArray jout) {
   DMatrixHandle result;
   DMatrixHandle handle = (DMatrixHandle) jhandle;
@@ -272,23 +272,23 @@ JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_XGDMatrixSliceDMatrix
 }
 
 /*
- * Class:     ml_dmlc_xgboost4j_XgboostJNI
+ * Class:     ml_dmlc_xgboost4j_java_XGBoostJNI
  * Method:    XGDMatrixFree
  * Signature: (J)V
  */
-JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_XGDMatrixFree
+JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_java_XGBoostJNI_XGDMatrixFree
   (JNIEnv *jenv, jclass jcls, jlong jhandle) {
   DMatrixHandle handle = (DMatrixHandle) jhandle;
   int ret = XGDMatrixFree(handle);
   return ret;
 }
 
 /*
- * Class:     ml_dmlc_xgboost4j_XgboostJNI
+ * Class:     ml_dmlc_xgboost4j_java_XGBoostJNI
  * Method:    XGDMatrixSaveBinary
  * Signature: (JLjava/lang/String;I)V
  */
-JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_XGDMatrixSaveBinary
+JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_java_XGBoostJNI_XGDMatrixSaveBinary
   (JNIEnv *jenv, jclass jcls, jlong jhandle, jstring jfname, jint jsilent) {
   DMatrixHandle handle = (DMatrixHandle) jhandle;
   const char* fname = jenv->GetStringUTFChars(jfname, 0);
@@ -298,11 +298,11 @@ JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_XGDMatrixSaveBinary
 }
 
 /*
- * Class:     ml_dmlc_xgboost4j_XgboostJNI
+ * Class:     ml_dmlc_xgboost4j_java_XGBoostJNI
  * Method:    XGDMatrixSetFloatInfo
  * Signature: (JLjava/lang/String;[F)V
  */
-JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_XGDMatrixSetFloatInfo
+JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_java_XGBoostJNI_XGDMatrixSetFloatInfo
   (JNIEnv *jenv, jclass jcls, jlong jhandle, jstring jfield, jfloatArray jarray) {
   DMatrixHandle handle = (DMatrixHandle) jhandle;
   const char*  field = jenv->GetStringUTFChars(jfield, 0);
@@ -317,11 +317,11 @@ JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_XGDMatrixSetFloatInfo
 }
 
 /*
- * Class:     ml_dmlc_xgboost4j_XgboostJNI
+ * Class:     ml_dmlc_xgboost4j_java_XGBoostJNI
  * Method:    XGDMatrixSetUIntInfo
  * Signature: (JLjava/lang/String;[I)V
  */
-JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_XGDMatrixSetUIntInfo
+JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_java_XGBoostJNI_XGDMatrixSetUIntInfo
   (JNIEnv *jenv, jclass jcls, jlong jhandle, jstring jfield, jintArray jarray) {
   DMatrixHandle handle = (DMatrixHandle) jhandle;
   const char*  field = jenv->GetStringUTFChars(jfield, 0);
@@ -336,11 +336,11 @@ JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_XGDMatrixSetUIntInfo
 }
 
 /*
- * Class:     ml_dmlc_xgboost4j_XgboostJNI
+ * Class:     ml_dmlc_xgboost4j_java_XGBoostJNI
  * Method:    XGDMatrixSetGroup
  * Signature: (J[I)V
  */
-JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_XGDMatrixSetGroup
+JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_java_XGBoostJNI_XGDMatrixSetGroup
   (JNIEnv * jenv, jclass jcls, jlong jhandle, jintArray jarray) {
   DMatrixHandle handle = (DMatrixHandle) jhandle;
   jint* array = jenv->GetIntArrayElements(jarray, NULL);
@@ -352,11 +352,11 @@ JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_XGDMatrixSetGroup
 }
 
 /*
- * Class:     ml_dmlc_xgboost4j_XgboostJNI
+ * Class:     ml_dmlc_xgboost4j_java_XGBoostJNI
  * Method:    XGDMatrixGetFloatInfo
  * Signature: (JLjava/lang/String;)[F
  */
-JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_XGDMatrixGetFloatInfo
+JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_java_XGBoostJNI_XGDMatrixGetFloatInfo
   (JNIEnv *jenv, jclass jcls, jlong jhandle, jstring jfield, jobjectArray jout) {
   DMatrixHandle handle = (DMatrixHandle) jhandle;
   const char*  field = jenv->GetStringUTFChars(jfield, 0);
@@ -374,11 +374,11 @@ JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_XGDMatrixGetFloatInfo
 }
 
 /*
- * Class:     ml_dmlc_xgboost4j_XgboostJNI
+ * Class:     ml_dmlc_xgboost4j_java_XGBoostJNI
  * Method:    XGDMatrixGetUIntInfo
  * Signature: (JLjava/lang/String;)[I
  */
-JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_XGDMatrixGetUIntInfo
+JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_java_XGBoostJNI_XGDMatrixGetUIntInfo
   (JNIEnv *jenv, jclass jcls, jlong jhandle, jstring jfield, jobjectArray jout) {
   DMatrixHandle handle = (DMatrixHandle) jhandle;
   const char*  field = jenv->GetStringUTFChars(jfield, 0);
@@ -395,11 +395,11 @@ JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_XGDMatrixGetUIntInfo
 }
 
 /*
- * Class:     ml_dmlc_xgboost4j_XgboostJNI
+ * Class:     ml_dmlc_xgboost4j_java_XGBoostJNI
  * Method:    XGDMatrixNumRow
  * Signature: (J)J
  */
-JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_XGDMatrixNumRow
+JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_java_XGBoostJNI_XGDMatrixNumRow
   (JNIEnv *jenv, jclass jcls, jlong jhandle, jlongArray jout) {
   DMatrixHandle handle = (DMatrixHandle) jhandle;
   bst_ulong result[1];
@@ -409,11 +409,11 @@ JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_XGDMatrixNumRow
 }
 
 /*
- * Class:     ml_dmlc_xgboost4j_XgboostJNI
+ * Class:     ml_dmlc_xgboost4j_java_XGBoostJNI
  * Method:    XGBoosterCreate
  * Signature: ([J)J
  */
-JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_XGBoosterCreate
+JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_java_XGBoostJNI_XGBoosterCreate
   (JNIEnv *jenv, jclass jcls, jlongArray jhandles, jlongArray jout) {
   std::vector<DMatrixHandle> handles;
   if (jhandles != nullptr) {
@@ -431,23 +431,23 @@ JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_XGBoosterCreate
 }
 
 /*
- * Class:     ml_dmlc_xgboost4j_XgboostJNI
+ * Class:     ml_dmlc_xgboost4j_java_XGBoostJNI
  * Method:    XGBoosterFree
  * Signature: (J)V
  */
-JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_XGBoosterFree
+JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_java_XGBoostJNI_XGBoosterFree
   (JNIEnv *jenv, jclass jcls, jlong jhandle) {
     BoosterHandle handle = (BoosterHandle) jhandle;
     return XGBoosterFree(handle);
 }
 
 
 /*
- * Class:     ml_dmlc_xgboost4j_XgboostJNI
+ * Class:     ml_dmlc_xgboost4j_java_XGBoostJNI
  * Method:    XGBoosterSetParam
  * Signature: (JLjava/lang/String;Ljava/lang/String;)V
  */
-JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_XGBoosterSetParam
+JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_java_XGBoostJNI_XGBoosterSetParam
   (JNIEnv *jenv, jclass jcls, jlong jhandle, jstring jname, jstring jvalue) {
   BoosterHandle handle = (BoosterHandle) jhandle;
   const char* name = jenv->GetStringUTFChars(jname, 0);
@@ -460,23 +460,23 @@ JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_XGBoosterSetParam
 }
 
 /*
- * Class:     ml_dmlc_xgboost4j_XgboostJNI
+ * Class:     ml_dmlc_xgboost4j_java_XGBoostJNI
  * Method:    XGBoosterUpdateOneIter
  * Signature: (JIJ)V
  */
-JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_XGBoosterUpdateOneIter
+JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_java_XGBoostJNI_XGBoosterUpdateOneIter
   (JNIEnv *jenv, jclass jcls, jlong jhandle, jint jiter, jlong jdtrain) {
   BoosterHandle handle = (BoosterHandle) jhandle;
   DMatrixHandle dtrain = (DMatrixHandle) jdtrain;
   return XGBoosterUpdateOneIter(handle, jiter, dtrain);
 }
 
 /*
- * Class:     ml_dmlc_xgboost4j_XgboostJNI
+ * Class:     ml_dmlc_xgboost4j_java_XGBoostJNI
  * Method:    XGBoosterBoostOneIter
  * Signature: (JJ[F[F)V
  */
-JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_XGBoosterBoostOneIter
+JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_java_XGBoostJNI_XGBoosterBoostOneIter
   (JNIEnv *jenv, jclass jcls, jlong jhandle, jlong jdtrain, jfloatArray jgrad, jfloatArray jhess) {
   BoosterHandle handle = (BoosterHandle) jhandle;
   DMatrixHandle dtrain = (DMatrixHandle) jdtrain;
@@ -491,11 +491,11 @@ JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_XGBoosterBoostOneIter
 }
 
 /*
- * Class:     ml_dmlc_xgboost4j_XgboostJNI
+ * Class:     ml_dmlc_xgboost4j_java_XGBoostJNI
  * Method:    XGBoosterEvalOneIter
  * Signature: (JI[J[Ljava/lang/String;)Ljava/lang/String;
  */
-JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_XGBoosterEvalOneIter
+JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_java_XGBoostJNI_XGBoosterEvalOneIter
   (JNIEnv *jenv, jclass jcls, jlong jhandle, jint jiter, jlongArray jdmats, jobjectArray jevnames, jobjectArray jout) {
   BoosterHandle handle = (BoosterHandle) jhandle;
   std::vector<DMatrixHandle> dmats;
@@ -530,11 +530,11 @@ JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_XGBoosterEvalOneIter
 }
 
 /*
- * Class:     ml_dmlc_xgboost4j_XgboostJNI
+ * Class:     ml_dmlc_xgboost4j_java_XGBoostJNI
  * Method:    XGBoosterPredict
  * Signature: (JJIJ)[F
  */
-JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_XGBoosterPredict
+JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_java_XGBoostJNI_XGBoosterPredict
   (JNIEnv *jenv, jclass jcls, jlong jhandle, jlong jdmat, jint joption_mask, jint jntree_limit, jobjectArray jout) {
   BoosterHandle handle = (BoosterHandle) jhandle;
   DMatrixHandle dmat = (DMatrixHandle) jdmat;
@@ -550,11 +550,11 @@ JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_XGBoosterPredict
 }
 
 /*
- * Class:     ml_dmlc_xgboost4j_XgboostJNI
+ * Class:     ml_dmlc_xgboost4j_java_XGBoostJNI
  * Method:    XGBoosterLoadModel
  * Signature: (JLjava/lang/String;)V
  */
-JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_XGBoosterLoadModel
+JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_java_XGBoostJNI_XGBoosterLoadModel
   (JNIEnv *jenv, jclass jcls, jlong jhandle, jstring jfname) {
   BoosterHandle handle = (BoosterHandle) jhandle;
   const char* fname = jenv->GetStringUTFChars(jfname, 0);
@@ -565,11 +565,11 @@ JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_XGBoosterLoadModel
 }
 
 /*
- * Class:     ml_dmlc_xgboost4j_XgboostJNI
+ * Class:     ml_dmlc_xgboost4j_java_XGBoostJNI
  * Method:    XGBoosterSaveModel
  * Signature: (JLjava/lang/String;)V
  */
-JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_XGBoosterSaveModel
+JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_java_XGBoostJNI_XGBoosterSaveModel
   (JNIEnv *jenv, jclass jcls, jlong jhandle, jstring jfname) {
   BoosterHandle handle = (BoosterHandle) jhandle;
   const char*  fname = jenv->GetStringUTFChars(jfname, 0);
@@ -580,11 +580,11 @@ JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_XGBoosterSaveModel
 }
 
 /*
- * Class:     ml_dmlc_xgboost4j_XgboostJNI
+ * Class:     ml_dmlc_xgboost4j_java_XGBoostJNI
  * Method:    XGBoosterLoadModelFromBuffer
  * Signature: (J[B)I
  */
-JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_XGBoosterLoadModelFromBuffer
+JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_java_XGBoostJNI_XGBoosterLoadModelFromBuffer
     (JNIEnv *jenv, jclass jcls, jlong jhandle, jbyteArray jbytes) {
   BoosterHandle handle = (BoosterHandle) jhandle;
   jbyte* buffer = jenv->GetByteArrayElements(jbytes, 0);
@@ -595,11 +595,11 @@ JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_XGBoosterLoadModelFromB
 }
 
 /*
- * Class:     ml_dmlc_xgboost4j_XgboostJNI
+ * Class:     ml_dmlc_xgboost4j_java_XGBoostJNI
  * Method:    XGBoosterGetModelRaw
  * Signature: (J[[B)I
  */
-JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_XGBoosterGetModelRaw
+JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_java_XGBoostJNI_XGBoosterGetModelRaw
   (JNIEnv * jenv, jclass jcls, jlong jhandle, jobjectArray jout) {
   BoosterHandle handle = (BoosterHandle) jhandle;
   bst_ulong len = 0;
@@ -615,11 +615,11 @@ JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_XGBoosterGetModelRaw
 }
 
 /*
- * Class:     ml_dmlc_xgboost4j_XgboostJNI
+ * Class:     ml_dmlc_xgboost4j_java_XGBoostJNI
  * Method:    XGBoosterDumpModel
  * Signature: (JLjava/lang/String;I)[Ljava/lang/String;
  */
-JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_XGBoosterDumpModel
+JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_java_XGBoostJNI_XGBoosterDumpModel
   (JNIEnv *jenv, jclass jcls, jlong jhandle, jstring jfmap, jint jwith_stats, jobjectArray jout) {
   BoosterHandle handle = (BoosterHandle) jhandle;
   const char *fmap = jenv->GetStringUTFChars(jfmap, 0);
@@ -640,11 +640,11 @@ JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_XGBoosterDumpModel
 }
 
 /*
- * Class:     ml_dmlc_xgboost4j_XgboostJNI
+ * Class:     ml_dmlc_xgboost4j_java_XGBoostJNI
  * Method:    XGBoosterLoadRabitCheckpoint
  * Signature: (J[I)I
  */
-JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_XGBoosterLoadRabitCheckpoint
+JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_java_XGBoostJNI_XGBoosterLoadRabitCheckpoint
   (JNIEnv *jenv , jclass jcls, jlong jhandle, jintArray jout) {
   BoosterHandle handle = (BoosterHandle) jhandle;
   int version;
@@ -654,22 +654,22 @@ JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_XGBoosterLoadRabitCheck
 }
 
 /*
- * Class:     ml_dmlc_xgboost4j_XgboostJNI
+ * Class:     ml_dmlc_xgboost4j_java_XGBoostJNI
  * Method:    XGBoosterSaveRabitCheckpoint
  * Signature: (J)I
  */
-JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_XGBoosterSaveRabitCheckpoint
+JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_java_XGBoostJNI_XGBoosterSaveRabitCheckpoint
   (JNIEnv *jenv, jclass jcls, jlong jhandle) {
   BoosterHandle handle = (BoosterHandle) jhandle;
   return XGBoosterSaveRabitCheckpoint(handle);
 }
 
 /*
- * Class:     ml_dmlc_xgboost4j_XgboostJNI
+ * Class:     ml_dmlc_xgboost4j_java_XGBoostJNI
  * Method:    RabitInit
  * Signature: ([Ljava/lang/String;)I
  */
-JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_RabitInit
+JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_java_XGBoostJNI_RabitInit
   (JNIEnv *jenv, jclass jcls, jobjectArray jargs) {
   std::vector<std::string> args;
   std::vector<char*> argv;
@@ -691,22 +691,22 @@ JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_RabitInit
 }
 
 /*
- * Class:     ml_dmlc_xgboost4j_XgboostJNI
+ * Class:     ml_dmlc_xgboost4j_java_XGBoostJNI
  * Method:    RabitFinalize
  * Signature: ()I
  */
-JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_RabitFinalize
+JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_java_XGBoostJNI_RabitFinalize
   (JNIEnv *jenv, jclass jcls) {
   RabitFinalize();
   return 0;
 }
 
 /*
- * Class:     ml_dmlc_xgboost4j_XgboostJNI
+ * Class:     ml_dmlc_xgboost4j_java_XGBoostJNI
  * Method:    RabitTrackerPrint
  * Signature: (Ljava/lang/String;)I
  */
-JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_RabitTrackerPrint
+JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_java_XGBoostJNI_RabitTrackerPrint
   (JNIEnv *jenv, jclass jcls, jstring jmsg) {
   std::string str(jenv->GetStringUTFChars(jmsg, 0),
                   jenv->GetStringLength(jmsg));
@@ -715,35 +715,35 @@ JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_RabitTrackerPrint
 }
 
 /*
- * Class:     ml_dmlc_xgboost4j_XgboostJNI
+ * Class:     ml_dmlc_xgboost4j_java_XGBoostJNI
  * Method:    RabitGetRank
  * Signature: ([I)I
  */
-JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_RabitGetRank
+JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_java_XGBoostJNI_RabitGetRank
   (JNIEnv *jenv, jclass jcls, jintArray jout) {
   int rank = RabitGetRank();
   jenv->SetIntArrayRegion(jout, 0, 1, &rank);
   return 0;
 }
 
 /*
- * Class:     ml_dmlc_xgboost4j_XgboostJNI
+ * Class:     ml_dmlc_xgboost4j_java_XGBoostJNI
  * Method:    RabitGetWorldSize
  * Signature: ([I)I
  */
-JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_RabitGetWorldSize
+JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_java_XGBoostJNI_RabitGetWorldSize
   (JNIEnv *jenv, jclass jcls, jintArray jout) {
   int out = RabitGetWorldSize();
   jenv->SetIntArrayRegion(jout, 0, 1, &out);
   return 0;
 }
 
 /*
- * Class:     ml_dmlc_xgboost4j_XgboostJNI
+ * Class:     ml_dmlc_xgboost4j_java_XGBoostJNI
  * Method:    RabitVersionNumber
  * Signature: ([I)I
  */
-JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_RabitVersionNumber
+JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_java_XGBoostJNI_RabitVersionNumber
   (JNIEnv *jenv, jclass jcls, jintArray jout) {
   int out = RabitVersionNumber();
   jenv->SetIntArrayRegion(jout, 0, 1, &out);