@@ -378,8 +378,8 @@ typedef struct zset {
 } zset;
 
 typedef struct clientBufferLimitsConfig {
-    unsigned long hard_limit_bytes;
-    unsigned long soft_limit_bytes;
+    unsigned long long hard_limit_bytes;
+    unsigned long long soft_limit_bytes;
     time_t soft_limit_seconds;
 } clientBufferLimitsConfig;
 
@@ -805,6 +805,8 @@ void rewriteClientCommandArgument(redisClient *c, int i, robj *newval);
 unsigned long getClientOutputBufferMemoryUsage(redisClient *c);
 void freeClientsInAsyncFreeQueue(void);
 void asyncCloseClientOnOutputBufferLimitReached(redisClient *c);
+int getClientLimitClassByName(char *name);
+char *getClientLimitClassName(int class);
 
 #ifdef __GNUC__
 void addReplyErrorFormat(redisClient *c, const char *fmt, ...)