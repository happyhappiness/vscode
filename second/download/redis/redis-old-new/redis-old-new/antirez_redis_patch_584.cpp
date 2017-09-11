@@ -1053,14 +1053,14 @@ void acceptTcpHandler(aeEventLoop *el, int fd, void *privdata, int mask);
 void acceptUnixHandler(aeEventLoop *el, int fd, void *privdata, int mask);
 void readQueryFromClient(aeEventLoop *el, int fd, void *privdata, int mask);
 void addReplyBulk(redisClient *c, robj *obj);
-void addReplyBulkCString(redisClient *c, char *s);
-void addReplyBulkCBuffer(redisClient *c, void *p, size_t len);
+void addReplyBulkCString(redisClient *c, const char *s);
+void addReplyBulkCBuffer(redisClient *c, const void *p, size_t len);
 void addReplyBulkLongLong(redisClient *c, long long ll);
 void addReply(redisClient *c, robj *obj);
 void addReplySds(redisClient *c, sds s);
 void addReplyBulkSds(redisClient *c, sds s);
-void addReplyError(redisClient *c, char *err);
-void addReplyStatus(redisClient *c, char *status);
+void addReplyError(redisClient *c, const char *err);
+void addReplyStatus(redisClient *c, const char *status);
 void addReplyDouble(redisClient *c, double d);
 void addReplyLongLong(redisClient *c, long long ll);
 void addReplyMultiBulkLen(redisClient *c, long length);
@@ -1136,9 +1136,9 @@ void freeSetObject(robj *o);
 void freeZsetObject(robj *o);
 void freeHashObject(robj *o);
 robj *createObject(int type, void *ptr);
-robj *createStringObject(char *ptr, size_t len);
-robj *createRawStringObject(char *ptr, size_t len);
-robj *createEmbeddedStringObject(char *ptr, size_t len);
+robj *createStringObject(const char *ptr, size_t len);
+robj *createRawStringObject(const char *ptr, size_t len);
+robj *createEmbeddedStringObject(const char *ptr, size_t len);
 robj *dupStringObject(robj *o);
 int isObjectRepresentableAsLongLong(robj *o, long long *llongval);
 robj *tryObjectEncoding(robj *o);
@@ -1274,7 +1274,7 @@ void closeListeningSockets(int unlink_unix_socket);
 void updateCachedTime(void);
 void resetServerStats(void);
 unsigned int getLRUClock(void);
-char *maxmemoryToString(void);
+const char *maxmemoryToString(void);
 
 /* Set data type */
 robj *setTypeCreate(robj *value);
@@ -1327,7 +1327,7 @@ void loadServerConfig(char *filename, char *options);
 void appendServerSaveParams(time_t seconds, int changes);
 void resetServerSaveParams(void);
 struct rewriteConfigState; /* Forward declaration to export API. */
-void rewriteConfigRewriteLine(struct rewriteConfigState *state, char *option, sds line, int force);
+void rewriteConfigRewriteLine(struct rewriteConfigState *state, const char *option, sds line, int force);
 int rewriteConfig(char *path);
 
 /* db.c -- Keyspace access API */