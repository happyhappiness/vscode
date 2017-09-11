@@ -3722,7 +3722,7 @@ sds clusterGenNodesDescription(int filter) {
  * CLUSTER command
  * -------------------------------------------------------------------------- */
 
-int getSlotOrReply(redisClient *c, robj *o) {
+int getSlotOrReply(client *c, robj *o) {
     long long slot;
 
     if (getLongLongFromObject(o,&slot) != REDIS_OK ||
@@ -3734,7 +3734,7 @@ int getSlotOrReply(redisClient *c, robj *o) {
     return (int) slot;
 }
 
-void clusterReplyMultiBulkSlots(redisClient *c) {
+void clusterReplyMultiBulkSlots(client *c) {
     /* Format: 1) 1) start slot
      *            2) end slot
      *            3) 1) master IP
@@ -3804,7 +3804,7 @@ void clusterReplyMultiBulkSlots(redisClient *c) {
     setDeferredMultiBulkLength(c, slot_replylen, num_masters);
 }
 
-void clusterCommand(redisClient *c) {
+void clusterCommand(client *c) {
     if (server.cluster_enabled == 0) {
         addReplyError(c,"This instance has cluster support disabled");
         return;
@@ -4363,7 +4363,7 @@ int verifyDumpPayload(unsigned char *p, size_t len) {
 /* DUMP keyname
  * DUMP is actually not used by Redis Cluster but it is the obvious
  * complement of RESTORE and can be useful for different applications. */
-void dumpCommand(redisClient *c) {
+void dumpCommand(client *c) {
     robj *o, *dumpobj;
     rio payload;
 
@@ -4384,7 +4384,7 @@ void dumpCommand(redisClient *c) {
 }
 
 /* RESTORE key ttl serialized-value [REPLACE] */
-void restoreCommand(redisClient *c) {
+void restoreCommand(client *c) {
     long long ttl;
     rio payload;
     int j, type, replace = 0;
@@ -4466,7 +4466,7 @@ typedef struct migrateCachedSocket {
  * If the caller detects an error while using the socket, migrateCloseSocket()
  * should be called so that the connection will be created from scratch
  * the next time. */
-migrateCachedSocket* migrateGetSocket(redisClient *c, robj *host, robj *port, long timeout) {
+migrateCachedSocket* migrateGetSocket(client *c, robj *host, robj *port, long timeout) {
     int fd;
     sds name = sdsempty();
     migrateCachedSocket *cs;
@@ -4558,7 +4558,7 @@ void migrateCloseTimedoutSockets(void) {
 }
 
 /* MIGRATE host port key dbid timeout [COPY | REPLACE] */
-void migrateCommand(redisClient *c) {
+void migrateCommand(client *c) {
     migrateCachedSocket *cs;
     int copy, replace, j;
     long timeout;
@@ -4723,7 +4723,7 @@ void migrateCommand(redisClient *c) {
  * The client should issue ASKING before to actually send the command to
  * the target instance. See the Redis Cluster specification for more
  * information. */
-void askingCommand(redisClient *c) {
+void askingCommand(client *c) {
     if (server.cluster_enabled == 0) {
         addReplyError(c,"This instance has cluster support disabled");
         return;
@@ -4735,7 +4735,7 @@ void askingCommand(redisClient *c) {
 /* The READONLY command is used by clients to enter the read-only mode.
  * In this mode slaves will not redirect clients as long as clients access
  * with read-only commands to keys that are served by the slave's master. */
-void readonlyCommand(redisClient *c) {
+void readonlyCommand(client *c) {
     if (server.cluster_enabled == 0) {
         addReplyError(c,"This instance has cluster support disabled");
         return;
@@ -4745,7 +4745,7 @@ void readonlyCommand(redisClient *c) {
 }
 
 /* The READWRITE command just clears the READONLY command state. */
-void readwriteCommand(redisClient *c) {
+void readwriteCommand(client *c) {
     c->flags &= ~REDIS_READONLY;
     addReply(c,shared.ok);
 }
@@ -4779,7 +4779,7 @@ void readwriteCommand(redisClient *c) {
  * not bound to any node. In this case the cluster global state should be
  * already "down" but it is fragile to rely on the update of the global state,
  * so we also handle it here. */
-clusterNode *getNodeByQuery(redisClient *c, struct redisCommand *cmd, robj **argv, int argc, int *hashslot, int *error_code) {
+clusterNode *getNodeByQuery(client *c, struct redisCommand *cmd, robj **argv, int argc, int *hashslot, int *error_code) {
     clusterNode *n = NULL;
     robj *firstkey = NULL;
     int multiple_keys = 0;
@@ -4940,7 +4940,7 @@ clusterNode *getNodeByQuery(redisClient *c, struct redisCommand *cmd, robj **arg
  * are used, then the node 'n' should not be NULL, but should be the
  * node we want to mention in the redirection. Moreover hashslot should
  * be set to the hash slot that caused the redirection. */
-void clusterRedirectClient(redisClient *c, clusterNode *n, int hashslot, int error_code) {
+void clusterRedirectClient(client *c, clusterNode *n, int hashslot, int error_code) {
     if (error_code == REDIS_CLUSTER_REDIR_CROSS_SLOT) {
         addReplySds(c,sdsnew("-CROSSSLOT Keys in request don't hash to the same slot\r\n"));
     } else if (error_code == REDIS_CLUSTER_REDIR_UNSTABLE) {
@@ -4975,7 +4975,7 @@ void clusterRedirectClient(redisClient *c, clusterNode *n, int hashslot, int err
  * If the client is found to be blocked into an hash slot this node no
  * longer handles, the client is sent a redirection error, and the function
  * returns 1. Otherwise 0 is returned and no operation is performed. */
-int clusterRedirectBlockedClientIfNeeded(redisClient *c) {
+int clusterRedirectBlockedClientIfNeeded(client *c) {
     if (c->flags & REDIS_BLOCKED && c->btype == REDIS_BLOCKED_LIST) {
         dictEntry *de;
         dictIterator *di;