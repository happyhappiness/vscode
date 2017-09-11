@@ -3,10 +3,10 @@
 #include <utility>
 #include <cstring>
 #include "xgboost_R.h"
-#include "../../wrapper/xgboost_wrapper.h"
-#include "../../src/utils/utils.h"
-#include "../../src/utils/omp.h"
-#include "../../src/utils/matrix_csr.h"
+#include "xgboost_wrapper.h"
+#include "../src/utils/utils.h"
+#include "../src/utils/omp.h"
+#include "../src/utils/matrix_csr.h"
 
 using namespace xgboost;
 // implements error handling
@@ -119,7 +119,7 @@ extern "C" {
     }
   }
   SEXP XGDMatrixGetInfo_R(SEXP handle, SEXP field) {
-    size_t olen;
+    uint64_t olen;
     const float *res = XGDMatrixGetFloatInfo(R_ExternalPtrAddr(handle),
                                              CHAR(asChar(field)), &olen);
     SEXP ret = PROTECT(allocVector(REALSXP, olen));
@@ -188,7 +188,7 @@ extern "C" {
                                          &vec_dmats[0], &vec_sptr[0], len));
   }
   SEXP XGBoosterPredict_R(SEXP handle, SEXP dmat, SEXP output_margin) {
-    size_t olen;
+    uint64_t olen;
     const float *res = XGBoosterPredict(R_ExternalPtrAddr(handle),
                                         R_ExternalPtrAddr(dmat),
                                         asInteger(output_margin),
@@ -207,13 +207,13 @@ extern "C" {
     XGBoosterSaveModel(R_ExternalPtrAddr(handle), CHAR(asChar(fname)));
   }
   void XGBoosterDumpModel_R(SEXP handle, SEXP fname, SEXP fmap) {
-    size_t olen;
+    uint64_t olen;
     const char **res = XGBoosterDumpModel(R_ExternalPtrAddr(handle),
                                           CHAR(asChar(fmap)),
                                           &olen);
     FILE *fo = utils::FopenCheck(CHAR(asChar(fname)), "w");
     for (size_t i = 0; i < olen; ++i) {
-      fprintf(fo, "booster[%u]:\n", static_cast<unsigned>(i));
+      fprintf(fo, "booster[%lu]:\n", i);
       fprintf(fo, "%s", res[i]);
     }
     fclose(fo);