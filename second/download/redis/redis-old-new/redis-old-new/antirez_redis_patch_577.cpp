@@ -4176,9 +4176,12 @@ void clusterCommand(redisClient *c) {
         if (nodeIsMaster(myself)) {
             addReplyError(c,"You should send CLUSTER FAILOVER to a slave");
             return;
+        } else if (myself->slaveof == NULL) {
+            addReplyError(c,"I'm a slave but my master is unknown to me");
+            return;
         } else if (!force &&
-                   (myself->slaveof == NULL || nodeFailed(myself->slaveof) ||
-                   myself->slaveof->link == NULL))
+                   (nodeFailed(myself->slaveof) ||
+                    myself->slaveof->link == NULL))
         {
             addReplyError(c,"Master is down or failed, "
                             "please use CLUSTER FAILOVER FORCE");