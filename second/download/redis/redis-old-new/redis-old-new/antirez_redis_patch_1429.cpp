@@ -1801,10 +1801,18 @@ void monitorCommand(redisClient *c) {
 int freeMemoryIfNeeded(void) {
     size_t mem_used, mem_tofree, mem_freed;
     int slaves = listLength(server.slaves);
+    static time_t xt;
+    int debug = 0;
+
+    if (xt != time(NULL)) {
+        debug = 1;
+        xt = time(NULL);
+    }
 
     /* Remove the size of slaves output buffers and AOF buffer from the
      * count of used memory. */
     mem_used = zmalloc_used_memory();
+    if (debug) printf("used_full: %zu\n", mem_used);
     if (slaves) {
         listIter li;
         listNode *ln;
@@ -1819,6 +1827,7 @@ int freeMemoryIfNeeded(void) {
                 mem_used -= obuf_bytes;
         }
     }
+    if (debug) printf("used_nosl: %zu\n", mem_used);
     if (server.aof_state != REDIS_AOF_OFF) {
         mem_used -= sdslen(server.aof_buf);
         mem_used -= sdslen(server.aof_rewrite_buf);
@@ -1833,6 +1842,7 @@ int freeMemoryIfNeeded(void) {
     /* Compute how much memory we need to free. */
     mem_tofree = mem_used - server.maxmemory;
     mem_freed = 0;
+    if (debug) printf("tofree: %zu\n", mem_tofree);
     while (mem_freed < mem_tofree) {
         int j, k, keys_freed = 0;
 
@@ -1934,8 +1944,12 @@ int freeMemoryIfNeeded(void) {
                 if (slaves) flushSlavesOutputBuffers();
             }
         }
-        if (!keys_freed) return REDIS_ERR; /* nothing to free... */
+        if (!keys_freed) {
+            if (debug) printf("-freed: %zu\n\n", mem_freed);
+            return REDIS_ERR; /* nothing to free... */
+        }
     }
+    if (debug) printf("+freed: %zu\n\n", mem_freed);
     return REDIS_OK;
 }
 