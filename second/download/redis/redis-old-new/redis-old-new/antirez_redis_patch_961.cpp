@@ -2407,8 +2407,13 @@ sds genRedisInfoString(char *section) {
     if (allsections || defsections || !strcasecmp(section,"memory")) {
         char hmem[64];
         char peak_hmem[64];
+        size_t zmalloc_used = zmalloc_used_memory();
 
-        bytesToHuman(hmem,zmalloc_used_memory());
+        if (zmalloc_used > server.stat_peak_memory) {
+            server.stat_peak_memory = zmalloc_used;
+        }
+
+        bytesToHuman(hmem,zmalloc_used);
         bytesToHuman(peak_hmem,server.stat_peak_memory);
         if (sections++) info = sdscat(info,"\r\n");
         info = sdscatprintf(info,
@@ -2421,7 +2426,7 @@ sds genRedisInfoString(char *section) {
             "used_memory_lua:%lld\r\n"
             "mem_fragmentation_ratio:%.2f\r\n"
             "mem_allocator:%s\r\n",
-            zmalloc_used_memory(),
+            zmalloc_used,
             hmem,
             zmalloc_get_rss(),
             server.stat_peak_memory,