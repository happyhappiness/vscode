@@ -120,6 +120,7 @@
 #define REDIS_SET 2
 #define REDIS_ZSET 3
 #define REDIS_HASH 4
+#define REDIS_VMPOINTER 8
 
 /* Objects encoding. Some kind of objects like Strings and Hashes can be
  * internally represented in multiple ways. The 'encoding' field of the object
@@ -247,30 +248,41 @@ static void _redisPanic(char *msg, char *file, int line);
 
 /* A redis object, that is a type able to hold a string / list / set */
 
-/* The VM object structure */
-struct redisObjectVM {
-    off_t page;         /* the page at witch the object is stored on disk */
-    off_t usedpages;    /* number of pages used on disk */
-    time_t atime;       /* Last access time */
-} vm;
-
 /* The actual Redis Object */
 typedef struct redisObject {
-    void *ptr;
-    unsigned char type;
-    unsigned char encoding;
-    unsigned char storage;  /* If this object is a key, where is the value?
-                             * REDIS_VM_MEMORY, REDIS_VM_SWAPPED, ... */
-    unsigned char vtype; /* If this object is a key, and value is swapped out,
-                          * this is the type of the swapped out object. */
+    unsigned type:4;
+    unsigned storage:2;     /* REDIS_VM_MEMORY or REDIS_VM_SWAPPING */
+    unsigned encoding:4;
+    unsigned lru:22;        /* lru time (relative to server.lruclock) */
     int refcount;
+    void *ptr;
     /* VM fields, this are only allocated if VM is active, otherwise the
      * object allocation function will just allocate
      * sizeof(redisObjct) minus sizeof(redisObjectVM), so using
      * Redis without VM active will not have any overhead. */
-    struct redisObjectVM vm;
 } robj;
 
+/* The VM pointer structure - identifies an object in the swap file.
+ *
+ * This object is stored in place of the value
+ * object in the main key->value hash table representing a database.
+ * Note that the first fields (type, storage) are the same as the redisObject
+ * structure so that vmPointer strucuters can be accessed even when casted
+ * as redisObject structures.
+ *
+ * This is useful as we don't know if a value object is or not on disk, but we
+ * are always free of accessing obj->storage to check this. For vmPointer
+ * structures "type" is set to REDIS_VMPOINTER (even if without this field
+ * is still possible to check the kind of object from the value of 'storage').*/
+typedef struct vmPointer {
+    unsigned type:4;
+    unsigned storage:2; /* REDIS_VM_SWAPPED or REDIS_VM_LOADING */
+    unsigned notused:26;
+    unsigned int vtype; /* type of the object stored in the swap file */
+    off_t page;         /* the page at witch the object is stored on disk */
+    off_t usedpages;    /* number of pages used on disk */
+} vmpointer;
+
 /* Macro used to initalize a Redis object allocated on the stack.
  * Note that this macro is taken near the structure definition to make sure
  * we'll update it when the structure is changed, to avoid bugs like
@@ -280,7 +292,7 @@ typedef struct redisObject {
     _var.type = REDIS_STRING; \
     _var.encoding = REDIS_ENCODING_RAW; \
     _var.ptr = _ptr; \
-    if (server.vm_enabled) _var.storage = REDIS_VM_MEMORY; \
+    _var.storage = REDIS_VM_MEMORY; \
 } while(0);
 
 typedef struct redisDb {
@@ -450,6 +462,8 @@ struct redisServer {
     list *pubsub_patterns; /* A list of pubsub_patterns */
     /* Misc */
     FILE *devnull;
+    unsigned lruclock:22;        /* clock incrementing every minute, for LRU */
+    unsigned lruclock_padding:10;
 };
 
 typedef struct pubsubPattern {
@@ -542,6 +556,9 @@ typedef struct iojob {
     int type;   /* Request type, REDIS_IOJOB_* */
     redisDb *db;/* Redis database */
     robj *key;  /* This I/O request is about swapping this key */
+    robj *id;   /* Unique identifier of this job:
+                   this is the object to swap for REDIS_IOREQ_*_SWAP, or the
+                   vmpointer objct for REDIS_IOREQ_LOAD. */
     robj *val;  /* the value to swap for REDIS_IOREQ_*_SWAP, otherwise this
                  * field is populated by the I/O thread for REDIS_IOREQ_LOAD. */
     off_t page; /* Swap page where to read/write the object */
@@ -598,8 +615,8 @@ static void unblockClientWaitingData(redisClient *c);
 static int handleClientsWaitingListPush(redisClient *c, robj *key, robj *ele);
 static void vmInit(void);
 static void vmMarkPagesFree(off_t page, off_t count);
-static robj *vmLoadObject(robj *key);
-static robj *vmPreviewObject(robj *key);
+static robj *vmLoadObject(robj *o);
+static robj *vmPreviewObject(robj *o);
 static int vmSwapOneObjectBlocking(void);
 static int vmSwapOneObjectThreaded(void);
 static int vmCanSwapOut(void);
@@ -635,7 +652,7 @@ static int compareStringObjects(robj *a, robj *b);
 static int equalStringObjects(robj *a, robj *b);
 static void usage();
 static int rewriteAppendOnlyFileBackground(void);
-static int vmSwapObjectBlocking(robj *key, robj *val);
+static vmpointer *vmSwapObjectBlocking(robj *val);
 static int prepareForShutdown();
 static void touchWatchedKey(redisDb *db, robj *key);
 static void touchWatchedKeysOnFlush(int dbid);
@@ -1432,6 +1449,19 @@ static int serverCron(struct aeEventLoop *eventLoop, long long id, void *clientD
      * in objects at every object access, and accuracy is not needed.
      * To access a global var is faster than calling time(NULL) */
     server.unixtime = time(NULL);
+    /* We have just 21 bits per object for LRU information.
+     * So we use an (eventually wrapping) LRU clock with minutes resolution.
+     *
+     * When we need to select what object to swap, we compute the minimum
+     * time distance between the current lruclock and the object last access
+     * lruclock info. Even if clocks will wrap on overflow, there is
+     * the interesting property that we are sure that at least
+     * ABS(A-B) minutes passed between current time and timestamp B.
+     *
+     * This is not precise but we don't need at all precision, but just
+     * something statistically reasonable.
+     */
+    server.lruclock = (time(NULL)/60)&((1<<21)-1);
 
     /* We received a SIGTERM, shutting down here in a safe way, as it is
      * not ok doing so inside the signal handler. */
@@ -2938,23 +2968,20 @@ static robj *createObject(int type, void *ptr) {
         listDelNode(server.objfreelist,head);
         if (server.vm_enabled) pthread_mutex_unlock(&server.obj_freelist_mutex);
     } else {
-        if (server.vm_enabled) {
+        if (server.vm_enabled)
             pthread_mutex_unlock(&server.obj_freelist_mutex);
-            o = zmalloc(sizeof(*o));
-        } else {
-            o = zmalloc(sizeof(*o)-sizeof(struct redisObjectVM));
-        }
+        o = zmalloc(sizeof(*o));
     }
     o->type = type;
     o->encoding = REDIS_ENCODING_RAW;
     o->ptr = ptr;
     o->refcount = 1;
     if (server.vm_enabled) {
         /* Note that this code may run in the context of an I/O thread
-         * and accessing to server.unixtime in theory is an error
+         * and accessing server.lruclock in theory is an error
          * (no locks). But in practice this is safe, and even if we read
-         * garbage Redis will not fail, as it's just a statistical info */
-        o->vm.atime = server.unixtime;
+         * garbage Redis will not fail. */
+        o->lru = server.lruclock;
         o->storage = REDIS_VM_MEMORY;
     }
     return o;
@@ -3059,24 +3086,19 @@ static void incrRefCount(robj *o) {
 static void decrRefCount(void *obj) {
     robj *o = obj;
 
-    if (o->refcount <= 0) redisPanic("decrRefCount against refcount <= 0");
-    /* Object is a key of a swapped out value, or in the process of being
-     * loaded. */
+    /* Object is a swapped out value, or in the process of being loaded. */
     if (server.vm_enabled &&
         (o->storage == REDIS_VM_SWAPPED || o->storage == REDIS_VM_LOADING))
     {
-        if (o->storage == REDIS_VM_LOADING) vmCancelThreadedIOJob(obj);
-        redisAssert(o->type == REDIS_STRING);
-        freeStringObject(o);
-        vmMarkPagesFree(o->vm.page,o->vm.usedpages);
-        pthread_mutex_lock(&server.obj_freelist_mutex);
-        if (listLength(server.objfreelist) > REDIS_OBJFREELIST_MAX ||
-            !listAddNodeHead(server.objfreelist,o))
-            zfree(o);
-        pthread_mutex_unlock(&server.obj_freelist_mutex);
+        vmpointer *vp = obj;
+        if (o->storage == REDIS_VM_LOADING) vmCancelThreadedIOJob(o);
+        vmMarkPagesFree(vp->page,vp->usedpages);
         server.vm_stats_swapped_objects--;
+        zfree(vp);
         return;
     }
+
+    if (o->refcount <= 0) redisPanic("decrRefCount against refcount <= 0");
     /* Object is in memory, or in the process of being swapped out. */
     if (--(o->refcount) == 0) {
         if (server.vm_enabled && o->storage == REDIS_VM_SWAPPING)
@@ -3104,21 +3126,20 @@ static robj *lookupKey(redisDb *db, robj *key) {
         robj *val = dictGetEntryVal(de);
 
         if (server.vm_enabled) {
-            if (key->storage == REDIS_VM_MEMORY ||
-                key->storage == REDIS_VM_SWAPPING)
+            if (val->storage == REDIS_VM_MEMORY ||
+                val->storage == REDIS_VM_SWAPPING)
             {
-                /* If we were swapping the object out, stop it, this key
-                 * was requested. */
-                if (key->storage == REDIS_VM_SWAPPING)
-                    vmCancelThreadedIOJob(key);
+                /* If we were swapping the object out, cancel the operation */
+                if (val->storage == REDIS_VM_SWAPPING)
+                    vmCancelThreadedIOJob(val);
                 /* Update the access time of the key for the aging algorithm. */
-                key->vm.atime = server.unixtime;
+                val->lru = server.lruclock;
             } else {
-                int notify = (key->storage == REDIS_VM_LOADING);
+                int notify = (val->storage == REDIS_VM_LOADING);
 
                 /* Our value was swapped on disk. Bring it at home. */
-                redisAssert(val == NULL);
-                val = vmLoadObject(key);
+                redisAssert(val->type == REDIS_VMPOINTER);
+                val = vmLoadObject(val);
                 dictGetEntryVal(de) = val;
 
                 /* Clients blocked by the VM subsystem may be waiting for
@@ -3764,8 +3785,8 @@ static int rdbSave(char *filename) {
             }
             /* Save the key and associated value. This requires special
              * handling if the value is swapped out. */
-            if (!server.vm_enabled || key->storage == REDIS_VM_MEMORY ||
-                                      key->storage == REDIS_VM_SWAPPING) {
+            if (!server.vm_enabled || o->storage == REDIS_VM_MEMORY ||
+                                      o->storage == REDIS_VM_SWAPPING) {
                 /* Save type, key, value */
                 if (rdbSaveType(fp,o->type) == -1) goto werr;
                 if (rdbSaveStringObject(fp,key) == -1) goto werr;
@@ -3774,9 +3795,9 @@ static int rdbSave(char *filename) {
                 /* REDIS_VM_SWAPPED or REDIS_VM_LOADING */
                 robj *po;
                 /* Get a preview of the object in memory */
-                po = vmPreviewObject(key);
+                po = vmPreviewObject(o);
                 /* Save type, key, value */
-                if (rdbSaveType(fp,key->vtype) == -1) goto werr;
+                if (rdbSaveType(fp,po->type) == -1) goto werr;
                 if (rdbSaveStringObject(fp,key) == -1) goto werr;
                 if (rdbSaveObject(fp,po) == -1) goto werr;
                 /* Remove the loaded object from memory */
@@ -4174,12 +4195,13 @@ static int rdbLoad(char *filename) {
 
             /* de may be NULL since the key already expired */
             if (de) {
+                vmpointer *vp;
                 key = dictGetEntryKey(de);
                 val = dictGetEntryVal(de);
 
-                if (vmSwapObjectBlocking(key,val) == REDIS_OK) {
-                    dictGetEntryVal(de) = NULL;
-                }
+                if (val->refcount == 1 &&
+                    (vp = vmSwapObjectBlocking(val)) != NULL)
+                    dictGetEntryVal(de) = vp;
             }
             continue;
         }
@@ -8240,6 +8262,48 @@ static void freeMemoryIfNeeded(void) {
 
 /* ============================== Append Only file ========================== */
 
+/* Called when the user switches from "appendonly yes" to "appendonly no"
+ * at runtime using the CONFIG command. */
+static void stopAppendOnly(void) {
+    flushAppendOnlyFile();
+    aof_fsync(server.appendfd);
+    close(server.appendfd);
+
+    server.appendfd = -1;
+    server.appendseldb = -1;
+    server.appendonly = 0;
+    /* rewrite operation in progress? kill it, wait child exit */
+    if (server.bgsavechildpid != -1) {
+        int statloc;
+
+        if (kill(server.bgsavechildpid,SIGKILL) != -1)
+            wait3(&statloc,0,NULL);
+        /* reset the buffer accumulating changes while the child saves */
+        sdsfree(server.bgrewritebuf);
+        server.bgrewritebuf = sdsempty();
+        server.bgsavechildpid = -1;
+    }
+}
+
+/* Called when the user switches from "appendonly no" to "appendonly yes"
+ * at runtime using the CONFIG command. */
+static int startAppendOnly(void) {
+    server.appendonly = 1;
+    server.lastfsync = time(NULL);
+    server.appendfd = open(server.appendfilename,O_WRONLY|O_APPEND|O_CREAT,0644);
+    if (server.appendfd == -1) {
+        redisLog(REDIS_WARNING,"Used tried to switch on AOF via CONFIG, but I can't open the AOF file: %s",strerror(errno));
+        return REDIS_ERR;
+    }
+    if (rewriteAppendOnlyFileBackground() == REDIS_ERR) {
+        server.appendonly = 0;
+        close(server.appendfd);
+        redisLog(REDIS_WARNING,"Used tried to switch on AOF via CONFIG, I can't trigger a background AOF rewrite operation. Check the above logs for more info about the error.",strerror(errno));
+        return REDIS_ERR;
+    }
+    return REDIS_OK;
+}
+
 /* Write the append only file buffer on disk.
  *
  * Since we are required to write the AOF before replying to the client,
@@ -8596,16 +8660,16 @@ static int rewriteAppendOnlyFile(char *filename) {
             int swapped;
 
             key = dictGetEntryKey(de);
+            o = dictGetEntryVal(de);
             /* If the value for this key is swapped, load a preview in memory.
              * We use a "swapped" flag to remember if we need to free the
              * value object instead to just increment the ref count anyway
              * in order to avoid copy-on-write of pages if we are forked() */
-            if (!server.vm_enabled || key->storage == REDIS_VM_MEMORY ||
-                key->storage == REDIS_VM_SWAPPING) {
-                o = dictGetEntryVal(de);
+            if (!server.vm_enabled || o->storage == REDIS_VM_MEMORY ||
+                o->storage == REDIS_VM_SWAPPING) {
                 swapped = 0;
             } else {
-                o = vmPreviewObject(key);
+                o = vmPreviewObject(o);
                 swapped = 1;
             }
             expiretime = getExpire(db,key);
@@ -8829,50 +8893,19 @@ static void aofRemoveTempFile(pid_t childpid) {
  * as a fully non-blocking VM.
  */
 
-/* Called when the user switches from "appendonly yes" to "appendonly no"
- * at runtime using the CONFIG command. */
-static void stopAppendOnly(void) {
-    flushAppendOnlyFile();
-    aof_fsync(server.appendfd);
-    close(server.appendfd);
+/* =================== Virtual Memory - Blocking Side  ====================== */
 
-    server.appendfd = -1;
-    server.appendseldb = -1;
-    server.appendonly = 0;
-    /* rewrite operation in progress? kill it, wait child exit */
-    if (server.bgsavechildpid != -1) {
-        int statloc;
+/* Create a VM pointer object. This kind of objects are used in place of
+ * values in the key -> value hash table, for swapped out objects. */
+static vmpointer *createVmPointer(int vtype) {
+    vmpointer *vp = zmalloc(sizeof(vmpointer));
 
-        if (kill(server.bgsavechildpid,SIGKILL) != -1)
-            wait3(&statloc,0,NULL);
-        /* reset the buffer accumulating changes while the child saves */
-        sdsfree(server.bgrewritebuf);
-        server.bgrewritebuf = sdsempty();
-        server.bgsavechildpid = -1;
-    }
+    vp->type = REDIS_VMPOINTER;
+    vp->storage = REDIS_VM_SWAPPED;
+    vp->vtype = vtype;
+    return vp;
 }
 
-/* Called when the user switches from "appendonly no" to "appendonly yes"
- * at runtime using the CONFIG command. */
-static int startAppendOnly(void) {
-    server.appendonly = 1;
-    server.lastfsync = time(NULL);
-    server.appendfd = open(server.appendfilename,O_WRONLY|O_APPEND|O_CREAT,0644);
-    if (server.appendfd == -1) {
-        redisLog(REDIS_WARNING,"Used tried to switch on AOF via CONFIG, but I can't open the AOF file: %s",strerror(errno));
-        return REDIS_ERR;
-    }
-    if (rewriteAppendOnlyFileBackground() == REDIS_ERR) {
-        server.appendonly = 0;
-        close(server.appendfd);
-        redisLog(REDIS_WARNING,"Used tried to switch on AOF via CONFIG, I can't trigger a background AOF rewrite operation. Check the above logs for more info about the error.",strerror(errno));
-        return REDIS_ERR;
-    }
-    return REDIS_OK;
-}
-
-/* =================== Virtual Memory - Blocking Side  ====================== */
-
 static void vmInit(void) {
     off_t totsize;
     int pipefds[2];
@@ -9091,26 +9124,27 @@ static int vmWriteObjectOnSwap(robj *o, off_t page) {
  * needed to later retrieve the object into the key object.
  * If we can't find enough contiguous empty pages to swap the object on disk
  * REDIS_ERR is returned. */
-static int vmSwapObjectBlocking(robj *key, robj *val) {
+static vmpointer *vmSwapObjectBlocking(robj *val) {
     off_t pages = rdbSavedObjectPages(val,NULL);
     off_t page;
+    vmpointer *vp;
 
-    assert(key->storage == REDIS_VM_MEMORY);
-    assert(key->refcount == 1);
-    if (vmFindContiguousPages(&page,pages) == REDIS_ERR) return REDIS_ERR;
-    if (vmWriteObjectOnSwap(val,page) == REDIS_ERR) return REDIS_ERR;
-    key->vm.page = page;
-    key->vm.usedpages = pages;
-    key->storage = REDIS_VM_SWAPPED;
-    key->vtype = val->type;
+    assert(val->storage == REDIS_VM_MEMORY);
+    assert(val->refcount == 1);
+    if (vmFindContiguousPages(&page,pages) == REDIS_ERR) return NULL;
+    if (vmWriteObjectOnSwap(val,page) == REDIS_ERR) return NULL;
+
+    vp = createVmPointer(val->type);
+    vp->page = page;
+    vp->usedpages = pages;
     decrRefCount(val); /* Deallocate the object from memory. */
     vmMarkPagesUsed(page,pages);
-    redisLog(REDIS_DEBUG,"VM: object %s swapped out at %lld (%lld pages)",
-        (unsigned char*) key->ptr,
+    redisLog(REDIS_DEBUG,"VM: object %p swapped out at %lld (%lld pages)",
+        (void*) val,
         (unsigned long long) page, (unsigned long long) pages);
     server.vm_stats_swapped_objects++;
     server.vm_stats_swapouts++;
-    return REDIS_OK;
+    return vp;
 }
 
 static robj *vmReadObjectFromSwap(off_t page, int type) {
@@ -9132,46 +9166,47 @@ static robj *vmReadObjectFromSwap(off_t page, int type) {
     return o;
 }
 
-/* Load the value object relative to the 'key' object from swap to memory.
+/* Load the specified object from swap to memory.
  * The newly allocated object is returned.
  *
  * If preview is true the unserialized object is returned to the caller but
- * no changes are made to the key object, nor the pages are marked as freed */
-static robj *vmGenericLoadObject(robj *key, int preview) {
+ * the pages are not marked as freed, nor the vp object is freed. */
+static robj *vmGenericLoadObject(vmpointer *vp, int preview) {
     robj *val;
 
-    redisAssert(key->storage == REDIS_VM_SWAPPED || key->storage == REDIS_VM_LOADING);
-    val = vmReadObjectFromSwap(key->vm.page,key->vtype);
+    redisAssert(vp->type == REDIS_VMPOINTER &&
+        (vp->storage == REDIS_VM_SWAPPED || vp->storage == REDIS_VM_LOADING));
+    val = vmReadObjectFromSwap(vp->page,vp->vtype);
     if (!preview) {
-        key->storage = REDIS_VM_MEMORY;
-        key->vm.atime = server.unixtime;
-        vmMarkPagesFree(key->vm.page,key->vm.usedpages);
-        redisLog(REDIS_DEBUG, "VM: object %s loaded from disk",
-            (unsigned char*) key->ptr);
+        redisLog(REDIS_DEBUG, "VM: object %p loaded from disk", (void*)vp);
+        vmMarkPagesFree(vp->page,vp->usedpages);
+        zfree(vp);
         server.vm_stats_swapped_objects--;
     } else {
-        redisLog(REDIS_DEBUG, "VM: object %s previewed from disk",
-            (unsigned char*) key->ptr);
+        redisLog(REDIS_DEBUG, "VM: object %p previewed from disk", (void*)vp);
     }
     server.vm_stats_swapins++;
     return val;
 }
 
-/* Plain object loading, from swap to memory */
-static robj *vmLoadObject(robj *key) {
+/* Plain object loading, from swap to memory.
+ *
+ * 'o' is actually a redisVmPointer structure that will be freed by the call.
+ * The return value is the loaded object. */
+static robj *vmLoadObject(robj *o) {
     /* If we are loading the object in background, stop it, we
      * need to load this object synchronously ASAP. */
-    if (key->storage == REDIS_VM_LOADING)
-        vmCancelThreadedIOJob(key);
-    return vmGenericLoadObject(key,0);
+    if (o->storage == REDIS_VM_LOADING)
+        vmCancelThreadedIOJob(o);
+    return vmGenericLoadObject((vmpointer*)o,0);
 }
 
 /* Just load the value on disk, without to modify the key.
  * This is useful when we want to perform some operation on the value
  * without to really bring it from swap to memory, like while saving the
  * dataset or rewriting the append only log. */
-static robj *vmPreviewObject(robj *key) {
-    return vmGenericLoadObject(key,1);
+static robj *vmPreviewObject(robj *o) {
+    return vmGenericLoadObject((vmpointer*)o,1);
 }
 
 /* How a good candidate is this object for swapping?
@@ -9186,14 +9221,16 @@ static robj *vmPreviewObject(robj *key) {
  * proportionally, this is why we use the logarithm. This algorithm is
  * just a first try and will probably be tuned later. */
 static double computeObjectSwappability(robj *o) {
-    time_t age = server.unixtime - o->vm.atime;
+    /* actual age can be >= minage, but not < minage. As we use wrapping
+     * 21 bit clocks with minutes resolution for the LRU. */
+    time_t minage = abs(server.lruclock - o->lru);
     long asize = 0;
     list *l;
     dict *d;
     struct dictEntry *de;
     int z;
 
-    if (age <= 0) return 0;
+    if (minage <= 0) return 0;
     switch(o->type) {
     case REDIS_STRING:
         if (o->encoding != REDIS_ENCODING_RAW) {
@@ -9212,8 +9249,7 @@ static double computeObjectSwappability(robj *o) {
             long elesize;
 
             elesize = (ele->encoding == REDIS_ENCODING_RAW) ?
-                            (sizeof(*o)+sdslen(ele->ptr)) :
-                            sizeof(*o);
+                            (sizeof(*o)+sdslen(ele->ptr)) : sizeof(*o);
             asize += (sizeof(listNode)+elesize)*listLength(l);
         }
         break;
@@ -9231,8 +9267,7 @@ static double computeObjectSwappability(robj *o) {
             de = dictGetRandomKey(d);
             ele = dictGetEntryKey(de);
             elesize = (ele->encoding == REDIS_ENCODING_RAW) ?
-                            (sizeof(*o)+sdslen(ele->ptr)) :
-                            sizeof(*o);
+                            (sizeof(*o)+sdslen(ele->ptr)) : sizeof(*o);
             asize += (sizeof(struct dictEntry)+elesize)*dictSize(d);
             if (z) asize += sizeof(zskiplistNode)*dictSize(d);
         }
@@ -9259,18 +9294,16 @@ static double computeObjectSwappability(robj *o) {
                 de = dictGetRandomKey(d);
                 ele = dictGetEntryKey(de);
                 elesize = (ele->encoding == REDIS_ENCODING_RAW) ?
-                                (sizeof(*o)+sdslen(ele->ptr)) :
-                                sizeof(*o);
+                                (sizeof(*o)+sdslen(ele->ptr)) : sizeof(*o);
                 ele = dictGetEntryVal(de);
                 elesize = (ele->encoding == REDIS_ENCODING_RAW) ?
-                                (sizeof(*o)+sdslen(ele->ptr)) :
-                                sizeof(*o);
+                                (sizeof(*o)+sdslen(ele->ptr)) : sizeof(*o);
                 asize += (sizeof(struct dictEntry)+elesize)*dictSize(d);
             }
         }
         break;
     }
-    return (double)age*log(1+asize);
+    return (double)minage*log(1+asize);
 }
 
 /* Try to swap an object that's a good candidate for swapping.
@@ -9304,12 +9337,11 @@ static int vmSwapOneObject(int usethreads) {
             val = dictGetEntryVal(de);
             /* Only swap objects that are currently in memory.
              *
-             * Also don't swap shared objects if threaded VM is on, as we
-             * try to ensure that the main thread does not touch the
+             * Also don't swap shared objects: not a good idea in general and
+             * we need to ensure that the main thread does not touch the
              * object while the I/O thread is using it, but we can't
              * control other keys without adding additional mutex. */
-            if (key->storage != REDIS_VM_MEMORY ||
-                (server.vm_max_threads != 0 && val->refcount != 1)) {
+            if (val->storage != REDIS_VM_MEMORY || val->refcount != 1) {
                 if (maxtries) i--; /* don't count this try */
                 continue;
             }
@@ -9328,19 +9360,15 @@ static int vmSwapOneObject(int usethreads) {
     redisLog(REDIS_DEBUG,"Key with best swappability: %s, %f",
         key->ptr, best_swappability);
 
-    /* Unshare the key if needed */
-    if (key->refcount > 1) {
-        robj *newkey = dupStringObject(key);
-        decrRefCount(key);
-        key = dictGetEntryKey(best) = newkey;
-    }
     /* Swap it */
     if (usethreads) {
         vmSwapObjectThreaded(key,val,best_db);
         return REDIS_OK;
     } else {
-        if (vmSwapObjectBlocking(key,val) == REDIS_OK) {
-            dictGetEntryVal(best) = NULL;
+        vmpointer *vp;
+
+        if ((vp = vmSwapObjectBlocking(val)) != NULL) {
+            dictGetEntryVal(best) = vp;
             return REDIS_OK;
         } else {
             return REDIS_ERR;
@@ -9366,12 +9394,10 @@ static int vmCanSwapOut(void) {
 /* Delete a key if swapped. Returns 1 if the key was found, was swapped
  * and was deleted. Otherwise 0 is returned. */
 static int deleteIfSwapped(redisDb *db, robj *key) {
-    dictEntry *de;
-    robj *foundkey;
+    robj *val;
 
-    if ((de = dictFind(db->dict,key)) == NULL) return 0;
-    foundkey = dictGetEntryKey(de);
-    if (foundkey->storage == REDIS_VM_MEMORY) return 0;
+    if ((val = dictFetchValue(db->dict,key)) == NULL) return 0;
+    if (val->storage == REDIS_VM_MEMORY) return 0;
     deleteKey(db,key);
     return 1;
 }
@@ -9382,11 +9408,16 @@ static void freeIOJob(iojob *j) {
     if ((j->type == REDIS_IOJOB_PREPARE_SWAP ||
         j->type == REDIS_IOJOB_DO_SWAP ||
         j->type == REDIS_IOJOB_LOAD) && j->val != NULL)
+    {
+        /* Our value object was successfully swapped if
+         * refcount == 1 and storage == REDIS_VM_SWAPPING,
+         * we fix the storage type, otherwise decrRefCount() will try to
+         * kill the I/O thread Job (that does no longer exists). */
+        if (j->val->refcount == 1 && j->val->storage == REDIS_VM_SWAPPING)
+            j->val->storage = REDIS_VM_MEMORY;
         decrRefCount(j->val);
-    /* We don't decrRefCount the j->key field as we did't incremented
-     * the count creating IO Jobs. This is because the key field here is
-     * just used as an indentifier and if a key is removed the Job should
-     * never be touched again. */
+    }
+    decrRefCount(j->key);
     zfree(j);
 }
 
@@ -9407,7 +9438,6 @@ static void vmThreadedIOCompletedJob(aeEventLoop *el, int fd, void *privdata,
     while((retval = read(fd,buf,1)) == 1) {
         iojob *j;
         listNode *ln;
-        robj *key;
         struct dictEntry *de;
 
         redisLog(REDIS_DEBUG,"Processing I/O completed job");
@@ -9430,27 +9460,26 @@ static void vmThreadedIOCompletedJob(aeEventLoop *el, int fd, void *privdata,
         }
         /* Post process it in the main thread, as there are things we
          * can do just here to avoid race conditions and/or invasive locks */
-        redisLog(REDIS_DEBUG,"Job %p type: %d, key at %p (%s) refcount: %d\n", (void*) j, j->type, (void*)j->key, (char*)j->key->ptr, j->key->refcount);
+        redisLog(REDIS_DEBUG,"COMPLETED Job type: %d, ID %p, key: %s", j->type, (void*)j->id, (unsigned char*)j->key->ptr);
         de = dictFind(j->db->dict,j->key);
         assert(de != NULL);
-        key = dictGetEntryKey(de);
         if (j->type == REDIS_IOJOB_LOAD) {
             redisDb *db;
+            vmpointer *vp = dictGetEntryVal(de);
 
             /* Key loaded, bring it at home */
-            key->storage = REDIS_VM_MEMORY;
-            key->vm.atime = server.unixtime;
-            vmMarkPagesFree(key->vm.page,key->vm.usedpages);
+            vmMarkPagesFree(vp->page,vp->usedpages);
             redisLog(REDIS_DEBUG, "VM: object %s loaded from disk (threaded)",
-                (unsigned char*) key->ptr);
+                (unsigned char*) j->key->ptr);
             server.vm_stats_swapped_objects--;
             server.vm_stats_swapins++;
             dictGetEntryVal(de) = j->val;
             incrRefCount(j->val);
             db = j->db;
-            freeIOJob(j);
             /* Handle clients waiting for this key to be loaded. */
-            handleClientsBlockedOnSwappedKey(db,key);
+            handleClientsBlockedOnSwappedKey(db,j->key);
+            freeIOJob(j);
+            zfree(vp);
         } else if (j->type == REDIS_IOJOB_PREPARE_SWAP) {
             /* Now we know the amount of pages required to swap this object.
              * Let's find some space for it, and queue this task again
@@ -9460,8 +9489,8 @@ static void vmThreadedIOCompletedJob(aeEventLoop *el, int fd, void *privdata,
             {
                 /* Ooops... no space or we can't swap as there is
                  * a fork()ed Redis trying to save stuff on disk. */
+                j->val->storage = REDIS_VM_MEMORY; /* undo operation */
                 freeIOJob(j);
-                key->storage = REDIS_VM_MEMORY; /* undo operation */
             } else {
                 /* Note that we need to mark this pages as used now,
                  * if the job will be canceled, we'll mark them as freed
@@ -9473,28 +9502,26 @@ static void vmThreadedIOCompletedJob(aeEventLoop *el, int fd, void *privdata,
                 unlockThreadedIO();
             }
         } else if (j->type == REDIS_IOJOB_DO_SWAP) {
-            robj *val;
+            vmpointer *vp;
 
             /* Key swapped. We can finally free some memory. */
-            if (key->storage != REDIS_VM_SWAPPING) {
-                printf("key->storage: %d\n",key->storage);
-                printf("key->name: %s\n",(char*)key->ptr);
-                printf("key->refcount: %d\n",key->refcount);
+            if (j->val->storage != REDIS_VM_SWAPPING) {
+                vmpointer *vp = (vmpointer*) j->id;
+                printf("storage: %d\n",vp->storage);
+                printf("key->name: %s\n",(char*)j->key->ptr);
                 printf("val: %p\n",(void*)j->val);
                 printf("val->type: %d\n",j->val->type);
                 printf("val->ptr: %s\n",(char*)j->val->ptr);
             }
-            redisAssert(key->storage == REDIS_VM_SWAPPING);
-            val = dictGetEntryVal(de);
-            key->vm.page = j->page;
-            key->vm.usedpages = j->pages;
-            key->storage = REDIS_VM_SWAPPED;
-            key->vtype = j->val->type;
-            decrRefCount(val); /* Deallocate the object from memory. */
-            dictGetEntryVal(de) = NULL;
+            redisAssert(j->val->storage == REDIS_VM_SWAPPING);
+            vp = createVmPointer(j->val->type);
+            vp->page = j->page;
+            vp->usedpages = j->pages;
+            dictGetEntryVal(de) = vp;
+            decrRefCount(j->val);
             redisLog(REDIS_DEBUG,
                 "VM: object %s swapped out at %lld (%lld pages) (threaded)",
-                (unsigned char*) key->ptr,
+                (unsigned char*) j->key->ptr,
                 (unsigned long long) j->page, (unsigned long long) j->pages);
             server.vm_stats_swapped_objects++;
             server.vm_stats_swapouts++;
@@ -9549,7 +9576,7 @@ static void vmCancelThreadedIOJob(robj *o) {
     assert(o->storage == REDIS_VM_LOADING || o->storage == REDIS_VM_SWAPPING);
 again:
     lockThreadedIO();
-    /* Search for a matching key in one of the queues */
+    /* Search for a matching object in one of the queues */
     for (i = 0; i < 3; i++) {
         listNode *ln;
         listIter li;
@@ -9559,7 +9586,7 @@ static void vmCancelThreadedIOJob(robj *o) {
             iojob *job = ln->value;
 
             if (job->canceled) continue; /* Skip this, already canceled. */
-            if (job->key == o) {
+            if (job->id == o) {
                 redisLog(REDIS_DEBUG,"*** CANCELED %p (%s) (type %d) (LIST ID %d)\n",
                     (void*)job, (char*)o->ptr, job->type, i);
                 /* Mark the pages as free since the swap didn't happened
@@ -9614,7 +9641,8 @@ static void vmCancelThreadedIOJob(robj *o) {
         }
     }
     unlockThreadedIO();
-    assert(1 != 1); /* We should never reach this */
+    printf("Not found: %p\n", (void*)o);
+    redisAssert(1 != 1); /* We should never reach this */
 }
 
 static void *IOThreadEntryPoint(void *arg) {
@@ -9647,7 +9675,8 @@ static void *IOThreadEntryPoint(void *arg) {
 
         /* Process the Job */
         if (j->type == REDIS_IOJOB_LOAD) {
-            j->val = vmReadObjectFromSwap(j->page,j->key->vtype);
+            vmpointer *vp = (vmpointer*)j->id;
+            j->val = vmReadObjectFromSwap(j->page,vp->vtype);
         } else if (j->type == REDIS_IOJOB_PREPARE_SWAP) {
             FILE *fp = fopen("/dev/null","w+");
             j->pages = rdbSavedObjectPages(j->val,fp);
@@ -9744,17 +9773,16 @@ static int vmSwapObjectThreaded(robj *key, robj *val, redisDb *db) {
     iojob *j;
 
     assert(key->storage == REDIS_VM_MEMORY);
-    assert(key->refcount == 1);
 
     j = zmalloc(sizeof(*j));
     j->type = REDIS_IOJOB_PREPARE_SWAP;
     j->db = db;
     j->key = key;
-    j->val = val;
+    j->id = j->val = val;
     incrRefCount(val);
     j->canceled = 0;
     j->thread = (pthread_t) -1;
-    key->storage = REDIS_VM_SWAPPING;
+    val->storage = REDIS_VM_SWAPPING;
 
     lockThreadedIO();
     queueIOJob(j);
@@ -9778,7 +9806,7 @@ static int waitForSwappedKey(redisClient *c, robj *key) {
      * block the client at all. */
     de = dictFind(c->db->dict,key);
     if (de == NULL) return 0;
-    o = dictGetEntryKey(de);
+    o = dictGetEntryVal(de);
     if (o->storage == REDIS_VM_MEMORY) {
         return 0;
     } else if (o->storage == REDIS_VM_SWAPPING) {
@@ -9812,14 +9840,16 @@ static int waitForSwappedKey(redisClient *c, robj *key) {
     /* Are we already loading the key from disk? If not create a job */
     if (o->storage == REDIS_VM_SWAPPED) {
         iojob *j;
+        vmpointer *vp = (vmpointer*)o;
 
         o->storage = REDIS_VM_LOADING;
         j = zmalloc(sizeof(*j));
         j->type = REDIS_IOJOB_LOAD;
         j->db = c->db;
-        j->key = o;
-        j->key->vtype = o->vtype;
-        j->page = o->vm.page;
+        j->id = (robj*)vp;
+        j->key = key;
+        incrRefCount(key);
+        j->page = vp->page;
         j->val = NULL;
         j->canceled = 0;
         j->thread = (pthread_t) -1;
@@ -9944,6 +9974,8 @@ static int dontWaitForSwappedKey(redisClient *c, robj *key) {
     return listLength(c->io_keys) == 0;
 }
 
+/* Every time we now a key was loaded back in memory, we handle clients
+ * waiting for this key if any. */
 static void handleClientsBlockedOnSwappedKey(redisDb *db, robj *key) {
     struct dictEntry *de;
     list *l;
@@ -10800,8 +10832,8 @@ static void debugCommand(redisClient *c) {
         }
         key = dictGetEntryKey(de);
         val = dictGetEntryVal(de);
-        if (!server.vm_enabled || (key->storage == REDIS_VM_MEMORY ||
-                                   key->storage == REDIS_VM_SWAPPING)) {
+        if (!server.vm_enabled || (val->storage == REDIS_VM_MEMORY ||
+                                   val->storage == REDIS_VM_SWAPPING)) {
             char *strenc;
             char buf[128];
 
@@ -10817,18 +10849,20 @@ static void debugCommand(redisClient *c) {
                 (void*)key, key->refcount, (void*)val, val->refcount,
                 strenc, (long long) rdbSavedObjectLen(val,NULL)));
         } else {
+            vmpointer *vp = (vmpointer*) val;
             addReplySds(c,sdscatprintf(sdsempty(),
                 "+Key at:%p refcount:%d, value swapped at: page %llu "
                 "using %llu pages\r\n",
-                (void*)key, key->refcount, (unsigned long long) key->vm.page,
-                (unsigned long long) key->vm.usedpages));
+                (void*)key, key->refcount, (unsigned long long) vp->page,
+                (unsigned long long) vp->usedpages));
         }
     } else if (!strcasecmp(c->argv[1]->ptr,"swapin") && c->argc == 3) {
         lookupKeyRead(c->db,c->argv[2]);
         addReply(c,shared.ok);
     } else if (!strcasecmp(c->argv[1]->ptr,"swapout") && c->argc == 3) {
         dictEntry *de = dictFind(c->db->dict,c->argv[2]);
         robj *key, *val;
+        vmpointer *vp;
 
         if (!server.vm_enabled) {
             addReplySds(c,sdsnew("-ERR Virtual Memory is disabled\r\n"));
@@ -10840,17 +10874,13 @@ static void debugCommand(redisClient *c) {
         }
         key = dictGetEntryKey(de);
         val = dictGetEntryVal(de);
-        /* If the key is shared we want to create a copy */
-        if (key->refcount > 1) {
-            robj *newkey = dupStringObject(key);
-            decrRefCount(key);
-            key = dictGetEntryKey(de) = newkey;
-        }
         /* Swap it */
-        if (key->storage != REDIS_VM_MEMORY) {
+        if (val->storage != REDIS_VM_MEMORY) {
             addReplySds(c,sdsnew("-ERR This key is not in memory\r\n"));
-        } else if (vmSwapObjectBlocking(key,val) == REDIS_OK) {
-            dictGetEntryVal(de) = NULL;
+        } else if (val->refcount != 1) {
+            addReplySds(c,sdsnew("-ERR Object is shared\r\n"));
+        } else if ((vp = vmSwapObjectBlocking(val)) != NULL) {
+            dictGetEntryVal(de) = vp;
             addReply(c,shared.ok);
         } else {
             addReply(c,shared.err);