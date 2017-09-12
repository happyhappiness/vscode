@@ -6449,6 +6449,9 @@ static sds genRedisInfoString(void) {
     time_t uptime = time(NULL)-server.stat_starttime;
     int j;
     char hmem[64];
+
+    server.hash_max_zipmap_entries = REDIS_HASH_MAX_ZIPMAP_ENTRIES;
+    server.hash_max_zipmap_value = REDIS_HASH_MAX_ZIPMAP_VALUE;
   
     bytesToHuman(hmem,zmalloc_used_memory());
     info = sdscatprintf(sdsempty(),
@@ -6469,6 +6472,8 @@ static sds genRedisInfoString(void) {
         "bgrewriteaof_in_progress:%d\r\n"
         "total_connections_received:%lld\r\n"
         "total_commands_processed:%lld\r\n"
+        "hash_max_zipmap_entries:%ld\r\n"
+        "hash_max_zipmap_value:%ld\r\n"
         "vm_enabled:%d\r\n"
         "role:%s\r\n"
         ,REDIS_VERSION,
@@ -6488,6 +6493,8 @@ static sds genRedisInfoString(void) {
         server.bgrewritechildpid != -1,
         server.stat_numconnections,
         server.stat_numcommands,
+        server.hash_max_zipmap_entries,
+        server.hash_max_zipmap_value,
         server.vm_enabled != 0,
         server.masterhost == NULL ? "master" : "slave"
     );