@@ -807,8 +807,9 @@ int clusterProcessPacket(clusterLink *link) {
         if (totlen != explen) return 1;
     }
 
-    /* Ready to process the packet. Dispatch by type. */
+    /* Process packets by type. */
     sender = clusterLookupNode(hdr->sender);
+
     if (type == CLUSTERMSG_TYPE_PING || type == CLUSTERMSG_TYPE_MEET) {
         int update_config = 0;
         redisLog(REDIS_DEBUG,"Ping packet received: %p", (void*)link->node);
@@ -835,11 +836,16 @@ int clusterProcessPacket(clusterLink *link) {
 
         /* Update config if needed */
         if (update_config) clusterSaveConfigOrDie();
-    } else if (type == CLUSTERMSG_TYPE_PONG) {
+    }
+
+    /* PING or PONG: process config information. */
+    if (type == CLUSTERMSG_TYPE_PING || type == CLUSTERMSG_TYPE_PONG) {
         int update_state = 0;
         int update_config = 0;
 
-        redisLog(REDIS_DEBUG,"Pong packet received: %p", (void*)link->node);
+        redisLog(REDIS_DEBUG,"%s packet received: %p",
+            type == CLUSTERMSG_TYPE_PING ? "ping" : "pong",
+            (void*)link->node);
         if (link->node) {
             if (link->node->flags & REDIS_NODE_HANDSHAKE) {
                 /* If we already have this node, try to change the
@@ -1253,14 +1259,13 @@ void clusterSendPing(clusterLink *link, int type) {
     clusterSendMessage(link,buf,totlen);
 }
 
-/* Send a PING packet to every connected node that's not in handshake state.
+/* Send a PONG packet to every connected node that's not in handshake state.
  *
- * Usually cluster nodes will ping just another node every second, however
- * in Redis Cluster pings are not just used for failure detection, but also
- * to carry important configuration informations. So broadcasting a ping is
+ * In Redis Cluster pings are not just used for failure detection, but also
+ * to carry important configuration informations. So broadcasting a pong is
  * useful when something changes in the configuration and we want to make
  * the cluster aware ASAP (for instance after a slave promotion). */
-void clusterBroadcastPing(void) {
+void clusterBroadcastPong(void) {
     dictIterator *di;
     dictEntry *de;
 
@@ -1478,9 +1483,9 @@ void clusterHandleSlaveFailover(void) {
             }
         }
 
-        /* 3) Ping all the other nodes so that they can update the state
+        /* 3) Pong all the other nodes so that they can update the state
          *    accordingly and detect that we switched to master role. */
-        clusterBroadcastPing();
+        clusterBroadcastPong();
 
         /* 4) Update state and save config. */
         clusterUpdateState();