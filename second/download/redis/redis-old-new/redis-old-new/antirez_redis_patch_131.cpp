@@ -2812,6 +2812,7 @@ sds genRedisInfoString(char *section) {
         size_t total_system_mem = server.system_memory_size;
         const char *evict_policy = evictPolicyToString();
         long long memory_lua = (long long)lua_gc(server.lua,LUA_GCCOUNT,0)*1024;
+        struct redisMemOverhead *mh = getMemoryOverheadData();
 
         /* Peak memory is updated from time to time by serverCron() so it
          * may happen that the instantaneous value is slightly bigger than
@@ -2827,6 +2828,10 @@ sds genRedisInfoString(char *section) {
         bytesToHuman(used_memory_rss_hmem,server.resident_set_size);
         bytesToHuman(maxmemory_hmem,server.maxmemory);
 
+        size_t net_usage = 1;
+        if (zmalloc_used > mh->startup_allocated)
+            net_usage = zmalloc_used - mh->startup_allocated;
+
         if (sections++) info = sdscat(info,"\r\n");
         info = sdscatprintf(info,
             "# Memory\r\n"
@@ -2836,6 +2841,10 @@ sds genRedisInfoString(char *section) {
             "used_memory_rss_human:%s\r\n"
             "used_memory_peak:%zu\r\n"
             "used_memory_peak_human:%s\r\n"
+            "used_memory_overhead:%zu\r\n"
+            "used_memory_startup:%zu\r\n"
+            "used_memory_dataset:%zu\r\n"
+            "used_memory_dataset_perc:%.2f%%\r\n"
             "total_system_memory:%lu\r\n"
             "total_system_memory_human:%s\r\n"
             "used_memory_lua:%lld\r\n"
@@ -2852,6 +2861,10 @@ sds genRedisInfoString(char *section) {
             used_memory_rss_hmem,
             server.stat_peak_memory,
             peak_hmem,
+            mh->overhead_total,
+            mh->startup_allocated,
+            mh->dataset,
+            (float)mh->dataset*100/net_usage,
             (unsigned long)total_system_mem,
             total_system_hmem,
             memory_lua,
@@ -2862,7 +2875,8 @@ sds genRedisInfoString(char *section) {
             zmalloc_get_fragmentation_ratio(server.resident_set_size),
             ZMALLOC_LIB,
             lazyfreeGetPendingObjectsCount()
-            );
+        );
+        freeMemoryOverheadData(mh);
     }
 
     /* Persistence */