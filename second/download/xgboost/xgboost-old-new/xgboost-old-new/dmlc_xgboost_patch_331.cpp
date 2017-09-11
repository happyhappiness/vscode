@@ -62,9 +62,9 @@ extern "C" {
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
@@ -119,7 +119,7 @@ extern "C" {
     }
   }
   SEXP XGDMatrixGetInfo_R(SEXP handle, SEXP field) {
-    uint64_t olen;
+    bst_ulong olen;
     const float *res = XGDMatrixGetFloatInfo(R_ExternalPtrAddr(handle),
                                              CHAR(asChar(field)), &olen);
     SEXP ret = PROTECT(allocVector(REALSXP, olen));
@@ -188,7 +188,7 @@ extern "C" {
                                          &vec_dmats[0], &vec_sptr[0], len));
   }
   SEXP XGBoosterPredict_R(SEXP handle, SEXP dmat, SEXP output_margin) {
-    uint64_t olen;
+    bst_ulong olen;
     const float *res = XGBoosterPredict(R_ExternalPtrAddr(handle),
                                         R_ExternalPtrAddr(dmat),
                                         asInteger(output_margin),
@@ -207,13 +207,13 @@ extern "C" {
     XGBoosterSaveModel(R_ExternalPtrAddr(handle), CHAR(asChar(fname)));
   }
   void XGBoosterDumpModel_R(SEXP handle, SEXP fname, SEXP fmap) {
-    uint64_t olen;
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