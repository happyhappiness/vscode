@@ -2,13 +2,24 @@
 #include <string>
 #include <utility>
 #include <cstring>
-#include "xgboost_wrapper.h"
 #include "xgboost_R.h"
+#include "xgboost_wrapper.h"
 #include "../src/utils/utils.h"
 #include "../src/utils/omp.h"
 #include "../src/utils/matrix_csr.h"
 
 using namespace xgboost;
+// implements error handling
+namespace xgboost {
+namespace utils {
+void HandleAssertError(const char *msg) {
+  error("%s", msg);
+}
+void HandleCheckError(const char *msg) {
+  error("%s", msg);
+}
+}  // namespace utils
+}  // namespace xgboost
 
 extern "C" {
   void _DMatrixFinalizer(SEXP ext) {    
@@ -51,9 +62,9 @@ extern "C" {
     int ncol = length(indptr) - 1;
     int ndata = length(data);
     // transform into CSR format
-    std::vector<size_t> row_ptr;
+    std::vector<bst_ulong> row_ptr;
     std::vector< std::pair<unsigned, float> > csr_data;
-    utils::SparseCSRMBuilder< std::pair<unsigned,float> > builder(row_ptr, csr_data);
+    utils::SparseCSRMBuilder<std::pair<unsigned,float>, false, bst_ulong> builder(row_ptr, csr_data);
     builder.InitBudget();
     for (int i = 0; i < ncol; ++i) {
       for (int j = col_ptr[i]; j < col_ptr[i+1]; ++j) {
@@ -108,7 +119,7 @@ extern "C" {
     }
   }
   SEXP XGDMatrixGetInfo_R(SEXP handle, SEXP field) {
-    size_t olen;
+    bst_ulong olen;
     const float *res = XGDMatrixGetFloatInfo(R_ExternalPtrAddr(handle),
                                              CHAR(asChar(field)), &olen);
     SEXP ret = PROTECT(allocVector(REALSXP, olen));
@@ -165,17 +176,19 @@ extern "C" {
     std::vector<void*> vec_dmats;
     std::vector<std::string> vec_names;
     std::vector<const char*> vec_sptr;
-    for (int i = 0; i < len; ++i){
+    for (int i = 0; i < len; ++i) {
       vec_dmats.push_back(R_ExternalPtrAddr(VECTOR_ELT(dmats, i)));
       vec_names.push_back(std::string(CHAR(asChar(VECTOR_ELT(evnames, i)))));
-      vec_sptr.push_back(vec_names.back().c_str());
+    }
+    for (int i = 0; i < len; ++i) {
+      vec_sptr.push_back(vec_names[i].c_str());
     }
     return mkString(XGBoosterEvalOneIter(R_ExternalPtrAddr(handle),
                                          asInteger(iter),
-                                         &vec_dmats[0], &vec_sptr[0], len)); 
+                                         &vec_dmats[0], &vec_sptr[0], len));
   }
   SEXP XGBoosterPredict_R(SEXP handle, SEXP dmat, SEXP output_margin) {
-    size_t olen;
+    bst_ulong olen;
     const float *res = XGBoosterPredict(R_ExternalPtrAddr(handle),
                                         R_ExternalPtrAddr(dmat),
                                         asInteger(output_margin),
@@ -194,13 +207,13 @@ extern "C" {
     XGBoosterSaveModel(R_ExternalPtrAddr(handle), CHAR(asChar(fname)));
   }
   void XGBoosterDumpModel_R(SEXP handle, SEXP fname, SEXP fmap) {
-    size_t olen;
+    bst_ulong olen;
     const char **res = XGBoosterDumpModel(R_ExternalPtrAddr(handle),
                                           CHAR(asChar(fmap)),
                                           &olen);
     FILE *fo = utils::FopenCheck(CHAR(asChar(fname)), "w");
     for (size_t i = 0; i < olen; ++i) {
-      fprintf(fo, "booster[%lu]:\n", i);
+      fprintf(fo, "booster[%u]:\n", static_cast<unsigned>(i));
       fprintf(fo, "%s", res[i]);
     }
     fclose(fo);