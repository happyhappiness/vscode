@@ -381,6 +381,11 @@ struct redisServer {
     off_t vm_near_pages; /* Number of pages allocated sequentially */
     unsigned char *vm_bitmap; /* Bitmap of free/used pages */
     time_t unixtime;    /* Unix time sampled every second. */
+    /* Virtual memory stats */
+    unsigned long long vm_stats_used_pages;
+    unsigned long long vm_stats_swapped_objects;
+    unsigned long long vm_stats_swapouts;
+    unsigned long long vm_stats_swapins;
 };
 
 typedef void redisCommandProc(redisClient *c);
@@ -2382,6 +2387,7 @@ static void decrRefCount(void *obj) {
         if (listLength(server.objfreelist) > REDIS_OBJFREELIST_MAX ||
             !listAddNodeHead(server.objfreelist,o))
             zfree(o);
+        server.vm_stats_swapped_objects--;
         return;
     }
     /* REDIS_VM_MEMORY */
@@ -5417,6 +5423,7 @@ static sds genRedisInfoString(void) {
         "bgrewriteaof_in_progress:%d\r\n"
         "total_connections_received:%lld\r\n"
         "total_commands_processed:%lld\r\n"
+        "vm_enabled:%d\r\n"
         "role:%s\r\n"
         ,REDIS_VERSION,
         (sizeof(long) == 8) ? "64" : "32",
@@ -5433,6 +5440,7 @@ static sds genRedisInfoString(void) {
         server.bgrewritechildpid != -1,
         server.stat_numconnections,
         server.stat_numcommands,
+        server.vm_enabled != 0,
         server.masterhost == NULL ? "master" : "slave"
     );
     if (server.masterhost) {
@@ -5448,6 +5456,24 @@ static sds genRedisInfoString(void) {
             server.master ? ((int)(time(NULL)-server.master->lastinteraction)) : -1
         );
     }
+    if (server.vm_enabled) {
+        info = sdscatprintf(info,
+            "vm_conf_max_memory:%llu\r\n"
+            "vm_conf_page_size:%llu\r\n"
+            "vm_conf_pages:%llu\r\n"
+            "vm_stats_used_pages:%llu\r\n"
+            "vm_stats_swapped_objects:%llu\r\n"
+            "vm_stats_swappin_count:%llu\r\n"
+            "vm_stats_swappout_count:%llu\r\n"
+            ,(unsigned long long) server.vm_max_memory,
+            (unsigned long long) server.vm_page_size,
+            (unsigned long long) server.vm_pages,
+            (unsigned long long) server.vm_stats_used_pages,
+            (unsigned long long) server.vm_stats_swapped_objects,
+            (unsigned long long) server.vm_stats_swapins,
+            (unsigned long long) server.vm_stats_swapouts
+        );
+    }
     for (j = 0; j < server.dbnum; j++) {
         long long keys, vkeys;
 
@@ -6734,6 +6760,10 @@ static void vmInit(void) {
     server.vm_fd = fileno(server.vm_fp);
     server.vm_next_page = 0;
     server.vm_near_pages = 0;
+    server.vm_stats_used_pages = 0;
+    server.vm_stats_swapped_objects = 0;
+    server.vm_stats_swapouts = 0;
+    server.vm_stats_swapins = 0;
     totsize = server.vm_pages*server.vm_page_size;
     redisLog(REDIS_NOTICE,"Allocating %lld bytes of swap file",totsize);
     if (ftruncate(server.vm_fd,totsize) == -1) {
@@ -6767,6 +6797,7 @@ static void vmMarkPagesUsed(off_t page, off_t count) {
 
     for (j = 0; j < count; j++)
         vmMarkPageUsed(page+j);
+    server.vm_stats_used_pages += count;
 }
 
 /* Mark the page as free */
@@ -6782,6 +6813,7 @@ static void vmMarkPagesFree(off_t page, off_t count) {
 
     for (j = 0; j < count; j++)
         vmMarkPageFree(page+j);
+    server.vm_stats_used_pages -= count;
 }
 
 /* Test if the page is free */
@@ -6891,6 +6923,8 @@ static int vmSwapObject(robj *key, robj *val) {
     redisLog(REDIS_DEBUG,"VM: object %s swapped out at %lld (%lld pages)",
         (unsigned char*) key->ptr,
         (unsigned long long) page, (unsigned long long) pages);
+    server.vm_stats_swapped_objects++;
+    server.vm_stats_swapouts++;
     return REDIS_OK;
 }
 
@@ -6920,7 +6954,9 @@ static robj *vmGenericLoadObject(robj *key, int preview) {
         vmMarkPagesFree(key->vm.page,key->vm.usedpages);
         redisLog(REDIS_DEBUG, "VM: object %s loaded from disk",
             (unsigned char*) key->ptr);
+        server.vm_stats_swapped_objects--;
     }
+    server.vm_stats_swapins++;
     return val;
 }
 