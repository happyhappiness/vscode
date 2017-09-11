@@ -2828,10 +2828,6 @@ sds genRedisInfoString(char *section) {
         bytesToHuman(used_memory_rss_hmem,server.resident_set_size);
         bytesToHuman(maxmemory_hmem,server.maxmemory);
 
-        size_t net_usage = 1;
-        if (zmalloc_used > mh->startup_allocated)
-            net_usage = zmalloc_used - mh->startup_allocated;
-
         if (sections++) info = sdscat(info,"\r\n");
         info = sdscatprintf(info,
             "# Memory\r\n"
@@ -2864,7 +2860,7 @@ sds genRedisInfoString(char *section) {
             mh->overhead_total,
             mh->startup_allocated,
             mh->dataset,
-            (float)mh->dataset*100/net_usage,
+            mh->dataset_perc,
             (unsigned long)total_system_mem,
             total_system_hmem,
             memory_lua,