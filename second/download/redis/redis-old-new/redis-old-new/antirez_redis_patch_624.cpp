@@ -2702,6 +2702,7 @@ sds genRedisInfoString(char *section) {
         char total_system_hmem[64];
         char used_memory_lua_hmem[64];
         char used_memory_rss_hmem[64];
+        char maxmemory_hmem[64];
         size_t zmalloc_used = zmalloc_used_memory();
         size_t total_system_mem = server.system_memory_size;
         char *evict_policy = maxmemoryToString();
@@ -2719,6 +2720,7 @@ sds genRedisInfoString(char *section) {
         bytesToHuman(total_system_hmem,total_system_mem);
         bytesToHuman(used_memory_lua_hmem,memory_lua);
         bytesToHuman(used_memory_rss_hmem,server.resident_set_size);
+        bytesToHuman(maxmemory_hmem,server.maxmemory);
 
         if (sections++) info = sdscat(info,"\r\n");
         info = sdscatprintf(info,
@@ -2733,9 +2735,11 @@ sds genRedisInfoString(char *section) {
             "total_system_memory_human:%s\r\n"
             "used_memory_lua:%lld\r\n"
             "used_memory_lua_human:%s\r\n"
+            "maxmemory:%lld\r\n"
+            "maxmemory_human:%s\r\n"
+            "maxmemory_policy:%s\r\n"
             "mem_fragmentation_ratio:%.2f\r\n"
-            "mem_allocator:%s\r\n"
-            "maxmemory_policy:%s\r\n",
+            "mem_allocator:%s\r\n",
             zmalloc_used,
             hmem,
             server.resident_set_size,
@@ -2746,9 +2750,11 @@ sds genRedisInfoString(char *section) {
             total_system_hmem,
             memory_lua,
             used_memory_lua_hmem,
+            server.maxmemory,
+            maxmemory_hmem,
+            evict_policy,
             zmalloc_get_fragmentation_ratio(server.resident_set_size),
-            ZMALLOC_LIB,
-            evict_policy
+            ZMALLOC_LIB
             );
     }
 