@@ -8,21 +8,22 @@
 #include "src/utils/utils.h"
 #include "src/utils/omp.h"
 #include "src/utils/matrix_csr.h"
-
 using namespace xgboost;
+
+extern "C" {
+  void XGBoostAssert_R(int exp, const char *fmt, ...);
+  void XGBoostCheck_R(int exp, const char *fmt, ...);
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
-}
-void HandlePrint(const char *msg) {
-  Rprintf("%s", msg);
-}
+void (*Printf)(const char *fmt, ...) = Rprintf;
+void (*Assert)(int exp, const char *fmt, ...) = XGBoostAssert_R;
+void (*Check)(int exp, const char *fmt, ...) = XGBoostCheck_R;
+void (*Error)(const char *fmt, ...) = error;
 }  // namespace utils
+
 namespace random {
 void Seed(unsigned seed) {
   warning("parameter seed is ignored, please set random seed using set.seed");