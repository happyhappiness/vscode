@@ -221,8 +221,9 @@ static void _redisAssert(char *estr);
 
 /* The VM object structure */
 struct redisObjectVM {
-    off_t offset;   /* the page at witch the object is stored on disk */
-    int pages;   /* number of pages used on disk */
+    off_t page;         /* the page at witch the object is stored on disk */
+    off_t usedpages;    /* number of pages used on disk */
+    time_t atime;       /* Last access time */
 } vm;
 
 /* The actual Redis Object */
@@ -249,6 +250,7 @@ typedef struct redisObject {
     _var.type = REDIS_STRING; \
     _var.encoding = REDIS_ENCODING_RAW; \
     _var.ptr = _ptr; \
+    if (server.vm_enabled) _var.storage = REDIS_VM_MEMORY; \
 } while(0);
 
 typedef struct redisDb {
@@ -375,6 +377,7 @@ struct redisServer {
     off_t vm_next_page; /* Next probably empty page */
     off_t vm_near_pages; /* Number of pages allocated sequentially */
     unsigned char *vm_bitmap; /* Bitmap of free/used pages */
+    time_t unixtime;    /* Unix time sampled every second. */
 };
 
 typedef void redisCommandProc(redisClient *c);
@@ -1062,6 +1065,12 @@ static int serverCron(struct aeEventLoop *eventLoop, long long id, void *clientD
     REDIS_NOTUSED(id);
     REDIS_NOTUSED(clientData);
 
+    /* We take a cached value of the unix time in the global state because
+     * with virtual memory and aging there is to store the current time
+     * in objects at every object access, and accuracy is not needed.
+     * To access a global var is faster than calling time(NULL) */
+    server.unixtime = time(NULL);
+
     /* Update the global state with the amount of used memory */
     server.usedmemory = zmalloc_used_memory();
 
@@ -1305,6 +1314,7 @@ static void initServer() {
     server.stat_numcommands = 0;
     server.stat_numconnections = 0;
     server.stat_starttime = time(NULL);
+    server.unixtime = time(NULL);
     aeCreateTimeEvent(server.el, 1, serverCron, NULL, NULL);
 
     if (server.appendonly) {
@@ -2252,6 +2262,10 @@ static robj *createObject(int type, void *ptr) {
     o->encoding = REDIS_ENCODING_RAW;
     o->ptr = ptr;
     o->refcount = 1;
+    if (server.vm_enabled) {
+        o->vm.atime = server.unixtime;
+        o->storage = REDIS_VM_MEMORY;
+    }
     return o;
 }
 
@@ -2337,7 +2351,15 @@ static void decrRefCount(void *obj) {
 
 static robj *lookupKey(redisDb *db, robj *key) {
     dictEntry *de = dictFind(db->dict,key);
-    return de ? dictGetEntryVal(de) : NULL;
+    if (de) {
+        robj *o = dictGetEntryVal(de);
+
+        /* Update the access time of the key for the aging algorithm. */
+        if (server.vm_enabled) o->vm.atime = server.unixtime;
+        return o;
+    } else {
+        return NULL;
+    }
 }
 
 static robj *lookupKeyRead(redisDb *db, robj *key) {
@@ -6658,8 +6680,8 @@ static int vmFreePage(off_t page) {
 }
 
 /* Find N contiguous free pages storing the first page of the cluster in *first.
- * Returns 1 if it was able to find N contiguous pages, otherwise 0 is
- * returned.
+ * Returns REDIS_OK if it was able to find N contiguous pages, otherwise 
+ * REDIS_ERR is returned.
  *
  * This function uses a simple algorithm: we try to allocate
  * REDIS_VM_MAX_NEAR_PAGES sequentially, when we reach this limit we start
@@ -6704,7 +6726,7 @@ static int vmFindContiguousPages(off_t *first, int n) {
             /* Already got N free pages? Return to the caller, with success */
             if (numfree == n) {
                 *first = this;
-                return 1;
+                return REDIS_OK;
             }
         } else {
             /* The current one is not a free page */
@@ -6725,7 +6747,55 @@ static int vmFindContiguousPages(off_t *first, int n) {
             offset++;
         }
     }
-    return 0;
+    return REDIS_ERR;
+}
+
+/* Swap the 'val' object relative to 'key' into disk. Store all the information
+ * needed to later retrieve the object into the key object.
+ * If we can't find enough contiguous empty pages to swap the object on disk
+ * REDIS_ERR is returned. */
+static int vmSwapObject(robj *key, robj *val) {
+    off_t pages = rdbSavedObjectPages(val);
+    off_t page;
+
+    assert(key->storage == REDIS_VM_MEMORY);
+    if (vmFindContiguousPages(&page,pages) == REDIS_ERR) return REDIS_ERR;
+    if (fseeko(server.vm_fp,page*server.vm_page_size,SEEK_SET) == -1) {
+        redisLog(REDIS_WARNING,
+            "Critical VM problem in vmSwapObject(): can't seek: %s",
+            strerror(errno));
+        return REDIS_ERR;
+    }
+    rdbSaveObject(server.vm_fp,val);
+    key->vm.page = page;
+    key->vm.usedpages = pages;
+    key->storage = REDIS_VM_SWAPPED;
+    decrRefCount(val); /* Deallocate the object from memory. */
+    vmMarkPagesUsed(page,pages);
+    return REDIS_OK;
+}
+
+/* Load the value object relative to the 'key' object from swap to memory.
+ * The newly allocated object is returned. */
+static robj *vmLoadObject(robj *key) {
+    robj *val;
+
+    assert(key->storage == REDIS_VM_SWAPPED);
+    if (fseeko(server.vm_fp,key->vm.page*server.vm_page_size,SEEK_SET) == -1) {
+        redisLog(REDIS_WARNING,
+            "Unrecoverable VM problem in vmLoadObject(): can't seek: %s",
+            strerror(errno));
+        exit(1);
+    }
+    val = rdbLoadObject(key->type,server.vm_fp);
+    if (val == NULL) {
+        redisLog(REDIS_WARNING, "Unrecoverable VM problem in vmLoadObject(): can't load object from swap file: %s", strerror(errno));
+        exit(1);
+    }
+    key->storage = REDIS_VM_MEMORY;
+    key->vm.atime = server.unixtime;
+    vmMarkPagesFree(key->vm.page,key->vm.usedpages);
+    return val;
 }
 
 /* ================================= Debugging ============================== */