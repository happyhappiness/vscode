     }
 
     /* Memory */
     if (allsections || defsections || !strcasecmp(section,"memory")) {
         char hmem[64];
         char peak_hmem[64];
+        size_t zmalloc_used = zmalloc_used_memory();
 
-        bytesToHuman(hmem,zmalloc_used_memory());
+        /* Peak memory is updated from time to time by serverCron() so it
+         * may happen that the instantaneous value is slightly bigger than
+         * the peak value. This may confuse users, so we update the peak
+         * if found smaller than the current memory usage. */
+        if (zmalloc_used > server.stat_peak_memory)
+            server.stat_peak_memory = zmalloc_used;
+
+        bytesToHuman(hmem,zmalloc_used);
         bytesToHuman(peak_hmem,server.stat_peak_memory);
         if (sections++) info = sdscat(info,"\r\n");
         info = sdscatprintf(info,
             "# Memory\r\n"
             "used_memory:%zu\r\n"
             "used_memory_human:%s\r\n"
             "used_memory_rss:%zu\r\n"
             "used_memory_peak:%zu\r\n"
             "used_memory_peak_human:%s\r\n"
             "used_memory_lua:%lld\r\n"
             "mem_fragmentation_ratio:%.2f\r\n"
             "mem_allocator:%s\r\n",
-            zmalloc_used_memory(),
+            zmalloc_used,
             hmem,
             zmalloc_get_rss(),
             server.stat_peak_memory,
             peak_hmem,
             ((long long)lua_gc(server.lua,LUA_GCCOUNT,0))*1024LL,
             zmalloc_get_fragmentation_ratio(),
