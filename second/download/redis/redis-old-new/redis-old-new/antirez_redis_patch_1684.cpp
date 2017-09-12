@@ -505,6 +505,7 @@ int clusterProcessPacket(clusterLink *link) {
 
     sender = clusterLookupNode(hdr->sender);
     if (type == CLUSTERMSG_TYPE_PING || type == CLUSTERMSG_TYPE_MEET) {
+        int update_config = 0;
         redisLog(REDIS_DEBUG,"Ping packet received: %p", link->node);
 
         /* Add this node if it is new for us and the msg type is MEET.
@@ -518,13 +519,17 @@ int clusterProcessPacket(clusterLink *link) {
             nodeIp2String(node->ip,link);
             node->port = ntohs(hdr->port);
             clusterAddNode(node);
+            update_config = 1;
         }
 
         /* Get info from the gossip section */
         clusterProcessGossipSection(hdr,link);
 
         /* Anyway reply with a PONG */
         clusterSendPing(link,CLUSTERMSG_TYPE_PONG);
+
+        /* Update config if needed */
+        if (update_config) clusterSaveConfigOrDie();
     } else if (type == CLUSTERMSG_TYPE_PONG) {
         int update_state = 0;
         int update_config = 0;
@@ -879,7 +884,7 @@ void clusterCron(void) {
              * normal PING packets. */
             node->flags &= ~REDIS_NODE_MEET;
 
-            redisLog(REDIS_NOTICE,"Connecting with Node %.40s at %s:%d\n", node->name, node->ip, node->port+REDIS_CLUSTER_PORT_INCR);
+            redisLog(REDIS_NOTICE,"Connecting with Node %.40s at %s:%d", node->name, node->ip, node->port+REDIS_CLUSTER_PORT_INCR);
         }
     }
     dictReleaseIterator(di);