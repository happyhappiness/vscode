@@ -2736,9 +2736,13 @@ sds genRedisInfoString(char *section) {
         char hmem[64];
         char peak_hmem[64];
         char total_system_hmem[64];
+        char used_memory_lua_hmem[64];
+        char used_memory_rss_hmem[64];
+        char maxmemory_hmem[64];
         size_t zmalloc_used = zmalloc_used_memory();
         size_t total_system_mem = server.system_memory_size;
         char *evict_policy = maxmemoryToString();
+        long long memory_lua = (long long)lua_gc(server.lua,LUA_GCCOUNT,0)*1024;
 
         /* Peak memory is updated from time to time by serverCron() so it
          * may happen that the instantaneous value is slightly bigger than
@@ -2750,32 +2754,43 @@ sds genRedisInfoString(char *section) {
         bytesToHuman(hmem,zmalloc_used);
         bytesToHuman(peak_hmem,server.stat_peak_memory);
         bytesToHuman(total_system_hmem,total_system_mem);
+        bytesToHuman(used_memory_lua_hmem,memory_lua);
+        bytesToHuman(used_memory_rss_hmem,server.resident_set_size);
+        bytesToHuman(maxmemory_hmem,server.maxmemory);
 
         if (sections++) info = sdscat(info,"\r\n");
         info = sdscatprintf(info,
             "# Memory\r\n"
             "used_memory:%zu\r\n"
             "used_memory_human:%s\r\n"
             "used_memory_rss:%zu\r\n"
+            "used_memory_rss_human:%s\r\n"
             "used_memory_peak:%zu\r\n"
             "used_memory_peak_human:%s\r\n"
             "total_system_memory:%lu\r\n"
             "total_system_memory_human:%s\r\n"
             "used_memory_lua:%lld\r\n"
+            "used_memory_lua_human:%s\r\n"
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
+            used_memory_rss_hmem,
             server.stat_peak_memory,
             peak_hmem,
             (unsigned long)total_system_mem,
             total_system_hmem,
-            ((long long)lua_gc(server.lua,LUA_GCCOUNT,0))*1024LL,
+            memory_lua,
+            used_memory_lua_hmem,
+            server.maxmemory,
+            maxmemory_hmem,
+            evict_policy,
             zmalloc_get_fragmentation_ratio(server.resident_set_size),
-            ZMALLOC_LIB,
-            evict_policy
+            ZMALLOC_LIB
             );
     }
 