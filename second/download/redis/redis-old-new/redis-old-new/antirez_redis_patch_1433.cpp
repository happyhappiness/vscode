@@ -1275,12 +1275,13 @@ int processCommand(redisClient *c) {
      * First we try to free some memory if possible (if there are volatile
      * keys in the dataset). If there are not the only thing we can do
      * is returning an error. */
-    if (server.maxmemory) freeMemoryIfNeeded();
-    if (server.maxmemory && (c->cmd->flags & REDIS_CMD_DENYOOM) &&
-        zmalloc_used_memory() > server.maxmemory)
-    {
-        addReplyError(c,"command not allowed when used memory > 'maxmemory'");
-        return REDIS_OK;
+    if (server.maxmemory) {
+        int retval = freeMemoryIfNeeded();
+        if ((c->cmd->flags & REDIS_CMD_DENYOOM) && retval == REDIS_ERR) {
+            addReplyError(c,
+                "command not allowed when used memory > 'maxmemory'");
+            return REDIS_OK;
+        }
     }
 
     /* Only allow SUBSCRIBE and UNSUBSCRIBE in the context of Pub/Sub */
@@ -1783,23 +1784,54 @@ void monitorCommand(redisClient *c) {
 /* ============================ Maxmemory directive  ======================== */
 
 /* This function gets called when 'maxmemory' is set on the config file to limit
- * the max memory used by the server, and we are out of memory.
- * This function will try to, in order:
+ * the max memory used by the server, before processing a command.
  *
- * - Free objects from the free list
- * - Try to remove keys with an EXPIRE set
+ * The goal of the function is to free enough memory to keep Redis under the
+ * configured memory limit.
  *
- * It is not possible to free enough memory to reach used-memory < maxmemory
- * the server will start refusing commands that will enlarge even more the
- * memory usage.
+ * The function starts calculating how many bytes should be freed to keep
+ * Redis under the limit, and enters a loop selecting the best keys to
+ * evict accordingly to the configured policy.
+ *
+ * If all the bytes needed to return back under the limit were freed the
+ * function returns REDIS_OK, otherwise REDIS_ERR is returned, and the caller
+ * should block the execution of commands that will result in more memory
+ * used by the server.
  */
-void freeMemoryIfNeeded(void) {
-    /* Remove keys accordingly to the active policy as long as we are
-     * over the memory limit. */
-    if (server.maxmemory_policy == REDIS_MAXMEMORY_NO_EVICTION) return;
+int freeMemoryIfNeeded(void) {
+    size_t mem_used, mem_tofree, mem_freed;
+    int slaves = listLength(server.slaves);
+
+    /* Remove the size of slaves output buffers from the count of used
+     * memory. */
+    mem_used = zmalloc_used_memory();
+    if (slaves) {
+        listIter li;
+        listNode *ln;
+
+        listRewind(server.slaves,&li);
+        while((ln = listNext(&li))) {
+            redisClient *slave = listNodeValue(ln);
+            unsigned long obuf_bytes = getClientOutputBufferMemoryUsage(slave);
+            if (obuf_bytes > mem_used)
+                mem_used = 0;
+            else
+                mem_used -= obuf_bytes;
+        }
+    }
 
-    while (server.maxmemory && zmalloc_used_memory() > server.maxmemory) {
-        int j, k, freed = 0;
+    /* Check if we are over the memory limit. */
+    if (mem_used <= server.maxmemory) return REDIS_OK;
+
+    if (server.maxmemory_policy == REDIS_MAXMEMORY_NO_EVICTION)
+        return REDIS_ERR; /* We need to free memory, but policy forbids. */
+
+    /* Compute how much memory we need to free. */
+    mem_tofree = mem_used - server.maxmemory;
+    printf("USED: %zu, TOFREE: %zu\n", mem_used, mem_tofree);
+    mem_freed = 0;
+    while (mem_freed < mem_tofree) {
+        int j, k, keys_freed = 0;
 
         for (j = 0; j < server.dbnum; j++) {
             long bestval = 0; /* just to prevent warning */
@@ -1872,16 +1904,57 @@ void freeMemoryIfNeeded(void) {
 
             /* Finally remove the selected key. */
             if (bestkey) {
+                long long delta;
+
                 robj *keyobj = createStringObject(bestkey,sdslen(bestkey));
                 propagateExpire(db,keyobj);
+                /* We compute the amount of memory freed by dbDelete() alone.
+                 * It is possible that actually the memory needed to propagate
+                 * the DEL in AOF and replication link is greater than the one
+                 * we are freeing removing the key, but we can't account for
+                 * that otherwise we would never exit the loop.
+                 *
+                 * AOF and Output buffer memory will be freed eventually so
+                 * we only care about memory used by the key space. */
+                delta = (long long) zmalloc_used_memory();
                 dbDelete(db,keyobj);
+                delta -= (long long) zmalloc_used_memory();
+                // printf("%lld\n",delta);
+                mem_freed += delta;
                 server.stat_evictedkeys++;
                 decrRefCount(keyobj);
-                freed++;
+                keys_freed++;
+
+                /* When the memory to free starts to be big enough, we may
+                 * start spending so much time here that is impossible to
+                 * deliver data to the slaves fast enough, so we force the
+                 * transmission here inside the loop. */
+                if (slaves) {
+                    listIter li;
+                    listNode *ln;
+
+                    listRewind(server.slaves,&li);
+                    while((ln = listNext(&li))) {
+                        redisClient *slave = listNodeValue(ln);
+                        int events;
+
+                        events = aeGetFileEvents(server.el,slave->fd);
+                        printf("EVENTS: %d\n", events);
+                        if (events & AE_WRITABLE &&
+                            slave->replstate == REDIS_REPL_ONLINE &&
+                            listLength(slave->reply))
+                        {
+                            printf("SLAVE %d -> %d\n",
+                                slave->fd, (int) listLength(slave->reply));
+                            sendReplyToClient(server.el,slave->fd,slave,0);
+                        }
+                    }
+                }
             }
         }
-        if (!freed) return; /* nothing to free... */
+        if (!keys_freed) return REDIS_ERR; /* nothing to free... */
     }
+    return REDIS_OK;
 }
 
 /* =================================== Main! ================================ */