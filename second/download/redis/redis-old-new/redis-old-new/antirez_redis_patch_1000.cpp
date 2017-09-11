@@ -967,8 +967,12 @@ void clusterProcessGossipSection(clusterMsg *hdr, clusterLink *link) {
              * Note that we require that the sender of this gossip message
              * is a well known node in our cluster, otherwise we risk
              * joining another cluster. */
-            if (sender && !(flags & REDIS_NODE_NOADDR))
+            if (sender &&
+                !(flags & REDIS_NODE_NOADDR) &&
+                !clusterBlacklistExists(g->nodename))
+            {
                 clusterStartHandshake(g->ip,ntohs(g->port));
+            }
         }
 
         /* Next node */
@@ -2875,6 +2879,7 @@ void clusterCommand(redisClient *c) {
             addReplyErrorFormat(c,"Unknown node %s", (char*)c->argv[2]->ptr);
             return;
         }
+        clusterBlacklistAddNode(n);
         clusterDelNode(n);
         clusterDoBeforeSleep(CLUSTER_TODO_UPDATE_STATE|CLUSTER_TODO_SAVE_CONFIG);
         addReply(c,shared.ok);