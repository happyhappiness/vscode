@@ -11,14 +11,10 @@
 #include <cstdlib>
 #ifdef _MSC_VER
 #define fopen64 fopen
-// temporal solution for MSVC
-inline int snprintf(char *ptr, size_t sz, const char *fmt, ...) {
-  va_list args;
-  va_start(args, fmt);
-  int ret = vsprintf(ptr, fmt, args);
-  va_end(args);
-  return ret;
-}
+// NOTE: sprintf_s is not equivalent to snprintf, 
+// they are equivalent when success, which is sufficient for our case
+#define snprintf sprintf_s
+#define vsnprintf vsprintf_s
 #else
 #ifdef _FILE_OFFSET_BITS
 #if _FILE_OFFSET_BITS == 32
@@ -50,41 +46,65 @@ typedef long int64_t;
 namespace xgboost {
 /*! \brief namespace for helper utils of the project */
 namespace utils {
+/*! \brief error message buffer length */
+const int kErrorBuffer = 1 << 12;
+
+#ifndef XGBOOST_CUSTOMIZE_ERROR_
+/*! 
+ * \brief handling of Assert error, caused by in-apropriate input
+ * \param msg error message 
+ */
+inline void HandleAssertError(const char *msg) {
+  fprintf(stderr, "AssertError:%s\n", msg);
+  exit(-1);
+}
+/*! 
+ * \brief handling of Check error, caused by in-apropriate input
+ * \param msg error message 
+ */
+inline void HandleCheckError(const char *msg) {
+  fprintf(stderr, "%s\n", msg);
+  exit(-1);
+}
+#else
+// include declarations, some one must implement this
+void HandleAssertError(const char *msg);
+void HandleCheckError(const char *msg);
+#endif
 
 /*! \brief assert an condition is true, use this to handle debug information */
 inline void Assert(bool exp, const char *fmt, ...) {
   if (!exp) {
+    std::string msg(kErrorBuffer, '\0');
     va_list args;
     va_start(args, fmt);
-    fprintf(stderr, "AssertError:");
-    vfprintf(stderr, fmt, args);
+    vsnprintf(&msg[0], kErrorBuffer, fmt, args);
     va_end(args);
-    fprintf(stderr, "\n");
-    exit(-1);
+    HandleAssertError(msg.c_str());
   }
 }
 
 /*!\brief same as assert, but this is intended to be used as message for user*/
 inline void Check(bool exp, const char *fmt, ...) {
   if (!exp) {
+    std::string msg(kErrorBuffer, '\0');
     va_list args;
     va_start(args, fmt);
-    vfprintf(stderr, fmt, args);
+    vsnprintf(&msg[0], kErrorBuffer, fmt, args);
     va_end(args);
-    fprintf(stderr, "\n");
-    exit(-1);
+    HandleCheckError(msg.c_str());
   }
 }
 
 /*! \brief report error message, same as check */
 inline void Error(const char *fmt, ...) {
   {
+    std::string msg(kErrorBuffer, '\0');
     va_list args;
     va_start(args, fmt);
-    vfprintf(stderr, fmt, args);
+    vsnprintf(&msg[0], kErrorBuffer, fmt, args);
     va_end(args);
-    fprintf(stderr, "\n");
-    exit(-1);
+    HandleCheckError(msg.c_str());
   }
 }
 