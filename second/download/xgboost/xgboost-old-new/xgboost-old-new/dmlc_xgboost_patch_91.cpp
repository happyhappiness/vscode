@@ -1,3 +1,4 @@
+// Copyright (c) 2014 by Contributors
 #include <stdio.h>
 #include <stdarg.h>
 #include <Rinternals.h>
@@ -6,17 +7,17 @@
 void XGBoostAssert_R(int exp, const char *fmt, ...) {
   char buf[1024];
   if (exp == 0) {
-    va_list args;  
+    va_list args;
     va_start(args, fmt);
     vsprintf(buf, fmt, args);
     va_end(args);
     error("AssertError:%s\n", buf);
-  }  
+  }
 }
 void XGBoostCheck_R(int exp, const char *fmt, ...) {
   char buf[1024];
   if (exp == 0) {
-    va_list args;  
+    va_list args;
     va_start(args, fmt);
     vsprintf(buf, fmt, args);
     va_end(args);
@@ -25,7 +26,7 @@ void XGBoostCheck_R(int exp, const char *fmt, ...) {
 }
 int XGBoostSPrintf_R(char *buf, size_t size, const char *fmt, ...) {
   int ret;
-  va_list args;  
+  va_list args;
   va_start(args, fmt);
   ret = vsnprintf(buf, size, fmt, args);
   va_end(args);