@@ -6,10 +6,9 @@
 #include "wrapper/xgboost_wrapper.h"
 #include "src/utils/utils.h"
 #include "src/utils/omp.h"
-#include "src/utils/matrix_csr.h"
-
 #include "xgboost_R.h"
 
+using namespace std;
 using namespace xgboost;
 
 extern "C" {
@@ -92,37 +91,25 @@ extern "C" {
                                 SEXP indices,
                                 SEXP data) {
     _WrapperBegin();
-    const int *col_ptr = INTEGER(indptr);
-    const int *row_index = INTEGER(indices);
-    const double *col_data = REAL(data);
-    int ncol = length(indptr) - 1;
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
-    void *handle = XGDMatrixCreateFromCSR(BeginPtr(row_ptr), BeginPtr(col_index),
-                                          BeginPtr(row_data), row_ptr.size(), ndata );
+    void *handle = XGDMatrixCreateFromCSC(BeginPtr(col_ptr_), BeginPtr(indices_),
+                                          BeginPtr(data_), nindptr, ndata);
     SEXP ret = PROTECT(R_MakeExternalPtr(handle, R_NilValue, R_NilValue));
     R_RegisterCFinalizerEx(ret, _DMatrixFinalizer, TRUE);
     UNPROTECT(1);
@@ -188,6 +175,10 @@ extern "C" {
     _WrapperEnd();
     return ret;
   }
+  SEXP XGDMatrixNumRow_R(SEXP handle) {
+    bst_ulong nrow = XGDMatrixNumRow(R_ExternalPtrAddr(handle));
+    return ScalarInteger(static_cast<int>(nrow));
+  }
   // functions related to booster
   void _BoosterFinalizer(SEXP ext) {    
     if (R_ExternalPtrAddr(ext) == NULL) return;