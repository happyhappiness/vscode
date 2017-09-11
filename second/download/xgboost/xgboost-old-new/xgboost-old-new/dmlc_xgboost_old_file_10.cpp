/*
  Copyright (c) 2014 by Contributors
  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

  http://www.apache.org/licenses/LICENSE-2.0
  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.
*/

#include <xgboost/c_api.h>
#include <xgboost/base.h>
#include <xgboost/logging.h>
#include "./xgboost4j.h"
#include <cstring>
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
  const char* result = XGBGetLastError();
  if (result != NULL) {
    jresult = jenv->NewStringUTF(result);
  }
  return jresult;
}

JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_XGDMatrixCreateFromFile
  (JNIEnv *jenv, jclass jcls, jstring jfname, jint jsilent, jlongArray jout) {
  DMatrixHandle result;
  const char* fname = jenv->GetStringUTFChars(jfname, 0);
  int ret = XGDMatrixCreateFromFile(fname, jsilent, &result);
  if (fname) {
    jenv->ReleaseStringUTFChars(jfname, fname);
  }
  setHandle(jenv, jout, result);
  return ret;
}

/*
 * Class:     ml_dmlc_xgboost4j_XgboostJNI
 * Method:    XGDMatrixCreateFromCSR
 * Signature: ([J[J[F)J
 */
JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_XGDMatrixCreateFromCSR
  (JNIEnv *jenv, jclass jcls, jlongArray jindptr, jintArray jindices, jfloatArray jdata, jlongArray jout) {
  DMatrixHandle result;
  jlong* indptr = jenv->GetLongArrayElements(jindptr, 0);
  jint* indices = jenv->GetIntArrayElements(jindices, 0);
  jfloat* data = jenv->GetFloatArrayElements(jdata, 0);
  bst_ulong nindptr = (bst_ulong)jenv->GetArrayLength(jindptr);
  bst_ulong nelem = (bst_ulong)jenv->GetArrayLength(jdata);
  int ret = (jint) XGDMatrixCreateFromCSR((unsigned long const *)indptr, (unsigned int const *)indices, (float const *)data, nindptr, nelem, &result);
  setHandle(jenv, jout, result);
  //Release
  jenv->ReleaseLongArrayElements(jindptr, indptr, 0);
  jenv->ReleaseIntArrayElements(jindices, indices, 0);
  jenv->ReleaseFloatArrayElements(jdata, data, 0);
  return ret;
}

/*
 * Class:     ml_dmlc_xgboost4j_XgboostJNI
 * Method:    XGDMatrixCreateFromCSC
 * Signature: ([J[J[F)J
 */
JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_XGDMatrixCreateFromCSC
  (JNIEnv *jenv, jclass jcls, jlongArray jindptr, jintArray jindices, jfloatArray jdata, jlongArray jout) {
  DMatrixHandle result;
  jlong* indptr = jenv->GetLongArrayElements(jindptr, NULL);
  jint* indices = jenv->GetIntArrayElements(jindices, 0);
  jfloat* data = jenv->GetFloatArrayElements(jdata, NULL);
  bst_ulong nindptr = (bst_ulong)jenv->GetArrayLength(jindptr);
  bst_ulong nelem = (bst_ulong)jenv->GetArrayLength(jdata);

  int ret = (jint) XGDMatrixCreateFromCSC((unsigned long const *)indptr, (unsigned int const *)indices, (float const *)data, nindptr, nelem, &result);
  setHandle(jenv, jout, result);
  //release
  jenv->ReleaseLongArrayElements(jindptr, indptr, 0);
  jenv->ReleaseIntArrayElements(jindices, indices, 0);
  jenv->ReleaseFloatArrayElements(jdata, data, 0);

  return ret;
}

/*
 * Class:     ml_dmlc_xgboost4j_XgboostJNI
 * Method:    XGDMatrixCreateFromMat
 * Signature: ([FIIF)J
 */
JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_XGDMatrixCreateFromMat
  (JNIEnv *jenv, jclass jcls, jfloatArray jdata, jint jnrow, jint jncol, jfloat jmiss, jlongArray jout) {
  DMatrixHandle result;
  jfloat* data = jenv->GetFloatArrayElements(jdata, 0);
  bst_ulong nrow = (bst_ulong)jnrow;
  bst_ulong ncol = (bst_ulong)jncol;
  int ret = (jint) XGDMatrixCreateFromMat((float const *)data, nrow, ncol, jmiss, &result);
  setHandle(jenv, jout, result);
  //release
  jenv->ReleaseFloatArrayElements(jdata, data, 0);
  return ret;
}

/*
 * Class:     ml_dmlc_xgboost4j_XgboostJNI
 * Method:    XGDMatrixSliceDMatrix
 * Signature: (J[I)J
 */
JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_XGDMatrixSliceDMatrix
  (JNIEnv *jenv, jclass jcls, jlong jhandle, jintArray jindexset, jlongArray jout) {
  DMatrixHandle result;
  DMatrixHandle handle = (DMatrixHandle) jhandle;

  jint* indexset = jenv->GetIntArrayElements(jindexset, 0);
  bst_ulong len = (bst_ulong)jenv->GetArrayLength(jindexset);

  int ret = XGDMatrixSliceDMatrix(handle, (int const *)indexset, len, &result);
  setHandle(jenv, jout, result);
  //release
  jenv->ReleaseIntArrayElements(jindexset, indexset, 0);

  return ret;
}

/*
 * Class:     ml_dmlc_xgboost4j_XgboostJNI
 * Method:    XGDMatrixFree
 * Signature: (J)V
 */
JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_XGDMatrixFree
  (JNIEnv *jenv, jclass jcls, jlong jhandle) {
  DMatrixHandle handle = (DMatrixHandle) jhandle;
  int ret = XGDMatrixFree(handle);
  return ret;
}

/*
 * Class:     ml_dmlc_xgboost4j_XgboostJNI
 * Method:    XGDMatrixSaveBinary
 * Signature: (JLjava/lang/String;I)V
 */
JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_XGDMatrixSaveBinary
  (JNIEnv *jenv, jclass jcls, jlong jhandle, jstring jfname, jint jsilent) {
  DMatrixHandle handle = (DMatrixHandle) jhandle;
  const char* fname = jenv->GetStringUTFChars(jfname, 0);
  int ret = XGDMatrixSaveBinary(handle, fname, jsilent);
  if (fname) jenv->ReleaseStringUTFChars(jfname, (const char *)fname);
  return ret;
}

/*
 * Class:     ml_dmlc_xgboost4j_XgboostJNI
 * Method:    XGDMatrixSetFloatInfo
 * Signature: (JLjava/lang/String;[F)V
 */
JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_XGDMatrixSetFloatInfo
  (JNIEnv *jenv, jclass jcls, jlong jhandle, jstring jfield, jfloatArray jarray) {
  DMatrixHandle handle = (DMatrixHandle) jhandle;
  const char*  field = jenv->GetStringUTFChars(jfield, 0);

  jfloat* array = jenv->GetFloatArrayElements(jarray, NULL);
  bst_ulong len = (bst_ulong)jenv->GetArrayLength(jarray);
  int ret = XGDMatrixSetFloatInfo(handle, field, (float const *)array, len);
  //release
  if (field) jenv->ReleaseStringUTFChars(jfield, field);
  jenv->ReleaseFloatArrayElements(jarray, array, 0);
  return ret;
}

/*
 * Class:     ml_dmlc_xgboost4j_XgboostJNI
 * Method:    XGDMatrixSetUIntInfo
 * Signature: (JLjava/lang/String;[I)V
 */
JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_XGDMatrixSetUIntInfo
  (JNIEnv *jenv, jclass jcls, jlong jhandle, jstring jfield, jintArray jarray) {
  DMatrixHandle handle = (DMatrixHandle) jhandle;
  const char*  field = jenv->GetStringUTFChars(jfield, 0);
  jint* array = jenv->GetIntArrayElements(jarray, NULL);
  bst_ulong len = (bst_ulong)jenv->GetArrayLength(jarray);
  int ret = XGDMatrixSetUIntInfo(handle, (char const *)field, (unsigned int const *)array, len);
  //release
  if (field) jenv->ReleaseStringUTFChars(jfield, (const char *)field);
  jenv->ReleaseIntArrayElements(jarray, array, 0);

  return ret;
}

/*
 * Class:     ml_dmlc_xgboost4j_XgboostJNI
 * Method:    XGDMatrixSetGroup
 * Signature: (J[I)V
 */
JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_XGDMatrixSetGroup
  (JNIEnv * jenv, jclass jcls, jlong jhandle, jintArray jarray) {
  DMatrixHandle handle = (DMatrixHandle) jhandle;
  jint* array = jenv->GetIntArrayElements(jarray, NULL);
  bst_ulong len = (bst_ulong)jenv->GetArrayLength(jarray);
  int ret = XGDMatrixSetGroup(handle, (unsigned int const *)array, len);
  //release
  jenv->ReleaseIntArrayElements(jarray, array, 0);
  return ret;
}

/*
 * Class:     ml_dmlc_xgboost4j_XgboostJNI
 * Method:    XGDMatrixGetFloatInfo
 * Signature: (JLjava/lang/String;)[F
 */
JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_XGDMatrixGetFloatInfo
  (JNIEnv *jenv, jclass jcls, jlong jhandle, jstring jfield, jobjectArray jout) {
  DMatrixHandle handle = (DMatrixHandle) jhandle;
  const char*  field = jenv->GetStringUTFChars(jfield, 0);
  bst_ulong len;
  float *result;
  int ret = XGDMatrixGetFloatInfo(handle, field, &len, (const float**) &result);
  if (field) jenv->ReleaseStringUTFChars(jfield, field);

  jsize jlen = (jsize) len;
  jfloatArray jarray = jenv->NewFloatArray(jlen);
  jenv->SetFloatArrayRegion(jarray, 0, jlen, (jfloat *) result);
  jenv->SetObjectArrayElement(jout, 0, (jobject) jarray);

  return ret;
}

/*
 * Class:     ml_dmlc_xgboost4j_XgboostJNI
 * Method:    XGDMatrixGetUIntInfo
 * Signature: (JLjava/lang/String;)[I
 */
JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_XGDMatrixGetUIntInfo
  (JNIEnv *jenv, jclass jcls, jlong jhandle, jstring jfield, jobjectArray jout) {
  DMatrixHandle handle = (DMatrixHandle) jhandle;
  const char*  field = jenv->GetStringUTFChars(jfield, 0);
  bst_ulong len;
  unsigned int *result;
  int ret = (jint) XGDMatrixGetUIntInfo(handle, field, &len, (const unsigned int **) &result);
  if (field) jenv->ReleaseStringUTFChars(jfield, field);

  jsize jlen = (jsize) len;
  jintArray jarray = jenv->NewIntArray(jlen);
  jenv->SetIntArrayRegion(jarray, 0, jlen, (jint *) result);
  jenv->SetObjectArrayElement(jout, 0, jarray);
  return ret;
}

/*
 * Class:     ml_dmlc_xgboost4j_XgboostJNI
 * Method:    XGDMatrixNumRow
 * Signature: (J)J
 */
JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_XGDMatrixNumRow
  (JNIEnv *jenv, jclass jcls, jlong jhandle, jlongArray jout) {
  DMatrixHandle handle = (DMatrixHandle) jhandle;
  bst_ulong result[1];
  int ret = (jint) XGDMatrixNumRow(handle, result);
  jenv->SetLongArrayRegion(jout, 0, 1, (const jlong *) result);
  return ret;
}

/*
 * Class:     ml_dmlc_xgboost4j_XgboostJNI
 * Method:    XGBoosterCreate
 * Signature: ([J)J
 */
JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_XGBoosterCreate
  (JNIEnv *jenv, jclass jcls, jlongArray jhandles, jlongArray jout) {
  std::vector<DMatrixHandle> handles;
  if (jhandles != nullptr) {
    size_t len = jenv->GetArrayLength(jhandles);
    jlong *cjhandles = jenv->GetLongArrayElements(jhandles, 0);
    for (size_t i = 0; i < len; ++i) {
      handles.push_back((DMatrixHandle) cjhandles[i]);
    }
    jenv->ReleaseLongArrayElements(jhandles, cjhandles, 0);
  }
  BoosterHandle result;
  int ret = XGBoosterCreate(dmlc::BeginPtr(handles), handles.size(), &result);
  setHandle(jenv, jout, result);
  return ret;
}

/*
 * Class:     ml_dmlc_xgboost4j_XgboostJNI
 * Method:    XGBoosterFree
 * Signature: (J)V
 */
JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_XGBoosterFree
  (JNIEnv *jenv, jclass jcls, jlong jhandle) {
    BoosterHandle handle = (BoosterHandle) jhandle;
    return XGBoosterFree(handle);
}


/*
 * Class:     ml_dmlc_xgboost4j_XgboostJNI
 * Method:    XGBoosterSetParam
 * Signature: (JLjava/lang/String;Ljava/lang/String;)V
 */
JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_XGBoosterSetParam
  (JNIEnv *jenv, jclass jcls, jlong jhandle, jstring jname, jstring jvalue) {
  BoosterHandle handle = (BoosterHandle) jhandle;
  const char* name = jenv->GetStringUTFChars(jname, 0);
  const char* value = jenv->GetStringUTFChars(jvalue, 0);
  int ret = XGBoosterSetParam(handle, name, value);
  //release
  if (name) jenv->ReleaseStringUTFChars(jname, name);
  if (value) jenv->ReleaseStringUTFChars(jvalue, value);
  return ret;
}

/*
 * Class:     ml_dmlc_xgboost4j_XgboostJNI
 * Method:    XGBoosterUpdateOneIter
 * Signature: (JIJ)V
 */
JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_XGBoosterUpdateOneIter
  (JNIEnv *jenv, jclass jcls, jlong jhandle, jint jiter, jlong jdtrain) {
  BoosterHandle handle = (BoosterHandle) jhandle;
  DMatrixHandle dtrain = (DMatrixHandle) jdtrain;
  return XGBoosterUpdateOneIter(handle, jiter, dtrain);
}

/*
 * Class:     ml_dmlc_xgboost4j_XgboostJNI
 * Method:    XGBoosterBoostOneIter
 * Signature: (JJ[F[F)V
 */
JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_XGBoosterBoostOneIter
  (JNIEnv *jenv, jclass jcls, jlong jhandle, jlong jdtrain, jfloatArray jgrad, jfloatArray jhess) {
  BoosterHandle handle = (BoosterHandle) jhandle;
  DMatrixHandle dtrain = (DMatrixHandle) jdtrain;
  jfloat* grad = jenv->GetFloatArrayElements(jgrad, 0);
  jfloat* hess = jenv->GetFloatArrayElements(jhess, 0);
  bst_ulong len = (bst_ulong)jenv->GetArrayLength(jgrad);
  int ret = XGBoosterBoostOneIter(handle, dtrain, grad, hess, len);
  //release
  jenv->ReleaseFloatArrayElements(jgrad, grad, 0);
  jenv->ReleaseFloatArrayElements(jhess, hess, 0);
  return ret;
}

/*
 * Class:     ml_dmlc_xgboost4j_XgboostJNI
 * Method:    XGBoosterEvalOneIter
 * Signature: (JI[J[Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_XGBoosterEvalOneIter
  (JNIEnv *jenv, jclass jcls, jlong jhandle, jint jiter, jlongArray jdmats, jobjectArray jevnames, jobjectArray jout) {
  BoosterHandle handle = (BoosterHandle) jhandle;
  std::vector<DMatrixHandle> dmats;
  std::vector<std::string> evnames;
  std::vector<const char*> evchars;

  size_t len =  static_cast<size_t>(jenv->GetArrayLength(jdmats));
  // put handle from jhandles to chandles
  jlong* cjdmats = jenv->GetLongArrayElements(jdmats, 0);
  for (size_t i = 0; i < len; ++i) {
    dmats.push_back((DMatrixHandle) cjdmats[i]);
    jstring jevname = (jstring)jenv->GetObjectArrayElement(jevnames, i);
    const char *s =jenv->GetStringUTFChars(jevname, 0);
    evnames.push_back(std::string(s, jenv->GetStringLength(jevname)));
    if (s != nullptr) jenv->ReleaseStringUTFChars(jevname, s);
  }
  jenv->ReleaseLongArrayElements(jdmats, cjdmats, 0);
  for (size_t i = 0; i < len; ++i) {
    evchars.push_back(evnames[i].c_str());
  }
  const char* result;
  int ret = XGBoosterEvalOneIter(handle, jiter,
                                 dmlc::BeginPtr(dmats),
                                 dmlc::BeginPtr(evchars),
                                 len, &result);
  jstring jinfo = nullptr;
  if (result != nullptr) {
    jinfo = jenv->NewStringUTF(result);
  }
  jenv->SetObjectArrayElement(jout, 0, jinfo);
  return ret;
}

/*
 * Class:     ml_dmlc_xgboost4j_XgboostJNI
 * Method:    XGBoosterPredict
 * Signature: (JJIJ)[F
 */
JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_XGBoosterPredict
  (JNIEnv *jenv, jclass jcls, jlong jhandle, jlong jdmat, jint joption_mask, jint jntree_limit, jobjectArray jout) {
  BoosterHandle handle = (BoosterHandle) jhandle;
  DMatrixHandle dmat = (DMatrixHandle) jdmat;
  bst_ulong len;
  float *result;
  int ret = XGBoosterPredict(handle, dmat, joption_mask, (unsigned int) jntree_limit, &len, (const float **) &result);

  jsize jlen = (jsize) len;
  jfloatArray jarray = jenv->NewFloatArray(jlen);
  jenv->SetFloatArrayRegion(jarray, 0, jlen, (jfloat *) result);
  jenv->SetObjectArrayElement(jout, 0, jarray);
  return ret;
}

/*
 * Class:     ml_dmlc_xgboost4j_XgboostJNI
 * Method:    XGBoosterLoadModel
 * Signature: (JLjava/lang/String;)V
 */
JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_XGBoosterLoadModel
  (JNIEnv *jenv, jclass jcls, jlong jhandle, jstring jfname) {
  BoosterHandle handle = (BoosterHandle) jhandle;
  const char* fname = jenv->GetStringUTFChars(jfname, 0);

  int ret = XGBoosterLoadModel(handle, fname);
  if (fname) jenv->ReleaseStringUTFChars(jfname,fname);
  return ret;
}

/*
 * Class:     ml_dmlc_xgboost4j_XgboostJNI
 * Method:    XGBoosterSaveModel
 * Signature: (JLjava/lang/String;)V
 */
JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_XGBoosterSaveModel
  (JNIEnv *jenv, jclass jcls, jlong jhandle, jstring jfname) {
  BoosterHandle handle = (BoosterHandle) jhandle;
  const char*  fname = jenv->GetStringUTFChars(jfname, 0);

  int ret = XGBoosterSaveModel(handle, fname);
  if (fname) jenv->ReleaseStringUTFChars(jfname, fname);
  return ret;
}

/*
 * Class:     ml_dmlc_xgboost4j_XgboostJNI
 * Method:    XGBoosterLoadModelFromBuffer
 * Signature: (J[B)I
 */
JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_XGBoosterLoadModelFromBuffer
    (JNIEnv *jenv, jclass jcls, jlong jhandle, jbyteArray jbytes) {
  BoosterHandle handle = (BoosterHandle) jhandle;
  jbyte* buffer = jenv->GetByteArrayElements(jbytes, 0);
  int ret = XGBoosterLoadModelFromBuffer(
      handle, buffer, jenv->GetArrayLength(jbytes));
  jenv->ReleaseByteArrayElements(jbytes, buffer, 0);
  return ret;
}

/*
 * Class:     ml_dmlc_xgboost4j_XgboostJNI
 * Method:    XGBoosterGetModelRaw
 * Signature: (J[[B)I
 */
JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_XGBoosterGetModelRaw
  (JNIEnv * jenv, jclass jcls, jlong jhandle, jobjectArray jout) {
  BoosterHandle handle = (BoosterHandle) jhandle;
  bst_ulong len = 0;
  const char* result;
  int ret = XGBoosterGetModelRaw(handle, &len, &result);

  if (result) {
    jbyteArray jarray = jenv->NewByteArray(len);
    jenv->SetByteArrayRegion(jarray, 0, len, (jbyte*)result);
    jenv->SetObjectArrayElement(jout, 0, jarray);
  }
  return ret;
}

/*
 * Class:     ml_dmlc_xgboost4j_XgboostJNI
 * Method:    XGBoosterDumpModel
 * Signature: (JLjava/lang/String;I)[Ljava/lang/String;
 */
JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_XGBoosterDumpModel
  (JNIEnv *jenv, jclass jcls, jlong jhandle, jstring jfmap, jint jwith_stats, jobjectArray jout) {
  BoosterHandle handle = (BoosterHandle) jhandle;
  const char *fmap = jenv->GetStringUTFChars(jfmap, 0);
  bst_ulong len = 0;
  char **result;

  int ret = XGBoosterDumpModel(handle, fmap, jwith_stats, &len, (const char ***) &result);

  jsize jlen = (jsize) len;
  jobjectArray jinfos = jenv->NewObjectArray(jlen, jenv->FindClass("java/lang/String"), jenv->NewStringUTF(""));
  for(int i=0 ; i<jlen; i++) {
    jenv->SetObjectArrayElement(jinfos, i, jenv->NewStringUTF((const char*) result[i]));
  }
  jenv->SetObjectArrayElement(jout, 0, jinfos);

  if (fmap) jenv->ReleaseStringUTFChars(jfmap, (const char *)fmap);
  return ret;
}

/*
 * Class:     ml_dmlc_xgboost4j_XgboostJNI
 * Method:    XGBoosterLoadRabitCheckpoint
 * Signature: (J[I)I
 */
JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_XGBoosterLoadRabitCheckpoint
  (JNIEnv *jenv , jclass jcls, jlong jhandle, jintArray jout) {
  BoosterHandle handle = (BoosterHandle) jhandle;
  int version;
  int ret = XGBoosterLoadRabitCheckpoint(handle, &version);
  jenv->SetIntArrayRegion(jout, 0, 1, &version);
  return ret;
}

/*
 * Class:     ml_dmlc_xgboost4j_XgboostJNI
 * Method:    XGBoosterSaveRabitCheckpoint
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_XGBoosterSaveRabitCheckpoint
  (JNIEnv *jenv, jclass jcls, jlong jhandle) {
  BoosterHandle handle = (BoosterHandle) jhandle;
  return XGBoosterSaveRabitCheckpoint(handle);
}

/*
 * Class:     ml_dmlc_xgboost4j_XgboostJNI
 * Method:    RabitInit
 * Signature: ([Ljava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_RabitInit
  (JNIEnv *jenv, jclass jcls, jobjectArray jargs) {
  std::vector<std::string> args;
  std::vector<char*> argv;
  bst_ulong len = (bst_ulong)jenv->GetArrayLength(jargs);
  for (bst_ulong i = 0; i < len; ++i) {
    jstring arg = (jstring)jenv->GetObjectArrayElement(jargs, i);
    const char *s = jenv->GetStringUTFChars(arg, 0);
    args.push_back(std::string(s, jenv->GetStringLength(arg)));
    if (s != nullptr) jenv->ReleaseStringUTFChars(arg, s);
    if (args.back().length() == 0) args.pop_back();
  }

  for (size_t i = 0; i < args.size(); ++i) {
    argv.push_back(&args[i][0]);
  }

  RabitInit(args.size(), dmlc::BeginPtr(argv));
  return 0;
}

/*
 * Class:     ml_dmlc_xgboost4j_XgboostJNI
 * Method:    RabitFinalize
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_RabitFinalize
  (JNIEnv *jenv, jclass jcls) {
  RabitFinalize();
  return 0;
}

/*
 * Class:     ml_dmlc_xgboost4j_XgboostJNI
 * Method:    RabitTrackerPrint
 * Signature: (Ljava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_RabitTrackerPrint
  (JNIEnv *jenv, jclass jcls, jstring jmsg) {
  std::string str(jenv->GetStringUTFChars(jmsg, 0),
                  jenv->GetStringLength(jmsg));
  RabitTrackerPrint(str.c_str());
  return 0;
}

/*
 * Class:     ml_dmlc_xgboost4j_XgboostJNI
 * Method:    RabitGetRank
 * Signature: ([I)I
 */
JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_RabitGetRank
  (JNIEnv *jenv, jclass jcls, jintArray jout) {
  int rank = RabitGetRank();
  jenv->SetIntArrayRegion(jout, 0, 1, &rank);
  return 0;
}

/*
 * Class:     ml_dmlc_xgboost4j_XgboostJNI
 * Method:    RabitGetWorldSize
 * Signature: ([I)I
 */
JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_RabitGetWorldSize
  (JNIEnv *jenv, jclass jcls, jintArray jout) {
  int out = RabitGetWorldSize();
  jenv->SetIntArrayRegion(jout, 0, 1, &out);
  return 0;
}

/*
 * Class:     ml_dmlc_xgboost4j_XgboostJNI
 * Method:    RabitVersionNumber
 * Signature: ([I)I
 */
JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_RabitVersionNumber
  (JNIEnv *jenv, jclass jcls, jintArray jout) {
  int out = RabitVersionNumber();
  jenv->SetIntArrayRegion(jout, 0, 1, &out);
  return 0;
}
