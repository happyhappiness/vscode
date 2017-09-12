@@ -7384,6 +7384,11 @@ static void vmThreadedIOCompletedJob(aeEventLoop *el, int fd, void *privdata,
         }
         /* Post process it in the main thread, as there are things we
          * can do just here to avoid race conditions and/or invasive locks */
+        redisLog(REDIS_DEBUG,"Job type: %d, key at %p (%s) refcount: %d\n", j->type, (void*)j->key, (char*)j->key->ptr, j->key->refcount);
+        if (j->key->refcount <= 0) {
+            printf("Ooops ref count is <= 0!\n");
+            exit(1);
+        }
         de = dictFind(j->db->dict,j->key);
         assert(de != NULL);
         key = dictGetEntryKey(de);
@@ -7420,6 +7425,7 @@ static void vmThreadedIOCompletedJob(aeEventLoop *el, int fd, void *privdata,
             key->storage = REDIS_VM_SWAPPED;
             key->vtype = j->val->type;
             decrRefCount(val); /* Deallocate the object from memory. */
+            dictGetEntryVal(de) = NULL;
             vmMarkPagesUsed(j->page,j->pages);
             redisLog(REDIS_DEBUG,
                 "VM: object %s swapped out at %lld (%lld pages) (threaded)",
@@ -7428,6 +7434,19 @@ static void vmThreadedIOCompletedJob(aeEventLoop *el, int fd, void *privdata,
             server.vm_stats_swapped_objects++;
             server.vm_stats_swapouts++;
             freeIOJob(j);
+            /* Put a few more swap requests in queue if we are still
+             * out of memory */
+            if (zmalloc_used_memory() > server.vm_max_memory) {
+                int more = 1;
+                while(more) {
+                    lockThreadedIO();
+                    more = listLength(server.io_newjobs) <
+                            (unsigned) server.vm_max_threads;
+                    unlockThreadedIO();
+                    /* Don't waste CPU time if swappable objects are rare. */
+                    if (vmSwapOneObjectThreaded() == REDIS_ERR) break;
+                }
+            }
         }
     }
     if (retval < 0 && errno != EAGAIN) {
@@ -7572,6 +7591,7 @@ static int vmSwapObjectThreaded(robj *key, robj *val, redisDb *db) {
     incrRefCount(val);
     j->canceled = 0;
     j->thread = (pthread_t) -1;
+    key->storage = REDIS_VM_SWAPPING;
 
     lockThreadedIO();
     queueIOJob(j);