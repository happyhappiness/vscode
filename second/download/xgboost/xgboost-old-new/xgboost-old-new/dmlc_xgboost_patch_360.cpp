@@ -3,6 +3,8 @@
 #include "xgboost_wrapper.h"
 #include "xgboost_wrapper_R.h"
 #include "../src/utils/utils.h"
+#include "../src/utils/omp.h"
+
 using namespace xgboost;
 
 extern "C" {
@@ -11,13 +13,17 @@ extern "C" {
     XGDMatrixFree(R_ExternalPtrAddr(ext));
     R_ClearExternalPtr(ext);
   }
-  SEXP XGDMatrixCreateFromFile_R(SEXP fname) {
-    void *handle = XGDMatrixCreateFromFile(CHAR(asChar(fname)), 0);
+  SEXP XGDMatrixCreateFromFile_R(SEXP fname, SEXP silent) {
+    void *handle = XGDMatrixCreateFromFile(CHAR(asChar(fname)), asInteger(silent));
     SEXP ret = PROTECT(R_MakeExternalPtr(handle, R_NilValue, R_NilValue));
     R_RegisterCFinalizerEx(ret, _DMatrixFinalizer, TRUE);
     UNPROTECT(1);
     return ret;
-  } 
+  }
+  void XGDMatrixSaveBinary_R(SEXP handle, SEXP fname, SEXP silent) {
+    XGDMatrixSaveBinary(R_ExternalPtrAddr(handle),
+                        CHAR(asChar(fname)), asInteger(silent));
+  }
 
   // functions related to booster
   void _BoosterFinalizer(SEXP ext) {    
@@ -47,6 +53,19 @@ extern "C" {
                            asInteger(iter),
                            R_ExternalPtrAddr(dtrain));
   }
+  void XGBoosterBoostOneIter_R(SEXP handle, SEXP dtrain, SEXP grad, SEXP hess) {
+    utils::Check(length(grad) == length(hess), "gradient and hess must have same length");
+    int len = length(grad);
+    std::vector<float> tgrad(len), thess(len);
+    #pragma omp parallel for schedule(static)
+    for (int j = 0; j < len; ++j) {
+      tgrad[j] = REAL(grad)[j];
+      thess[j] = REAL(hess)[j];
+    }
+    XGBoosterBoostOneIter(R_ExternalPtrAddr(handle),
+                          R_ExternalPtrAddr(dtrain),
+                          &tgrad[0], &thess[0], len);
+  }
   SEXP XGBoosterEvalOneIter_R(SEXP handle, SEXP iter, SEXP dmats, SEXP evnames) {
     utils::Check(length(dmats) == length(evnames), "dmats and evnams must have same length");
     int len = length(dmats);
@@ -62,4 +81,35 @@ extern "C" {
                                          asInteger(iter),
                                          &vec_dmats[0], &vec_sptr[0], len)); 
   }
+  SEXP XGBoosterPredict_R(SEXP handle, SEXP dmat, SEXP output_margin) {
+    size_t olen;
+    const float *res = XGBoosterPredict(R_ExternalPtrAddr(handle),
+                                        R_ExternalPtrAddr(dmat),
+                                        asInteger(output_margin),
+                                        &olen);
+    SEXP ret = PROTECT(allocVector(REALSXP, olen));
+    for (size_t i = 0; i < olen; ++i) {
+      REAL(ret)[i] = res[i];
+    }
+    UNPROTECT(1);
+    return ret;
+  }
+  void XGBoosterLoadModel_R(SEXP handle, SEXP fname) {
+    XGBoosterLoadModel(R_ExternalPtrAddr(handle), CHAR(asChar(fname)));
+  }
+  void XGBoosterSaveModel_R(SEXP handle, SEXP fname) {
+    XGBoosterSaveModel(R_ExternalPtrAddr(handle), CHAR(asChar(fname)));
+  }
+  void XGBoosterDumpModel_R(SEXP handle, SEXP fname, SEXP fmap) {
+    size_t olen;
+    const char **res = XGBoosterDumpModel(R_ExternalPtrAddr(handle),
+                                          CHAR(asChar(fmap)),
+                                          &olen);
+    FILE *fo = utils::FopenCheck(CHAR(asChar(fname)), "w");
+    for (size_t i = 0; i < olen; ++i) {
+      fprintf(fo, "booster[%lu]:\n", i);
+      fprintf(fo, "%s\n", res[i]);
+    }
+    fclose(fo);
+  }
 }