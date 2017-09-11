@@ -1565,12 +1565,14 @@ void clusterCommand(redisClient *c) {
             "cluster_slots_pfail:%d\r\n"
             "cluster_slots_fail:%d\r\n"
             "cluster_known_nodes:%lu\r\n"
+            "cluster_size:%d\r\n"
             , statestr[server.cluster->state],
             slots_assigned,
             slots_ok,
             slots_pfail,
             slots_fail,
-            dictSize(server.cluster->nodes)
+            dictSize(server.cluster->nodes),
+            server.cluster->size
         );
         addReplySds(c,sdscatprintf(sdsempty(),"$%lu\r\n",
             (unsigned long)sdslen(info)));