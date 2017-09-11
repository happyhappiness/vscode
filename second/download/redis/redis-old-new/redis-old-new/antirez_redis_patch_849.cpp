@@ -3564,6 +3564,7 @@ void clusterCommand(redisClient *c) {
         /* CLUSTER INFO */
         char *statestr[] = {"ok","fail","needhelp"};
         int slots_assigned = 0, slots_ok = 0, slots_pfail = 0, slots_fail = 0;
+        uint64_t myepoch;
         int j;
 
         for (j = 0; j < REDIS_CLUSTER_SLOTS; j++) {
@@ -3580,6 +3581,9 @@ void clusterCommand(redisClient *c) {
             }
         }
 
+        myepoch = (nodeIsSlave(myself) && myself->slaveof) ?
+                  myself->slaveof->configEpoch : myself->configEpoch;
+
         sds info = sdscatprintf(sdsempty(),
             "cluster_state:%s\r\n"
             "cluster_slots_assigned:%d\r\n"
@@ -3589,6 +3593,7 @@ void clusterCommand(redisClient *c) {
             "cluster_known_nodes:%lu\r\n"
             "cluster_size:%d\r\n"
             "cluster_current_epoch:%llu\r\n"
+            "cluster_my_epoch:%llu\r\n"
             "cluster_stats_messages_sent:%lld\r\n"
             "cluster_stats_messages_received:%lld\r\n"
             , statestr[server.cluster->state],
@@ -3599,6 +3604,7 @@ void clusterCommand(redisClient *c) {
             dictSize(server.cluster->nodes),
             server.cluster->size,
             (unsigned long long) server.cluster->currentEpoch,
+            (unsigned long long) myepoch,
             server.cluster->stats_bus_messages_sent,
             server.cluster->stats_bus_messages_received
         );