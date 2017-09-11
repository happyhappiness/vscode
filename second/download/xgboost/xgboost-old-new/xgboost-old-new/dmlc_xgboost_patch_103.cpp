@@ -12,6 +12,7 @@
 #include <string>
 #include <cstdlib>
 #include <vector>
+#include <stdexcept>
 
 #ifndef XGBOOST_STRICT_CXX98_
 #include <cstdarg>
@@ -73,8 +74,7 @@ inline void HandleAssertError(const char *msg) {
  * \param msg error message
  */
 inline void HandleCheckError(const char *msg) {
-  fprintf(stderr, "%s\n", msg);
-  exit(-1);
+  throw std::runtime_error(msg);
 }
 inline void HandlePrint(const char *msg) {
   printf("%s", msg);