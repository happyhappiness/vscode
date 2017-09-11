@@ -2,40 +2,72 @@
 #include <string>
 #include <utility>
 #include <cstring>
+#include <cstdio>
 #include "xgboost_R.h"
-#include "../../wrapper/xgboost_wrapper.h"
-#include "../../src/utils/utils.h"
-#include "../../src/utils/omp.h"
-#include "../../src/utils/matrix_csr.h"
-
+#include "wrapper/xgboost_wrapper.h"
+#include "src/utils/utils.h"
+#include "src/utils/omp.h"
+using namespace std;
 using namespace xgboost;
+
+extern "C" {
+  void XGBoostAssert_R(int exp, const char *fmt, ...);
+  void XGBoostCheck_R(int exp, const char *fmt, ...);
+  int XGBoostSPrintf_R(char *buf, size_t size, const char *fmt, ...);
+}
+
 // implements error handling
 namespace xgboost {
 namespace utils {
-void HandleAssertError(const char *msg) {
-  error("%s", msg);
-}
-void HandleCheckError(const char *msg) {
-  error("%s", msg);
+extern "C" {
+  void (*Printf)(const char *fmt, ...) = Rprintf;
+  int (*SPrintf)(char *buf, size_t size, const char *fmt, ...) = XGBoostSPrintf_R;
+  void (*Assert)(int exp, const char *fmt, ...) = XGBoostAssert_R;
+  void (*Check)(int exp, const char *fmt, ...) = XGBoostCheck_R;
+  void (*Error)(const char *fmt, ...) = error;
 }
 }  // namespace utils
+
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
@@ -47,55 +79,64 @@ extern "C" {
         data[i * ncol +j] = din[i + nrow * j];
       }
     }
-    void *handle = XGDMatrixCreateFromMat(&data[0], nrow, ncol, asReal(missing));
+    void *handle = XGDMatrixCreateFromMat(BeginPtr(data), nrow, ncol, asReal(missing));
     SEXP ret = PROTECT(R_MakeExternalPtr(handle, R_NilValue, R_NilValue));
     R_RegisterCFinalizerEx(ret, _DMatrixFinalizer, TRUE);
     UNPROTECT(1);
+    _WrapperEnd();
     return ret;    
   }
   SEXP XGDMatrixCreateFromCSC_R(SEXP indptr,
                                 SEXP indices,
                                 SEXP data) {
-    const int *col_ptr = INTEGER(indptr);
-    const int *row_index = INTEGER(indices);
-    const double *col_data = REAL(data);
-    int ncol = length(indptr) - 1;
+    _WrapperBegin();
+    const int *p_indptr = INTEGER(indptr);
+    const int *p_indices = INTEGER(indices);
+    const double *p_data = REAL(data);
+    int nindptr = length(indptr);
     int ndata = length(data);
-    // transform into CSR format
-    std::vector<bst_ulong> row_ptr;
-    std::vector< std::pair<unsigned, float> > csr_data;
-    utils::SparseCSRMBuilder<std::pair<unsigned,float>, false, bst_ulong> builder(row_ptr, csr_data);
-    builder.InitBudget();
-    for (int i = 0; i < ncol; ++i) {
-      for (int j = col_ptr[i]; j < col_ptr[i+1]; ++j) {
-        builder.AddBudget(row_index[j]);
-      }
-    }
-    builder.InitStorage();
-    for (int i = 0; i < ncol; ++i) {
-      for (int j = col_ptr[i]; j < col_ptr[i+1]; ++j) {
-        builder.PushElem(row_index[j], std::make_pair(i, col_data[j]));
-      }
+    std::vector<bst_ulong> col_ptr_(nindptr);
+    std::vector<unsigned> indices_(ndata);
+    std::vector<float> data_(ndata);
+
+    for (int i = 0; i < nindptr; ++i) {
+      col_ptr_[i] = static_cast<bst_ulong>(p_indptr[i]);
     }
-    utils::Assert(csr_data.size() == static_cast<size_t>(ndata), "BUG CreateFromCSC");
-    std::vector<float> row_data(ndata);
-    std::vector<unsigned> col_index(ndata);
     #pragma omp parallel for schedule(static)
     for (int i = 0; i < ndata; ++i) {
-      col_index[i] = csr_data[i].first;
-      row_data[i] = csr_data[i].second;      
+      indices_[i] = static_cast<unsigned>(p_indices[i]);
+      data_[i] = static_cast<float>(p_data[i]);
     }
-    void *handle = XGDMatrixCreateFromCSR(&row_ptr[0], &col_index[0], &row_data[0], row_ptr.size(), ndata );
+    void *handle = XGDMatrixCreateFromCSC(BeginPtr(col_ptr_), BeginPtr(indices_),
+                                          BeginPtr(data_), nindptr, ndata);
     SEXP ret = PROTECT(R_MakeExternalPtr(handle, R_NilValue, R_NilValue));
     R_RegisterCFinalizerEx(ret, _DMatrixFinalizer, TRUE);
     UNPROTECT(1);
+    _WrapperEnd();
     return ret;
   }
+  SEXP XGDMatrixSliceDMatrix_R(SEXP handle, SEXP idxset) {
+    _WrapperBegin();
+    int len = length(idxset);
+    std::vector<int> idxvec(len);
+    for (int i = 0; i < len; ++i) {
+      idxvec[i] = INTEGER(idxset)[i] - 1;
+    }
+    void *res = XGDMatrixSliceDMatrix(R_ExternalPtrAddr(handle), BeginPtr(idxvec), len);
+    SEXP ret = PROTECT(R_MakeExternalPtr(res, R_NilValue, R_NilValue));
+    R_RegisterCFinalizerEx(ret, _DMatrixFinalizer, TRUE);
+    UNPROTECT(1);
+    _WrapperEnd();
+    return ret;        
+  }
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
@@ -104,7 +145,8 @@ extern "C" {
       for (int i = 0; i < len; ++i) {
         vec[i] = static_cast<unsigned>(INTEGER(array)[i]);
       }
-      XGDMatrixSetGroup(R_ExternalPtrAddr(handle), &vec[0], len);
+      XGDMatrixSetGroup(R_ExternalPtrAddr(handle), BeginPtr(vec), len);
+      _WrapperEnd();
       return;
     }
     {
@@ -115,10 +157,12 @@ extern "C" {
       }
       XGDMatrixSetFloatInfo(R_ExternalPtrAddr(handle), 
                             CHAR(asChar(field)),
-                            &vec[0], len);
+                            BeginPtr(vec), len);
     }
+    _WrapperEnd();
   }
   SEXP XGDMatrixGetInfo_R(SEXP handle, SEXP field) {
+    _WrapperBegin();
     bst_ulong olen;
     const float *res = XGDMatrixGetFloatInfo(R_ExternalPtrAddr(handle),
                                              CHAR(asChar(field)), &olen);
@@ -127,6 +171,7 @@ extern "C" {
       REAL(ret)[i] = res[i];
     }
     UNPROTECT(1);
+    _WrapperEnd();
     return ret;
   }
   // functions related to booster
@@ -136,28 +181,35 @@ extern "C" {
     R_ClearExternalPtr(ext);
   }
   SEXP XGBoosterCreate_R(SEXP dmats) {
+    _WrapperBegin();
     int len = length(dmats);
     std::vector<void*> dvec;
     for (int i = 0; i < len; ++i){
       dvec.push_back(R_ExternalPtrAddr(VECTOR_ELT(dmats, i)));
     }
-    void *handle = XGBoosterCreate(&dvec[0], dvec.size());
+    void *handle = XGBoosterCreate(BeginPtr(dvec), dvec.size());
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
@@ -168,9 +220,11 @@ extern "C" {
     }
     XGBoosterBoostOneIter(R_ExternalPtrAddr(handle),
                           R_ExternalPtrAddr(dtrain),
-                          &tgrad[0], &thess[0], len);
+                          BeginPtr(tgrad), BeginPtr(thess), len);
+    _WrapperEnd();
   }
   SEXP XGBoosterEvalOneIter_R(SEXP handle, SEXP iter, SEXP dmats, SEXP evnames) {
+    _WrapperBegin();
     utils::Check(length(dmats) == length(evnames), "dmats and evnams must have same length");
     int len = length(dmats);
     std::vector<void*> vec_dmats;
@@ -185,28 +239,37 @@ extern "C" {
     }
     return mkString(XGBoosterEvalOneIter(R_ExternalPtrAddr(handle),
                                          asInteger(iter),
-                                         &vec_dmats[0], &vec_sptr[0], len));
+                                         BeginPtr(vec_dmats), BeginPtr(vec_sptr), len));
+    _WrapperEnd();
   }
-  SEXP XGBoosterPredict_R(SEXP handle, SEXP dmat, SEXP output_margin) {
+  SEXP XGBoosterPredict_R(SEXP handle, SEXP dmat, SEXP output_margin, SEXP ntree_limit) {
+    _WrapperBegin();
     bst_ulong olen;
     const float *res = XGBoosterPredict(R_ExternalPtrAddr(handle),
                                         R_ExternalPtrAddr(dmat),
                                         asInteger(output_margin),
+                                        asInteger(ntree_limit),
                                         &olen);
     SEXP ret = PROTECT(allocVector(REALSXP, olen));
     for (size_t i = 0; i < olen; ++i) {
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
@@ -217,5 +280,6 @@ extern "C" {
       fprintf(fo, "%s", res[i]);
     }
     fclose(fo);
+    _WrapperEnd();
   }
 }