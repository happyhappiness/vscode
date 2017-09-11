@@ -259,6 +259,8 @@ void clusterInit(void) {
     server.cluster->failover_auth_count = 0;
     server.cluster->failover_auth_epoch = 0;
     server.cluster->last_vote_epoch = 0;
+    server.cluster->stats_bus_messages_sent = 0;
+    server.cluster->stats_bus_messages_received = 0;
     memset(server.cluster->migrating_slots_to,0,
         sizeof(server.cluster->migrating_slots_to));
     memset(server.cluster->importing_slots_from,0,
@@ -878,6 +880,7 @@ int clusterProcessPacket(clusterLink *link) {
     uint64_t senderCurrentEpoch, senderConfigEpoch;
     clusterNode *sender;
 
+    server.cluster->stats_bus_messages_received++;
     redisLog(REDIS_DEBUG,"--- Processing packet of type %d, %lu bytes",
         type, (unsigned long) totlen);
 
@@ -1318,6 +1321,7 @@ void clusterSendMessage(clusterLink *link, unsigned char *msg, size_t msglen) {
                     clusterWriteHandler,link);
 
     link->sndbuf = sdscatlen(link->sndbuf, msg, msglen);
+    server.cluster->stats_bus_messages_sent++;
 }
 
 /* Send a message to all the nodes that are part of the cluster having
@@ -2449,14 +2453,18 @@ void clusterCommand(redisClient *c) {
             "cluster_known_nodes:%lu\r\n"
             "cluster_size:%d\r\n"
             "cluster_current_epoch:%llu\r\n"
+            "cluster_stats_messages_sent:%lld\r\n"
+            "cluster_stats_messages_received:%lld\r\n"
             , statestr[server.cluster->state],
             slots_assigned,
             slots_ok,
             slots_pfail,
             slots_fail,
             dictSize(server.cluster->nodes),
             server.cluster->size,
-            (unsigned long long) server.cluster->currentEpoch
+            (unsigned long long) server.cluster->currentEpoch,
+            server.cluster->stats_bus_messages_sent,
+            server.cluster->stats_bus_messages_received
         );
         addReplySds(c,sdscatprintf(sdsempty(),"$%lu\r\n",
             (unsigned long)sdslen(info)));