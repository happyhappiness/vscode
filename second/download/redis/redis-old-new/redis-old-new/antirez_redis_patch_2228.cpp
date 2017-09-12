@@ -536,7 +536,8 @@ static void vmInit(void);
 static void vmMarkPagesFree(off_t page, off_t count);
 static robj *vmLoadObject(robj *key);
 static robj *vmPreviewObject(robj *key);
-static int vmSwapOneObject(void);
+static int vmSwapOneObjectBlocking(void);
+static int vmSwapOneObjectThreaded(void);
 static int vmCanSwapOut(void);
 static void freeOneObjectFromFreelist(void);
 static void acceptHandler(aeEventLoop *el, int fd, void *privdata, int mask);
@@ -1232,11 +1233,17 @@ static int serverCron(struct aeEventLoop *eventLoop, long long id, void *clientD
         {
             if (listLength(server.objfreelist)) {
                 freeOneObjectFromFreelist();
-            } else if (vmSwapOneObject() == REDIS_ERR) {
-                if ((loops % 30) == 0 && zmalloc_used_memory() >
-                    (server.vm_max_memory+server.vm_max_memory/10)) {
-                    redisLog(REDIS_WARNING,"WARNING: vm-max-memory limit exceeded by more than 10%% but unable to swap more objects out!");
+            } else {
+                if (vmSwapOneObjectThreaded() == REDIS_ERR) {
+                    if ((loops % 30) == 0 && zmalloc_used_memory() >
+                        (server.vm_max_memory+server.vm_max_memory/10)) {
+                        redisLog(REDIS_WARNING,"WARNING: vm-max-memory limit exceeded by more than 10%% but unable to swap more objects out!");
+                    }
                 }
+                /* Note that we freed just one object, because anyway when
+                 * the I/O thread in charge to swap this object out will
+                 * do its work, the handler of completed jobs will try to swap
+                 * more objects if we are out of memory. */
                 break;
             }
         }
@@ -1635,6 +1642,7 @@ static void freeClient(redisClient *c) {
     aeDeleteFileEvent(server.el,c->fd,AE_READABLE);
     aeDeleteFileEvent(server.el,c->fd,AE_WRITABLE);
     listRelease(c->reply);
+    listRelease(c->io_keys);
     freeClientArgv(c);
     close(c->fd);
     /* Remove from the list of clients */
@@ -3329,7 +3337,7 @@ static int rdbLoad(char *filename) {
         loadedkeys++;
         if (server.vm_enabled && (loadedkeys % 5000) == 0) {
             while (zmalloc_used_memory() > server.vm_max_memory) {
-                if (vmSwapOneObject() == REDIS_ERR) break;
+                if (vmSwapOneObjectBlocking() == REDIS_ERR) break;
             }
         }
     }
@@ -6605,7 +6613,7 @@ int loadAppendOnlyFile(char *filename) {
         loadedkeys++;
         if (server.vm_enabled && (loadedkeys % 5000) == 0) {
             while (zmalloc_used_memory() > server.vm_max_memory) {
-                if (vmSwapOneObject() == REDIS_ERR) break;
+                if (vmSwapOneObjectBlocking() == REDIS_ERR) break;
             }
         }
     }
@@ -7071,7 +7079,7 @@ static int vmFindContiguousPages(off_t *first, int n) {
  * needed to later retrieve the object into the key object.
  * If we can't find enough contiguous empty pages to swap the object on disk
  * REDIS_ERR is returned. */
-static int vmSwapObject(robj *key, robj *val) {
+static int vmSwapObjectBlocking(robj *key, robj *val) {
     off_t pages = rdbSavedObjectPages(val);
     off_t page;
 
@@ -7080,7 +7088,7 @@ static int vmSwapObject(robj *key, robj *val) {
     if (vmFindContiguousPages(&page,pages) == REDIS_ERR) return REDIS_ERR;
     if (fseeko(server.vm_fp,page*server.vm_page_size,SEEK_SET) == -1) {
         redisLog(REDIS_WARNING,
-            "Critical VM problem in vmSwapObject(): can't seek: %s",
+            "Critical VM problem in vmSwapObjectBlocking(): can't seek: %s",
             strerror(errno));
         return REDIS_ERR;
     }
@@ -7100,6 +7108,13 @@ static int vmSwapObject(robj *key, robj *val) {
     return REDIS_OK;
 }
 
+static int vmSwapObjectThreaded(robj *key, robj *val) {
+
+    key = key;
+    val = val;
+    return REDIS_OK;
+}
+
 /* Load the value object relative to the 'key' object from swap to memory.
  * The newly allocated object is returned.
  *
@@ -7221,8 +7236,11 @@ static double computeObjectSwappability(robj *o) {
 
 /* Try to swap an object that's a good candidate for swapping.
  * Returns REDIS_OK if the object was swapped, REDIS_ERR if it's not possible
- * to swap any object at all. */
-static int vmSwapOneObject(void) {
+ * to swap any object at all.
+ *
+ * If 'usethreaded' is true, Redis will try to swap the object in background
+ * using I/O threads. */
+static int vmSwapOneObject(int usethreads) {
     int j, i;
     struct dictEntry *best = NULL;
     double best_swappability = 0;
@@ -7269,14 +7287,27 @@ static int vmSwapOneObject(void) {
         key = dictGetEntryKey(best) = newkey;
     }
     /* Swap it */
-    if (vmSwapObject(key,val) == REDIS_OK) {
-        dictGetEntryVal(best) = NULL;
+    if (usethreads) {
+        vmSwapObjectThreaded(key,val);
         return REDIS_OK;
     } else {
-        return REDIS_ERR;
+        if (vmSwapObjectBlocking(key,val) == REDIS_OK) {
+            dictGetEntryVal(best) = NULL;
+            return REDIS_OK;
+        } else {
+            return REDIS_ERR;
+        }
     }
 }
 
+static int vmSwapOneObjectBlocking() {
+    return vmSwapOneObject(0);
+}
+
+static int vmSwapOneObjectThreaded() {
+    return vmSwapOneObject(1);
+}
+
 /* Return true if it's safe to swap out objects in a given moment.
  * Basically we don't want to swap objects out while there is a BGSAVE
  * or a BGAEOREWRITE running in backgroud. */
@@ -7358,6 +7389,7 @@ static void vmCancelThreadedIOJob(robj *o) {
                     if (job->type == REDIS_IOJOB_SWAP)
                         decrRefCount(job->val);
                     listDelNode(lists[i],ln);
+                    zfree(job);
                     break;
                 case 1: /* io_processing */
                 case 2: /* io_processed */
@@ -7448,7 +7480,7 @@ static void debugCommand(redisClient *c) {
         /* Swap it */
         if (key->storage != REDIS_VM_MEMORY) {
             addReplySds(c,sdsnew("-ERR This key is not in memory\r\n"));
-        } else if (vmSwapObject(key,val) == REDIS_OK) {
+        } else if (vmSwapObjectBlocking(key,val) == REDIS_OK) {
             dictGetEntryVal(de) = NULL;
             addReply(c,shared.ok);
         } else {