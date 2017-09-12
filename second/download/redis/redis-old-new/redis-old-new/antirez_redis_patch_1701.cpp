@@ -187,7 +187,10 @@ struct redisCommand redisCommandTable[] = {
     {"punsubscribe",punsubscribeCommand,-1,0,NULL,0,0,0,0,0},
     {"publish",publishCommand,3,REDIS_CMD_FORCE_REPLICATION,NULL,0,0,0,0,0},
     {"watch",watchCommand,-2,0,noPreloadGetKeys,1,-1,1,0,0},
-    {"unwatch",unwatchCommand,1,0,NULL,0,0,0,0,0}
+    {"unwatch",unwatchCommand,1,0,NULL,0,0,0,0,0},
+    {"cluster",clusterCommand,-2,0,NULL,0,0,0,0,0},
+    {"restore",restoreCommand,3,0,NULL,0,0,0,0,0},
+    {"migrate",migrateCommand,6,0,NULL,0,0,0,0,0}
 };
 
 /*============================ Utility functions ============================ */
@@ -440,6 +443,17 @@ dictType keylistDictType = {
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
 
@@ -669,6 +683,9 @@ int serverCron(struct aeEventLoop *eventLoop, long long id, void *clientData) {
      * to detect transfer failures. */
     if (!(loops % 10)) replicationCron();
 
+    /* Run other sub-systems specific cron jobs */
+    if (server.cluster_enabled && !(loops % 10)) clusterCron();
+
     server.cronloops++;
     return 100;
 }
@@ -823,6 +840,7 @@ void initServerConfig() {
     server.set_max_intset_entries = REDIS_SET_MAX_INTSET_ENTRIES;
     server.shutdown_asap = 0;
     server.cache_flush_delay = 0;
+    server.cluster_enabled = 0;
 
     updateLRUClock();
     resetServerSaveParams();
@@ -945,6 +963,7 @@ void initServer() {
     }
 
     if (server.ds_enabled) dsInit();
+    if (server.cluster_enabled) clusterInit();
     srand(time(NULL)^getpid());
 }
 
@@ -1051,6 +1070,27 @@ int processCommand(redisClient *c) {
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