@@ -23,3 +23,11 @@ void XGBoostCheck_R(int exp, const char *fmt, ...) {
     error("%s\n", buf);
   }
 }
+int XGBoostSPrintf_R(char *buf, size_t size, const char *fmt, ...) {
+  int ret;
+  va_list args;  
+  va_start(args, fmt);
+  ret = vsnprintf(buf, size, fmt, args);
+  va_end(args);
+  return ret;
+}