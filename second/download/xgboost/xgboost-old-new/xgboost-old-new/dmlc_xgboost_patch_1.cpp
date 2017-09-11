@@ -25,7 +25,7 @@
 // set handle
 void setHandle(JNIEnv *jenv, jlongArray jhandle, void* handle) {
 #ifdef __APPLE__
-  long out = (long) handle;
+  jlong out = (long) handle;
 #else
   int64_t out = (int64_t) handle;
 #endif
@@ -76,7 +76,8 @@ XGB_EXTERN_C int XGBoost4jCallbackDataIterNext(
         batch, jenv->GetFieldID(batchClass, "featureValue", "[F"));
       XGBoostBatchCSR cbatch;
       cbatch.size = jenv->GetArrayLength(joffset) - 1;
-      cbatch.offset = jenv->GetLongArrayElements(joffset, 0);
+      cbatch.offset = reinterpret_cast<long *>(
+          jenv->GetLongArrayElements(joffset, 0));
       if (jlabel != nullptr) {
         cbatch.label = jenv->GetFloatArrayElements(jlabel, 0);
         CHECK_EQ(jenv->GetArrayLength(jlabel), static_cast<long>(cbatch.size))
@@ -103,7 +104,8 @@ XGB_EXTERN_C int XGBoost4jCallbackDataIterNext(
       CHECK_EQ((*set_function)(set_function_handle, cbatch), 0)
           << XGBGetLastError();
       // release the elements.
-      jenv->ReleaseLongArrayElements(joffset, cbatch.offset, 0);
+      jenv->ReleaseLongArrayElements(
+          joffset, reinterpret_cast<jlong *>(cbatch.offset), 0);
       jenv->DeleteLocalRef(joffset);
       if (jlabel != nullptr) {
         jenv->ReleaseFloatArrayElements(jlabel, cbatch.label, 0);