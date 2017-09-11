@@ -7,11 +7,17 @@
  */
 #define _CRT_SECURE_NO_WARNINGS
 #include <cstdio>
-#include <cstdarg>
 #include <string>
 #include <cstdlib>
-#ifdef _MSC_VER
+
+#ifndef XGBOOST_STRICT_CXX98_
+#include <cstdarg>
+#endif
+
+#if !defined(__GNUC__)
 #define fopen64 fopen
+#endif
+#ifdef _MSC_VER
 // NOTE: sprintf_s is not equivalent to snprintf, 
 // they are equivalent when success, which is sufficient for our case
 #define snprintf sprintf_s
@@ -70,7 +76,7 @@ inline void HandlePrint(const char *msg) {
   printf("%s", msg);
 }
 #else
-#ifndef XGBOOST_STRICT_CXX98__
+#ifndef XGBOOST_STRICT_CXX98_
 // include declarations, some one must implement this
 void HandleAssertError(const char *msg);
 void HandleCheckError(const char *msg);