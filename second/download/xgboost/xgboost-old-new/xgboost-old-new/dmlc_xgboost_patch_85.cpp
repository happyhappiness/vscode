@@ -1,15 +1,18 @@
-#ifndef XGBOOST_UTILS_UTILS_H_
-#define XGBOOST_UTILS_UTILS_H_
 /*!
+ * Copyright 2014 by Contributors
  * \file utils.h
  * \brief simple utils to support the code
  * \author Tianqi Chen
  */
+#ifndef XGBOOST_UTILS_UTILS_H_
+#define XGBOOST_UTILS_UTILS_H_
+
 #define _CRT_SECURE_NO_WARNINGS
 #include <cstdio>
 #include <string>
 #include <cstdlib>
 #include <vector>
+#include <stdexcept>
 
 #ifndef XGBOOST_STRICT_CXX98_
 #include <cstdarg>
@@ -19,18 +22,18 @@
 #define fopen64 std::fopen
 #endif
 #ifdef _MSC_VER
-// NOTE: sprintf_s is not equivalent to snprintf, 
+// NOTE: sprintf_s is not equivalent to snprintf,
 // they are equivalent when success, which is sufficient for our case
 #define snprintf sprintf_s
 #define vsnprintf vsprintf_s
 #else
 #ifdef _FILE_OFFSET_BITS
 #if _FILE_OFFSET_BITS == 32
-#pragma message ("Warning: FILE OFFSET BITS defined to be 32 bit")
+#pragma message("Warning: FILE OFFSET BITS defined to be 32 bit")
 #endif
 #endif
 
-#ifdef __APPLE__ 
+#ifdef __APPLE__
 #define off64_t off_t
 #define fopen64 std::fopen
 #endif
@@ -58,21 +61,20 @@ namespace utils {
 const int kPrintBuffer = 1 << 12;
 
 #ifndef XGBOOST_CUSTOMIZE_MSG_
-/*! 
+/*!
  * \brief handling of Assert error, caused by in-apropriate input
- * \param msg error message 
+ * \param msg error message
  */
 inline void HandleAssertError(const char *msg) {
   fprintf(stderr, "AssertError:%s\n", msg);
   exit(-1);
 }
-/*! 
+/*!
  * \brief handling of Check error, caused by in-apropriate input
- * \param msg error message 
+ * \param msg error message
  */
 inline void HandleCheckError(const char *msg) {
-  fprintf(stderr, "%s\n", msg);
-  exit(-1);
+  throw std::runtime_error(msg);
 }
 inline void HandlePrint(const char *msg) {
   printf("%s", msg);
@@ -158,7 +160,7 @@ inline std::FILE *FopenCheck(const char *fname, const char *flag) {
 // easy utils that can be directly acessed in xgboost
 /*! \brief get the beginning address of a vector */
 template<typename T>
-inline T *BeginPtr(std::vector<T> &vec) {
+inline T *BeginPtr(std::vector<T> &vec) { // NOLINT(*)
   if (vec.size() == 0) {
     return NULL;
   } else {
@@ -174,7 +176,7 @@ inline const T *BeginPtr(const std::vector<T> &vec) {
     return &vec[0];
   }
 }
-inline char* BeginPtr(std::string &str) {
+inline char* BeginPtr(std::string &str) { // NOLINT(*)
   if (str.length() == 0) return NULL;
   return &str[0];
 }