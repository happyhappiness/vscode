@@ -257,6 +257,11 @@
 #define REDIS_PROPAGATE_AOF 1
 #define REDIS_PROPAGATE_REPL 2
 
+/* Using the following macro you can run code inside serverCron() with the
+ * specified period, specified in milliseconds.
+ * The actual resolution depends on REDIS_HZ. */
+#define run_with_period(_ms_) if (!(server.cronloops%((_ms_)/(1000/REDIS_HZ))))
+
 /* We can print the stacktrace, so our assert is defined this way: */
 #define redisAssertWithInfo(_c,_o,_e) ((_e)?(void)0 : (_redisAssertWithInfo(_c,_o,#_e,__FILE__,__LINE__),_exit(1)))
 #define redisAssert(_e) ((_e)?(void)0 : (_redisAssert(#_e,__FILE__,__LINE__),_exit(1)))
@@ -579,6 +584,7 @@ struct redisServer {
     int arch_bits;              /* 32 or 64 depending on sizeof(long) */
     int cronloops;              /* Number of times the cron function run */
     char runid[REDIS_RUN_ID_SIZE+1];  /* ID always different at every exec. */
+    int sentinel_mode;          /* True if this instance is a Sentinel. */
     /* Networking */
     int port;                   /* TCP listening port */
     char *bindaddr;             /* Bind address or NULL */
@@ -1115,6 +1121,12 @@ void clusterCron(void);
 clusterNode *getNodeByQuery(redisClient *c, struct redisCommand *cmd, robj **argv, int argc, int *hashslot, int *ask);
 void clusterPropagatePublish(robj *channel, robj *message);
 
+/* Sentinel */
+void initSentinelConfig(void);
+void initSentinel(void);
+void sentinelTimer(void);
+char *sentinelHandleConfiguration(char **argv, int argc);
+
 /* Scripting */
 void scriptingInit(void);
 
@@ -1280,4 +1292,10 @@ void enableWatchdog(int period);
 void disableWatchdog(void);
 void watchdogScheduleSignal(int period);
 void redisLogHexDump(int level, char *descr, void *value, size_t len);
+
+#define redisDebug(fmt, ...) \
+    printf("DEBUG %s:%d > " fmt "\n", __FILE__, __LINE__, __VA_ARGS__)
+#define redisDebugMark() \
+    printf("-- MARK %s:%d --\n", __FILE__, __LINE__)
+
 #endif