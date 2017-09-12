@@ -408,6 +408,7 @@ struct redisServer {
     unsigned long long vm_stats_swapped_objects;
     unsigned long long vm_stats_swapouts;
     unsigned long long vm_stats_swapins;
+    FILE *devnull;
 };
 
 typedef void redisCommandProc(redisClient *c);
@@ -474,15 +475,17 @@ struct sharedObjectsStruct {
 static double R_Zero, R_PosInf, R_NegInf, R_Nan;
 
 /* VM threaded I/O request message */
-#define REDIS_IOJOB_LOAD 0
-#define REDIS_IOJOB_SWAP 1
+#define REDIS_IOJOB_LOAD 0          /* Load from disk to memory */
+#define REDIS_IOJOB_PREPARE_SWAP 1  /* Compute needed pages */
+#define REDIS_IOJOB_DO_SWAP 2       /* Swap from memory to disk */
 typedef struct iojon {
     int type;   /* Request type, REDIS_IOJOB_* */
-    int dbid;   /* Redis database ID */
+    redisDb *db;/* Redis database */
     robj *key;  /* This I/O request is about swapping this key */
-    robj *val;  /* the value to swap for REDIS_IOREQ_SWAP, otherwise this
+    robj *val;  /* the value to swap for REDIS_IOREQ_*_SWAP, otherwise this
                  * field is populated by the I/O thread for REDIS_IOREQ_LOAD. */
     off_t page; /* Swap page where to read/write the object */
+    off_t pages; /* Swap pages needed to safe object. PREPARE_SWAP return val */
     int canceled; /* True if this command was canceled by blocking side of VM */
     pthread_t thread; /* ID of the thread processing this entry */
 } iojob;
@@ -543,6 +546,11 @@ static void freeOneObjectFromFreelist(void);
 static void acceptHandler(aeEventLoop *el, int fd, void *privdata, int mask);
 static void vmThreadedIOCompletedJob(aeEventLoop *el, int fd, void *privdata, int mask);
 static void vmCancelThreadedIOJob(robj *o);
+static void lockThreadedIO(void);
+static void unlockThreadedIO(void);
+static int vmSwapObjectThreaded(robj *key, robj *val, redisDb *db);
+static void freeIOJob(iojob *j);
+static void queueIOJob(iojob *j);
 
 static void authCommand(redisClient *c);
 static void pingCommand(redisClient *c);
@@ -1367,6 +1375,11 @@ static void initServer() {
     signal(SIGPIPE, SIG_IGN);
     setupSigSegvAction();
 
+    server.devnull = fopen("/dev/null","w");
+    if (server.devnull == NULL) {
+        redisLog(REDIS_WARNING, "Can't open /dev/null: %s", server.neterr);
+        exit(1);
+    }
     server.clients = listCreate();
     server.slaves = listCreate();
     server.monitors = listCreate();
@@ -1400,12 +1413,6 @@ static void initServer() {
     aeCreateTimeEvent(server.el, 1, serverCron, NULL, NULL);
     if (aeCreateFileEvent(server.el, server.fd, AE_READABLE,
         acceptHandler, NULL) == AE_ERR) oom("creating file event");
-    if (server.vm_enabled) {
-        /* Listen for events in the threaded I/O pipe */
-        if (aeCreateFileEvent(server.el, server.io_ready_pipe_read, AE_READABLE,
-            vmThreadedIOCompletedJob, NULL) == AE_ERR)
-            oom("creating file event");
-    }
 
     if (server.appendonly) {
         server.appendfd = open(server.appendfilename,O_WRONLY|O_APPEND|O_CREAT,0644);
@@ -2389,6 +2396,7 @@ static robj *createStringObject(char *ptr, size_t len) {
 }
 
 static robj *dupStringObject(robj *o) {
+    assert(o->encoding == REDIS_ENCODING_RAW);
     return createStringObject(o->ptr,sdslen(o->ptr));
 }
 
@@ -2932,20 +2940,16 @@ static int rdbSaveObject(FILE *fp, robj *o) {
  * the rdbSaveObject() function. Currently we use a trick to get
  * this length with very little changes to the code. In the future
  * we could switch to a faster solution. */
-static off_t rdbSavedObjectLen(robj *o) {
-    static FILE *fp = NULL;
-
-    if (fp == NULL) fp = fopen("/dev/null","w");
-    assert(fp != NULL);
-
+static off_t rdbSavedObjectLen(robj *o, FILE *fp) {
+    if (fp == NULL) fp = server.devnull;
     rewind(fp);
     assert(rdbSaveObject(fp,o) != 1);
     return ftello(fp);
 }
 
 /* Return the number of pages required to save this object in the swap file */
-static off_t rdbSavedObjectPages(robj *o) {
-    off_t bytes = rdbSavedObjectLen(o);
+static off_t rdbSavedObjectPages(robj *o, FILE *fp) {
+    off_t bytes = rdbSavedObjectLen(o,fp);
     
     return (bytes+(server.vm_page_size-1))/server.vm_page_size;
 }
@@ -3003,19 +3007,15 @@ static int rdbSave(char *filename) {
                 if (rdbSaveObject(fp,o) == -1) goto werr;
             } else {
                 /* REDIS_VM_SWAPPED or REDIS_VM_LOADING */
-                robj *po, *newkey;
+                robj *po;
                 /* Get a preview of the object in memory */
                 po = vmPreviewObject(key);
-                /* Also duplicate the key object, to pass around a standard
-                 * string object. */
-                newkey = dupStringObject(key);
                 /* Save type, key, value */
                 if (rdbSaveType(fp,key->vtype) == -1) goto werr;
-                if (rdbSaveStringObject(fp,newkey) == -1) goto werr;
+                if (rdbSaveStringObject(fp,key) == -1) goto werr;
                 if (rdbSaveObject(fp,po) == -1) goto werr;
                 /* Remove the loaded object from memory */
                 decrRefCount(po);
-                decrRefCount(newkey);
             }
         }
         dictReleaseIterator(di);
@@ -5597,13 +5597,21 @@ static sds genRedisInfoString(void) {
             "vm_stats_swapped_objects:%llu\r\n"
             "vm_stats_swappin_count:%llu\r\n"
             "vm_stats_swappout_count:%llu\r\n"
+            "vm_stats_io_newjobs_len:%lu\r\n"
+            "vm_stats_io_processing_len:%lu\r\n"
+            "vm_stats_io_processed_len:%lu\r\n"
+            "vm_stats_io_waiting_clients:%lu\r\n"
             ,(unsigned long long) server.vm_max_memory,
             (unsigned long long) server.vm_page_size,
             (unsigned long long) server.vm_pages,
             (unsigned long long) server.vm_stats_used_pages,
             (unsigned long long) server.vm_stats_swapped_objects,
             (unsigned long long) server.vm_stats_swapins,
-            (unsigned long long) server.vm_stats_swapouts
+            (unsigned long long) server.vm_stats_swapouts,
+            (unsigned long) listLength(server.io_newjobs),
+            (unsigned long) listLength(server.io_processing),
+            (unsigned long) listLength(server.io_processed),
+            (unsigned long) listLength(server.io_clients)
         );
     }
     for (j = 0; j < server.dbnum; j++) {
@@ -6636,16 +6644,21 @@ int loadAppendOnlyFile(char *filename) {
 /* Write an object into a file in the bulk format $<count>\r\n<payload>\r\n */
 static int fwriteBulk(FILE *fp, robj *obj) {
     char buf[128];
-    obj = getDecodedObject(obj);
+    int decrrc = 0;
+
+    if (obj->storage == REDIS_VM_MEMORY && obj->encoding != REDIS_ENCODING_RAW){
+        obj = getDecodedObject(obj);
+        decrrc = 1;
+    }
     snprintf(buf,sizeof(buf),"$%ld\r\n",(long)sdslen(obj->ptr));
     if (fwrite(buf,strlen(buf),1,fp) == 0) goto err;
     if (sdslen(obj->ptr) && fwrite(obj->ptr,sdslen(obj->ptr),1,fp) == 0)
         goto err;
     if (fwrite("\r\n",2,1,fp) == 0) goto err;
-    decrRefCount(obj);
+    if (decrrc) decrRefCount(obj);
     return 1;
 err:
-    decrRefCount(obj);
+    if (decrrc) decrRefCount(obj);
     return 0;
 }
 
@@ -6711,13 +6724,16 @@ static int rewriteAppendOnlyFile(char *filename) {
             int swapped;
 
             key = dictGetEntryKey(de);
+            /* If the value for this key is swapped, load a preview in memory.
+             * We use a "swapped" flag to remember if we need to free the
+             * value object instead to just increment the ref count anyway
+             * in order to avoid copy-on-write of pages if we are forked() */
             if (!server.vm_enabled || key->storage == REDIS_VM_MEMORY ||
                 key->storage == REDIS_VM_SWAPPING) {
                 o = dictGetEntryVal(de);
                 swapped = 0;
             } else {
                 o = vmPreviewObject(key);
-                key = dupStringObject(key);
                 swapped = 1;
             }
             expiretime = getExpire(db,key);
@@ -6788,12 +6804,7 @@ static int rewriteAppendOnlyFile(char *filename) {
                 if (fwriteBulk(fp,key) == 0) goto werr;
                 if (fwriteBulkLong(fp,expiretime) == 0) goto werr;
             }
-            /* We created a few temp objects if the key->value pair
-             * was about a swapped out object. Free both. */
-            if (swapped) {
-                decrRefCount(key);
-                decrRefCount(o);
-            }
+            if (swapped) decrRefCount(o);
         }
         dictReleaseIterator(di);
     }
@@ -6959,6 +6970,10 @@ static void vmInit(void) {
     server.io_ready_pipe_read = pipefds[0];
     server.io_ready_pipe_write = pipefds[1];
     redisAssert(anetNonBlock(NULL,server.io_ready_pipe_read) != ANET_ERR);
+    /* Listen for events in the threaded I/O pipe */
+    if (aeCreateFileEvent(server.el, server.io_ready_pipe_read, AE_READABLE,
+        vmThreadedIOCompletedJob, NULL) == AE_ERR)
+        oom("creating file event");
 }
 
 /* Mark the page as used */
@@ -7080,7 +7095,7 @@ static int vmFindContiguousPages(off_t *first, int n) {
  * If we can't find enough contiguous empty pages to swap the object on disk
  * REDIS_ERR is returned. */
 static int vmSwapObjectBlocking(robj *key, robj *val) {
-    off_t pages = rdbSavedObjectPages(val);
+    off_t pages = rdbSavedObjectPages(val,NULL);
     off_t page;
 
     assert(key->storage == REDIS_VM_MEMORY);
@@ -7108,13 +7123,6 @@ static int vmSwapObjectBlocking(robj *key, robj *val) {
     return REDIS_OK;
 }
 
-static int vmSwapObjectThreaded(robj *key, robj *val) {
-
-    key = key;
-    val = val;
-    return REDIS_OK;
-}
-
 /* Load the value object relative to the 'key' object from swap to memory.
  * The newly allocated object is returned.
  *
@@ -7244,6 +7252,7 @@ static int vmSwapOneObject(int usethreads) {
     int j, i;
     struct dictEntry *best = NULL;
     double best_swappability = 0;
+    redisDb *best_db = NULL;
     robj *key, *val;
 
     for (j = 0; j < server.dbnum; j++) {
@@ -7267,6 +7276,7 @@ static int vmSwapOneObject(int usethreads) {
             if (!best || swappability > best_swappability) {
                 best = de;
                 best_swappability = swappability;
+                best_db = db;
             }
         }
     }
@@ -7288,7 +7298,7 @@ static int vmSwapOneObject(int usethreads) {
     }
     /* Swap it */
     if (usethreads) {
-        vmSwapObjectThreaded(key,val);
+        vmSwapObjectThreaded(key,val,best_db);
         return REDIS_OK;
     } else {
         if (vmSwapObjectBlocking(key,val) == REDIS_OK) {
@@ -7330,6 +7340,14 @@ static int deleteIfSwapped(redisDb *db, robj *key) {
 
 /* =================== Virtual Memory - Threaded I/O  ======================= */
 
+static void freeIOJob(iojob *j) {
+    if (j->type == REDIS_IOJOB_PREPARE_SWAP ||
+        j->type == REDIS_IOJOB_DO_SWAP)
+        decrRefCount(j->val);
+    decrRefCount(j->key);
+    zfree(j);
+}
+
 /* Every time a thread finished a Job, it writes a byte into the write side
  * of an unix pipe in order to "awake" the main thread, and this function
  * is called. */
@@ -7345,7 +7363,72 @@ static void vmThreadedIOCompletedJob(aeEventLoop *el, int fd, void *privdata,
     /* For every byte we read in the read side of the pipe, there is one
      * I/O job completed to process. */
     while((retval = read(fd,buf,1)) == 1) {
+        iojob *j;
+        listNode *ln;
+        robj *key;
+        struct dictEntry *de;
+
         redisLog(REDIS_DEBUG,"Processing I/O completed job");
+        assert(listLength(server.io_processed) != 0);
+
+        /* Get the processed element (the oldest one) */
+        lockThreadedIO();
+        ln = listFirst(server.io_processed);
+        j = ln->value;
+        listDelNode(server.io_processed,ln);
+        unlockThreadedIO();
+        /* If this job is marked as canceled, just ignore it */
+        if (j->canceled) {
+            freeIOJob(j);
+            continue;
+        }
+        /* Post process it in the main thread, as there are things we
+         * can do just here to avoid race conditions and/or invasive locks */
+        de = dictFind(j->db->dict,j->key);
+        assert(de != NULL);
+        key = dictGetEntryKey(de);
+        if (j->type == REDIS_IOJOB_LOAD) {
+            /* Key loaded, bring it at home */
+            key->storage = REDIS_VM_MEMORY;
+            key->vm.atime = server.unixtime;
+            vmMarkPagesFree(key->vm.page,key->vm.usedpages);
+            redisLog(REDIS_DEBUG, "VM: object %s loaded from disk (threaded)",
+                (unsigned char*) key->ptr);
+            server.vm_stats_swapped_objects--;
+            server.vm_stats_swapins++;
+            freeIOJob(j);
+        } else if (j->type == REDIS_IOJOB_PREPARE_SWAP) {
+            /* Now we know the amount of pages required to swap this object.
+             * Let's find some space for it, and queue this task again
+             * rebranded as REDIS_IOJOB_DO_SWAP. */
+            if (vmFindContiguousPages(&j->page,j->pages) == REDIS_ERR) {
+                /* Ooops... no space! */
+                freeIOJob(j);
+            } else {
+                j->type = REDIS_IOJOB_DO_SWAP;
+                lockThreadedIO();
+                queueIOJob(j);
+                unlockThreadedIO();
+            }
+        } else if (j->type == REDIS_IOJOB_DO_SWAP) {
+            robj *val;
+
+            /* Key swapped. We can finally free some memory. */
+            val = dictGetEntryVal(de);
+            key->vm.page = j->page;
+            key->vm.usedpages = j->pages;
+            key->storage = REDIS_VM_SWAPPED;
+            key->vtype = j->val->type;
+            decrRefCount(val); /* Deallocate the object from memory. */
+            vmMarkPagesUsed(j->page,j->pages);
+            redisLog(REDIS_DEBUG,
+                "VM: object %s swapped out at %lld (%lld pages) (threaded)",
+                (unsigned char*) key->ptr,
+                (unsigned long long) j->page, (unsigned long long) j->pages);
+            server.vm_stats_swapped_objects++;
+            server.vm_stats_swapouts++;
+            freeIOJob(j);
+        }
     }
     if (retval < 0 && errno != EAGAIN) {
         redisLog(REDIS_WARNING,
@@ -7386,7 +7469,8 @@ static void vmCancelThreadedIOJob(robj *o) {
                     /* If the job was not yet processed the best thing to do
                      * is to remove it from the queue at all */
                     decrRefCount(job->key);
-                    if (job->type == REDIS_IOJOB_SWAP)
+                    if (job->type == REDIS_IOJOB_PREPARE_SWAP ||
+                        job->type == REDIS_IOJOB_DO_SWAP)
                         decrRefCount(job->val);
                     listDelNode(lists[i],ln);
                     zfree(job);
@@ -7409,6 +7493,92 @@ static void vmCancelThreadedIOJob(robj *o) {
     assert(1 != 1); /* We should never reach this */
 }
 
+static void *IOThreadEntryPoint(void *arg) {
+    iojob *j;
+    listNode *ln;
+    REDIS_NOTUSED(arg);
+
+    pthread_detach(pthread_self());
+    while(1) {
+        /* Get a new job to process */
+        lockThreadedIO();
+        if (listLength(server.io_newjobs) == 0) {
+            /* No new jobs in queue, exit. */
+            printf("Thread %lld exiting, nothing to do\n",
+                (long long) pthread_self());
+            server.io_active_threads--;
+            unlockThreadedIO();
+            return NULL;
+        }
+        ln = listFirst(server.io_newjobs);
+        j = ln->value;
+        listDelNode(server.io_newjobs,ln);
+        /* Add the job in the processing queue */
+        j->thread = pthread_self();
+        listAddNodeTail(server.io_processing,j);
+        ln = listLast(server.io_processing); /* We use ln later to remove it */
+        unlockThreadedIO();
+        printf("Thread %lld got a new job: %p about key '%s'\n",
+            (long long) pthread_self(), (void*)j, (char*)j->key->ptr);
+
+        /* Process the Job */
+        if (j->type == REDIS_IOJOB_LOAD) {
+        } else if (j->type == REDIS_IOJOB_PREPARE_SWAP) {
+            FILE *fp = fopen("/dev/null","w+");
+            j->pages = rdbSavedObjectPages(j->val,fp);
+            fclose(fp);
+        } else if (j->type == REDIS_IOJOB_DO_SWAP) {
+        }
+
+        /* Done: insert the job into the processed queue */
+        printf("Thread %lld completed the job: %p\n",
+            (long long) pthread_self(), (void*)j);
+        lockThreadedIO();
+        listDelNode(server.io_processing,ln);
+        listAddNodeTail(server.io_processed,j);
+        unlockThreadedIO();
+        
+        /* Signal the main thread there is new stuff to process */
+        assert(write(server.io_ready_pipe_write,"x",1) == 1);
+    }
+    return NULL; /* never reached */
+}
+
+static void spawnIOThread(void) {
+    pthread_t thread;
+
+    pthread_create(&thread,NULL,IOThreadEntryPoint,NULL);
+    server.io_active_threads++;
+}
+
+/* This function must be called while with threaded IO locked */
+static void queueIOJob(iojob *j) {
+    listAddNodeTail(server.io_newjobs,j);
+    if (server.io_active_threads < server.vm_max_threads)
+        spawnIOThread();
+}
+
+static int vmSwapObjectThreaded(robj *key, robj *val, redisDb *db) {
+    iojob *j;
+    
+    assert(key->storage == REDIS_VM_MEMORY);
+    assert(key->refcount == 1);
+
+    j = zmalloc(sizeof(*j));
+    j->type = REDIS_IOJOB_PREPARE_SWAP;
+    j->db = db;
+    j->key = dupStringObject(key);
+    j->val = val;
+    incrRefCount(val);
+    j->canceled = 0;
+    j->thread = (pthread_t) -1;
+
+    lockThreadedIO();
+    queueIOJob(j);
+    unlockThreadedIO();
+    return REDIS_OK;
+}
+
 /* ================================= Debugging ============================== */
 
 static void debugCommand(redisClient *c) {
@@ -7444,12 +7614,13 @@ static void debugCommand(redisClient *c) {
         }
         key = dictGetEntryKey(de);
         val = dictGetEntryVal(de);
-        if (server.vm_enabled && key->storage == REDIS_VM_MEMORY) {
+        if (server.vm_enabled && (key->storage == REDIS_VM_MEMORY ||
+                                  key->storage == REDIS_VM_SWAPPING)) {
             addReplySds(c,sdscatprintf(sdsempty(),
                 "+Key at:%p refcount:%d, value at:%p refcount:%d "
                 "encoding:%d serializedlength:%lld\r\n",
                 (void*)key, key->refcount, (void*)val, val->refcount,
-                val->encoding, rdbSavedObjectLen(val)));
+                val->encoding, rdbSavedObjectLen(val,NULL)));
         } else {
             addReplySds(c,sdscatprintf(sdsempty(),
                 "+Key at:%p refcount:%d, value swapped at: page %llu "