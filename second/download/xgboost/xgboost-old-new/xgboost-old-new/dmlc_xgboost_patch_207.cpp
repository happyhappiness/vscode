@@ -272,20 +272,21 @@ extern "C" {
     XGBoosterSaveModel(R_ExternalPtrAddr(handle), CHAR(asChar(fname)));
     _WrapperEnd();
   }
-  void XGBoosterDumpModel_R(SEXP handle, SEXP fname,
-                            SEXP fmap, SEXP with_stats) {
+  SEXP XGBoosterDumpModel_R(SEXP handle, SEXP fmap, SEXP with_stats) {
     _WrapperBegin();
     bst_ulong olen;
     const char **res = XGBoosterDumpModel(R_ExternalPtrAddr(handle),
                                           CHAR(asChar(fmap)),
                                           asInteger(with_stats),
                                           &olen);
-    FILE *fo = utils::FopenCheck(CHAR(asChar(fname)), "w");
-    for (size_t i = 0; i < olen; ++i) {
-      fprintf(fo, "booster[%u]:\n", static_cast<unsigned>(i));
-      fprintf(fo, "%s", res[i]);
+    SEXP out = PROTECT(allocVector(STRSXP, olen));    
+    char buffer [2000];
+    for (size_t i = 0; i < olen; ++i) {      
+      sprintf (buffer, "booster[%u]:\n%s", static_cast<unsigned>(i), res[i]);
+      SET_STRING_ELT(out, i, mkChar(buffer));
     }
-    fclose(fo);
     _WrapperEnd();
+  UNPROTECT(1);
+  return out;
   }
-}
+}
\ No newline at end of file