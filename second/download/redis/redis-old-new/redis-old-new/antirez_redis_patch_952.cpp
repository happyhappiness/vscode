@@ -2021,15 +2021,25 @@ int processCommand(redisClient *c) {
             addReplySds(c,sdsnew("-CLUSTERDOWN The cluster is down. Use CLUSTER INFO for more information\r\n"));
             return REDIS_OK;
         } else {
-            int ask;
-            clusterNode *n = getNodeByQuery(c,c->cmd,c->argv,c->argc,&hashslot,&ask);
+            int error_code;
+            clusterNode *n = getNodeByQuery(c,c->cmd,c->argv,c->argc,&hashslot,&error_code);
             if (n == NULL) {
-                addReplyError(c,"Multi keys request invalid in cluster");
+                if (error_code == REDIS_CLUSTER_REDIR_CROSS_SLOT) {
+                    addReplySds(c,sdsnew("-CROSSSLOT Keys in request don't hash to the same slot\r\n"));
+                } else if (error_code == REDIS_CLUSTER_REDIR_UNSTABLE) {
+                    /* The request spawns mutliple keys in the same slot,
+                     * but the slot is not "stable" currently as there is
+                     * a migration or import in progress. */
+                    addReplySds(c,sdsnew("-TRYAGAIN Multiple keys request during rehashing of slot\r\n"));
+                } else {
+                    redisPanic("getNodeByQuery() unknown error.");
+                }
                 return REDIS_OK;
             } else if (n != server.cluster->myself) {
                 flagTransaction(c);
                 addReplySds(c,sdscatprintf(sdsempty(),
-                    "-%s %d %s:%d\r\n", ask ? "ASK" : "MOVED",
+                    "-%s %d %s:%d\r\n",
+                    (error_code == REDIS_CLUSTER_REDIR_ASK) ? "ASK" : "MOVED",
                     hashslot,n->ip,n->port));
                 return REDIS_OK;
             }