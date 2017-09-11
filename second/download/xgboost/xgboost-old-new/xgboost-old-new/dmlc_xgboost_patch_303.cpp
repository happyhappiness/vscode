@@ -7,9 +7,13 @@
  */
 #define _CRT_SECURE_NO_WARNINGS
 #include <cstdio>
-#include <cstdarg>
 #include <string>
 #include <cstdlib>
+
+#ifndef XGBOOST_STRICT_CXX98_
+#include <cstdarg>
+#endif
+
 #if !defined(__GNUC__)
 #define fopen64 fopen
 #endif
@@ -72,7 +76,7 @@ inline void HandlePrint(const char *msg) {
   printf("%s", msg);
 }
 #else
-#ifndef XGBOOST_STRICT_CXX98__
+#ifndef XGBOOST_STRICT_CXX98_
 // include declarations, some one must implement this
 void HandleAssertError(const char *msg);
 void HandleCheckError(const char *msg);