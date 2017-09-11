@@ -1,8 +1,8 @@
+#include "xgboost_R.h"
 #include <vector>
 #include <string>
 #include <utility>
 #include <cstring>
-#include "xgboost_R.h"
 #include "wrapper/xgboost_wrapper.h"
 #include "src/utils/utils.h"
 #include "src/utils/omp.h"
@@ -22,23 +22,46 @@ void HandlePrint(const char *msg) {
   Rprintf("%s", msg);
 }
 }  // namespace utils
+namespace random {
+void Seed(unsigned seed) {
+  warning("parameter seed is ignored, please set random seed using set.seed");
+}
+double Uniform(void) {
+  return unif_rand();
+}
+double Normal(void) {
+  return norm_rand();
+}
+}  // namespace random
 }  // namespace xgboost
 
+// call before wrapper starts
+inline void _WrapperBegin(void) {
+  GetRNGstate();
+}
+// call after wrapper starts
+inline void _WrapperEnd(void) {
+  PutRNGstate();
+}
+
 extern "C" {
   void _DMatrixFinalizer(SEXP ext) {    
     if (R_ExternalPtrAddr(ext) == NULL) return;
     XGDMatrixFree(R_ExternalPtrAddr(ext));
     R_ClearExternalPtr(ext);
   }
   SEXP XGDMatrixCreateFromFile_R(SEXP fname, SEXP silent) {
+    _WrapperBegin();
     void *handle = XGDMatrixCreateFromFile(CHAR(asChar(fname)), asInteger(silent));
     SEXP ret = PROTECT(R_MakeExternalPtr(handle, R_NilValue, R_NilValue));
     R_RegisterCFinalizerEx(ret, _DMatrixFinalizer, TRUE);
     UNPROTECT(1);
+    _WrapperEnd();
     return ret;
   }
   SEXP XGDMatrixCreateFromMat_R(SEXP mat, 
                                 SEXP missing) {
+    _WrapperBegin();
     SEXP dim = getAttrib(mat, R_DimSymbol);
     int nrow = INTEGER(dim)[0];
     int ncol = INTEGER(dim)[1];    
@@ -54,11 +77,13 @@ extern "C" {
     SEXP ret = PROTECT(R_MakeExternalPtr(handle, R_NilValue, R_NilValue));
     R_RegisterCFinalizerEx(ret, _DMatrixFinalizer, TRUE);
     UNPROTECT(1);
+    _WrapperEnd();
     return ret;    
   }
   SEXP XGDMatrixCreateFromCSC_R(SEXP indptr,
                                 SEXP indices,
                                 SEXP data) {
+    _WrapperBegin();
     const int *col_ptr = INTEGER(indptr);
     const int *row_index = INTEGER(indices);
     const double *col_data = REAL(data);
@@ -92,9 +117,11 @@ extern "C" {
     SEXP ret = PROTECT(R_MakeExternalPtr(handle, R_NilValue, R_NilValue));
     R_RegisterCFinalizerEx(ret, _DMatrixFinalizer, TRUE);
     UNPROTECT(1);
+    _WrapperEnd();
     return ret;
   }
   SEXP XGDMatrixSliceDMatrix_R(SEXP handle, SEXP idxset) {
+    _WrapperBegin();
     int len = length(idxset);
     std::vector<int> idxvec(len);
     for (int i = 0; i < len; ++i) {
@@ -104,13 +131,17 @@ extern "C" {
     SEXP ret = PROTECT(R_MakeExternalPtr(res, R_NilValue, R_NilValue));
     R_RegisterCFinalizerEx(ret, _DMatrixFinalizer, TRUE);
     UNPROTECT(1);
+    _WrapperEnd();
     return ret;        
   }
   void XGDMatrixSaveBinary_R(SEXP handle, SEXP fname, SEXP silent) {
+    _WrapperBegin();
     XGDMatrixSaveBinary(R_ExternalPtrAddr(handle),
                         CHAR(asChar(fname)), asInteger(silent));
+    _WrapperEnd();
   }
   void XGDMatrixSetInfo_R(SEXP handle, SEXP field, SEXP array) {
+    _WrapperBegin();
     int len = length(array);
     const char *name = CHAR(asChar(field));
     if (!strcmp("group", name)) {
@@ -120,6 +151,7 @@ extern "C" {
         vec[i] = static_cast<unsigned>(INTEGER(array)[i]);
       }
       XGDMatrixSetGroup(R_ExternalPtrAddr(handle), &vec[0], len);
+      _WrapperEnd();
       return;
     }
     {
@@ -132,8 +164,10 @@ extern "C" {
                             CHAR(asChar(field)),
                             &vec[0], len);
     }
+    _WrapperEnd();
   }
   SEXP XGDMatrixGetInfo_R(SEXP handle, SEXP field) {
+    _WrapperBegin();
     bst_ulong olen;
     const float *res = XGDMatrixGetFloatInfo(R_ExternalPtrAddr(handle),
                                              CHAR(asChar(field)), &olen);
@@ -142,6 +176,7 @@ extern "C" {
       REAL(ret)[i] = res[i];
     }
     UNPROTECT(1);
+    _WrapperEnd();
     return ret;
   }
   // functions related to booster
@@ -151,6 +186,7 @@ extern "C" {
     R_ClearExternalPtr(ext);
   }
   SEXP XGBoosterCreate_R(SEXP dmats) {
+    _WrapperBegin();
     int len = length(dmats);
     std::vector<void*> dvec;
     for (int i = 0; i < len; ++i){
@@ -160,19 +196,25 @@ extern "C" {
     SEXP ret = PROTECT(R_MakeExternalPtr(handle, R_NilValue, R_NilValue));
     R_RegisterCFinalizerEx(ret, _BoosterFinalizer, TRUE);
     UNPROTECT(1);
+    _WrapperEnd();
     return ret;
   }
   void XGBoosterSetParam_R(SEXP handle, SEXP name, SEXP val) {
+    _WrapperBegin();
     XGBoosterSetParam(R_ExternalPtrAddr(handle),
                       CHAR(asChar(name)),
                       CHAR(asChar(val)));
+    _WrapperEnd();
   }
   void XGBoosterUpdateOneIter_R(SEXP handle, SEXP iter, SEXP dtrain) {
+    _WrapperBegin();
     XGBoosterUpdateOneIter(R_ExternalPtrAddr(handle),
                            asInteger(iter),
                            R_ExternalPtrAddr(dtrain));
+    _WrapperEnd();
   }
   void XGBoosterBoostOneIter_R(SEXP handle, SEXP dtrain, SEXP grad, SEXP hess) {
+    _WrapperBegin();
     utils::Check(length(grad) == length(hess), "gradient and hess must have same length");
     int len = length(grad);
     std::vector<float> tgrad(len), thess(len);
@@ -184,8 +226,10 @@ extern "C" {
     XGBoosterBoostOneIter(R_ExternalPtrAddr(handle),
                           R_ExternalPtrAddr(dtrain),
                           &tgrad[0], &thess[0], len);
+    _WrapperEnd();
   }
   SEXP XGBoosterEvalOneIter_R(SEXP handle, SEXP iter, SEXP dmats, SEXP evnames) {
+    _WrapperBegin();
     utils::Check(length(dmats) == length(evnames), "dmats and evnams must have same length");
     int len = length(dmats);
     std::vector<void*> vec_dmats;
@@ -201,8 +245,10 @@ extern "C" {
     return mkString(XGBoosterEvalOneIter(R_ExternalPtrAddr(handle),
                                          asInteger(iter),
                                          &vec_dmats[0], &vec_sptr[0], len));
+    _WrapperEnd();
   }
   SEXP XGBoosterPredict_R(SEXP handle, SEXP dmat, SEXP output_margin) {
+    _WrapperBegin();
     bst_ulong olen;
     const float *res = XGBoosterPredict(R_ExternalPtrAddr(handle),
                                         R_ExternalPtrAddr(dmat),
@@ -213,15 +259,21 @@ extern "C" {
       REAL(ret)[i] = res[i];
     }
     UNPROTECT(1);
+    _WrapperEnd();
     return ret;
   }
   void XGBoosterLoadModel_R(SEXP handle, SEXP fname) {
+    _WrapperBegin();
     XGBoosterLoadModel(R_ExternalPtrAddr(handle), CHAR(asChar(fname)));
+    _WrapperEnd();
   }
   void XGBoosterSaveModel_R(SEXP handle, SEXP fname) {
+    _WrapperBegin();
     XGBoosterSaveModel(R_ExternalPtrAddr(handle), CHAR(asChar(fname)));
+    _WrapperEnd();
   }
   void XGBoosterDumpModel_R(SEXP handle, SEXP fname, SEXP fmap) {
+    _WrapperBegin();
     bst_ulong olen;
     const char **res = XGBoosterDumpModel(R_ExternalPtrAddr(handle),
                                           CHAR(asChar(fmap)),
@@ -232,5 +284,6 @@ extern "C" {
       fprintf(fo, "%s", res[i]);
     }
     fclose(fo);
+    _WrapperEnd();
   }
 }