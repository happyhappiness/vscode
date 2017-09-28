             server.stat_evictedkeys,
             server.stat_keyspace_hits,
             server.stat_keyspace_misses,
             dictSize(server.pubsub_channels),
             listLength(server.pubsub_patterns),
             server.stat_fork_time,
-            dictSize(server.migrate_cached_sockets));
+            dictSize(server.migrate_cached_sockets),
+            getSlaveKeyWithExpireCount(),
+            server.stat_active_defrag_hits,
+            server.stat_active_defrag_misses,
+            server.stat_active_defrag_key_hits,
+            server.stat_active_defrag_key_misses);
     }
 
     /* Replication */
     if (allsections || defsections || !strcasecmp(section,"replication")) {
         if (sections++) info = sdscat(info,"\r\n");
         info = sdscatprintf(info,
