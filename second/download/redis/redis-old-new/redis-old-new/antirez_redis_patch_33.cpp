@@ -423,8 +423,10 @@ void clusterInit(void) {
     server.cluster->failover_auth_epoch = 0;
     server.cluster->cant_failover_reason = CLUSTER_CANT_FAILOVER_NONE;
     server.cluster->lastVoteEpoch = 0;
-    server.cluster->stats_bus_messages_sent = 0;
-    server.cluster->stats_bus_messages_received = 0;
+    for (int i = 0; i < CLUSTERMSG_TYPE_COUNT; i++) {
+        server.cluster->stats_bus_messages_sent[i] = 0;
+        server.cluster->stats_bus_messages_received[i] = 0;
+    }
     memset(server.cluster->slots,0, sizeof(server.cluster->slots));
     clusterCloseAllSlots();
 
@@ -1583,7 +1585,8 @@ int clusterProcessPacket(clusterLink *link) {
     uint32_t totlen = ntohl(hdr->totlen);
     uint16_t type = ntohs(hdr->type);
 
-    server.cluster->stats_bus_messages_received++;
+    if (type < CLUSTERMSG_TYPE_COUNT)
+        server.cluster->stats_bus_messages_received[type]++;
     serverLog(LL_DEBUG,"--- Processing packet of type %d, %lu bytes",
         type, (unsigned long) totlen);
 
@@ -2130,7 +2133,12 @@ void clusterSendMessage(clusterLink *link, unsigned char *msg, size_t msglen) {
                     clusterWriteHandler,link);
 
     link->sndbuf = sdscatlen(link->sndbuf, msg, msglen);
-    server.cluster->stats_bus_messages_sent++;
+
+    /* Populate sent messages stats. */
+    clusterMsg *hdr = (clusterMsg*) msg;
+    uint16_t type = ntohs(hdr->type);
+    if (type < CLUSTERMSG_TYPE_COUNT)
+        server.cluster->stats_bus_messages_sent[type]++;
 }
 
 /* Send a message to all the nodes that are part of the cluster having
@@ -3877,6 +3885,21 @@ sds clusterGenNodesDescription(int filter) {
  * CLUSTER command
  * -------------------------------------------------------------------------- */
 
+const char *clusterGetMessageTypeString(int type) {
+    switch(type) {
+    case CLUSTERMSG_TYPE_PING: return "ping";
+    case CLUSTERMSG_TYPE_PONG: return "pong";
+    case CLUSTERMSG_TYPE_MEET: return "meet";
+    case CLUSTERMSG_TYPE_FAIL: return "fail";
+    case CLUSTERMSG_TYPE_PUBLISH: return "publish";
+    case CLUSTERMSG_TYPE_FAILOVER_AUTH_REQUEST: return "auth-req";
+    case CLUSTERMSG_TYPE_FAILOVER_AUTH_ACK: return "auth-ack";
+    case CLUSTERMSG_TYPE_UPDATE: return "update";
+    case CLUSTERMSG_TYPE_MFSTART: return "mfstart";
+    }
+    return "unknown";
+}
+
 int getSlotOrReply(client *c, robj *o) {
     long long slot;
 
@@ -4208,8 +4231,6 @@ void clusterCommand(client *c) {
             "cluster_size:%d\r\n"
             "cluster_current_epoch:%llu\r\n"
             "cluster_my_epoch:%llu\r\n"
-            "cluster_stats_messages_sent:%lld\r\n"
-            "cluster_stats_messages_received:%lld\r\n"
             , statestr[server.cluster->state],
             slots_assigned,
             slots_ok,
@@ -4218,10 +4239,36 @@ void clusterCommand(client *c) {
             dictSize(server.cluster->nodes),
             server.cluster->size,
             (unsigned long long) server.cluster->currentEpoch,
-            (unsigned long long) myepoch,
-            server.cluster->stats_bus_messages_sent,
-            server.cluster->stats_bus_messages_received
+            (unsigned long long) myepoch
         );
+
+        /* Show stats about messages sent and received. */
+        long long tot_msg_sent = 0;
+        long long tot_msg_received = 0;
+
+        for (int i = 0; i < CLUSTERMSG_TYPE_COUNT; i++) {
+            if (server.cluster->stats_bus_messages_sent[i] == 0) continue;
+            tot_msg_sent += server.cluster->stats_bus_messages_sent[i];
+            info = sdscatprintf(info,
+                "cluster_stats_messages_%s_sent:%lld\r\n",
+                clusterGetMessageTypeString(i),
+                server.cluster->stats_bus_messages_sent[i]);
+        }
+        info = sdscatprintf(info,
+            "cluster_stats_messages_sent:%lld\r\n", tot_msg_sent);
+
+        for (int i = 0; i < CLUSTERMSG_TYPE_COUNT; i++) {
+            if (server.cluster->stats_bus_messages_received[i] == 0) continue;
+            tot_msg_received += server.cluster->stats_bus_messages_received[i];
+            info = sdscatprintf(info,
+                "cluster_stats_messages_%s_received:%lld\r\n",
+                clusterGetMessageTypeString(i),
+                server.cluster->stats_bus_messages_received[i]);
+        }
+        info = sdscatprintf(info,
+            "cluster_stats_messages_received:%lld\r\n", tot_msg_received);
+
+        /* Produce the reply protocol. */
         addReplySds(c,sdscatprintf(sdsempty(),"$%lu\r\n",
             (unsigned long)sdslen(info)));
         addReplySds(c,info);