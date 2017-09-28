 void pfselftestCommand(client *c);
 void pfaddCommand(client *c);
 void pfcountCommand(client *c);
 void pfmergeCommand(client *c);
 void pfdebugCommand(client *c);
 void latencyCommand(client *c);
+void moduleCommand(client *c);
 void securityWarningCommand(client *c);
 
 #if defined(__GNUC__)
 void *calloc(size_t count, size_t size) __attribute__ ((deprecated));
 void free(void *ptr) __attribute__ ((deprecated));
 void *malloc(size_t size) __attribute__ ((deprecated));
 void *realloc(void *ptr, size_t size) __attribute__ ((deprecated));
 #endif
 
 /* Debugging stuff */
-void _serverAssertWithInfo(client *c, robj *o, char *estr, char *file, int line);
-void _serverAssert(char *estr, char *file, int line);
-void _serverPanic(char *msg, char *file, int line);
+void _serverAssertWithInfo(const client *c, const robj *o, const char *estr, const char *file, int line);
+void _serverAssert(const char *estr, const char *file, int line);
+void _serverPanic(const char *file, int line, const char *msg, ...);
 void bugReportStart(void);
-void serverLogObjectDebugInfo(robj *o);
+void serverLogObjectDebugInfo(const robj *o);
 void sigsegvHandler(int sig, siginfo_t *info, void *secret);
 sds genRedisInfoString(char *section);
 void enableWatchdog(int period);
 void disableWatchdog(void);
 void watchdogScheduleSignal(int period);
 void serverLogHexDump(int level, char *descr, void *value, size_t len);
 int memtest_preserving_test(unsigned long *m, size_t bytes, int passes);
+void mixDigest(unsigned char *digest, void *ptr, size_t len);
+void xorDigest(unsigned char *digest, void *ptr, size_t len);
 
 #define redisDebug(fmt, ...) \
     printf("DEBUG %s:%d > " fmt "\n", __FILE__, __LINE__, __VA_ARGS__)
 #define redisDebugMark() \
     printf("-- MARK %s:%d --\n", __FILE__, __LINE__)
 
