@@ -47,6 +47,7 @@
 #define REDIS_MAX_WRITE_PER_EVENT (1024*64)
 #define REDIS_REQUEST_MAX_SIZE (1024*1024*256) /* max bytes in inline command */
 #define REDIS_SHARED_INTEGERS 10000
+#define REDIS_REPLY_CHUNK_BYTES (5*1500) /* 5 TCP packets with default MTU */
 
 /* If more then REDIS_WRITEV_THRESHOLD write packets are pending use writev */
 #define REDIS_WRITEV_THRESHOLD      3
@@ -309,6 +310,11 @@ typedef struct redisClient {
     list *watched_keys;     /* Keys WATCHED for MULTI/EXEC CAS */
     dict *pubsub_channels;  /* channels a client is interested in (SUBSCRIBE) */
     list *pubsub_patterns;  /* patterns a client is interested in (SUBSCRIBE) */
+
+    /* Response buffer */
+    int bufpos;
+    int buflen;
+    char buf[];
 } redisClient;
 
 struct saveparam {
@@ -588,6 +594,8 @@ void resetClient(redisClient *c);
 void sendReplyToClient(aeEventLoop *el, int fd, void *privdata, int mask);
 void sendReplyToClientWritev(aeEventLoop *el, int fd, void *privdata, int mask);
 void addReply(redisClient *c, robj *obj);
+void *addDeferredMultiBulkLength(redisClient *c);
+void setDeferredMultiBulkLength(redisClient *c, void *node, long length);
 void addReplySds(redisClient *c, sds s);
 void processInputBuffer(redisClient *c);
 void acceptHandler(aeEventLoop *el, int fd, void *privdata, int mask);
@@ -597,11 +605,23 @@ void addReplyBulkCString(redisClient *c, char *s);
 void acceptHandler(aeEventLoop *el, int fd, void *privdata, int mask);
 void addReply(redisClient *c, robj *obj);
 void addReplySds(redisClient *c, sds s);
+void addReplyError(redisClient *c, char *err);
+void addReplyStatus(redisClient *c, char *status);
 void addReplyDouble(redisClient *c, double d);
 void addReplyLongLong(redisClient *c, long long ll);
-void addReplyUlong(redisClient *c, unsigned long ul);
+void addReplyMultiBulkLen(redisClient *c, long length);
 void *dupClientReplyValue(void *o);
 
+#ifdef __GNUC__
+void addReplyErrorFormat(redisClient *c, const char *fmt, ...)
+    __attribute__((format(printf, 2, 3)));
+void addReplyStatusFormat(redisClient *c, const char *fmt, ...)
+    __attribute__((format(printf, 2, 3)));
+#else
+void addReplyErrorFormat(redisClient *c, const char *fmt, ...);
+void addReplyStatusFormat(redisClient *c, const char *fmt, ...);
+#endif
+
 /* List data type */
 void listTypeTryConversion(robj *subject, robj *value);
 void listTypePush(robj *subject, robj *value, int where);