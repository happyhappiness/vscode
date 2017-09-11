@@ -869,6 +869,7 @@ void asyncCloseClientOnOutputBufferLimitReached(redisClient *c);
 int getClientLimitClassByName(char *name);
 char *getClientLimitClassName(int class);
 void flushSlavesOutputBuffers(void);
+void disconnectSlaves(void);
 
 #ifdef __GNUC__
 void addReplyErrorFormat(redisClient *c, const char *fmt, ...)