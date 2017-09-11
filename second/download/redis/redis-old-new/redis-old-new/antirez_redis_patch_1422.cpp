@@ -851,12 +851,17 @@ void createSharedObjects(void) {
     shared.unsubscribebulk = createStringObject("$11\r\nunsubscribe\r\n",18);
     shared.psubscribebulk = createStringObject("$10\r\npsubscribe\r\n",17);
     shared.punsubscribebulk = createStringObject("$12\r\npunsubscribe\r\n",19);
-    shared.mbulk3 = createStringObject("*3\r\n",4);
-    shared.mbulk4 = createStringObject("*4\r\n",4);
+    shared.del = createStringObject("DEL",3);
     for (j = 0; j < REDIS_SHARED_INTEGERS; j++) {
         shared.integers[j] = createObject(REDIS_STRING,(void*)(long)j);
         shared.integers[j]->encoding = REDIS_ENCODING_INT;
     }
+    for (j = 0; j < REDIS_SHARED_BULKHDR_LEN; j++) {
+        shared.mbulkhdr[j] = createObject(REDIS_STRING,
+            sdscatprintf(sdsempty(),"*%d\r\n",j));
+        shared.bulkhdr[j] = createObject(REDIS_STRING,
+            sdscatprintf(sdsempty(),"$%d\r\n",j));
+    }
 }
 
 void initServerConfig() {
@@ -1270,12 +1275,13 @@ int processCommand(redisClient *c) {
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
@@ -1778,23 +1784,57 @@ void monitorCommand(redisClient *c) {
 /* ============================ Maxmemory directive  ======================== */
 
 /* This function gets called when 'maxmemory' is set on the config file to limit
- * the max memory used by the server, and we are out of memory.
- * This function will try to, in order:
+ * the max memory used by the server, before processing a command.
+ *
+ * The goal of the function is to free enough memory to keep Redis under the
+ * configured memory limit.
  *
- * - Free objects from the free list
- * - Try to remove keys with an EXPIRE set
+ * The function starts calculating how many bytes should be freed to keep
+ * Redis under the limit, and enters a loop selecting the best keys to
+ * evict accordingly to the configured policy.
  *
- * It is not possible to free enough memory to reach used-memory < maxmemory
- * the server will start refusing commands that will enlarge even more the
- * memory usage.
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
+    /* Remove the size of slaves output buffers and AOF buffer from the
+     * count of used memory. */
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
+    if (server.aof_state != REDIS_AOF_OFF) {
+        mem_used -= sdslen(server.aof_buf);
+        mem_used -= sdslen(server.aof_rewrite_buf);
+    }
+
+    /* Check if we are over the memory limit. */
+    if (mem_used <= server.maxmemory) return REDIS_OK;
+
+    if (server.maxmemory_policy == REDIS_MAXMEMORY_NO_EVICTION)
+        return REDIS_ERR; /* We need to free memory, but policy forbids. */
 
-    while (server.maxmemory && zmalloc_used_memory() > server.maxmemory) {
-        int j, k, freed = 0;
+    /* Compute how much memory we need to free. */
+    mem_tofree = mem_used - server.maxmemory;
+    mem_freed = 0;
+    while (mem_freed < mem_tofree) {
+        int j, k, keys_freed = 0;
 
         for (j = 0; j < server.dbnum; j++) {
             long bestval = 0; /* just to prevent warning */
@@ -1867,16 +1907,36 @@ void freeMemoryIfNeeded(void) {
 
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
+                if (slaves) flushSlavesOutputBuffers();
             }
         }
-        if (!freed) return; /* nothing to free... */
+        if (!keys_freed) return REDIS_ERR; /* nothing to free... */
     }
+    return REDIS_OK;
 }
 
 /* =================================== Main! ================================ */