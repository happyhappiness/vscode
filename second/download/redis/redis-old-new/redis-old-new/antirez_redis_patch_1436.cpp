@@ -1465,7 +1465,7 @@ sds genRedisInfoString(char *section) {
         if (sections++) info = sdscat(info,"\r\n");
         info = sdscatprintf(info,
             "# Clients\r\n"
-            "connected_clients:%d\r\n"
+            "connected_clients:%lu\r\n"
             "client_longest_output_list:%lu\r\n"
             "client_biggest_input_buf:%lu\r\n"
             "blocked_clients:%d\r\n",
@@ -1580,7 +1580,7 @@ sds genRedisInfoString(char *section) {
             "keyspace_hits:%lld\r\n"
             "keyspace_misses:%lld\r\n"
             "pubsub_channels:%ld\r\n"
-            "pubsub_patterns:%u\r\n"
+            "pubsub_patterns:%lu\r\n"
             "latest_fork_usec:%lld\r\n",
             server.stat_numconnections,
             server.stat_numcommands,
@@ -1633,7 +1633,7 @@ sds genRedisInfoString(char *section) {
             }
         }
         info = sdscatprintf(info,
-            "connected_slaves:%d\r\n",
+            "connected_slaves:%lu\r\n",
             listLength(server.slaves));
         if (listLength(server.slaves)) {
             int slaveid = 0;