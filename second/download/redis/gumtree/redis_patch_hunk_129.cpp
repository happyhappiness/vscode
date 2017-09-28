 void addReplyMultiBulkLen(redisClient *c, long length);
 void copyClientOutputBuffer(redisClient *dst, redisClient *src);
 void *dupClientReplyValue(void *o);
 void getClientsMaxBuffers(unsigned long *longest_output_list,
                           unsigned long *biggest_input_buffer);
 void formatPeerId(char *peerid, size_t peerid_len, char *ip, int port);
-int getClientPeerId(redisClient *client, char *peerid, size_t peerid_len);
-sds getClientInfoString(redisClient *client);
+char *getClientPeerId(redisClient *client);
+sds catClientInfoString(sds s, redisClient *client);
 sds getAllClientsInfoString(void);
 void rewriteClientCommandVector(redisClient *c, int argc, ...);
 void rewriteClientCommandArgument(redisClient *c, int i, robj *newval);
 unsigned long getClientOutputBufferMemoryUsage(redisClient *c);
 void freeClientsInAsyncFreeQueue(void);
 void asyncCloseClientOnOutputBufferLimitReached(redisClient *c);
-int getClientLimitClassByName(char *name);
-char *getClientLimitClassName(int class);
+int getClientType(redisClient *c);
+int getClientTypeByName(char *name);
+char *getClientTypeName(int class);
 void flushSlavesOutputBuffers(void);
 void disconnectSlaves(void);
 int processEventsWhileBlocked(void);
 
 #ifdef __GNUC__
 void addReplyErrorFormat(redisClient *c, const char *fmt, ...)
