@@ -626,6 +626,12 @@ typedef struct redisOpArray {
 
 struct clusterState;
 
+/* AIX defines hz to __hz, we don't use this define and in order to allow
+ * Redis build on AIX we need to undef it. */
+#ifdef _AIX
+#undef hz
+#endif
+
 struct redisServer {
     /* General */
     pid_t pid;                  /* Main process pid. */
@@ -808,12 +814,12 @@ struct redisServer {
     /* Replication script cache. */
     dict *repl_scriptcache_dict;        /* SHA1 all slaves are aware of. */
     list *repl_scriptcache_fifo;        /* First in, first out LRU eviction. */
-    int repl_scriptcache_size;          /* Max number of elements. */
+    unsigned int repl_scriptcache_size; /* Max number of elements. */
     /* Synchronous replication. */
     list *clients_waiting_acks;         /* Clients waiting in WAIT command. */
     int get_ack_from_slaves;            /* If true we send REPLCONF GETACK. */
     /* Limits */
-    int maxclients;                 /* Max number of simultaneous clients */
+    unsigned int maxclients;            /* Max number of simultaneous clients */
     unsigned long long maxmemory;   /* Max number of memory bytes to use */
     int maxmemory_policy;           /* Policy for key eviction */
     int maxmemory_samples;          /* Pricision of random sampling */
@@ -993,19 +999,17 @@ void freeClient(redisClient *c);
 void freeClientAsync(redisClient *c);
 void resetClient(redisClient *c);
 void sendReplyToClient(aeEventLoop *el, int fd, void *privdata, int mask);
-void addReply(redisClient *c, robj *obj);
 void *addDeferredMultiBulkLength(redisClient *c);
 void setDeferredMultiBulkLength(redisClient *c, void *node, long length);
-void addReplySds(redisClient *c, sds s);
 void processInputBuffer(redisClient *c);
+void acceptHandler(aeEventLoop *el, int fd, void *privdata, int mask);
 void acceptTcpHandler(aeEventLoop *el, int fd, void *privdata, int mask);
 void acceptUnixHandler(aeEventLoop *el, int fd, void *privdata, int mask);
 void readQueryFromClient(aeEventLoop *el, int fd, void *privdata, int mask);
 void addReplyBulk(redisClient *c, robj *obj);
 void addReplyBulkCString(redisClient *c, char *s);
 void addReplyBulkCBuffer(redisClient *c, void *p, size_t len);
 void addReplyBulkLongLong(redisClient *c, long long ll);
-void acceptHandler(aeEventLoop *el, int fd, void *privdata, int mask);
 void addReply(redisClient *c, robj *obj);
 void addReplySds(redisClient *c, sds s);
 void addReplyError(redisClient *c, char *err);
@@ -1210,7 +1214,7 @@ void redisLog(int level, const char *fmt, ...);
 #endif
 void redisLogRaw(int level, const char *msg);
 void redisLogFromHandler(int level, const char *msg);
-void usage();
+void usage(void);
 void updateDictResizePolicy(void);
 int htNeedsResize(dict *dict);
 void oom(const char *msg);
@@ -1270,7 +1274,7 @@ sds keyspaceEventsFlagsToString(int flags);
 /* Configuration */
 void loadServerConfig(char *filename, char *options);
 void appendServerSaveParams(time_t seconds, int changes);
-void resetServerSaveParams();
+void resetServerSaveParams(void);
 struct rewriteConfigState; /* Forward declaration to export API. */
 void rewriteConfigRewriteLine(struct rewriteConfigState *state, char *option, sds line, int force);
 int rewriteConfig(char *path);