@@ -435,7 +435,7 @@ typedef long long mstime_t; /* millisecond time type. */
 /* We can print the stacktrace, so our assert is defined this way: */
 #define serverAssertWithInfo(_c,_o,_e) ((_e)?(void)0 : (_serverAssertWithInfo(_c,_o,#_e,__FILE__,__LINE__),_exit(1)))
 #define serverAssert(_e) ((_e)?(void)0 : (_serverAssert(#_e,__FILE__,__LINE__),_exit(1)))
-#define serverPanic(_e) _serverPanic(#_e,__FILE__,__LINE__),_exit(1)
+#define serverPanic(...) _serverPanic(__FILE__,__LINE__,__VA_ARGS__),_exit(1)
 
 /*-----------------------------------------------------------------------------
  * Data types
@@ -1960,7 +1960,7 @@ void *realloc(void *ptr, size_t size) __attribute__ ((deprecated));
 /* Debugging stuff */
 void _serverAssertWithInfo(const client *c, const robj *o, const char *estr, const char *file, int line);
 void _serverAssert(const char *estr, const char *file, int line);
-void _serverPanic(const char *msg, const char *file, int line);
+void _serverPanic(const char *file, int line, const char *msg, ...);
 void bugReportStart(void);
 void serverLogObjectDebugInfo(const robj *o);
 void sigsegvHandler(int sig, siginfo_t *info, void *secret);