@@ -268,6 +268,7 @@ void clusterInit(void) {
 
 clusterLink *createClusterLink(clusterNode *node) {
     clusterLink *link = zmalloc(sizeof(*link));
+    link->ctime = time(NULL);
     link->sndbuf = sdsempty();
     link->rcvbuf = sdsempty();
     link->node = node;
@@ -1596,21 +1597,20 @@ void clusterCron(void) {
             (REDIS_NODE_MYSELF|REDIS_NODE_NOADDR|REDIS_NODE_HANDSHAKE))
                 continue;
 
-#if 0
         /* If we are waiting for the PONG more than half the cluster
          * timeout, reconnect the link: maybe there is a connection
          * issue even if the node is alive. */
         if (node->link && /* is connected */
+            time(NULL) - node->link->ctime >
+            server.cluster_node_timeout && /* was not already reconnected */
             node->ping_sent && /* we already sent a ping */
             node->pong_received < node->ping_sent && /* still waiting pong */
             /* and we are waiting for the pong more than timeout/2 */
             now - node->ping_sent > server.cluster_node_timeout/2)
         {
             /* Disconnect the link, it will be reconnected automatically. */
-            printf("DISCONNECT!\n");
             freeClusterLink(node->link);
         }
-#endif
 
         /* If we have currently no active ping in this instance, and the
          * received PONG is older than half the cluster timeout, send