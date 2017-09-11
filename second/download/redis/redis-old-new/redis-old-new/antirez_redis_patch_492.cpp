@@ -528,7 +528,7 @@ typedef struct readyList {
 
 /* With multiplexing we need to take per-client state.
  * Clients are taken in a linked list. */
-typedef struct redisClient {
+typedef struct client {
     uint64_t id;            /* Client incremental unique ID. */
     int fd;
     redisDb *db;
@@ -574,7 +574,7 @@ typedef struct redisClient {
     /* Response buffer */
     int bufpos;
     char buf[REDIS_REPLY_CHUNK_BYTES];
-} redisClient;
+} client;
 
 struct saveparam {
     time_t seconds;
@@ -695,7 +695,7 @@ struct redisServer {
     list *clients;              /* List of active clients */
     list *clients_to_close;     /* Clients to close asynchronously */
     list *slaves, *monitors;    /* List of slaves and MONITORs */
-    redisClient *current_client; /* Current client, only used on crash report */
+    client *current_client; /* Current client, only used on crash report */
     int clients_paused;         /* True if clients are currently paused */
     mstime_t clients_pause_end_time; /* Time when we undo clients_paused */
     char neterr[ANET_ERR_LEN];   /* Error buffer for anet.c */
@@ -835,8 +835,8 @@ struct redisServer {
     char *masterhost;               /* Hostname of master */
     int masterport;                 /* Port of master */
     int repl_timeout;               /* Timeout after N seconds of master idle */
-    redisClient *master;     /* Client that is master for this slave */
-    redisClient *cached_master; /* Cached master to be reused for PSYNC. */
+    client *master;     /* Client that is master for this slave */
+    client *cached_master; /* Cached master to be reused for PSYNC. */
     int repl_syncio_timeout; /* Timeout for synchronous I/O calls */
     int repl_state;          /* Replication status if the instance is a slave */
     off_t repl_transfer_size; /* Size of RDB to read from master during sync. */
@@ -904,8 +904,8 @@ struct redisServer {
                                           there is at least an uncovered slot. */
     /* Scripting */
     lua_State *lua; /* The Lua interpreter. We use just one for all clients */
-    redisClient *lua_client;   /* The "fake client" to query Redis from Lua */
-    redisClient *lua_caller;   /* The client running EVAL right now, or NULL */
+    client *lua_client;   /* The "fake client" to query Redis from Lua */
+    client *lua_caller;   /* The client running EVAL right now, or NULL */
     dict *lua_scripts;         /* A dictionary of SHA1 -> Lua scripts */
     mstime_t lua_time_limit;  /* Script timeout in milliseconds */
     mstime_t lua_time_start;  /* Start time of script, milliseconds time */
@@ -930,11 +930,11 @@ struct redisServer {
 };
 
 typedef struct pubsubPattern {
-    redisClient *client;
+    client *client;
     robj *pattern;
 } pubsubPattern;
 
-typedef void redisCommandProc(redisClient *c);
+typedef void redisCommandProc(client *c);
 typedef int *redisGetKeysProc(struct redisCommand *cmd, robj **argv, int argc, int *numkeys);
 struct redisCommand {
     char *name;
@@ -1039,46 +1039,46 @@ size_t redisPopcount(void *s, long count);
 void redisSetProcTitle(char *title);
 
 /* networking.c -- Networking and Client related operations */
-redisClient *createClient(int fd);
+client *createClient(int fd);
 void closeTimedoutClients(void);
-void freeClient(redisClient *c);
-void freeClientAsync(redisClient *c);
-void resetClient(redisClient *c);
+void freeClient(client *c);
+void freeClientAsync(client *c);
+void resetClient(client *c);
 void sendReplyToClient(aeEventLoop *el, int fd, void *privdata, int mask);
-void *addDeferredMultiBulkLength(redisClient *c);
-void setDeferredMultiBulkLength(redisClient *c, void *node, long length);
-void processInputBuffer(redisClient *c);
+void *addDeferredMultiBulkLength(client *c);
+void setDeferredMultiBulkLength(client *c, void *node, long length);
+void processInputBuffer(client *c);
 void acceptHandler(aeEventLoop *el, int fd, void *privdata, int mask);
 void acceptTcpHandler(aeEventLoop *el, int fd, void *privdata, int mask);
 void acceptUnixHandler(aeEventLoop *el, int fd, void *privdata, int mask);
 void readQueryFromClient(aeEventLoop *el, int fd, void *privdata, int mask);
-void addReplyBulk(redisClient *c, robj *obj);
-void addReplyBulkCString(redisClient *c, const char *s);
-void addReplyBulkCBuffer(redisClient *c, const void *p, size_t len);
-void addReplyBulkLongLong(redisClient *c, long long ll);
-void addReply(redisClient *c, robj *obj);
-void addReplySds(redisClient *c, sds s);
-void addReplyBulkSds(redisClient *c, sds s);
-void addReplyError(redisClient *c, const char *err);
-void addReplyStatus(redisClient *c, const char *status);
-void addReplyDouble(redisClient *c, double d);
-void addReplyLongLong(redisClient *c, long long ll);
-void addReplyMultiBulkLen(redisClient *c, long length);
-void copyClientOutputBuffer(redisClient *dst, redisClient *src);
+void addReplyBulk(client *c, robj *obj);
+void addReplyBulkCString(client *c, const char *s);
+void addReplyBulkCBuffer(client *c, const void *p, size_t len);
+void addReplyBulkLongLong(client *c, long long ll);
+void addReply(client *c, robj *obj);
+void addReplySds(client *c, sds s);
+void addReplyBulkSds(client *c, sds s);
+void addReplyError(client *c, const char *err);
+void addReplyStatus(client *c, const char *status);
+void addReplyDouble(client *c, double d);
+void addReplyLongLong(client *c, long long ll);
+void addReplyMultiBulkLen(client *c, long length);
+void copyClientOutputBuffer(client *dst, client *src);
 void *dupClientReplyValue(void *o);
 void getClientsMaxBuffers(unsigned long *longest_output_list,
                           unsigned long *biggest_input_buffer);
 void formatPeerId(char *peerid, size_t peerid_len, char *ip, int port);
-char *getClientPeerId(redisClient *client);
-sds catClientInfoString(sds s, redisClient *client);
+char *getClientPeerId(client *client);
+sds catClientInfoString(sds s, client *client);
 sds getAllClientsInfoString(void);
-void rewriteClientCommandVector(redisClient *c, int argc, ...);
-void rewriteClientCommandArgument(redisClient *c, int i, robj *newval);
-void replaceClientCommandVector(redisClient *c, int argc, robj **argv);
-unsigned long getClientOutputBufferMemoryUsage(redisClient *c);
+void rewriteClientCommandVector(client *c, int argc, ...);
+void rewriteClientCommandArgument(client *c, int i, robj *newval);
+void replaceClientCommandVector(client *c, int argc, robj **argv);
+unsigned long getClientOutputBufferMemoryUsage(client *c);
 void freeClientsInAsyncFreeQueue(void);
-void asyncCloseClientOnOutputBufferLimitReached(redisClient *c);
-int getClientType(redisClient *c);
+void asyncCloseClientOnOutputBufferLimitReached(client *c);
+int getClientType(client *c);
 int getClientTypeByName(char *name);
 char *getClientTypeName(int class);
 void flushSlavesOutputBuffers(void);
@@ -1089,13 +1089,13 @@ int clientsArePaused(void);
 int processEventsWhileBlocked(void);
 
 #ifdef __GNUC__
-void addReplyErrorFormat(redisClient *c, const char *fmt, ...)
+void addReplyErrorFormat(client *c, const char *fmt, ...)
     __attribute__((format(printf, 2, 3)));
-void addReplyStatusFormat(redisClient *c, const char *fmt, ...)
+void addReplyStatusFormat(client *c, const char *fmt, ...)
     __attribute__((format(printf, 2, 3)));
 #else
-void addReplyErrorFormat(redisClient *c, const char *fmt, ...);
-void addReplyStatusFormat(redisClient *c, const char *fmt, ...);
+void addReplyErrorFormat(client *c, const char *fmt, ...);
+void addReplyStatusFormat(client *c, const char *fmt, ...);
 #endif
 
 /* List data type */
@@ -1111,20 +1111,20 @@ void listTypeInsert(listTypeEntry *entry, robj *value, int where);
 int listTypeEqual(listTypeEntry *entry, robj *o);
 void listTypeDelete(listTypeIterator *iter, listTypeEntry *entry);
 void listTypeConvert(robj *subject, int enc);
-void unblockClientWaitingData(redisClient *c);
+void unblockClientWaitingData(client *c);
 void handleClientsBlockedOnLists(void);
-void popGenericCommand(redisClient *c, int where);
+void popGenericCommand(client *c, int where);
 void signalListAsReady(redisDb *db, robj *key);
 
 /* MULTI/EXEC/WATCH... */
-void unwatchAllKeys(redisClient *c);
-void initClientMultiState(redisClient *c);
-void freeClientMultiState(redisClient *c);
-void queueMultiCommand(redisClient *c);
+void unwatchAllKeys(client *c);
+void initClientMultiState(client *c);
+void freeClientMultiState(client *c);
+void queueMultiCommand(client *c);
 void touchWatchedKey(redisDb *db, robj *key);
 void touchWatchedKeysOnFlush(int dbid);
-void discardTransaction(redisClient *c);
-void flagTransaction(redisClient *c);
+void discardTransaction(client *c);
+void flagTransaction(client *c);
 
 /* Redis object implementation */
 void decrRefCount(robj *o);
@@ -1154,13 +1154,13 @@ robj *createIntsetObject(void);
 robj *createHashObject(void);
 robj *createZsetObject(void);
 robj *createZsetZiplistObject(void);
-int getLongFromObjectOrReply(redisClient *c, robj *o, long *target, const char *msg);
-int checkType(redisClient *c, robj *o, int type);
-int getLongLongFromObjectOrReply(redisClient *c, robj *o, long long *target, const char *msg);
-int getDoubleFromObjectOrReply(redisClient *c, robj *o, double *target, const char *msg);
+int getLongFromObjectOrReply(client *c, robj *o, long *target, const char *msg);
+int checkType(client *c, robj *o, int type);
+int getLongLongFromObjectOrReply(client *c, robj *o, long long *target, const char *msg);
+int getDoubleFromObjectOrReply(client *c, robj *o, double *target, const char *msg);
 int getLongLongFromObject(robj *o, long long *target);
 int getLongDoubleFromObject(robj *o, long double *target);
-int getLongDoubleFromObjectOrReply(redisClient *c, robj *o, long double *target, const char *msg);
+int getLongDoubleFromObjectOrReply(client *c, robj *o, long double *target, const char *msg);
 char *strEncoding(int encoding);
 int compareStringObjects(robj *a, robj *b);
 int collateStringObjects(robj *a, robj *b);
@@ -1175,11 +1175,11 @@ ssize_t syncReadLine(int fd, char *ptr, ssize_t size, long long timeout);
 
 /* Replication */
 void replicationFeedSlaves(list *slaves, int dictid, robj **argv, int argc);
-void replicationFeedMonitors(redisClient *c, list *monitors, int dictid, robj **argv, int argc);
+void replicationFeedMonitors(client *c, list *monitors, int dictid, robj **argv, int argc);
 void updateSlavesWaitingBgsave(int bgsaveerr, int type);
 void replicationCron(void);
 void replicationHandleMasterDisconnection(void);
-void replicationCacheMaster(redisClient *c);
+void replicationCacheMaster(client *c);
 void resizeReplicationBacklog(long long newsize);
 void replicationSetMaster(char *ip, int port);
 void replicationUnsetMaster(void);
@@ -1189,11 +1189,11 @@ void replicationScriptCacheFlush(void);
 void replicationScriptCacheAdd(sds sha1);
 int replicationScriptCacheExists(sds sha1);
 void processClientsWaitingReplicas(void);
-void unblockClientWaitingReplicas(redisClient *c);
+void unblockClientWaitingReplicas(client *c);
 int replicationCountAcksByOffset(long long offset);
 void replicationSendNewlineToMaster(void);
 long long replicationGetSlaveOffset(void);
-char *replicationGetSlaveName(redisClient *c);
+char *replicationGetSlaveName(client *c);
 
 /* Generic persistence functions */
 void startLoading(FILE *fp);
@@ -1246,16 +1246,16 @@ unsigned long zslGetRank(zskiplist *zsl, double score, robj *o);
 
 /* Core functions */
 int freeMemoryIfNeeded(void);
-int processCommand(redisClient *c);
+int processCommand(client *c);
 void setupSignalHandlers(void);
 struct redisCommand *lookupCommand(sds name);
 struct redisCommand *lookupCommandByCString(char *s);
 struct redisCommand *lookupCommandOrOriginal(sds name);
-void call(redisClient *c, int flags);
+void call(client *c, int flags);
 void propagate(struct redisCommand *cmd, int dbid, robj **argv, int argc, int flags);
 void alsoPropagate(struct redisCommand *cmd, int dbid, robj **argv, int argc, int target);
-void forceCommandPropagation(redisClient *c, int flags);
-void preventCommandPropagation(redisClient *c);
+void forceCommandPropagation(client *c, int flags);
+void preventCommandPropagation(client *c);
 int prepareForShutdown();
 #ifdef __GNUC__
 void serverLog(int level, const char *fmt, ...)
@@ -1310,11 +1310,11 @@ void hashTypeCurrentFromZiplist(hashTypeIterator *hi, int what,
                                 long long *vll);
 void hashTypeCurrentFromHashTable(hashTypeIterator *hi, int what, robj **dst);
 robj *hashTypeCurrentObject(hashTypeIterator *hi, int what);
-robj *hashTypeLookupWriteOrCreate(redisClient *c, robj *key);
+robj *hashTypeLookupWriteOrCreate(client *c, robj *key);
 
 /* Pub / Sub */
-int pubsubUnsubscribeAllChannels(redisClient *c, int notify);
-int pubsubUnsubscribeAllPatterns(redisClient *c, int notify);
+int pubsubUnsubscribeAllChannels(client *c, int notify);
+int pubsubUnsubscribeAllPatterns(client *c, int notify);
 void freePubsubPattern(void *p);
 int listMatchPubsubPattern(void *a, void *b);
 int pubsubPublishMessage(robj *channel, robj *message);
@@ -1341,8 +1341,8 @@ void setExpire(redisDb *db, robj *key, long long when);
 robj *lookupKey(redisDb *db, robj *key);
 robj *lookupKeyRead(redisDb *db, robj *key);
 robj *lookupKeyWrite(redisDb *db, robj *key);
-robj *lookupKeyReadOrReply(redisClient *c, robj *key, robj *reply);
-robj *lookupKeyWriteOrReply(redisClient *c, robj *key, robj *reply);
+robj *lookupKeyReadOrReply(client *c, robj *key, robj *reply);
+robj *lookupKeyWriteOrReply(client *c, robj *key, robj *reply);
 void dbAdd(redisDb *db, robj *key, robj *val);
 void dbOverwrite(redisDb *db, robj *key, robj *val);
 void setKey(redisDb *db, robj *key, robj *val);
@@ -1351,15 +1351,15 @@ robj *dbRandomKey(redisDb *db);
 int dbDelete(redisDb *db, robj *key);
 robj *dbUnshareStringValue(redisDb *db, robj *key, robj *o);
 long long emptyDb(void(callback)(void*));
-int selectDb(redisClient *c, int id);
+int selectDb(client *c, int id);
 void signalModifiedKey(redisDb *db, robj *key);
 void signalFlushedDb(int dbid);
 unsigned int getKeysInSlot(unsigned int hashslot, robj **keys, unsigned int count);
 unsigned int countKeysInSlot(unsigned int hashslot);
 unsigned int delKeysInSlot(unsigned int hashslot);
 int verifyClusterConfigWithData(void);
-void scanGenericCommand(redisClient *c, robj *o, unsigned long cursor);
-int parseScanCursorOrReply(redisClient *c, robj *o, unsigned long *cursor);
+void scanGenericCommand(client *c, robj *o, unsigned long cursor);
+int parseScanCursorOrReply(client *c, robj *o, unsigned long *cursor);
 
 /* API to get key arguments from commands */
 int *getKeysFromCommand(struct redisCommand *cmd, robj **argv, int argc, int *numkeys);
@@ -1393,10 +1393,10 @@ void scriptingInit(void);
 
 /* Blocked clients */
 void processUnblockedClients(void);
-void blockClient(redisClient *c, int btype);
-void unblockClient(redisClient *c);
-void replyToBlockedClientTimedOut(redisClient *c);
-int getTimeoutFromObjectOrReply(redisClient *c, robj *object, mstime_t *timeout, int unit);
+void blockClient(client *c, int btype);
+void unblockClient(client *c);
+void replyToBlockedClientTimedOut(client *c);
+int getTimeoutFromObjectOrReply(client *c, robj *object, mstime_t *timeout, int unit);
 void disconnectAllBlockedClients(void);
 
 /* Git SHA1 */
@@ -1405,173 +1405,173 @@ char *redisGitDirty(void);
 uint64_t redisBuildId(void);
 
 /* Commands prototypes */
-void authCommand(redisClient *c);
-void pingCommand(redisClient *c);
-void echoCommand(redisClient *c);
-void commandCommand(redisClient *c);
-void setCommand(redisClient *c);
-void setnxCommand(redisClient *c);
-void setexCommand(redisClient *c);
-void psetexCommand(redisClient *c);
-void getCommand(redisClient *c);
-void delCommand(redisClient *c);
-void existsCommand(redisClient *c);
-void setbitCommand(redisClient *c);
-void getbitCommand(redisClient *c);
-void setrangeCommand(redisClient *c);
-void getrangeCommand(redisClient *c);
-void incrCommand(redisClient *c);
-void decrCommand(redisClient *c);
-void incrbyCommand(redisClient *c);
-void decrbyCommand(redisClient *c);
-void incrbyfloatCommand(redisClient *c);
-void selectCommand(redisClient *c);
-void randomkeyCommand(redisClient *c);
-void keysCommand(redisClient *c);
-void scanCommand(redisClient *c);
-void dbsizeCommand(redisClient *c);
-void lastsaveCommand(redisClient *c);
-void saveCommand(redisClient *c);
-void bgsaveCommand(redisClient *c);
-void bgrewriteaofCommand(redisClient *c);
-void shutdownCommand(redisClient *c);
-void moveCommand(redisClient *c);
-void renameCommand(redisClient *c);
-void renamenxCommand(redisClient *c);
-void lpushCommand(redisClient *c);
-void rpushCommand(redisClient *c);
-void lpushxCommand(redisClient *c);
-void rpushxCommand(redisClient *c);
-void linsertCommand(redisClient *c);
-void lpopCommand(redisClient *c);
-void rpopCommand(redisClient *c);
-void llenCommand(redisClient *c);
-void lindexCommand(redisClient *c);
-void lrangeCommand(redisClient *c);
-void ltrimCommand(redisClient *c);
-void typeCommand(redisClient *c);
-void lsetCommand(redisClient *c);
-void saddCommand(redisClient *c);
-void sremCommand(redisClient *c);
-void smoveCommand(redisClient *c);
-void sismemberCommand(redisClient *c);
-void scardCommand(redisClient *c);
-void spopCommand(redisClient *c);
-void srandmemberCommand(redisClient *c);
-void sinterCommand(redisClient *c);
-void sinterstoreCommand(redisClient *c);
-void sunionCommand(redisClient *c);
-void sunionstoreCommand(redisClient *c);
-void sdiffCommand(redisClient *c);
-void sdiffstoreCommand(redisClient *c);
-void sscanCommand(redisClient *c);
-void syncCommand(redisClient *c);
-void flushdbCommand(redisClient *c);
-void flushallCommand(redisClient *c);
-void sortCommand(redisClient *c);
-void lremCommand(redisClient *c);
-void rpoplpushCommand(redisClient *c);
-void infoCommand(redisClient *c);
-void mgetCommand(redisClient *c);
-void monitorCommand(redisClient *c);
-void expireCommand(redisClient *c);
-void expireatCommand(redisClient *c);
-void pexpireCommand(redisClient *c);
-void pexpireatCommand(redisClient *c);
-void getsetCommand(redisClient *c);
-void ttlCommand(redisClient *c);
-void pttlCommand(redisClient *c);
-void persistCommand(redisClient *c);
-void slaveofCommand(redisClient *c);
-void roleCommand(redisClient *c);
-void debugCommand(redisClient *c);
-void msetCommand(redisClient *c);
-void msetnxCommand(redisClient *c);
-void zaddCommand(redisClient *c);
-void zincrbyCommand(redisClient *c);
-void zrangeCommand(redisClient *c);
-void zrangebyscoreCommand(redisClient *c);
-void zrevrangebyscoreCommand(redisClient *c);
-void zrangebylexCommand(redisClient *c);
-void zrevrangebylexCommand(redisClient *c);
-void zcountCommand(redisClient *c);
-void zlexcountCommand(redisClient *c);
-void zrevrangeCommand(redisClient *c);
-void zcardCommand(redisClient *c);
-void zremCommand(redisClient *c);
-void zscoreCommand(redisClient *c);
-void zremrangebyscoreCommand(redisClient *c);
-void zremrangebylexCommand(redisClient *c);
-void multiCommand(redisClient *c);
-void execCommand(redisClient *c);
-void discardCommand(redisClient *c);
-void blpopCommand(redisClient *c);
-void brpopCommand(redisClient *c);
-void brpoplpushCommand(redisClient *c);
-void appendCommand(redisClient *c);
-void strlenCommand(redisClient *c);
-void zrankCommand(redisClient *c);
-void zrevrankCommand(redisClient *c);
-void hsetCommand(redisClient *c);
-void hsetnxCommand(redisClient *c);
-void hgetCommand(redisClient *c);
-void hmsetCommand(redisClient *c);
-void hmgetCommand(redisClient *c);
-void hdelCommand(redisClient *c);
-void hlenCommand(redisClient *c);
-void hstrlenCommand(redisClient *c);
-void zremrangebyrankCommand(redisClient *c);
-void zunionstoreCommand(redisClient *c);
-void zinterstoreCommand(redisClient *c);
-void zscanCommand(redisClient *c);
-void hkeysCommand(redisClient *c);
-void hvalsCommand(redisClient *c);
-void hgetallCommand(redisClient *c);
-void hexistsCommand(redisClient *c);
-void hscanCommand(redisClient *c);
-void configCommand(redisClient *c);
-void hincrbyCommand(redisClient *c);
-void hincrbyfloatCommand(redisClient *c);
-void subscribeCommand(redisClient *c);
-void unsubscribeCommand(redisClient *c);
-void psubscribeCommand(redisClient *c);
-void punsubscribeCommand(redisClient *c);
-void publishCommand(redisClient *c);
-void pubsubCommand(redisClient *c);
-void watchCommand(redisClient *c);
-void unwatchCommand(redisClient *c);
-void clusterCommand(redisClient *c);
-void restoreCommand(redisClient *c);
-void migrateCommand(redisClient *c);
-void askingCommand(redisClient *c);
-void readonlyCommand(redisClient *c);
-void readwriteCommand(redisClient *c);
-void dumpCommand(redisClient *c);
-void objectCommand(redisClient *c);
-void clientCommand(redisClient *c);
-void evalCommand(redisClient *c);
-void evalShaCommand(redisClient *c);
-void scriptCommand(redisClient *c);
-void timeCommand(redisClient *c);
-void bitopCommand(redisClient *c);
-void bitcountCommand(redisClient *c);
-void bitposCommand(redisClient *c);
-void replconfCommand(redisClient *c);
-void waitCommand(redisClient *c);
-void geoencodeCommand(redisClient *c);
-void geodecodeCommand(redisClient *c);
-void georadiusByMemberCommand(redisClient *c);
-void georadiusCommand(redisClient *c);
-void geoaddCommand(redisClient *c);
-void geohashCommand(redisClient *c);
-void geoposCommand(redisClient *c);
-void geodistCommand(redisClient *c);
-void pfselftestCommand(redisClient *c);
-void pfaddCommand(redisClient *c);
-void pfcountCommand(redisClient *c);
-void pfmergeCommand(redisClient *c);
-void pfdebugCommand(redisClient *c);
-void latencyCommand(redisClient *c);
+void authCommand(client *c);
+void pingCommand(client *c);
+void echoCommand(client *c);
+void commandCommand(client *c);
+void setCommand(client *c);
+void setnxCommand(client *c);
+void setexCommand(client *c);
+void psetexCommand(client *c);
+void getCommand(client *c);
+void delCommand(client *c);
+void existsCommand(client *c);
+void setbitCommand(client *c);
+void getbitCommand(client *c);
+void setrangeCommand(client *c);
+void getrangeCommand(client *c);
+void incrCommand(client *c);
+void decrCommand(client *c);
+void incrbyCommand(client *c);
+void decrbyCommand(client *c);
+void incrbyfloatCommand(client *c);
+void selectCommand(client *c);
+void randomkeyCommand(client *c);
+void keysCommand(client *c);
+void scanCommand(client *c);
+void dbsizeCommand(client *c);
+void lastsaveCommand(client *c);
+void saveCommand(client *c);
+void bgsaveCommand(client *c);
+void bgrewriteaofCommand(client *c);
+void shutdownCommand(client *c);
+void moveCommand(client *c);
+void renameCommand(client *c);
+void renamenxCommand(client *c);
+void lpushCommand(client *c);
+void rpushCommand(client *c);
+void lpushxCommand(client *c);
+void rpushxCommand(client *c);
+void linsertCommand(client *c);
+void lpopCommand(client *c);
+void rpopCommand(client *c);
+void llenCommand(client *c);
+void lindexCommand(client *c);
+void lrangeCommand(client *c);
+void ltrimCommand(client *c);
+void typeCommand(client *c);
+void lsetCommand(client *c);
+void saddCommand(client *c);
+void sremCommand(client *c);
+void smoveCommand(client *c);
+void sismemberCommand(client *c);
+void scardCommand(client *c);
+void spopCommand(client *c);
+void srandmemberCommand(client *c);
+void sinterCommand(client *c);
+void sinterstoreCommand(client *c);
+void sunionCommand(client *c);
+void sunionstoreCommand(client *c);
+void sdiffCommand(client *c);
+void sdiffstoreCommand(client *c);
+void sscanCommand(client *c);
+void syncCommand(client *c);
+void flushdbCommand(client *c);
+void flushallCommand(client *c);
+void sortCommand(client *c);
+void lremCommand(client *c);
+void rpoplpushCommand(client *c);
+void infoCommand(client *c);
+void mgetCommand(client *c);
+void monitorCommand(client *c);
+void expireCommand(client *c);
+void expireatCommand(client *c);
+void pexpireCommand(client *c);
+void pexpireatCommand(client *c);
+void getsetCommand(client *c);
+void ttlCommand(client *c);
+void pttlCommand(client *c);
+void persistCommand(client *c);
+void slaveofCommand(client *c);
+void roleCommand(client *c);
+void debugCommand(client *c);
+void msetCommand(client *c);
+void msetnxCommand(client *c);
+void zaddCommand(client *c);
+void zincrbyCommand(client *c);
+void zrangeCommand(client *c);
+void zrangebyscoreCommand(client *c);
+void zrevrangebyscoreCommand(client *c);
+void zrangebylexCommand(client *c);
+void zrevrangebylexCommand(client *c);
+void zcountCommand(client *c);
+void zlexcountCommand(client *c);
+void zrevrangeCommand(client *c);
+void zcardCommand(client *c);
+void zremCommand(client *c);
+void zscoreCommand(client *c);
+void zremrangebyscoreCommand(client *c);
+void zremrangebylexCommand(client *c);
+void multiCommand(client *c);
+void execCommand(client *c);
+void discardCommand(client *c);
+void blpopCommand(client *c);
+void brpopCommand(client *c);
+void brpoplpushCommand(client *c);
+void appendCommand(client *c);
+void strlenCommand(client *c);
+void zrankCommand(client *c);
+void zrevrankCommand(client *c);
+void hsetCommand(client *c);
+void hsetnxCommand(client *c);
+void hgetCommand(client *c);
+void hmsetCommand(client *c);
+void hmgetCommand(client *c);
+void hdelCommand(client *c);
+void hlenCommand(client *c);
+void hstrlenCommand(client *c);
+void zremrangebyrankCommand(client *c);
+void zunionstoreCommand(client *c);
+void zinterstoreCommand(client *c);
+void zscanCommand(client *c);
+void hkeysCommand(client *c);
+void hvalsCommand(client *c);
+void hgetallCommand(client *c);
+void hexistsCommand(client *c);
+void hscanCommand(client *c);
+void configCommand(client *c);
+void hincrbyCommand(client *c);
+void hincrbyfloatCommand(client *c);
+void subscribeCommand(client *c);
+void unsubscribeCommand(client *c);
+void psubscribeCommand(client *c);
+void punsubscribeCommand(client *c);
+void publishCommand(client *c);
+void pubsubCommand(client *c);
+void watchCommand(client *c);
+void unwatchCommand(client *c);
+void clusterCommand(client *c);
+void restoreCommand(client *c);
+void migrateCommand(client *c);
+void askingCommand(client *c);
+void readonlyCommand(client *c);
+void readwriteCommand(client *c);
+void dumpCommand(client *c);
+void objectCommand(client *c);
+void clientCommand(client *c);
+void evalCommand(client *c);
+void evalShaCommand(client *c);
+void scriptCommand(client *c);
+void timeCommand(client *c);
+void bitopCommand(client *c);
+void bitcountCommand(client *c);
+void bitposCommand(client *c);
+void replconfCommand(client *c);
+void waitCommand(client *c);
+void geoencodeCommand(client *c);
+void geodecodeCommand(client *c);
+void georadiusByMemberCommand(client *c);
+void georadiusCommand(client *c);
+void geoaddCommand(client *c);
+void geohashCommand(client *c);
+void geoposCommand(client *c);
+void geodistCommand(client *c);
+void pfselftestCommand(client *c);
+void pfaddCommand(client *c);
+void pfcountCommand(client *c);
+void pfmergeCommand(client *c);
+void pfdebugCommand(client *c);
+void latencyCommand(client *c);
 
 #if defined(__GNUC__)
 void *calloc(size_t count, size_t size) __attribute__ ((deprecated));
@@ -1581,7 +1581,7 @@ void *realloc(void *ptr, size_t size) __attribute__ ((deprecated));
 #endif
 
 /* Debugging stuff */
-void _redisAssertWithInfo(redisClient *c, robj *o, char *estr, char *file, int line);
+void _redisAssertWithInfo(client *c, robj *o, char *estr, char *file, int line);
 void _redisAssert(char *estr, char *file, int line);
 void _redisPanic(char *msg, char *file, int line);
 void bugReportStart(void);