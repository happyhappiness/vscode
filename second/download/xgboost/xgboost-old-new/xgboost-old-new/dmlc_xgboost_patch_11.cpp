@@ -20,13 +20,124 @@
 #include <vector>
 #include <string>
 
-//helper functions
-//set handle
+// helper functions
+// set handle
 void setHandle(JNIEnv *jenv, jlongArray jhandle, void* handle) {
   long out = (long) handle;
   jenv->SetLongArrayRegion(jhandle, 0, 1, &out);
 }
 
+// global JVM
+static JavaVM* global_jvm = nullptr;
+
+// overrides JNI on load
+jint JNI_OnLoad(JavaVM *vm, void *reserved) {
+  global_jvm = vm;
+  return JNI_VERSION_1_6;
+}
+
+XGB_EXTERN_C int XGBoost4jCallbackDataIterNext(
+    DataIterHandle data_handle,
+    XGBCallbackSetData* set_function,
+    DataHolderHandle set_function_handle) {
+  jobject jiter = static_cast<jobject>(data_handle);
+  JNIEnv* jenv;
+  int jni_status = global_jvm->GetEnv((void **)&jenv, JNI_VERSION_1_6);
+  if (jni_status == JNI_EDETACHED) {
+    global_jvm->AttachCurrentThread(reinterpret_cast<void **>(&jenv), nullptr);
+  } else {
+    CHECK(jni_status == JNI_OK);
+  }
+  try {
+    jclass iterClass = jenv->FindClass("java/util/Iterator");
+    jmethodID hasNext = jenv->GetMethodID(iterClass,
+                                          "hasNext", "()Z");
+    jmethodID next = jenv->GetMethodID(iterClass,
+                                       "next", "()Ljava/lang/Object;");
+    int ret_value;
+    if (jenv->CallBooleanMethod(jiter, hasNext)) {
+      ret_value = 1;
+      jobject batch = jenv->CallObjectMethod(jiter, next);
+      jclass batchClass = jenv->GetObjectClass(batch);
+      jlongArray joffset = (jlongArray)jenv->GetObjectField(
+          batch, jenv->GetFieldID(batchClass, "rowOffset", "[J"));
+      jfloatArray jlabel = (jfloatArray)jenv->GetObjectField(
+          batch, jenv->GetFieldID(batchClass, "label", "[F"));
+      jfloatArray jweight = (jfloatArray)jenv->GetObjectField(
+          batch, jenv->GetFieldID(batchClass, "weight", "[F"));
+      jintArray jindex = (jintArray)jenv->GetObjectField(
+          batch, jenv->GetFieldID(batchClass, "featureIndex", "[I"));
+      jfloatArray jvalue = (jfloatArray)jenv->GetObjectField(
+        batch, jenv->GetFieldID(batchClass, "featureValue", "[F"));
+      XGBoostBatchCSR cbatch;
+      cbatch.size = jenv->GetArrayLength(joffset) - 1;
+      cbatch.offset = jenv->GetLongArrayElements(joffset, 0);
+      if (jlabel != nullptr) {
+        cbatch.label = jenv->GetFloatArrayElements(jlabel, 0);
+        CHECK_EQ(jenv->GetArrayLength(jlabel), static_cast<long>(cbatch.size))
+            << "batch.label.length must equal batch.numRows()";
+      } else {
+        cbatch.label = nullptr;
+      }
+      if (jweight != nullptr) {
+        cbatch.weight = jenv->GetFloatArrayElements(jweight, 0);
+        CHECK_EQ(jenv->GetArrayLength(jweight), static_cast<long>(cbatch.size))
+            << "batch.weight.length must equal batch.numRows()";
+      } else {
+        cbatch.weight = nullptr;
+      }
+      long max_elem = cbatch.offset[cbatch.size];
+      cbatch.index = jenv->GetIntArrayElements(jindex, 0);
+      cbatch.value = jenv->GetFloatArrayElements(jvalue, 0);
+      CHECK_EQ(jenv->GetArrayLength(jindex), max_elem)
+          << "batch.index.length must equal batch.offset.back()";
+      CHECK_EQ(jenv->GetArrayLength(jvalue), max_elem)
+          << "batch.index.length must equal batch.offset.back()";
+      // cbatch is ready
+      CHECK_EQ((*set_function)(set_function_handle, cbatch), 0)
+          << XGBGetLastError();
+      // release the elements.
+      jenv->ReleaseLongArrayElements(joffset, cbatch.offset, 0);
+      jenv->DeleteLocalRef(joffset);
+      if (jlabel != nullptr) {
+        jenv->ReleaseFloatArrayElements(jlabel, cbatch.label, 0);
+        jenv->DeleteLocalRef(jlabel);
+      }
+      if (jweight != nullptr) {
+        jenv->ReleaseFloatArrayElements(jweight, cbatch.weight, 0);
+        jenv->DeleteLocalRef(jweight);
+      }
+      jenv->ReleaseIntArrayElements(jindex, cbatch.index, 0);
+      jenv->DeleteLocalRef(jindex);
+      jenv->ReleaseFloatArrayElements(jvalue, cbatch.value, 0);
+      jenv->DeleteLocalRef(jvalue);
+      jenv->DeleteLocalRef(batch);
+      jenv->DeleteLocalRef(batchClass);
+      ret_value = 1;
+    } else {
+      ret_value = 0;
+    }
+    jenv->DeleteLocalRef(iterClass);
+    // only detach if it is a async call.
+    if (jni_status == JNI_EDETACHED) {
+      global_jvm->DetachCurrentThread();
+    }
+    return ret_value;
+  } catch(dmlc::Error e) {
+    // only detach if it is a async call.
+    if (jni_status == JNI_EDETACHED) {
+      global_jvm->DetachCurrentThread();
+    }
+    LOG(FATAL) << e.what();
+    return -1;
+  }
+}
+
+/*
+ * Class:     ml_dmlc_xgboost4j_XgboostJNI
+ * Method:    XGBGetLastError
+ * Signature: ()Ljava/lang/String;
+ */
 JNIEXPORT jstring JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_XGBGetLastError
   (JNIEnv *jenv, jclass jcls) {
   jstring jresult = 0;
@@ -37,6 +148,32 @@ JNIEXPORT jstring JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_XGBGetLastError
   return jresult;
 }
 
+/*
+ * Class:     ml_dmlc_xgboost4j_XgboostJNI
+ * Method:    XGDMatrixCreateFromDataIter
+ * Signature: (Ljava/util/Iterator;Ljava/lang/String;[J)I
+ */
+JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_XGDMatrixCreateFromDataIter
+  (JNIEnv *jenv, jclass jcls, jobject jiter, jstring jcache_info, jlongArray jout) {
+  DMatrixHandle result;
+  const char* cache_info = nullptr;
+  if (jcache_info != nullptr) {
+    cache_info = jenv->GetStringUTFChars(jcache_info, 0);
+  }
+  int ret = XGDMatrixCreateFromDataIter(
+      jiter, XGBoost4jCallbackDataIterNext, cache_info, &result);
+  if (cache_info) {
+    jenv->ReleaseStringUTFChars(jcache_info, cache_info);
+  }
+  setHandle(jenv, jout, result);
+  return ret;
+}
+
+/*
+ * Class:     ml_dmlc_xgboost4j_XgboostJNI
+ * Method:    XGDMatrixCreateFromFile
+ * Signature: (Ljava/lang/String;I[J)I
+ */
 JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_XGDMatrixCreateFromFile
   (JNIEnv *jenv, jclass jcls, jstring jfname, jint jsilent, jlongArray jout) {
   DMatrixHandle result;