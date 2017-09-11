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

#include "xgboost/c_api.h"
#include "xgboost4j.h"
#include <cstring>

//helper functions
//set handle
void setHandle(JNIEnv *jenv, jlongArray jhandle, void* handle) {
    long out[1];
    out[0] = (long) handle;
    jenv->SetLongArrayRegion(jhandle, 0, 1, (const jlong*) out);
}

JNIEXPORT jstring JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_XGBGetLastError
  (JNIEnv *jenv, jclass jcls) {
    jstring jresult = 0 ;
    const char* result = XGBGetLastError();
    if (result) jresult = jenv->NewStringUTF(result);
    return jresult;
}

JNIEXPORT jint JNICALL Java_ml_dmlc_xgboost4j_XgboostJNI_XGDMatrixCreateFromFile
  (JNIEnv *jenv, jclass jcls, jstring jfname, jint jsilent, jlongArray jout) {
    DMatrixHandle result;
    const char* fname = jenv->GetStringUTFChars(jfname, 0);
    int ret = XGDMatrixCreateFromFile(fname, jsilent, &result);
    if (fname) jenv->ReleaseStringUTFChars(jfname, fname);    
    setHandle(jenv, jout, result);
    return ret;
}

/*
