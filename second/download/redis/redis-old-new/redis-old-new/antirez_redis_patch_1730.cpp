@@ -1300,6 +1300,19 @@ sds genRedisInfoString(void) {
             eta
         );
     }
+
+    info = sdscat(info,"allocation_stats:");
+    for (j = 0; j <= ZMALLOC_MAX_ALLOC_STAT; j++) {
+        size_t count = zmalloc_allocations_for_size(j);
+        if (count) {
+            if (info[sdslen(info)-1] != ':') info = sdscatlen(info,",",1);
+            info = sdscatprintf(info,"%s%d=%zu",
+                (j == ZMALLOC_MAX_ALLOC_STAT) ? ">=" : "",
+                j,count);
+        }
+    }
+    info = sdscat(info,"\r\n");
+
     for (j = 0; j < server.dbnum; j++) {
         long long keys, vkeys;
 