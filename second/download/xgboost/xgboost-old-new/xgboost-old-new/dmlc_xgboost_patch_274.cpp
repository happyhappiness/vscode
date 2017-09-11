@@ -7,30 +7,37 @@
  */
 #define _CRT_SECURE_NO_WARNINGS
 #include <cstdio>
-#include <cstdarg>
+#include <string>
 #include <cstdlib>
+#include <vector>
+
+#ifndef XGBOOST_STRICT_CXX98_
+#include <cstdarg>
+#endif
+
+#if !defined(__GNUC__)
+#define fopen64 std::fopen
+#endif
 #ifdef _MSC_VER
-#define fopen64 fopen
 // NOTE: sprintf_s is not equivalent to snprintf, 
 // they are equivalent when success, which is sufficient for our case
 #define snprintf sprintf_s
 #define vsnprintf vsprintf_s
 #else
 #ifdef _FILE_OFFSET_BITS
 #if _FILE_OFFSET_BITS == 32
-#warning "FILE OFFSET BITS defined to be 32 bit"
+#pragma message ("Warning: FILE OFFSET BITS defined to be 32 bit")
 #endif
 #endif
 
-#ifdef __APPLE__
+#ifdef __APPLE__ 
 #define off64_t off_t
-#define fopen64 fopen
+#define fopen64 std::fopen
 #endif
 
-#define _FILE_OFFSET_BITS 64
 extern "C" {
 #include <sys/types.h>
-};
+}
 #endif
 
 #ifdef _MSC_VER
@@ -46,10 +53,11 @@ typedef long int64_t;
 namespace xgboost {
 /*! \brief namespace for helper utils of the project */
 namespace utils {
+
 /*! \brief error message buffer length */
-const int kErrorBuffer = 1 << 12;
+const int kPrintBuffer = 1 << 12;
 
-#ifndef XGBOOST_CUSTOMIZE_ERROR_
+#ifndef XGBOOST_CUSTOMIZE_MSG_
 /*! 
  * \brief handling of Assert error, caused by in-apropriate input
  * \param msg error message 
@@ -66,19 +74,50 @@ inline void HandleCheckError(const char *msg) {
   fprintf(stderr, "%s\n", msg);
   exit(-1);
 }
+inline void HandlePrint(const char *msg) {
+  printf("%s", msg);
+}
 #else
+#ifndef XGBOOST_STRICT_CXX98_
 // include declarations, some one must implement this
 void HandleAssertError(const char *msg);
 void HandleCheckError(const char *msg);
+void HandlePrint(const char *msg);
+#endif
 #endif
+#ifdef XGBOOST_STRICT_CXX98_
+// these function pointers are to be assigned
+extern "C" void (*Printf)(const char *fmt, ...);
+extern "C" int (*SPrintf)(char *buf, size_t size, const char *fmt, ...);
+extern "C" void (*Assert)(int exp, const char *fmt, ...);
+extern "C" void (*Check)(int exp, const char *fmt, ...);
+extern "C" void (*Error)(const char *fmt, ...);
+#else
+/*! \brief printf, print message to the console */
+inline void Printf(const char *fmt, ...) {
+  std::string msg(kPrintBuffer, '\0');
+  va_list args;
+  va_start(args, fmt);
+  vsnprintf(&msg[0], kPrintBuffer, fmt, args);
+  va_end(args);
+  HandlePrint(msg.c_str());
+}
+/*! \brief portable version of snprintf */
+inline int SPrintf(char *buf, size_t size, const char *fmt, ...) {
+  va_list args;
+  va_start(args, fmt);
+  int ret = vsnprintf(buf, size, fmt, args);
+  va_end(args);
+  return ret;
+}
 
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
@@ -87,10 +126,10 @@ inline void Assert(bool exp, const char *fmt, ...) {
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
@@ -99,22 +138,41 @@ inline void Check(bool exp, const char *fmt, ...) {
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
 }
+#endif
 
 /*! \brief replace fopen, report error when the file open fails */
-inline FILE *FopenCheck(const char *fname, const char *flag) {
-  FILE *fp = fopen64(fname, flag);
+inline std::FILE *FopenCheck(const char *fname, const char *flag) {
+  std::FILE *fp = fopen64(fname, flag);
   Check(fp != NULL, "can not open file \"%s\"\n", fname);
   return fp;
 }
-
 }  // namespace utils
+// easy utils that can be directly acessed in xgboost
+/*! \brief get the beginning address of a vector */
+template<typename T>
+inline T *BeginPtr(std::vector<T> &vec) {
+  if (vec.size() == 0) {
+    return NULL;
+  } else {
+    return &vec[0];
+  }
+}
+/*! \brief get the beginning address of a vector */
+template<typename T>
+inline const T *BeginPtr(const std::vector<T> &vec) {
+  if (vec.size() == 0) {
+    return NULL;
+  } else {
+    return &vec[0];
+  }
+}
 }  // namespace xgboost
 #endif  // XGBOOST_UTILS_UTILS_H_