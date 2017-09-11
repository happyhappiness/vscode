@@ -70,14 +70,23 @@ inline void HandlePrint(const char *msg) {
   printf("%s", msg);
 }
 #else
+#ifndef XGBOOST_STRICT_CXX98__
 // include declarations, some one must implement this
 void HandleAssertError(const char *msg);
 void HandleCheckError(const char *msg);
 void HandlePrint(const char *msg);
 #endif
+#endif
 
+#ifdef XGBOOST_STRICT_CXX98_
+// these function pointers are to be assigned 
+extern void (*Printf)(const char *fmt, ...);
+extern void (*Assert)(int exp, const char *fmt, ...);
+extern void (*Check)(int exp, const char *fmt, ...);
+extern void (*Error)(const char *fmt, ...);
+#else
 /*! \brief printf, print message to the console */
-inline void Printf(const char *fmt, ...) {
+inline void Printf(const char *fmt, ...) {  
   std::string msg(kPrintBuffer, '\0');
   va_list args;
   va_start(args, fmt);
@@ -121,6 +130,7 @@ inline void Error(const char *fmt, ...) {
     HandleCheckError(msg.c_str());
   }
 }
+#endif
 
 /*! \brief replace fopen, report error when the file open fails */
 inline FILE *FopenCheck(const char *fname, const char *flag) {