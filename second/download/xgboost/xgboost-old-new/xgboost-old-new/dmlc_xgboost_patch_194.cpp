@@ -3,6 +3,7 @@
 #include <utility>
 #include <cstring>
 #include <cstdio>
+#include <sstream> 
 #include "wrapper/xgboost_wrapper.h"
 #include "src/utils/utils.h"
 #include "src/utils/omp.h"
@@ -242,10 +243,10 @@ extern "C" {
     for (int i = 0; i < len; ++i) {
       vec_sptr.push_back(vec_names[i].c_str());
     }
+    _WrapperEnd();
     return mkString(XGBoosterEvalOneIter(R_ExternalPtrAddr(handle),
                                          asInteger(iter),
                                          BeginPtr(vec_dmats), BeginPtr(vec_sptr), len));
-    _WrapperEnd();
   }
   SEXP XGBoosterPredict_R(SEXP handle, SEXP dmat, SEXP output_margin, SEXP ntree_limit) {
     _WrapperBegin();
@@ -273,18 +274,21 @@ extern "C" {
     XGBoosterSaveModel(R_ExternalPtrAddr(handle), CHAR(asChar(fname)));
     _WrapperEnd();
   }
-  void XGBoosterDumpModel_R(SEXP handle, SEXP fname, SEXP fmap) {
+  SEXP XGBoosterDumpModel_R(SEXP handle, SEXP fmap, SEXP with_stats) {
     _WrapperBegin();
     bst_ulong olen;
     const char **res = XGBoosterDumpModel(R_ExternalPtrAddr(handle),
-                                          CHAR(asChar(fmap)),
-                                          &olen);
-    FILE *fo = utils::FopenCheck(CHAR(asChar(fname)), "w");
-    for (size_t i = 0; i < olen; ++i) {
-      fprintf(fo, "booster[%u]:\n", static_cast<unsigned>(i));
-      fprintf(fo, "%s", res[i]);
+    CHAR(asChar(fmap)),
+    asInteger(with_stats),
+    &olen);
+    SEXP out = PROTECT(allocVector(STRSXP, olen));    
+    for (size_t i = 0; i < olen; ++i) {     
+      stringstream stream;
+      stream <<  "booster["<<i<<"]\n" << res[i];
+      SET_STRING_ELT(out, i, mkChar(stream.str().c_str()));
     }
-    fclose(fo);
     _WrapperEnd();
+    UNPROTECT(1);
+    return out;
   }
 }