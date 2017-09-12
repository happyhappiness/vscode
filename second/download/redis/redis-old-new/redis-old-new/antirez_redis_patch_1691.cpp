@@ -70,12 +70,12 @@ struct redisServer server; /* server global state */
 struct redisCommand *commandTable;
 struct redisCommand redisCommandTable[] = {
     {"get",getCommand,2,0,NULL,1,1,1,0,0},
-    {"set",setCommand,3,REDIS_CMD_DENYOOM,NULL,0,0,0,0,0},
-    {"setnx",setnxCommand,3,REDIS_CMD_DENYOOM,NULL,0,0,0,0,0},
-    {"setex",setexCommand,4,REDIS_CMD_DENYOOM,NULL,0,0,0,0,0},
+    {"set",setCommand,3,REDIS_CMD_DENYOOM,noPreloadGetKeys,1,1,1,0,0},
+    {"setnx",setnxCommand,3,REDIS_CMD_DENYOOM,noPreloadGetKeys,1,1,1,0,0},
+    {"setex",setexCommand,4,REDIS_CMD_DENYOOM,noPreloadGetKeys,2,2,1,0,0},
     {"append",appendCommand,3,REDIS_CMD_DENYOOM,NULL,1,1,1,0,0},
     {"strlen",strlenCommand,2,0,NULL,1,1,1,0,0},
-    {"del",delCommand,-2,0,NULL,0,0,0,0,0},
+    {"del",delCommand,-2,0,noPreloadGetKeys,1,-1,1,0,0},
     {"exists",existsCommand,2,0,NULL,1,1,1,0,0},
     {"setbit",setbitCommand,4,REDIS_CMD_DENYOOM,NULL,1,1,1,0,0},
     {"getbit",getbitCommand,3,0,NULL,1,1,1,0,0},
@@ -94,7 +94,7 @@ struct redisCommand redisCommandTable[] = {
     {"lpop",lpopCommand,2,0,NULL,1,1,1,0,0},
     {"brpop",brpopCommand,-3,0,NULL,1,1,1,0,0},
     {"brpoplpush",brpoplpushCommand,4,REDIS_CMD_DENYOOM,NULL,1,2,1,0,0},
-    {"blpop",blpopCommand,-3,0,NULL,1,1,1,0,0},
+    {"blpop",blpopCommand,-3,0,NULL,1,-2,1,0,0},
     {"llen",llenCommand,2,0,NULL,1,1,1,0,0},
     {"lindex",lindexCommand,3,0,NULL,1,1,1,0,0},
     {"lset",lsetCommand,4,REDIS_CMD_DENYOOM,NULL,1,1,1,0,0},
@@ -121,8 +121,8 @@ struct redisCommand redisCommandTable[] = {
     {"zrem",zremCommand,3,0,NULL,1,1,1,0,0},
     {"zremrangebyscore",zremrangebyscoreCommand,4,0,NULL,1,1,1,0,0},
     {"zremrangebyrank",zremrangebyrankCommand,4,0,NULL,1,1,1,0,0},
-    {"zunionstore",zunionstoreCommand,-4,REDIS_CMD_DENYOOM,zunionInterBlockClientOnSwappedKeys,0,0,0,0,0},
-    {"zinterstore",zinterstoreCommand,-4,REDIS_CMD_DENYOOM,zunionInterBlockClientOnSwappedKeys,0,0,0,0,0},
+    {"zunionstore",zunionstoreCommand,-4,REDIS_CMD_DENYOOM,zunionInterGetKeys,0,0,0,0,0},
+    {"zinterstore",zinterstoreCommand,-4,REDIS_CMD_DENYOOM,zunionInterGetKeys,0,0,0,0,0},
     {"zrange",zrangeCommand,-4,0,NULL,1,1,1,0,0},
     {"zrangebyscore",zrangebyscoreCommand,-4,0,NULL,1,1,1,0,0},
     {"zrevrangebyscore",zrevrangebyscoreCommand,-4,0,NULL,1,1,1,0,0},
@@ -152,10 +152,10 @@ struct redisCommand redisCommandTable[] = {
     {"randomkey",randomkeyCommand,1,0,NULL,0,0,0,0,0},
     {"select",selectCommand,2,0,NULL,0,0,0,0,0},
     {"move",moveCommand,3,0,NULL,1,1,1,0,0},
-    {"rename",renameCommand,3,0,NULL,1,1,1,0,0},
-    {"renamenx",renamenxCommand,3,0,NULL,1,1,1,0,0},
-    {"expire",expireCommand,3,0,NULL,0,0,0,0,0},
-    {"expireat",expireatCommand,3,0,NULL,0,0,0,0,0},
+    {"rename",renameCommand,3,0,renameGetKeys,1,2,1,0,0},
+    {"renamenx",renamenxCommand,3,0,renameGetKeys,1,2,1,0,0},
+    {"expire",expireCommand,3,0,NULL,1,1,1,0,0},
+    {"expireat",expireatCommand,3,0,NULL,1,1,1,0,0},
     {"keys",keysCommand,2,0,NULL,0,0,0,0,0},
     {"dbsize",dbsizeCommand,1,0,NULL,0,0,0,0,0},
     {"auth",authCommand,2,0,NULL,0,0,0,0,0},
@@ -168,7 +168,7 @@ struct redisCommand redisCommandTable[] = {
     {"lastsave",lastsaveCommand,1,0,NULL,0,0,0,0,0},
     {"type",typeCommand,2,0,NULL,1,1,1,0,0},
     {"multi",multiCommand,1,0,NULL,0,0,0,0,0},
-    {"exec",execCommand,1,REDIS_CMD_DENYOOM,execBlockClientOnSwappedKeys,0,0,0,0,0},
+    {"exec",execCommand,1,REDIS_CMD_DENYOOM,NULL,0,0,0,0,0},
     {"discard",discardCommand,1,0,NULL,0,0,0,0,0},
     {"sync",syncCommand,1,0,NULL,0,0,0,0,0},
     {"flushdb",flushdbCommand,1,0,NULL,0,0,0,0,0},
@@ -186,8 +186,13 @@ struct redisCommand redisCommandTable[] = {
     {"psubscribe",psubscribeCommand,-2,0,NULL,0,0,0,0,0},
     {"punsubscribe",punsubscribeCommand,-1,0,NULL,0,0,0,0,0},
     {"publish",publishCommand,3,REDIS_CMD_FORCE_REPLICATION,NULL,0,0,0,0,0},
-    {"watch",watchCommand,-2,0,NULL,0,0,0,0,0},
-    {"unwatch",unwatchCommand,1,0,NULL,0,0,0,0,0}
+    {"watch",watchCommand,-2,0,noPreloadGetKeys,1,-1,1,0,0},
+    {"unwatch",unwatchCommand,1,0,NULL,0,0,0,0,0},
+    {"cluster",clusterCommand,-2,0,NULL,0,0,0,0,0},
+    {"restore",restoreCommand,4,0,NULL,0,0,0,0,0},
+    {"migrate",migrateCommand,6,0,NULL,0,0,0,0,0},
+    {"dump",dumpCommand,2,0,NULL,0,0,0,0,0},
+    {"object",objectCommand,-2,0,NULL,0,0,0,0,0}
 };
 
 /*============================ Utility functions ============================ */
@@ -440,6 +445,17 @@ dictType keylistDictType = {
     dictListDestructor          /* val destructor */
 };
 
+/* Cluster nodes hash table, mapping nodes addresses 1.2.3.4:6379 to
+ * clusterNode structures. */
+dictType clusterNodesDictType = {
+    dictSdsHash,                /* hash function */
+    NULL,                       /* key dup */
+    NULL,                       /* val dup */
+    dictSdsKeyCompare,          /* key compare */
+    dictSdsDestructor,          /* key destructor */
+    NULL                        /* val destructor */
+};
+
 int htNeedsResize(dict *dict) {
     long long size, used;
 
@@ -669,6 +685,9 @@ int serverCron(struct aeEventLoop *eventLoop, long long id, void *clientData) {
      * to detect transfer failures. */
     if (!(loops % 10)) replicationCron();
 
+    /* Run other sub-systems specific cron jobs */
+    if (server.cluster_enabled && !(loops % 10)) clusterCron();
+
     server.cronloops++;
     return 100;
 }
@@ -825,6 +844,8 @@ void initServerConfig() {
     server.zset_max_ziplist_value = REDIS_ZSET_MAX_ZIPLIST_VALUE;
     server.shutdown_asap = 0;
     server.cache_flush_delay = 0;
+    server.cluster_enabled = 0;
+    server.cluster.configfile = zstrdup("nodes.conf");
 
     updateLRUClock();
     resetServerSaveParams();
@@ -947,6 +968,7 @@ void initServer() {
     }
 
     if (server.ds_enabled) dsInit();
+    if (server.cluster_enabled) clusterInit();
     srand(time(NULL)^getpid());
 }
 
@@ -1053,6 +1075,27 @@ int processCommand(redisClient *c) {
         return REDIS_OK;
     }
 
+    /* If cluster is enabled, redirect here */
+    if (server.cluster_enabled &&
+                !(cmd->getkeys_proc == NULL && cmd->firstkey == 0)) {
+        int hashslot;
+
+        if (server.cluster.state != REDIS_CLUSTER_OK) {
+            addReplyError(c,"The cluster is down. Check with CLUSTER INFO for more information");
+            return REDIS_OK;
+        } else {
+            clusterNode *n = getNodeByQuery(c,cmd,c->argv,c->argc,&hashslot);
+            if (n == NULL) {
+                addReplyError(c,"Invalid cross-node request");
+                return REDIS_OK;
+            } else if (n != server.cluster.myself) {
+                addReplySds(c,sdscatprintf(sdsempty(),
+                    "-MOVED %d %s:%d\r\n",hashslot,n->ip,n->port));
+                return REDIS_OK;
+            }
+        }
+    }
+
     /* Handle the maxmemory directive.
      *
      * First we try to free some memory if possible (if there are volatile