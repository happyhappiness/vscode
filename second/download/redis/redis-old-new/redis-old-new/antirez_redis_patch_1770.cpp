@@ -109,67 +109,30 @@
 
 /* =================== Virtual Memory - Blocking Side  ====================== */
 
-void vmInit(void) {
+void dsInit(void) {
     off_t totsize;
     int pipefds[2];
     size_t stacksize;
     struct flock fl;
 
-    if (server.vm_max_threads != 0)
-        zmalloc_enable_thread_safeness(); /* we need thread safe zmalloc() */
+    zmalloc_enable_thread_safeness(); /* we need thread safe zmalloc() */
 
-    redisLog(REDIS_NOTICE,"Using '%s' as swap file",server.vm_swap_file);
-    /* Try to open the old swap file, otherwise create it */
-    if ((server.vm_fp = fopen(server.vm_swap_file,"r+b")) == NULL) {
-        server.vm_fp = fopen(server.vm_swap_file,"w+b");
-    }
-    if (server.vm_fp == NULL) {
-        redisLog(REDIS_WARNING,
-            "Can't open the swap file: %s. Exiting.",
-            strerror(errno));
-        exit(1);
-    }
-    server.vm_fd = fileno(server.vm_fp);
-    /* Lock the swap file for writing, this is useful in order to avoid
-     * another instance to use the same swap file for a config error. */
-    fl.l_type = F_WRLCK;
-    fl.l_whence = SEEK_SET;
-    fl.l_start = fl.l_len = 0;
-    if (fcntl(server.vm_fd,F_SETLK,&fl) == -1) {
-        redisLog(REDIS_WARNING,
-            "Can't lock the swap file at '%s': %s. Make sure it is not used by another Redis instance.", server.vm_swap_file, strerror(errno));
-        exit(1);
-    }
-    /* Initialize */
-    server.vm_next_page = 0;
-    server.vm_near_pages = 0;
-    server.vm_stats_used_pages = 0;
-    server.vm_stats_swapped_objects = 0;
-    server.vm_stats_swapouts = 0;
-    server.vm_stats_swapins = 0;
-    totsize = server.vm_pages*server.vm_page_size;
-    redisLog(REDIS_NOTICE,"Allocating %lld bytes of swap file",totsize);
-    if (ftruncate(server.vm_fd,totsize) == -1) {
-        redisLog(REDIS_WARNING,"Can't ftruncate swap file: %s. Exiting.",
-            strerror(errno));
+    redisLog(REDIS_NOTICE,"Initializing Disk Store at %s", server.ds_path);
+    /* Open Disk Store */
+    if (dsOpen() != REDIS_OK) {
+        redisLog(REDIS_WARNING,"Fatal error opening disk store. Exiting.");
         exit(1);
-    } else {
-        redisLog(REDIS_NOTICE,"Swap file allocated with success");
-    }
-    server.vm_bitmap = zcalloc((server.vm_pages+7)/8);
-    redisLog(REDIS_VERBOSE,"Allocated %lld bytes page table for %lld pages",
-        (long long) (server.vm_pages+7)/8, server.vm_pages);
+    };
 
-    /* Initialize threaded I/O (used by Virtual Memory) */
+    /* Initialize threaded I/O for Object Cache */
     server.io_newjobs = listCreate();
     server.io_processing = listCreate();
     server.io_processed = listCreate();
     server.io_ready_clients = listCreate();
     pthread_mutex_init(&server.io_mutex,NULL);
-    pthread_mutex_init(&server.io_swapfile_mutex,NULL);
     server.io_active_threads = 0;
     if (pipe(pipefds) == -1) {
-        redisLog(REDIS_WARNING,"Unable to intialized VM: pipe(2): %s. Exiting."
+        redisLog(REDIS_WARNING,"Unable to intialized DS: pipe(2): %s. Exiting."
             ,strerror(errno));
         exit(1);
     }
@@ -190,139 +153,21 @@ void vmInit(void) {
     if (aeCreateFileEvent(server.el, server.io_ready_pipe_read, AE_READABLE,
         vmThreadedIOCompletedJob, NULL) == AE_ERR)
         oom("creating file event");
-}
-
-/* Write the specified object at the specified page of the swap file */
-int vmWriteObjectOnSwap(robj *o, off_t page) {
-    if (server.vm_enabled) pthread_mutex_lock(&server.io_swapfile_mutex);
-    if (fseeko(server.vm_fp,page*server.vm_page_size,SEEK_SET) == -1) {
-        if (server.vm_enabled) pthread_mutex_unlock(&server.io_swapfile_mutex);
-        redisLog(REDIS_WARNING,
-            "Critical VM problem in vmWriteObjectOnSwap(): can't seek: %s",
-            strerror(errno));
-        return REDIS_ERR;
-    }
-    rdbSaveObject(server.vm_fp,o);
-    fflush(server.vm_fp);
-    if (server.vm_enabled) pthread_mutex_unlock(&server.io_swapfile_mutex);
-    return REDIS_OK;
-}
-
-/* Transfers the 'val' object to disk. Store all the information
- * a 'vmpointer' object containing all the information needed to load the
- * object back later is returned.
- *
- * If we can't find enough contiguous empty pages to swap the object on disk
- * NULL is returned. */
-vmpointer *vmSwapObjectBlocking(robj *val) {
-    off_t pages = rdbSavedObjectPages(val);
-    off_t page;
-    vmpointer *vp;
-
-    redisAssert(val->storage == REDIS_VM_MEMORY);
-    redisAssert(val->refcount == 1);
-    if (vmFindContiguousPages(&page,pages) == REDIS_ERR) return NULL;
-    if (vmWriteObjectOnSwap(val,page) == REDIS_ERR) return NULL;
-
-    vp = createVmPointer(val->type);
-    vp->page = page;
-    vp->usedpages = pages;
-    decrRefCount(val); /* Deallocate the object from memory. */
-    vmMarkPagesUsed(page,pages);
-    redisLog(REDIS_DEBUG,"VM: object %p swapped out at %lld (%lld pages)",
-        (void*) val,
-        (unsigned long long) page, (unsigned long long) pages);
-    server.vm_stats_swapped_objects++;
-    server.vm_stats_swapouts++;
-    return vp;
-}
-
-robj *vmReadObjectFromSwap(off_t page, int type) {
-    robj *o;
-
-    if (server.vm_enabled) pthread_mutex_lock(&server.io_swapfile_mutex);
-    if (fseeko(server.vm_fp,page*server.vm_page_size,SEEK_SET) == -1) {
-        redisLog(REDIS_WARNING,
-            "Unrecoverable VM problem in vmReadObjectFromSwap(): can't seek: %s",
-            strerror(errno));
-        _exit(1);
-    }
-    o = rdbLoadObject(type,server.vm_fp);
-    if (o == NULL) {
-        redisLog(REDIS_WARNING, "Unrecoverable VM problem in vmReadObjectFromSwap(): can't load object from swap file: %s", strerror(errno));
-        _exit(1);
-    }
-    if (server.vm_enabled) pthread_mutex_unlock(&server.io_swapfile_mutex);
-    return o;
-}
-
-/* Load the specified object from swap to memory.
- * The newly allocated object is returned.
- *
- * If preview is true the unserialized object is returned to the caller but
- * the pages are not marked as freed, nor the vp object is freed. */
-robj *vmGenericLoadObject(vmpointer *vp, int preview) {
-    robj *val;
-
-    redisAssert(vp->type == REDIS_VMPOINTER &&
-        (vp->storage == REDIS_VM_SWAPPED || vp->storage == REDIS_VM_LOADING));
-    val = vmReadObjectFromSwap(vp->page,vp->vtype);
-    if (!preview) {
-        redisLog(REDIS_DEBUG, "VM: object %p loaded from disk", (void*)vp);
-        vmMarkPagesFree(vp->page,vp->usedpages);
-        zfree(vp);
-        server.vm_stats_swapped_objects--;
-    } else {
-        redisLog(REDIS_DEBUG, "VM: object %p previewed from disk", (void*)vp);
-    }
-    server.vm_stats_swapins++;
-    return val;
-}
 
-/* Plain object loading, from swap to memory.
- *
- * 'o' is actually a redisVmPointer structure that will be freed by the call.
- * The return value is the loaded object. */
-robj *vmLoadObject(robj *o) {
-    /* If we are loading the object in background, stop it, we
-     * need to load this object synchronously ASAP. */
-    if (o->storage == REDIS_VM_LOADING)
-        vmCancelThreadedIOJob(o);
-    return vmGenericLoadObject((vmpointer*)o,0);
+    /* Spawn our I/O thread */
+    spawnIOThread();
 }
 
-/* Just load the value on disk, without to modify the key.
- * This is useful when we want to perform some operation on the value
- * without to really bring it from swap to memory, like while saving the
- * dataset or rewriting the append only log. */
-robj *vmPreviewObject(robj *o) {
-    return vmGenericLoadObject((vmpointer*)o,1);
-}
-
-/* How a good candidate is this object for swapping?
- * The better candidate it is, the greater the returned value.
- *
- * Currently we try to perform a fast estimation of the object size in
- * memory, and combine it with aging informations.
- *
- * Basically swappability = idle-time * log(estimated size)
- *
- * Bigger objects are preferred over smaller objects, but not
- * proportionally, this is why we use the logarithm. This algorithm is
- * just a first try and will probably be tuned later. */
+/* Compute how good candidate the specified object is for eviction.
+ * An higher number means a better candidate. */
 double computeObjectSwappability(robj *o) {
     /* actual age can be >= minage, but not < minage. As we use wrapping
      * 21 bit clocks with minutes resolution for the LRU. */
     return (double) estimateObjectIdleTime(o);
 }
 
-/* Try to swap an object that's a good candidate for swapping.
- * Returns REDIS_OK if the object was swapped, REDIS_ERR if it's not possible
- * to swap any object at all.
- *
- * If 'usethreaded' is true, Redis will try to swap the object in background
- * using I/O threads. */
-int vmSwapOneObject(int usethreads) {
+/* Try to free one entry from the diskstore object cache */
+int cacheFreeOneEntry(void) {
     int j, i;
     struct dictEntry *best = NULL;
     double best_swappability = 0;
@@ -351,7 +196,7 @@ int vmSwapOneObject(int usethreads) {
              * we need to ensure that the main thread does not touch the
              * object while the I/O thread is using it, but we can't
              * control other keys without adding additional mutex. */
-            if (val->storage != REDIS_VM_MEMORY || val->refcount != 1) {
+            if (val->storage != REDIS_DS_MEMORY) {
                 if (maxtries) i--; /* don't count this try */
                 continue;
             }
@@ -363,43 +208,31 @@ int vmSwapOneObject(int usethreads) {
             }
         }
     }
-    if (best == NULL) return REDIS_ERR;
+    if (best == NULL) {
+        /* FIXME: If there are objects marked as DS_DIRTY or DS_SAVING
+         * let's wait for this objects to be clear and retry...
+         *
+         * Object cache vm limit is considered an hard limit. */
+        return REDIS_ERR;
+    }
     key = dictGetEntryKey(best);
     val = dictGetEntryVal(best);
 
-    redisLog(REDIS_DEBUG,"Key with best swappability: %s, %f",
+    redisLog(REDIS_DEBUG,"Key selected for cache eviction: %s swappability:%f",
         key, best_swappability);
 
-    /* Swap it */
-    if (usethreads) {
-        robj *keyobj = createStringObject(key,sdslen(key));
-        vmSwapObjectThreaded(keyobj,val,best_db);
-        decrRefCount(keyobj);
-        return REDIS_OK;
-    } else {
-        vmpointer *vp;
-
-        if ((vp = vmSwapObjectBlocking(val)) != NULL) {
-            dictGetEntryVal(best) = vp;
-            return REDIS_OK;
-        } else {
-            return REDIS_ERR;
-        }
+    /* Delete this key from memory */
+    {
+        robj *kobj = createStringObject(key,sdslen(key));
+        dbDelete(best_db,kobj);
+        decrRefCount(kobj);
     }
 }
 
-int vmSwapOneObjectBlocking() {
-    return vmSwapOneObject(0);
-}
-
-int vmSwapOneObjectThreaded() {
-    return vmSwapOneObject(1);
-}
-
 /* Return true if it's safe to swap out objects in a given moment.
  * Basically we don't want to swap objects out while there is a BGSAVE
  * or a BGAEOREWRITE running in backgroud. */
-int vmCanSwapOut(void) {
+int dsCanTouchDiskStore(void) {
     return (server.bgsavechildpid == -1 && server.bgrewritechildpid == -1);
 }
 