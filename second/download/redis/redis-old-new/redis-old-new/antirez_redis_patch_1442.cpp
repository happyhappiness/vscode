@@ -804,7 +804,7 @@ void rewriteClientCommandVector(redisClient *c, int argc, ...);
 void rewriteClientCommandArgument(redisClient *c, int i, robj *newval);
 unsigned long getClientOutputBufferMemoryUsage(redisClient *c);
 void freeClientsInAsyncFreeQueue(void);
-int asyncCloseClientOnOutputBufferLimitReached(redisClient *c);
+void asyncCloseClientOnOutputBufferLimitReached(redisClient *c);
 
 #ifdef __GNUC__
 void addReplyErrorFormat(redisClient *c, const char *fmt, ...)