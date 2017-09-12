@@ -1096,13 +1096,15 @@ int processCommand(redisClient *c) {
             addReplyError(c,"The cluster is down. Check with CLUSTER INFO for more information");
             return REDIS_OK;
         } else {
-            clusterNode *n = getNodeByQuery(c,cmd,c->argv,c->argc,&hashslot);
+            int ask;
+            clusterNode *n = getNodeByQuery(c,cmd,c->argv,c->argc,&hashslot,&ask);
             if (n == NULL) {
-                addReplyError(c,"Invalid cross-node request");
+                addReplyError(c,"Multi keys request invalid in cluster");
                 return REDIS_OK;
             } else if (n != server.cluster.myself) {
                 addReplySds(c,sdscatprintf(sdsempty(),
-                    "-MOVED %d %s:%d\r\n",hashslot,n->ip,n->port));
+                    "-%s %d %s:%d\r\n", ask ? "ASK" : "MOVED",
+                    hashslot,n->ip,n->port));
                 return REDIS_OK;
             }
         }