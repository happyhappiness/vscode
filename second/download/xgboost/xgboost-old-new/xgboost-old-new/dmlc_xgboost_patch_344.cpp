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