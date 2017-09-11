@@ -18,6 +18,9 @@ void HandleAssertError(const char *msg) {
 void HandleCheckError(const char *msg) {
   error("%s", msg);
 }
+void HandlePrint(const char *msg) {
+  Rprintf("%s", msg);
+}
 }  // namespace utils
 }  // namespace xgboost
 