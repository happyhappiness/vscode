@@ -46,6 +46,7 @@
 #define REDIS_EXPIRELOOKUPS_PER_CRON    10 /* lookup 10 expires per loop */
 #define REDIS_MAX_WRITE_PER_EVENT (1024*64)
 #define REDIS_SHARED_INTEGERS 10000
+#define REDIS_SHARED_BULKHDR_LEN 32
 #define REDIS_MAX_LOGMSG_LEN    1024 /* Default maximum length of syslog messages */
 #define REDIS_AOF_REWRITE_PERC  100
 #define REDIS_AOF_REWRITE_MIN_SIZE (1024*1024)
@@ -358,9 +359,11 @@ struct sharedObjectsStruct {
     *outofrangeerr, *noscripterr, *loadingerr, *slowscripterr, *plus,
     *select0, *select1, *select2, *select3, *select4,
     *select5, *select6, *select7, *select8, *select9,
-    *messagebulk, *pmessagebulk, *subscribebulk, *unsubscribebulk, *mbulk3,
-    *mbulk4, *psubscribebulk, *punsubscribebulk,
-    *integers[REDIS_SHARED_INTEGERS];
+    *messagebulk, *pmessagebulk, *subscribebulk, *unsubscribebulk,
+    *psubscribebulk, *punsubscribebulk, *del,
+    *integers[REDIS_SHARED_INTEGERS],
+    *mbulkhdr[REDIS_SHARED_BULKHDR_LEN], /* "*<value>\r\n" */
+    *bulkhdr[REDIS_SHARED_BULKHDR_LEN];  /* "$<value>\r\n" */
 };
 
 /* ZSETs use a specialized version of Skiplists */
@@ -817,6 +820,7 @@ void freeClientsInAsyncFreeQueue(void);
 void asyncCloseClientOnOutputBufferLimitReached(redisClient *c);
 int getClientLimitClassByName(char *name);
 char *getClientLimitClassName(int class);
+void flushSlavesOutputBuffers(void);
 
 #ifdef __GNUC__
 void addReplyErrorFormat(redisClient *c, const char *fmt, ...)
@@ -940,7 +944,7 @@ unsigned int zsetLength(robj *zobj);
 void zsetConvert(robj *zobj, int encoding);
 
 /* Core functions */
-void freeMemoryIfNeeded(void);
+int freeMemoryIfNeeded(void);
 int processCommand(redisClient *c);
 void setupSignalHandlers(void);
 struct redisCommand *lookupCommand(sds name);