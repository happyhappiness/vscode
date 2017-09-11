@@ -740,8 +740,11 @@ int activeExpireCycleTryExpire(redisDb *db, dictEntry *de, long long now) {
         sds key = dictGetKey(de);
         robj *keyobj = createStringObject(key,sdslen(key));
 
-        propagateExpire(db,keyobj);
-        dbDelete(db,keyobj);
+        propagateExpire(db,keyobj,server.lazyfree_lazy_expire);
+        if (server.lazyfree_lazy_expire)
+            dbAsyncDelete(db,keyobj);
+        else
+            dbSyncDelete(db,keyobj);
         notifyKeyspaceEvent(NOTIFY_EXPIRED,
             "expired",keyobj,db->id);
         decrRefCount(keyobj);
@@ -1405,6 +1408,7 @@ void createSharedObjects(void) {
     shared.psubscribebulk = createStringObject("$10\r\npsubscribe\r\n",17);
     shared.punsubscribebulk = createStringObject("$12\r\npunsubscribe\r\n",19);
     shared.del = createStringObject("DEL",3);
+    shared.unlink = createStringObject("UNLINK",6);
     shared.rpop = createStringObject("RPOP",4);
     shared.lpop = createStringObject("LPOP",4);
     shared.lpush = createStringObject("LPUSH",5);
@@ -1497,10 +1501,6 @@ void initServerConfig(void) {
     server.zset_max_ziplist_value = OBJ_ZSET_MAX_ZIPLIST_VALUE;
     server.hll_sparse_max_bytes = CONFIG_DEFAULT_HLL_SPARSE_MAX_BYTES;
     server.shutdown_asap = 0;
-    server.repl_ping_slave_period = CONFIG_DEFAULT_REPL_PING_SLAVE_PERIOD;
-    server.repl_timeout = CONFIG_DEFAULT_REPL_TIMEOUT;
-    server.repl_min_slaves_to_write = CONFIG_DEFAULT_MIN_SLAVES_TO_WRITE;
-    server.repl_min_slaves_max_lag = CONFIG_DEFAULT_MIN_SLAVES_MAX_LAG;
     server.cluster_enabled = 0;
     server.cluster_node_timeout = CLUSTER_DEFAULT_NODE_TIMEOUT;
     server.cluster_migration_barrier = CLUSTER_DEFAULT_MIGRATION_BARRIER;
@@ -1514,13 +1514,17 @@ void initServerConfig(void) {
     server.migrate_cached_sockets = dictCreate(&migrateCacheDictType,NULL);
     server.next_client_id = 1; /* Client IDs, start from 1 .*/
     server.loading_process_events_interval_bytes = (1024*1024*2);
+    server.lazyfree_lazy_eviction = CONFIG_DEFAULT_LAZYFREE_LAZY_EVICTION;
+    server.lazyfree_lazy_expire = CONFIG_DEFAULT_LAZYFREE_LAZY_EXPIRE;
+    server.lazyfree_lazy_server_del = CONFIG_DEFAULT_LAZYFREE_LAZY_SERVER_DEL;
 
     server.lruclock = getLRUClock();
     resetServerSaveParams();
 
     appendServerSaveParams(60*60,1);  /* save after 1 hour and 1 change */
     appendServerSaveParams(300,100);  /* save after 5 minutes and 100 changes */
     appendServerSaveParams(60,10000); /* save after 1 minute and 10000 changes */
+
     /* Replication related */
     server.masterauth = NULL;
     server.masterhost = NULL;
@@ -1532,10 +1536,15 @@ void initServerConfig(void) {
     server.repl_syncio_timeout = CONFIG_REPL_SYNCIO_TIMEOUT;
     server.repl_serve_stale_data = CONFIG_DEFAULT_SLAVE_SERVE_STALE_DATA;
     server.repl_slave_ro = CONFIG_DEFAULT_SLAVE_READ_ONLY;
+    server.repl_slave_lazy_flush = CONFIG_DEFAULT_SLAVE_LAZY_FLUSH;
     server.repl_down_since = 0; /* Never connected, repl is down since EVER. */
     server.repl_disable_tcp_nodelay = CONFIG_DEFAULT_REPL_DISABLE_TCP_NODELAY;
     server.repl_diskless_sync = CONFIG_DEFAULT_REPL_DISKLESS_SYNC;
     server.repl_diskless_sync_delay = CONFIG_DEFAULT_REPL_DISKLESS_SYNC_DELAY;
+    server.repl_ping_slave_period = CONFIG_DEFAULT_REPL_PING_SLAVE_PERIOD;
+    server.repl_timeout = CONFIG_DEFAULT_REPL_TIMEOUT;
+    server.repl_min_slaves_to_write = CONFIG_DEFAULT_MIN_SLAVES_TO_WRITE;
+    server.repl_min_slaves_max_lag = CONFIG_DEFAULT_MIN_SLAVES_MAX_LAG;
     server.slave_priority = CONFIG_DEFAULT_SLAVE_PRIORITY;
     server.master_repl_offset = 0;
 
@@ -3408,8 +3417,8 @@ int freeMemoryIfNeeded(void) {
             /* Finally remove the selected key. */
             if (bestkey) {
                 robj *keyobj = createStringObject(bestkey,sdslen(bestkey));
-                propagateExpire(db,keyobj);
-                /* We compute the amount of memory freed by dbDelete() alone.
+                propagateExpire(db,keyobj,server.lazyfree_lazy_eviction);
+                /* We compute the amount of memory freed by db*Delete() alone.
                  * It is possible that actually the memory needed to propagate
                  * the DEL in AOF and replication link is greater than the one
                  * we are freeing removing the key, but we can't account for
@@ -3419,7 +3428,10 @@ int freeMemoryIfNeeded(void) {
                  * we only care about memory used by the key space. */
                 delta = (long long) zmalloc_used_memory();
                 latencyStartMonitor(eviction_latency);
-                dbDelete(db,keyobj);
+                if (server.lazyfree_lazy_eviction)
+                    dbAsyncDelete(db,keyobj);
+                else
+                    dbSyncDelete(db,keyobj);
                 latencyEndMonitor(eviction_latency);
                 latencyAddSampleIfNeeded("eviction-del",eviction_latency);
                 latencyRemoveNestedEvent(latency,eviction_latency);