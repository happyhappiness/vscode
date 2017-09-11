@@ -1258,13 +1258,13 @@ void forceCommandPropagation(redisClient *c, int flags);
 void preventCommandPropagation(redisClient *c);
 int prepareForShutdown();
 #ifdef __GNUC__
-void redisLog(int level, const char *fmt, ...)
+void serverLog(int level, const char *fmt, ...)
     __attribute__((format(printf, 2, 3)));
 #else
-void redisLog(int level, const char *fmt, ...);
+void serverLog(int level, const char *fmt, ...);
 #endif
-void redisLogRaw(int level, const char *msg);
-void redisLogFromHandler(int level, const char *msg);
+void serverLogRaw(int level, const char *msg);
+void serverLogFromHandler(int level, const char *msg);
 void usage(void);
 void updateDictResizePolicy(void);
 int htNeedsResize(dict *dict);
@@ -1585,13 +1585,13 @@ void _redisAssertWithInfo(redisClient *c, robj *o, char *estr, char *file, int l
 void _redisAssert(char *estr, char *file, int line);
 void _redisPanic(char *msg, char *file, int line);
 void bugReportStart(void);
-void redisLogObjectDebugInfo(robj *o);
+void serverLogObjectDebugInfo(robj *o);
 void sigsegvHandler(int sig, siginfo_t *info, void *secret);
 sds genRedisInfoString(char *section);
 void enableWatchdog(int period);
 void disableWatchdog(void);
 void watchdogScheduleSignal(int period);
-void redisLogHexDump(int level, char *descr, void *value, size_t len);
+void serverLogHexDump(int level, char *descr, void *value, size_t len);
 
 #define redisDebug(fmt, ...) \
     printf("DEBUG %s:%d > " fmt "\n", __FILE__, __LINE__, __VA_ARGS__)