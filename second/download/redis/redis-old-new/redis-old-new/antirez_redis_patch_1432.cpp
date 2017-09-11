@@ -820,6 +820,7 @@ void freeClientsInAsyncFreeQueue(void);
 void asyncCloseClientOnOutputBufferLimitReached(redisClient *c);
 int getClientLimitClassByName(char *name);
 char *getClientLimitClassName(int class);
+void flushSlavesOutputBuffers(void);
 
 #ifdef __GNUC__
 void addReplyErrorFormat(redisClient *c, const char *fmt, ...)