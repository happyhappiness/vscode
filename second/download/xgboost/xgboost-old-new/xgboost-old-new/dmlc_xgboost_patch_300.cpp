@@ -87,6 +87,7 @@ void HandlePrint(const char *msg);
 #ifdef XGBOOST_STRICT_CXX98_
 // these function pointers are to be assigned 
 extern "C" void (*Printf)(const char *fmt, ...);
+extern "C" int (*SPrintf)(char *buf, size_t size, const char *fmt, ...);
 extern "C" void (*Assert)(int exp, const char *fmt, ...);
 extern "C" void (*Check)(int exp, const char *fmt, ...);
 extern "C" void (*Error)(const char *fmt, ...);
@@ -100,6 +101,14 @@ inline void Printf(const char *fmt, ...) {
   va_end(args);
   HandlePrint(msg.c_str());
 }
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