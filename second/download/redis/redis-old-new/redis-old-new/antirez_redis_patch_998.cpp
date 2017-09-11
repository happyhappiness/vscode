@@ -2875,12 +2875,16 @@ void clusterCommand(redisClient *c) {
         /* CLUSTER FORGET <NODE ID> */
         clusterNode *n = clusterLookupNode(c->argv[2]->ptr);
 
-        if (n == server.cluster->myself) {
-            addReplyErrorFormat(c,"I tried hard but I can't forget myself...");
-            return;
-        } else if (!n) {
+        if (!n) {
             addReplyErrorFormat(c,"Unknown node %s", (char*)c->argv[2]->ptr);
             return;
+        } else if (n == server.cluster->myself) {
+            addReplyError(c,"I tried hard but I can't forget myself...");
+            return;
+        } else if (server.cluster->myself->flags & REDIS_NODE_SLAVE &&
+                   server.cluster->myself->slaveof == n) {
+            addReplyError(c,"Can't forget my master!");
+            return;
         }
         clusterBlacklistAddNode(n);
         clusterDelNode(n);