@@ -1,45 +1,50 @@
 /*
- Copyright (c) 2014 by Contributors 
- Licensed under the Apache License, Version 2.0 (the "License");
- you may not use this file except in compliance with the License.
- You may obtain a copy of the License at
-    
- http://www.apache.org/licenses/LICENSE-2.0
- Unless required by applicable law or agreed to in writing, software
- distributed under the License is distributed on an "AS IS" BASIS,
- WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
- See the License for the specific language governing permissions and
- limitations under the License.
- */
-
-#include "xgboost/c_api.h"
-#include "xgboost4j.h"
+  Copyright (c) 2014 by Contributors
+  Licensed under the Apache License, Version 2.0 (the "License");
+  you may not use this file except in compliance with the License.
+  You may obtain a copy of the License at
+
+  http://www.apache.org/licenses/LICENSE-2.0
+  Unless required by applicable law or agreed to in writing, software
+  distributed under the License is distributed on an "AS IS" BASIS,
+  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
+  See the License for the specific language governing permissions and
+  limitations under the License.
+*/
+
+#include <xgboost/c_api.h>
+#include "./xgboost4j.h"
 #include <cstring>
+#include <vector>
+#include <string>
 
 //helper functions
 //set handle
 void setHandle(JNIEnv *jenv, jlongArray jhandle, void* handle) {
-    long out[1];
-    out[0] = (long) handle;
-    jenv->SetLongArrayRegion(jhandle, 0, 1, (const jlong*) out);
+  long out = (long) handle;
+  jenv->SetLongArrayRegion(jhandle, 0, 1, &out);
 }
 
 JNIEXPORT jstring JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_XGBGetLastError
   (JNIEnv *jenv, jclass jcls) {
-    jstring jresult = 0 ;
-    const char* result = XGBGetLastError();
-    if (result) jresult = jenv->NewStringUTF(result);
-    return jresult;
+  jstring jresult = 0;
+  const char* result = XGBGetLastError();
+  if (result != NULL) {
+    jresult = jenv->NewStringUTF(result);
+  }
+  return jresult;
 }
 
 JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_XGDMatrixCreateFromFile
   (JNIEnv *jenv, jclass jcls, jstring jfname, jint jsilent, jlongArray jout) {
-    DMatrixHandle result;
-    const char* fname = jenv->GetStringUTFChars(jfname, 0);
-    int ret = XGDMatrixCreateFromFile(fname, jsilent, &result);
-    if (fname) jenv->ReleaseStringUTFChars(jfname, fname);    
-    setHandle(jenv, jout, result);
-    return ret;
+  DMatrixHandle result;
+  const char* fname = jenv->GetStringUTFChars(jfname, 0);
+  int ret = XGDMatrixCreateFromFile(fname, jsilent, &result);
+  if (fname) {
+    jenv->ReleaseStringUTFChars(jfname, fname);
+  }
+  setHandle(jenv, jout, result);
+  return ret;
 }
 
 /*
@@ -49,19 +54,19 @@ JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_XGDMatrixCreateFromFile
  */
 JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_XGDMatrixCreateFromCSR
   (JNIEnv *jenv, jclass jcls, jlongArray jindptr, jintArray jindices, jfloatArray jdata, jlongArray jout) {
-    DMatrixHandle result;
-    jlong* indptr = jenv->GetLongArrayElements(jindptr, 0);
-    jint* indices = jenv->GetIntArrayElements(jindices, 0);
-    jfloat* data = jenv->GetFloatArrayElements(jdata, 0); 
-    bst_ulong nindptr = (bst_ulong)jenv->GetArrayLength(jindptr); 
-    bst_ulong nelem = (bst_ulong)jenv->GetArrayLength(jdata); 
-    int ret = (jint) XGDMatrixCreateFromCSR((unsigned long const *)indptr, (unsigned int const *)indices, (float const *)data, nindptr, nelem, &result);    
-    setHandle(jenv, jout, result);
-    //Release
-    jenv->ReleaseLongArrayElements(jindptr, indptr, 0);
-    jenv->ReleaseIntArrayElements(jindices, indices, 0);
-    jenv->ReleaseFloatArrayElements(jdata, data, 0);
-    return ret;
+  DMatrixHandle result;
+  jlong* indptr = jenv->GetLongArrayElements(jindptr, 0);
+  jint* indices = jenv->GetIntArrayElements(jindices, 0);
+  jfloat* data = jenv->GetFloatArrayElements(jdata, 0);
+  bst_ulong nindptr = (bst_ulong)jenv->GetArrayLength(jindptr);
+  bst_ulong nelem = (bst_ulong)jenv->GetArrayLength(jdata);
+  int ret = (jint) XGDMatrixCreateFromCSR((unsigned long const *)indptr, (unsigned int const *)indices, (float const *)data, nindptr, nelem, &result);
+  setHandle(jenv, jout, result);
+  //Release
+  jenv->ReleaseLongArrayElements(jindptr, indptr, 0);
+  jenv->ReleaseIntArrayElements(jindices, indices, 0);
+  jenv->ReleaseFloatArrayElements(jdata, data, 0);
+  return ret;
 }
 
 /*
@@ -71,21 +76,21 @@ JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_XGDMatrixCreateFromCSR
  */
 JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_XGDMatrixCreateFromCSC
   (JNIEnv *jenv, jclass jcls, jlongArray jindptr, jintArray jindices, jfloatArray jdata, jlongArray jout) {
-    DMatrixHandle result;  
-    jlong* indptr = jenv->GetLongArrayElements(jindptr, NULL);
-    jint* indices = jenv->GetIntArrayElements(jindices, 0);
-    jfloat* data = jenv->GetFloatArrayElements(jdata, NULL);
-    bst_ulong nindptr = (bst_ulong)jenv->GetArrayLength(jindptr); 
-    bst_ulong nelem = (bst_ulong)jenv->GetArrayLength(jdata); 
-
-    int ret = (jint) XGDMatrixCreateFromCSC((unsigned long const *)indptr, (unsigned int const *)indices, (float const *)data, nindptr, nelem, &result);  
-    setHandle(jenv, jout, result);   
-    //release
-    jenv->ReleaseLongArrayElements(jindptr, indptr, 0);
-    jenv->ReleaseIntArrayElements(jindices, indices, 0);
-    jenv->ReleaseFloatArrayElements(jdata, data, 0);
-    
-    return ret;
+  DMatrixHandle result;
+  jlong* indptr = jenv->GetLongArrayElements(jindptr, NULL);
+  jint* indices = jenv->GetIntArrayElements(jindices, 0);
+  jfloat* data = jenv->GetFloatArrayElements(jdata, NULL);
+  bst_ulong nindptr = (bst_ulong)jenv->GetArrayLength(jindptr);
+  bst_ulong nelem = (bst_ulong)jenv->GetArrayLength(jdata);
+
+  int ret = (jint) XGDMatrixCreateFromCSC((unsigned long const *)indptr, (unsigned int const *)indices, (float const *)data, nindptr, nelem, &result);
+  setHandle(jenv, jout, result);
+  //release
+  jenv->ReleaseLongArrayElements(jindptr, indptr, 0);
+  jenv->ReleaseIntArrayElements(jindices, indices, 0);
+  jenv->ReleaseFloatArrayElements(jdata, data, 0);
+
+  return ret;
 }
 
 /*
@@ -95,15 +100,15 @@ JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_XGDMatrixCreateFromCSC
  */
 JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_XGDMatrixCreateFromMat
   (JNIEnv *jenv, jclass jcls, jfloatArray jdata, jint jnrow, jint jncol, jfloat jmiss, jlongArray jout) {
-    DMatrixHandle result;
-    jfloat* data = jenv->GetFloatArrayElements(jdata, 0);
-    bst_ulong nrow = (bst_ulong)jnrow; 
-    bst_ulong ncol = (bst_ulong)jncol; 
-    int ret = (jint) XGDMatrixCreateFromMat((float const *)data, nrow, ncol, jmiss, &result);
-    setHandle(jenv, jout, result);
-    //release
-    jenv->ReleaseFloatArrayElements(jdata, data, 0);
-    return ret;
+  DMatrixHandle result;
+  jfloat* data = jenv->GetFloatArrayElements(jdata, 0);
+  bst_ulong nrow = (bst_ulong)jnrow;
+  bst_ulong ncol = (bst_ulong)jncol;
+  int ret = (jint) XGDMatrixCreateFromMat((float const *)data, nrow, ncol, jmiss, &result);
+  setHandle(jenv, jout, result);
+  //release
+  jenv->ReleaseFloatArrayElements(jdata, data, 0);
+  return ret;
 }
 
 /*
@@ -113,18 +118,18 @@ JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_XGDMatrixCreateFromMat
  */
 JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_XGDMatrixSliceDMatrix
   (JNIEnv *jenv, jclass jcls, jlong jhandle, jintArray jindexset, jlongArray jout) {
-    DMatrixHandle result;
-    DMatrixHandle handle = (DMatrixHandle) jhandle; 
+  DMatrixHandle result;
+  DMatrixHandle handle = (DMatrixHandle) jhandle;
+
+  jint* indexset = jenv->GetIntArrayElements(jindexset, 0);
+  bst_ulong len = (bst_ulong)jenv->GetArrayLength(jindexset);
 
-    jint* indexset = jenv->GetIntArrayElements(jindexset, 0);
-    bst_ulong len = (bst_ulong)jenv->GetArrayLength(jindexset); 
+  int ret = XGDMatrixSliceDMatrix(handle, (int const *)indexset, len, &result);
+  setHandle(jenv, jout, result);
+  //release
+  jenv->ReleaseIntArrayElements(jindexset, indexset, 0);
 
-    int ret = XGDMatrixSliceDMatrix(handle, (int const *)indexset, len, &result);
-    setHandle(jenv, jout, result);
-    //release
-    jenv->ReleaseIntArrayElements(jindexset, indexset, 0);
-    
-    return ret;
+  return ret;
 }
 
 /*
@@ -133,10 +138,10 @@ JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_XGDMatrixSliceDMatrix
  * Signature: (J)V
  */
 JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_XGDMatrixFree
-  (JNIEnv *jenv, jclass jcls, jlong jhandle) {    
-    DMatrixHandle handle = (DMatrixHandle) jhandle;
-    int ret = XGDMatrixFree(handle);
-    return ret;
+  (JNIEnv *jenv, jclass jcls, jlong jhandle) {
+  DMatrixHandle handle = (DMatrixHandle) jhandle;
+  int ret = XGDMatrixFree(handle);
+  return ret;
 }
 
 /*
@@ -146,11 +151,11 @@ JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_XGDMatrixFree
  */
 JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_XGDMatrixSaveBinary
   (JNIEnv *jenv, jclass jcls, jlong jhandle, jstring jfname, jint jsilent) {
-    DMatrixHandle handle = (DMatrixHandle) jhandle;
-    const char* fname = jenv->GetStringUTFChars(jfname, 0);
-    int ret = XGDMatrixSaveBinary(handle, fname, jsilent);
-    if (fname) jenv->ReleaseStringUTFChars(jfname, (const char *)fname);    
-    return ret;
+  DMatrixHandle handle = (DMatrixHandle) jhandle;
+  const char* fname = jenv->GetStringUTFChars(jfname, 0);
+  int ret = XGDMatrixSaveBinary(handle, fname, jsilent);
+  if (fname) jenv->ReleaseStringUTFChars(jfname, (const char *)fname);
+  return ret;
 }
 
 /*
@@ -160,16 +165,16 @@ JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_XGDMatrixSaveBinary
  */
 JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_XGDMatrixSetFloatInfo
   (JNIEnv *jenv, jclass jcls, jlong jhandle, jstring jfield, jfloatArray jarray) {
-    DMatrixHandle handle = (DMatrixHandle) jhandle;
-    const char*  field = jenv->GetStringUTFChars(jfield, 0);
-   
-    jfloat* array = jenv->GetFloatArrayElements(jarray, NULL);
-    bst_ulong len = (bst_ulong)jenv->GetArrayLength(jarray); 
-    int ret = XGDMatrixSetFloatInfo(handle, field, (float const *)array, len);   
-    //release
-    if (field) jenv->ReleaseStringUTFChars(jfield, field);
-    jenv->ReleaseFloatArrayElements(jarray, array, 0);   
-    return ret;
+  DMatrixHandle handle = (DMatrixHandle) jhandle;
+  const char*  field = jenv->GetStringUTFChars(jfield, 0);
+
+  jfloat* array = jenv->GetFloatArrayElements(jarray, NULL);
+  bst_ulong len = (bst_ulong)jenv->GetArrayLength(jarray);
+  int ret = XGDMatrixSetFloatInfo(handle, field, (float const *)array, len);
+  //release
+  if (field) jenv->ReleaseStringUTFChars(jfield, field);
+  jenv->ReleaseFloatArrayElements(jarray, array, 0);
+  return ret;
 }
 
 /*
@@ -179,16 +184,16 @@ JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_XGDMatrixSetFloatInfo
  */
 JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_XGDMatrixSetUIntInfo
   (JNIEnv *jenv, jclass jcls, jlong jhandle, jstring jfield, jintArray jarray) {
-    DMatrixHandle handle = (DMatrixHandle) jhandle;
-    const char*  field = jenv->GetStringUTFChars(jfield, 0);   
-    jint* array = jenv->GetIntArrayElements(jarray, NULL);
-    bst_ulong len = (bst_ulong)jenv->GetArrayLength(jarray);
-    int ret = XGDMatrixSetUIntInfo(handle, (char const *)field, (unsigned int const *)array, len);
-    //release
-    if (field) jenv->ReleaseStringUTFChars(jfield, (const char *)field);
-    jenv->ReleaseIntArrayElements(jarray, array, 0);
-    
-    return ret;
+  DMatrixHandle handle = (DMatrixHandle) jhandle;
+  const char*  field = jenv->GetStringUTFChars(jfield, 0);
+  jint* array = jenv->GetIntArrayElements(jarray, NULL);
+  bst_ulong len = (bst_ulong)jenv->GetArrayLength(jarray);
+  int ret = XGDMatrixSetUIntInfo(handle, (char const *)field, (unsigned int const *)array, len);
+  //release
+  if (field) jenv->ReleaseStringUTFChars(jfield, (const char *)field);
+  jenv->ReleaseIntArrayElements(jarray, array, 0);
+
+  return ret;
 }
 
 /*
@@ -198,13 +203,13 @@ JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_XGDMatrixSetUIntInfo
  */
 JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_XGDMatrixSetGroup
   (JNIEnv * jenv, jclass jcls, jlong jhandle, jintArray jarray) {
-    DMatrixHandle handle = (DMatrixHandle) jhandle;
-    jint* array = jenv->GetIntArrayElements(jarray, NULL);
-    bst_ulong len = (bst_ulong)jenv->GetArrayLength(jarray); 
-    int ret = XGDMatrixSetGroup(handle, (unsigned int const *)array, len);    
-    //release
-    jenv->ReleaseIntArrayElements(jarray, array, 0);    
-    return ret;
+  DMatrixHandle handle = (DMatrixHandle) jhandle;
+  jint* array = jenv->GetIntArrayElements(jarray, NULL);
+  bst_ulong len = (bst_ulong)jenv->GetArrayLength(jarray);
+  int ret = XGDMatrixSetGroup(handle, (unsigned int const *)array, len);
+  //release
+  jenv->ReleaseIntArrayElements(jarray, array, 0);
+  return ret;
 }
 
 /*
@@ -214,19 +219,19 @@ JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_XGDMatrixSetGroup
  */
 JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_XGDMatrixGetFloatInfo
   (JNIEnv *jenv, jclass jcls, jlong jhandle, jstring jfield, jobjectArray jout) {
-    DMatrixHandle handle = (DMatrixHandle) jhandle;
-    const char*  field = jenv->GetStringUTFChars(jfield, 0);
-    bst_ulong len;
-    float *result;    
-    int ret = XGDMatrixGetFloatInfo(handle, field, &len, (const float**) &result);
-    if (field) jenv->ReleaseStringUTFChars(jfield, field);
-  
-    jsize jlen = (jsize) len;
-    jfloatArray jarray = jenv->NewFloatArray(jlen);
-    jenv->SetFloatArrayRegion(jarray, 0, jlen, (jfloat *) result);
-    jenv->SetObjectArrayElement(jout, 0, (jobject) jarray);
-    
-    return ret;
+  DMatrixHandle handle = (DMatrixHandle) jhandle;
+  const char*  field = jenv->GetStringUTFChars(jfield, 0);
+  bst_ulong len;
+  float *result;
+  int ret = XGDMatrixGetFloatInfo(handle, field, &len, (const float**) &result);
+  if (field) jenv->ReleaseStringUTFChars(jfield, field);
+
+  jsize jlen = (jsize) len;
+  jfloatArray jarray = jenv->NewFloatArray(jlen);
+  jenv->SetFloatArrayRegion(jarray, 0, jlen, (jfloat *) result);
+  jenv->SetObjectArrayElement(jout, 0, (jobject) jarray);
+
+  return ret;
 }
 
 /*
@@ -236,18 +241,18 @@ JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_XGDMatrixGetFloatInfo
  */
 JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_XGDMatrixGetUIntInfo
   (JNIEnv *jenv, jclass jcls, jlong jhandle, jstring jfield, jobjectArray jout) {
-    DMatrixHandle handle = (DMatrixHandle) jhandle;
-    const char*  field = jenv->GetStringUTFChars(jfield, 0);
-    bst_ulong len;
-    unsigned int *result;    
-    int ret = (jint) XGDMatrixGetUIntInfo(handle, field, &len, (const unsigned int **) &result);
-    if (field) jenv->ReleaseStringUTFChars(jfield, field);
-  
-    jsize jlen = (jsize) len;
-    jintArray jarray = jenv->NewIntArray(jlen);
-    jenv->SetIntArrayRegion(jarray, 0, jlen, (jint *) result);
-    jenv->SetObjectArrayElement(jout, 0, jarray);
-    return ret;
+  DMatrixHandle handle = (DMatrixHandle) jhandle;
+  const char*  field = jenv->GetStringUTFChars(jfield, 0);
+  bst_ulong len;
+  unsigned int *result;
+  int ret = (jint) XGDMatrixGetUIntInfo(handle, field, &len, (const unsigned int **) &result);
+  if (field) jenv->ReleaseStringUTFChars(jfield, field);
+
+  jsize jlen = (jsize) len;
+  jintArray jarray = jenv->NewIntArray(jlen);
+  jenv->SetIntArrayRegion(jarray, 0, jlen, (jint *) result);
+  jenv->SetObjectArrayElement(jout, 0, jarray);
+  return ret;
 }
 
 /*
@@ -257,11 +262,11 @@ JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_XGDMatrixGetUIntInfo
  */
 JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_XGDMatrixNumRow
   (JNIEnv *jenv, jclass jcls, jlong jhandle, jlongArray jout) {
-    DMatrixHandle handle = (DMatrixHandle) jhandle;
-    bst_ulong result[1];
-    int ret = (jint) XGDMatrixNumRow(handle, result);
-    jenv->SetLongArrayRegion(jout, 0, 1, (const jlong *) result);
-    return ret;
+  DMatrixHandle handle = (DMatrixHandle) jhandle;
+  bst_ulong result[1];
+  int ret = (jint) XGDMatrixNumRow(handle, result);
+  jenv->SetLongArrayRegion(jout, 0, 1, (const jlong *) result);
+  return ret;
 }
 
 /*
@@ -271,30 +276,29 @@ JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_XGDMatrixNumRow
  */
 JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_XGBoosterCreate
   (JNIEnv *jenv, jclass jcls, jlongArray jhandles, jlongArray jout) {
-    DMatrixHandle* handles;
-    bst_ulong len = 0;
-    jlong* cjhandles = 0;
-    BoosterHandle result;
-    
-    if(jhandles) {
-        len = (bst_ulong)jenv->GetArrayLength(jhandles);
-        handles = new DMatrixHandle[len];
-        //put handle from jhandles to chandles
-        cjhandles = jenv->GetLongArrayElements(jhandles, 0);
-        for(bst_ulong i=0; i<len; i++) {
-            handles[i] = (DMatrixHandle) cjhandles[i];
-        }
-    }
-    
-    int ret = XGBoosterCreate(handles, len, &result);    
-    //release
-    if(jhandles) {
-        delete[] handles;
-        jenv->ReleaseLongArrayElements(jhandles, cjhandles, 0);
+  DMatrixHandle* handles = NULL;
+  bst_ulong len = 0;
+  jlong* cjhandles = 0;
+  BoosterHandle result;
+
+  if (jhandles) {
+    len = (bst_ulong)jenv->GetArrayLength(jhandles);
+    handles = new DMatrixHandle[len];
+    //put handle from jhandles to chandles
+    cjhandles = jenv->GetLongArrayElements(jhandles, 0);
+    for(bst_ulong i=0; i<len; i++) {
+      handles[i] = (DMatrixHandle) cjhandles[i];
     }
-    setHandle(jenv, jout, result);
-    
-    return ret;
+  }
+
+  int ret = XGBoosterCreate(handles, len, &result);
+  //release
+  if (jhandles) {
+    delete[] handles;
+    jenv->ReleaseLongArrayElements(jhandles, cjhandles, 0);
+  }
+  setHandle(jenv, jout, result);
+  return ret;
 }
 
 /*
@@ -316,14 +320,14 @@ JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_XGBoosterFree
  */
 JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_XGBoosterSetParam
   (JNIEnv *jenv, jclass jcls, jlong jhandle, jstring jname, jstring jvalue) {
-    BoosterHandle handle = (BoosterHandle) jhandle;    
-    const char* name = jenv->GetStringUTFChars(jname, 0);
-    const char* value = jenv->GetStringUTFChars(jvalue, 0);
-    int ret = XGBoosterSetParam(handle, name, value);
-    //release
-    if (name) jenv->ReleaseStringUTFChars(jname, name);
-    if (value) jenv->ReleaseStringUTFChars(jvalue, value);    
-    return ret;
+  BoosterHandle handle = (BoosterHandle) jhandle;
+  const char* name = jenv->GetStringUTFChars(jname, 0);
+  const char* value = jenv->GetStringUTFChars(jvalue, 0);
+  int ret = XGBoosterSetParam(handle, name, value);
+  //release
+  if (name) jenv->ReleaseStringUTFChars(jname, name);
+  if (value) jenv->ReleaseStringUTFChars(jvalue, value);
+  return ret;
 }
 
 /*
@@ -333,9 +337,9 @@ JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_XGBoosterSetParam
  */
 JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_XGBoosterUpdateOneIter
   (JNIEnv *jenv, jclass jcls, jlong jhandle, jint jiter, jlong jdtrain) {
-    BoosterHandle handle = (BoosterHandle) jhandle;
-    DMatrixHandle dtrain = (DMatrixHandle) jdtrain;
-    return XGBoosterUpdateOneIter(handle, jiter, dtrain);
+  BoosterHandle handle = (BoosterHandle) jhandle;
+  DMatrixHandle dtrain = (DMatrixHandle) jdtrain;
+  return XGBoosterUpdateOneIter(handle, jiter, dtrain);
 }
 
 /*
@@ -345,16 +349,16 @@ JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_XGBoosterUpdateOneIter
  */
 JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_XGBoosterBoostOneIter
   (JNIEnv *jenv, jclass jcls, jlong jhandle, jlong jdtrain, jfloatArray jgrad, jfloatArray jhess) {
-    BoosterHandle handle = (BoosterHandle) jhandle;
-    DMatrixHandle dtrain = (DMatrixHandle) jdtrain;
-    jfloat* grad = jenv->GetFloatArrayElements(jgrad, 0);
-    jfloat* hess = jenv->GetFloatArrayElements(jhess, 0);
-    bst_ulong len = (bst_ulong)jenv->GetArrayLength(jgrad);
-    int ret = XGBoosterBoostOneIter(handle, dtrain, grad, hess, len);    
-    //release
-    jenv->ReleaseFloatArrayElements(jgrad, grad, 0);
-    jenv->ReleaseFloatArrayElements(jhess, hess, 0);    
-    return ret;
+  BoosterHandle handle = (BoosterHandle) jhandle;
+  DMatrixHandle dtrain = (DMatrixHandle) jdtrain;
+  jfloat* grad = jenv->GetFloatArrayElements(jgrad, 0);
+  jfloat* hess = jenv->GetFloatArrayElements(jhess, 0);
+  bst_ulong len = (bst_ulong)jenv->GetArrayLength(jgrad);
+  int ret = XGBoosterBoostOneIter(handle, dtrain, grad, hess, len);
+  //release
+  jenv->ReleaseFloatArrayElements(jgrad, grad, 0);
+  jenv->ReleaseFloatArrayElements(jhess, hess, 0);
+  return ret;
 }
 
 /*
@@ -364,45 +368,45 @@ JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_XGBoosterBoostOneIter
  */
 JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_XGBoosterEvalOneIter
   (JNIEnv *jenv, jclass jcls, jlong jhandle, jint jiter, jlongArray jdmats, jobjectArray jevnames, jobjectArray jout) {
-    BoosterHandle handle = (BoosterHandle) jhandle;
-    DMatrixHandle* dmats = 0;
-    char **evnames = 0;
-    char *result = 0;
-    bst_ulong len = (bst_ulong)jenv->GetArrayLength(jdmats);     
-    if(len > 0) {
-        dmats = new DMatrixHandle[len];
-        evnames = new char*[len];
-    }
-    //put handle from jhandles to chandles
-    jlong* cjdmats = jenv->GetLongArrayElements(jdmats, 0);
+  BoosterHandle handle = (BoosterHandle) jhandle;
+  DMatrixHandle* dmats = 0;
+  char **evnames = 0;
+  char *result = 0;
+  bst_ulong len = (bst_ulong)jenv->GetArrayLength(jdmats);
+  if(len > 0) {
+    dmats = new DMatrixHandle[len];
+    evnames = new char*[len];
+  }
+  //put handle from jhandles to chandles
+  jlong* cjdmats = jenv->GetLongArrayElements(jdmats, 0);
+  for(bst_ulong i=0; i<len; i++) {
+    dmats[i] = (DMatrixHandle) cjdmats[i];
+  }
+  //transfer jObjectArray to char**, user strcpy and release JNI char* inplace
+  for(bst_ulong i=0; i<len; i++) {
+    jstring jevname = (jstring)jenv->GetObjectArrayElement(jevnames, i);
+    const char* cevname = jenv->GetStringUTFChars(jevname, 0);
+    evnames[i] = new char[jenv->GetStringLength(jevname)];
+    strcpy(evnames[i], cevname);
+    jenv->ReleaseStringUTFChars(jevname, cevname);
+  }
+
+  int ret = XGBoosterEvalOneIter(handle, jiter, dmats, (char const *(*)) evnames, len, (const char **) &result);
+  if(len > 0) {
+    delete[] dmats;
+    //release string chars
     for(bst_ulong i=0; i<len; i++) {
-        dmats[i] = (DMatrixHandle) cjdmats[i];
-    }
-    //transfer jObjectArray to char**, user strcpy and release JNI char* inplace
-    for(bst_ulong i=0; i<len; i++) {
-        jstring jevname = (jstring)jenv->GetObjectArrayElement(jevnames, i);
-        const char* cevname = jenv->GetStringUTFChars(jevname, 0);
-        evnames[i] = new char[jenv->GetStringLength(jevname)];
-        strcpy(evnames[i], cevname);
-        jenv->ReleaseStringUTFChars(jevname, cevname);
-    }
-    
-    int ret = XGBoosterEvalOneIter(handle, jiter, dmats, (char const *(*)) evnames, len, (const char **) &result);    
-    if(len > 0) {
-        delete[] dmats;
-        //release string chars
-        for(bst_ulong i=0; i<len; i++) {
-            delete[] evnames[i];
-        }        
-        delete[] evnames;
-        jenv->ReleaseLongArrayElements(jdmats, cjdmats, 0);
+      delete[] evnames[i];
     }
-    
-    jstring jinfo = 0;
-    if (result) jinfo = jenv->NewStringUTF((const char *) result);
-    jenv->SetObjectArrayElement(jout, 0, jinfo);
-  
-    return ret;
+    delete[] evnames;
+    jenv->ReleaseLongArrayElements(jdmats, cjdmats, 0);
+  }
+
+  jstring jinfo = 0;
+  if (result) jinfo = jenv->NewStringUTF((const char *) result);
+  jenv->SetObjectArrayElement(jout, 0, jinfo);
+
+  return ret;
 }
 
 /*
@@ -412,17 +416,17 @@ JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_XGBoosterEvalOneIter
  */
 JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_XGBoosterPredict
   (JNIEnv *jenv, jclass jcls, jlong jhandle, jlong jdmat, jint joption_mask, jint jntree_limit, jobjectArray jout) {
-    BoosterHandle handle = (BoosterHandle) jhandle;
-    DMatrixHandle dmat = (DMatrixHandle) jdmat;
-    bst_ulong len;
-    float *result;
-    int ret = XGBoosterPredict(handle, dmat, joption_mask, (unsigned int) jntree_limit, &len, (const float **) &result);
-    
-    jsize jlen = (jsize) len;
-    jfloatArray jarray = jenv->NewFloatArray(jlen);
-    jenv->SetFloatArrayRegion(jarray, 0, jlen, (jfloat *) result);
-    jenv->SetObjectArrayElement(jout, 0, jarray);    
-    return ret;
+  BoosterHandle handle = (BoosterHandle) jhandle;
+  DMatrixHandle dmat = (DMatrixHandle) jdmat;
+  bst_ulong len;
+  float *result;
+  int ret = XGBoosterPredict(handle, dmat, joption_mask, (unsigned int) jntree_limit, &len, (const float **) &result);
+
+  jsize jlen = (jsize) len;
+  jfloatArray jarray = jenv->NewFloatArray(jlen);
+  jenv->SetFloatArrayRegion(jarray, 0, jlen, (jfloat *) result);
+  jenv->SetObjectArrayElement(jout, 0, jarray);
+  return ret;
 }
 
 /*
@@ -432,12 +436,12 @@ JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_XGBoosterPredict
  */
 JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_XGBoosterLoadModel
   (JNIEnv *jenv, jclass jcls, jlong jhandle, jstring jfname) {
-    BoosterHandle handle = (BoosterHandle) jhandle;
-    const char* fname = jenv->GetStringUTFChars(jfname, 0);
-  
-    int ret = XGBoosterLoadModel(handle, fname);
-    if (fname) jenv->ReleaseStringUTFChars(jfname,fname);
-    return ret;
+  BoosterHandle handle = (BoosterHandle) jhandle;
+  const char* fname = jenv->GetStringUTFChars(jfname, 0);
+
+  int ret = XGBoosterLoadModel(handle, fname);
+  if (fname) jenv->ReleaseStringUTFChars(jfname,fname);
+  return ret;
 }
 
 /*
@@ -447,13 +451,13 @@ JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_XGBoosterLoadModel
  */
 JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_XGBoosterSaveModel
   (JNIEnv *jenv, jclass jcls, jlong jhandle, jstring jfname) {
-    BoosterHandle handle = (BoosterHandle) jhandle;
-    const char*  fname = jenv->GetStringUTFChars(jfname, 0);
-    
-    int ret = XGBoosterSaveModel(handle, fname);
-    if (fname) jenv->ReleaseStringUTFChars(jfname, fname);
-    
-    return ret;
+  BoosterHandle handle = (BoosterHandle) jhandle;
+  const char*  fname = jenv->GetStringUTFChars(jfname, 0);
+
+  int ret = XGBoosterSaveModel(handle, fname);
+  if (fname) jenv->ReleaseStringUTFChars(jfname, fname);
+
+  return ret;
 }
 
 /*
@@ -463,9 +467,9 @@ JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_XGBoosterSaveModel
  */
 JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_XGBoosterLoadModelFromBuffer
   (JNIEnv *jenv, jclass jcls, jlong jhandle, jlong jbuf, jlong jlen) {
-    BoosterHandle handle = (BoosterHandle) jhandle;
-    void *buf = (void*) jbuf;
-    return XGBoosterLoadModelFromBuffer(handle, (void const *)buf, (bst_ulong) jlen);
+  BoosterHandle handle = (BoosterHandle) jhandle;
+  void *buf = (void*) jbuf;
+  return XGBoosterLoadModelFromBuffer(handle, (void const *)buf, (bst_ulong) jlen);
 }
 
 /*
@@ -475,16 +479,16 @@ JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_XGBoosterLoadModelFromB
  */
 JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_XGBoosterGetModelRaw
   (JNIEnv * jenv, jclass jcls, jlong jhandle, jobjectArray jout) {
-    BoosterHandle handle = (BoosterHandle) jhandle;
-    bst_ulong len = 0;
-    char *result;
+  BoosterHandle handle = (BoosterHandle) jhandle;
+  bst_ulong len = 0;
+  char *result;
 
-    int ret = XGBoosterGetModelRaw(handle, &len, (const char **) &result);
-    if (result){
-        jstring jinfo = jenv->NewStringUTF((const char *) result);
-        jenv->SetObjectArrayElement(jout, 0, jinfo);
-    }
-    return ret;
+  int ret = XGBoosterGetModelRaw(handle, &len, (const char **) &result);
+  if (result) {
+    jstring jinfo = jenv->NewStringUTF((const char *) result);
+    jenv->SetObjectArrayElement(jout, 0, jinfo);
+  }
+  return ret;
 }
 
 /*
@@ -494,20 +498,129 @@ JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_XGBoosterGetModelRaw
  */
 JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_XGBoosterDumpModel
   (JNIEnv *jenv, jclass jcls, jlong jhandle, jstring jfmap, jint jwith_stats, jobjectArray jout) {
-    BoosterHandle handle = (BoosterHandle) jhandle;
-    const char *fmap = jenv->GetStringUTFChars(jfmap, 0);
-    bst_ulong len = 0; 
-    char **result;
-    
-    int ret = XGBoosterDumpModel(handle, fmap, jwith_stats, &len, (const char ***) &result);
-    
-    jsize jlen = (jsize) len;
-    jobjectArray jinfos = jenv->NewObjectArray(jlen, jenv->FindClass("java/lang/String"), jenv->NewStringUTF(""));
-    for(int i=0 ; i<jlen; i++) {
-        jenv->SetObjectArrayElement(jinfos, i, jenv->NewStringUTF((const char*) result[i]));
-    }
-    jenv->SetObjectArrayElement(jout, 0, jinfos);
-    
-    if (fmap) jenv->ReleaseStringUTFChars(jfmap, (const char *)fmap);   
-    return ret;
+  BoosterHandle handle = (BoosterHandle) jhandle;
+  const char *fmap = jenv->GetStringUTFChars(jfmap, 0);
+  bst_ulong len = 0;
+  char **result;
+
+  int ret = XGBoosterDumpModel(handle, fmap, jwith_stats, &len, (const char ***) &result);
+
+  jsize jlen = (jsize) len;
+  jobjectArray jinfos = jenv->NewObjectArray(jlen, jenv->FindClass("java/lang/String"), jenv->NewStringUTF(""));
+  for(int i=0 ; i<jlen; i++) {
+    jenv->SetObjectArrayElement(jinfos, i, jenv->NewStringUTF((const char*) result[i]));
+  }
+  jenv->SetObjectArrayElement(jout, 0, jinfos);
+
+  if (fmap) jenv->ReleaseStringUTFChars(jfmap, (const char *)fmap);
+  return ret;
+}
+
+/*
+ * Class:     ml_dmlc_xgboost4j_XgboostJNI
+ * Method:    XGBoosterLoadRabitCheckpoint
+ * Signature: (J[I)I
+ */
+JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_XGBoosterLoadRabitCheckpoint
+  (JNIEnv *jenv , jclass jcls, jlong jhandle, jintArray jout) {
+  BoosterHandle handle = (BoosterHandle) jhandle;
+  int version;
+  int ret = XGBoosterLoadRabitCheckpoint(handle, &version);
+  jenv->SetIntArrayRegion(jout, 0, 1, &version);
+  return ret;
+}
+
+/*
+ * Class:     ml_dmlc_xgboost4j_XgboostJNI
+ * Method:    XGBoosterSaveRabitCheckpoint
+ * Signature: (J)I
+ */
+JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_XGBoosterSaveRabitCheckpoint
+  (JNIEnv *jenv, jclass jcls, jlong jhandle) {
+  BoosterHandle handle = (BoosterHandle) jhandle;
+  return XGBoosterSaveRabitCheckpoint(handle);
+}
+
+/*
+ * Class:     ml_dmlc_xgboost4j_XgboostJNI
+ * Method:    RabitInit
+ * Signature: ([Ljava/lang/String;)I
+ */
+JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_RabitInit
+  (JNIEnv *jenv, jclass jcls, jobjectArray jargs) {
+  std::vector<std::string> args;
+  std::vector<char*> argv;
+  bst_ulong len = (bst_ulong)jenv->GetArrayLength(jargs);
+  for (bst_ulong i = 0; i < len; ++i) {
+    jstring arg = (jstring)jenv->GetObjectArrayElement(jargs, i);
+    std::string s(jenv->GetStringUTFChars(arg, 0),
+                  jenv->GetStringLength(arg));
+    if (s.length() != 0) args.push_back(s);
+  }
+
+  for (size_t i = 0; i < args.size(); ++i) {
+    argv.push_back(&args[i][0]);
+  }
+  RabitInit(args.size(), args.size() == 0 ? NULL : &argv[0]);
+  return 0;
+}
+
+/*
+ * Class:     ml_dmlc_xgboost4j_XgboostJNI
+ * Method:    RabitFinalize
+ * Signature: ()I
+ */
+JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_RabitFinalize
+  (JNIEnv *jenv, jclass jcls) {
+  RabitFinalize();
+  return 0;
+}
+
+/*
+ * Class:     ml_dmlc_xgboost4j_XgboostJNI
+ * Method:    RabitTrackerPrint
+ * Signature: (Ljava/lang/String;)I
+ */
+JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_RabitTrackerPrint
+  (JNIEnv *jenv, jclass jcls, jstring jmsg) {
+  std::string str(jenv->GetStringUTFChars(jmsg, 0),
+                  jenv->GetStringLength(jmsg));
+  RabitTrackerPrint(str.c_str());
+  return 0;
+}
+
+/*
+ * Class:     ml_dmlc_xgboost4j_XgboostJNI
+ * Method:    RabitGetRank
+ * Signature: ([I)I
+ */
+JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_RabitGetRank
+  (JNIEnv *jenv, jclass jcls, jintArray jout) {
+  int rank = RabitGetRank();
+  jenv->SetIntArrayRegion(jout, 0, 1, &rank);
+  return 0;
+}
+
+/*
+ * Class:     ml_dmlc_xgboost4j_XgboostJNI
+ * Method:    RabitGetWorldSize
+ * Signature: ([I)I
+ */
+JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_RabitGetWorldSize
+  (JNIEnv *jenv, jclass jcls, jintArray jout) {
+  int out = RabitGetWorldSize();
+  jenv->SetIntArrayRegion(jout, 0, 1, &out);
+  return 0;
+}
+
+/*
+ * Class:     ml_dmlc_xgboost4j_XgboostJNI
+ * Method:    RabitVersionNumber
+ * Signature: ([I)I
+ */
+JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_RabitVersionNumber
+  (JNIEnv *jenv, jclass jcls, jintArray jout) {
+  int out = RabitVersionNumber();
+  jenv->SetIntArrayRegion(jout, 0, 1, &out);
+  return 0;
 }