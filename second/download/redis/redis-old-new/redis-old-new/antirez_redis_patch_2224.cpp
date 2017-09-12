@@ -395,6 +395,8 @@ struct redisServer {
     list *io_processed; /* List of VM I/O jobs already processed */
     list *io_clients; /* All the clients waiting for SWAP I/O operations */
     pthread_mutex_t io_mutex; /* lock to access io_jobs/io_done/io_thread_job */
+    pthread_mutex_t obj_freelist_mutex; /* safe redis objects creation/free */
+    pthread_mutex_t io_swapfile_mutex; /* So we can lseek + write */
     int io_active_threads; /* Number of running I/O threads */
     int vm_max_threads; /* Max number of I/O threads running at the same time */
     /* Our main thread is blocked on the event loop, locking for sockets ready
@@ -542,7 +544,7 @@ static robj *vmPreviewObject(robj *key);
 static int vmSwapOneObjectBlocking(void);
 static int vmSwapOneObjectThreaded(void);
 static int vmCanSwapOut(void);
-static void freeOneObjectFromFreelist(void);
+static int tryFreeOneObjectFromFreelist(void);
 static void acceptHandler(aeEventLoop *el, int fd, void *privdata, int mask);
 static void vmThreadedIOCompletedJob(aeEventLoop *el, int fd, void *privdata, int mask);
 static void vmCancelThreadedIOJob(robj *o);
@@ -551,6 +553,8 @@ static void unlockThreadedIO(void);
 static int vmSwapObjectThreaded(robj *key, robj *val, redisDb *db);
 static void freeIOJob(iojob *j);
 static void queueIOJob(iojob *j);
+static int vmWriteObjectOnSwap(robj *o, off_t page);
+static robj *vmReadObjectFromSwap(off_t page, int type);
 
 static void authCommand(redisClient *c);
 static void pingCommand(redisClient *c);
@@ -1239,21 +1243,18 @@ static int serverCron(struct aeEventLoop *eventLoop, long long id, void *clientD
         while (server.vm_enabled && zmalloc_used_memory() >
                 server.vm_max_memory)
         {
-            if (listLength(server.objfreelist)) {
-                freeOneObjectFromFreelist();
-            } else {
-                if (vmSwapOneObjectThreaded() == REDIS_ERR) {
-                    if ((loops % 30) == 0 && zmalloc_used_memory() >
-                        (server.vm_max_memory+server.vm_max_memory/10)) {
-                        redisLog(REDIS_WARNING,"WARNING: vm-max-memory limit exceeded by more than 10%% but unable to swap more objects out!");
-                    }
+            if (tryFreeOneObjectFromFreelist() == REDIS_OK) continue;
+            if (vmSwapOneObjectThreaded() == REDIS_ERR) {
+                if ((loops % 30) == 0 && zmalloc_used_memory() >
+                    (server.vm_max_memory+server.vm_max_memory/10)) {
+                    redisLog(REDIS_WARNING,"WARNING: vm-max-memory limit exceeded by more than 10%% but unable to swap more objects out!");
                 }
-                /* Note that we freed just one object, because anyway when
-                 * the I/O thread in charge to swap this object out will
-                 * do its work, the handler of completed jobs will try to swap
-                 * more objects if we are out of memory. */
-                break;
             }
+            /* Note that we freed just one object, because anyway when
+             * the I/O thread in charge to swap this object out will
+             * do its work, the handler of completed jobs will try to swap
+             * more objects if we are out of memory. */
+            break;
         }
     }
 
@@ -2369,12 +2370,15 @@ static void acceptHandler(aeEventLoop *el, int fd, void *privdata, int mask) {
 static robj *createObject(int type, void *ptr) {
     robj *o;
 
+    if (server.vm_enabled) pthread_mutex_lock(&server.obj_freelist_mutex);
     if (listLength(server.objfreelist)) {
         listNode *head = listFirst(server.objfreelist);
         o = listNodeValue(head);
         listDelNode(server.objfreelist,head);
+        if (server.vm_enabled) pthread_mutex_unlock(&server.obj_freelist_mutex);
     } else {
         if (server.vm_enabled) {
+            pthread_mutex_unlock(&server.obj_freelist_mutex);
             o = zmalloc(sizeof(*o));
         } else {
             o = zmalloc(sizeof(*o)-sizeof(struct redisObjectVM));
@@ -2465,9 +2469,11 @@ static void decrRefCount(void *obj) {
         redisAssert(o->type == REDIS_STRING);
         freeStringObject(o);
         vmMarkPagesFree(o->vm.page,o->vm.usedpages);
+        pthread_mutex_lock(&server.obj_freelist_mutex);
         if (listLength(server.objfreelist) > REDIS_OBJFREELIST_MAX ||
             !listAddNodeHead(server.objfreelist,o))
             zfree(o);
+        pthread_mutex_unlock(&server.obj_freelist_mutex);
         server.vm_stats_swapped_objects--;
         return;
     }
@@ -2483,9 +2489,11 @@ static void decrRefCount(void *obj) {
         case REDIS_HASH: freeHashObject(o); break;
         default: redisAssert(0 != 0); break;
         }
+        if (server.vm_enabled) pthread_mutex_lock(&server.obj_freelist_mutex);
         if (listLength(server.objfreelist) > REDIS_OBJFREELIST_MAX ||
             !listAddNodeHead(server.objfreelist,o))
             zfree(o);
+        if (server.vm_enabled) pthread_mutex_unlock(&server.obj_freelist_mutex);
     }
 }
 
@@ -6378,16 +6386,25 @@ static void slaveofCommand(redisClient *c) {
 
 /* ============================ Maxmemory directive  ======================== */
 
-/* Free one object form the pre-allocated objects free list. This is useful
- * under low mem conditions as by default we take 1 million free objects
- * allocated. */
-static void freeOneObjectFromFreelist(void) {
+/* Try to free one object form the pre-allocated objects free list.
+ * This is useful under low mem conditions as by default we take 1 million
+ * free objects allocated. On success REDIS_OK is returned, otherwise
+ * REDIS_ERR. */
+static int tryFreeOneObjectFromFreelist(void) {
     robj *o;
 
-    listNode *head = listFirst(server.objfreelist);
-    o = listNodeValue(head);
-    listDelNode(server.objfreelist,head);
-    zfree(o);
+    if (server.vm_enabled) pthread_mutex_lock(&server.obj_freelist_mutex);
+    if (listLength(server.objfreelist)) {
+        listNode *head = listFirst(server.objfreelist);
+        o = listNodeValue(head);
+        listDelNode(server.objfreelist,head);
+        if (server.vm_enabled) pthread_mutex_unlock(&server.obj_freelist_mutex);
+        zfree(o);
+        return REDIS_OK;
+    } else {
+        if (server.vm_enabled) pthread_mutex_unlock(&server.obj_freelist_mutex);
+        return REDIS_ERR;
+    }
 }
 
 /* This function gets called when 'maxmemory' is set on the config file to limit
@@ -6403,35 +6420,32 @@ static void freeOneObjectFromFreelist(void) {
  */
 static void freeMemoryIfNeeded(void) {
     while (server.maxmemory && zmalloc_used_memory() > server.maxmemory) {
-        if (listLength(server.objfreelist)) {
-            freeOneObjectFromFreelist();
-        } else {
-            int j, k, freed = 0;
-
-            for (j = 0; j < server.dbnum; j++) {
-                int minttl = -1;
-                robj *minkey = NULL;
-                struct dictEntry *de;
-
-                if (dictSize(server.db[j].expires)) {
-                    freed = 1;
-                    /* From a sample of three keys drop the one nearest to
-                     * the natural expire */
-                    for (k = 0; k < 3; k++) {
-                        time_t t;
-
-                        de = dictGetRandomKey(server.db[j].expires);
-                        t = (time_t) dictGetEntryVal(de);
-                        if (minttl == -1 || t < minttl) {
-                            minkey = dictGetEntryKey(de);
-                            minttl = t;
-                        }
+        int j, k, freed = 0;
+
+        if (tryFreeOneObjectFromFreelist() == REDIS_OK) continue;
+        for (j = 0; j < server.dbnum; j++) {
+            int minttl = -1;
+            robj *minkey = NULL;
+            struct dictEntry *de;
+
+            if (dictSize(server.db[j].expires)) {
+                freed = 1;
+                /* From a sample of three keys drop the one nearest to
+                 * the natural expire */
+                for (k = 0; k < 3; k++) {
+                    time_t t;
+
+                    de = dictGetRandomKey(server.db[j].expires);
+                    t = (time_t) dictGetEntryVal(de);
+                    if (minttl == -1 || t < minttl) {
+                        minkey = dictGetEntryKey(de);
+                        minttl = t;
                     }
-                    deleteKey(server.db+j,minkey);
                 }
+                deleteKey(server.db+j,minkey);
             }
-            if (!freed) return; /* nothing to free... */
         }
+        if (!freed) return; /* nothing to free... */
     }
 }
 
@@ -6961,6 +6975,8 @@ static void vmInit(void) {
     server.io_processed = listCreate();
     server.io_clients = listCreate();
     pthread_mutex_init(&server.io_mutex,NULL);
+    pthread_mutex_init(&server.obj_freelist_mutex,NULL);
+    pthread_mutex_init(&server.io_swapfile_mutex,NULL);
     server.io_active_threads = 0;
     if (pipe(pipefds) == -1) {
         redisLog(REDIS_WARNING,"Unable to intialized VM: pipe(2): %s. Exiting."
@@ -7090,6 +7106,21 @@ static int vmFindContiguousPages(off_t *first, int n) {
     return REDIS_ERR;
 }
 
+/* Write the specified object at the specified page of the swap file */
+static int vmWriteObjectOnSwap(robj *o, off_t page) {
+    if (server.vm_enabled) pthread_mutex_lock(&server.io_swapfile_mutex);
+    if (fseeko(server.vm_fp,page*server.vm_page_size,SEEK_SET) == -1) {
+        if (server.vm_enabled) pthread_mutex_unlock(&server.io_swapfile_mutex);
+        redisLog(REDIS_WARNING,
+            "Critical VM problem in vmSwapObjectBlocking(): can't seek: %s",
+            strerror(errno));
+        return REDIS_ERR;
+    }
+    rdbSaveObject(server.vm_fp,o);
+    if (server.vm_enabled) pthread_mutex_unlock(&server.io_swapfile_mutex);
+    return REDIS_OK;
+}
+
 /* Swap the 'val' object relative to 'key' into disk. Store all the information
  * needed to later retrieve the object into the key object.
  * If we can't find enough contiguous empty pages to swap the object on disk
@@ -7101,13 +7132,7 @@ static int vmSwapObjectBlocking(robj *key, robj *val) {
     assert(key->storage == REDIS_VM_MEMORY);
     assert(key->refcount == 1);
     if (vmFindContiguousPages(&page,pages) == REDIS_ERR) return REDIS_ERR;
-    if (fseeko(server.vm_fp,page*server.vm_page_size,SEEK_SET) == -1) {
-        redisLog(REDIS_WARNING,
-            "Critical VM problem in vmSwapObjectBlocking(): can't seek: %s",
-            strerror(errno));
-        return REDIS_ERR;
-    }
-    rdbSaveObject(server.vm_fp,val);
+    if (vmWriteObjectOnSwap(val,page) == REDIS_ERR) return REDIS_ERR;
     key->vm.page = page;
     key->vm.usedpages = pages;
     key->storage = REDIS_VM_SWAPPED;
@@ -7123,26 +7148,35 @@ static int vmSwapObjectBlocking(robj *key, robj *val) {
     return REDIS_OK;
 }
 
-/* Load the value object relative to the 'key' object from swap to memory.
- * The newly allocated object is returned.
- *
- * If preview is true the unserialized object is returned to the caller but
- * no changes are made to the key object, nor the pages are marked as freed */
-static robj *vmGenericLoadObject(robj *key, int preview) {
-    robj *val;
+static robj *vmReadObjectFromSwap(off_t page, int type) {
+    robj *o;
 
-    redisAssert(key->storage == REDIS_VM_SWAPPED);
-    if (fseeko(server.vm_fp,key->vm.page*server.vm_page_size,SEEK_SET) == -1) {
+    if (server.vm_enabled) pthread_mutex_lock(&server.io_swapfile_mutex);
+    if (fseeko(server.vm_fp,page*server.vm_page_size,SEEK_SET) == -1) {
         redisLog(REDIS_WARNING,
             "Unrecoverable VM problem in vmLoadObject(): can't seek: %s",
             strerror(errno));
         exit(1);
     }
-    val = rdbLoadObject(key->vtype,server.vm_fp);
-    if (val == NULL) {
+    o = rdbLoadObject(type,server.vm_fp);
+    if (o == NULL) {
         redisLog(REDIS_WARNING, "Unrecoverable VM problem in vmLoadObject(): can't load object from swap file: %s", strerror(errno));
         exit(1);
     }
+    if (server.vm_enabled) pthread_mutex_unlock(&server.io_swapfile_mutex);
+    return o;
+}
+
+/* Load the value object relative to the 'key' object from swap to memory.
+ * The newly allocated object is returned.
+ *
+ * If preview is true the unserialized object is returned to the caller but
+ * no changes are made to the key object, nor the pages are marked as freed */
+static robj *vmGenericLoadObject(robj *key, int preview) {
+    robj *val;
+
+    redisAssert(key->storage == REDIS_VM_SWAPPED);
+    val = vmReadObjectFromSwap(key->vm.page,key->vtype);
     if (!preview) {
         key->storage = REDIS_VM_MEMORY;
         key->vm.atime = server.unixtime;
@@ -7444,6 +7478,7 @@ static void vmThreadedIOCompletedJob(aeEventLoop *el, int fd, void *privdata,
                 }
             }
         }
+        return; /* XXX REMOVE ME */
     }
     if (retval < 0 && errno != EAGAIN) {
         redisLog(REDIS_WARNING,
@@ -7543,6 +7578,8 @@ static void *IOThreadEntryPoint(void *arg) {
             j->pages = rdbSavedObjectPages(j->val,fp);
             fclose(fp);
         } else if (j->type == REDIS_IOJOB_DO_SWAP) {
+            if (vmWriteObjectOnSwap(j->val,j->page) == REDIS_ERR)
+                j->canceled = 1;
         }
 
         /* Done: insert the job into the processed queue */