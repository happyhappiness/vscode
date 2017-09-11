@@ -48,9 +48,9 @@ namespace xgboost {
 /*! \brief namespace for helper utils of the project */
 namespace utils {
 /*! \brief error message buffer length */
-const int kErrorBuffer = 1 << 12;
+const int kPrintBuffer = 1 << 12;
 
-#ifndef XGBOOST_CUSTOMIZE_ERROR_
+#ifndef XGBOOST_CUSTOMIZE_MSG_
 /*! 
  * \brief handling of Assert error, caused by in-apropriate input
  * \param msg error message 
@@ -67,19 +67,33 @@ inline void HandleCheckError(const char *msg) {
   fprintf(stderr, "%s\n", msg);
   exit(-1);
 }
+inline void HandlePrint(const char *msg) {
+  printf("%s", msg);
+}
 #else
 // include declarations, some one must implement this
 void HandleAssertError(const char *msg);
 void HandleCheckError(const char *msg);
+void HandlePrint(const char *msg);
 #endif
 
+/*! \brief printf, print message to the console */
+inline void Printf(const char *fmt, ...) {
+  std::string msg(kPrintBuffer, '\0');
+  va_list args;
+  va_start(args, fmt);
+  vsnprintf(&msg[0], kPrintBuffer, fmt, args);
+  va_end(args);
+  HandlePrint(msg.c_str());
+}
+
 /*! \brief assert an condition is true, use this to handle debug information */
 inline void Assert(bool exp, const char *fmt, ...) {
   if (!exp) {
-    std::string msg(kErrorBuffer, '\0');
+    std::string msg(kPrintBuffer, '\0');
     va_list args;
     va_start(args, fmt);
-    vsnprintf(&msg[0], kErrorBuffer, fmt, args);
+    vsnprintf(&msg[0], kPrintBuffer, fmt, args);
     va_end(args);
     HandleAssertError(msg.c_str());
   }
@@ -88,10 +102,10 @@ inline void Assert(bool exp, const char *fmt, ...) {
 /*!\brief same as assert, but this is intended to be used as message for user*/
 inline void Check(bool exp, const char *fmt, ...) {
   if (!exp) {
-    std::string msg(kErrorBuffer, '\0');
+    std::string msg(kPrintBuffer, '\0');
     va_list args;
     va_start(args, fmt);
-    vsnprintf(&msg[0], kErrorBuffer, fmt, args);
+    vsnprintf(&msg[0], kPrintBuffer, fmt, args);
     va_end(args);
     HandleCheckError(msg.c_str());
   }
@@ -100,10 +114,10 @@ inline void Check(bool exp, const char *fmt, ...) {
 /*! \brief report error message, same as check */
 inline void Error(const char *fmt, ...) {
   {
-    std::string msg(kErrorBuffer, '\0');
+    std::string msg(kPrintBuffer, '\0');
     va_list args;
     va_start(args, fmt);
-    vsnprintf(&msg[0], kErrorBuffer, fmt, args);
+    vsnprintf(&msg[0], kPrintBuffer, fmt, args);
     va_end(args);
     HandleCheckError(msg.c_str());
   }