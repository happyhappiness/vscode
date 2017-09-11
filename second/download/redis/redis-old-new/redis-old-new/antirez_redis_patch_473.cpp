@@ -412,8 +412,8 @@ typedef long long mstime_t; /* millisecond time type. */
 #define run_with_period(_ms_) if ((_ms_ <= 1000/server.hz) || !(server.cronloops%((_ms_)/(1000/server.hz))))
 
 /* We can print the stacktrace, so our assert is defined this way: */
-#define redisAssertWithInfo(_c,_o,_e) ((_e)?(void)0 : (_redisAssertWithInfo(_c,_o,#_e,__FILE__,__LINE__),_exit(1)))
-#define redisAssert(_e) ((_e)?(void)0 : (_redisAssert(#_e,__FILE__,__LINE__),_exit(1)))
+#define serverAssertWithInfo(_c,_o,_e) ((_e)?(void)0 : (_serverAssertWithInfo(_c,_o,#_e,__FILE__,__LINE__),_exit(1)))
+#define serverAssert(_e) ((_e)?(void)0 : (_serverAssert(#_e,__FILE__,__LINE__),_exit(1)))
 #define redisPanic(_e) _redisPanic(#_e,__FILE__,__LINE__),_exit(1)
 
 /*-----------------------------------------------------------------------------
@@ -1581,8 +1581,8 @@ void *realloc(void *ptr, size_t size) __attribute__ ((deprecated));
 #endif
 
 /* Debugging stuff */
-void _redisAssertWithInfo(client *c, robj *o, char *estr, char *file, int line);
-void _redisAssert(char *estr, char *file, int line);
+void _serverAssertWithInfo(client *c, robj *o, char *estr, char *file, int line);
+void _serverAssert(char *estr, char *file, int line);
 void _redisPanic(char *msg, char *file, int line);
 void bugReportStart(void);
 void serverLogObjectDebugInfo(robj *o);