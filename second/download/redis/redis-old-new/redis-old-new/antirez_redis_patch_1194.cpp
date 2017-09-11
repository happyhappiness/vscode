@@ -1662,7 +1662,7 @@ int processCommand(redisClient *c) {
         int hashslot;
 
         if (server.cluster->state != REDIS_CLUSTER_OK) {
-            addReplyError(c,"The cluster is down. Check with CLUSTER INFO for more information");
+            addReplySds(c,sdsnew("-CLUSTERDOWN The cluster is down. Use CLUSTER INFO for more information\r\n"));
             return REDIS_OK;
         } else {
             int ask;