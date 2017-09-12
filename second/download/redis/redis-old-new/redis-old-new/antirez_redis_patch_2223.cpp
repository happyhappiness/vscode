@@ -216,8 +216,8 @@
 #define APPENDFSYNC_EVERYSEC 2
 
 /* We can print the stacktrace, so our assert is defined this way: */
-#define redisAssert(_e) ((_e)?(void)0 : (_redisAssert(#_e),exit(1)))
-static void _redisAssert(char *estr);
+#define redisAssert(_e) ((_e)?(void)0 : (_redisAssert(#_e,__FILE__,__LINE__),exit(1)))
+static void _redisAssert(char *estr, char *file, int line);
 
 /*================================= Data types ============================== */
 
@@ -7418,7 +7418,7 @@ static void vmThreadedIOCompletedJob(aeEventLoop *el, int fd, void *privdata,
         }
         /* Post process it in the main thread, as there are things we
          * can do just here to avoid race conditions and/or invasive locks */
-        redisLog(REDIS_DEBUG,"Job type: %d, key at %p (%s) refcount: %d\n", j->type, (void*)j->key, (char*)j->key->ptr, j->key->refcount);
+        redisLog(REDIS_DEBUG,"Job %p type: %d, key at %p (%s) refcount: %d\n", (void*) j, j->type, (void*)j->key, (char*)j->key->ptr, j->key->refcount);
         de = dictFind(j->db->dict,j->key);
         assert(de != NULL);
         key = dictGetEntryKey(de);
@@ -7449,6 +7449,15 @@ static void vmThreadedIOCompletedJob(aeEventLoop *el, int fd, void *privdata,
             robj *val;
 
             /* Key swapped. We can finally free some memory. */
+            if (key->storage != REDIS_VM_SWAPPING) {
+                printf("key->storage: %d\n",key->storage);
+                printf("key->name: %s\n",(char*)key->ptr);
+                printf("key->refcount: %d\n",key->refcount);
+                printf("val: %p\n",(void*)j->val);
+                printf("val->type: %d\n",j->val->type);
+                printf("val->ptr: %s\n",(char*)j->val->ptr);
+            }
+            redisAssert(key->storage == REDIS_VM_SWAPPING);
             val = dictGetEntryVal(de);
             key->vm.page = j->page;
             key->vm.usedpages = j->pages;
@@ -7499,7 +7508,9 @@ static void unlockThreadedIO(void) {
  * processed, otherwise make sure to flag it as canceled. */
 static void vmCancelThreadedIOJob(robj *o) {
     list *lists[3] = {
-        server.io_newjobs, server.io_processing, server.io_processed
+        server.io_newjobs,      /* 0 */
+        server.io_processing,   /* 1 */
+        server.io_processed     /* 2 */
     };
     int i;
 
@@ -7513,17 +7524,16 @@ static void vmCancelThreadedIOJob(robj *o) {
         while ((ln = listYield(lists[i])) != NULL) {
             iojob *job = ln->value;
 
+            if (job->canceled) continue; /* Skip this, already canceled. */
             if (compareStringObjects(job->key,o) == 0) {
+                redisLog(REDIS_DEBUG,"*** CANCELED %p (%s)\n",
+                    (void*)job, (char*)o->ptr);
                 switch(i) {
                 case 0: /* io_newjobs */
-                    /* If the job was not yet processed the best thing to do
+                    /* If the job was yet not processed the best thing to do
                      * is to remove it from the queue at all */
-                    decrRefCount(job->key);
-                    if (job->type == REDIS_IOJOB_PREPARE_SWAP ||
-                        job->type == REDIS_IOJOB_DO_SWAP)
-                        decrRefCount(job->val);
+                    freeIOJob(job);
                     listDelNode(lists[i],ln);
-                    zfree(job);
                     break;
                 case 1: /* io_processing */
                 case 2: /* io_processed */
@@ -7568,8 +7578,8 @@ static void *IOThreadEntryPoint(void *arg) {
         listAddNodeTail(server.io_processing,j);
         ln = listLast(server.io_processing); /* We use ln later to remove it */
         unlockThreadedIO();
-        redisLog(REDIS_DEBUG,"Thread %lld got a new job: %p about key '%s'\n",
-            (long long) pthread_self(), (void*)j, (char*)j->key->ptr);
+        redisLog(REDIS_DEBUG,"Thread %lld got a new job (type %d): %p about key '%s'\n",
+            (long long) pthread_self(), j->type, (void*)j, (char*)j->key->ptr);
 
         /* Process the Job */
         if (j->type == REDIS_IOJOB_LOAD) {
@@ -7583,8 +7593,8 @@ static void *IOThreadEntryPoint(void *arg) {
         }
 
         /* Done: insert the job into the processed queue */
-        redisLog(REDIS_DEBUG,"Thread %lld completed the job: %p\n",
-            (long long) pthread_self(), (void*)j);
+        redisLog(REDIS_DEBUG,"Thread %lld completed the job: %p (key %s)\n",
+            (long long) pthread_self(), (void*)j, (char*)j->key->ptr);
         lockThreadedIO();
         listDelNode(server.io_processing,ln);
         listAddNodeTail(server.io_processed,j);
@@ -7605,6 +7615,8 @@ static void spawnIOThread(void) {
 
 /* This function must be called while with threaded IO locked */
 static void queueIOJob(iojob *j) {
+    redisLog(REDIS_DEBUG,"Queued IO Job %p type %d about key '%s'\n",
+        (void*)j, j->type, (char*)j->key->ptr);
     listAddNodeTail(server.io_newjobs,j);
     if (server.io_active_threads < server.vm_max_threads)
         spawnIOThread();
@@ -7716,9 +7728,9 @@ static void debugCommand(redisClient *c) {
     }
 }
 
-static void _redisAssert(char *estr) {
+static void _redisAssert(char *estr, char *file, int line) {
     redisLog(REDIS_WARNING,"=== ASSERTION FAILED ===");
-    redisLog(REDIS_WARNING,"==> %s\n",estr);
+    redisLog(REDIS_WARNING,"==> %s:%d '%s' is not true\n",file,line,estr);
 #ifdef HAVE_BACKTRACE
     redisLog(REDIS_WARNING,"(forcing SIGSEGV in order to print the stack trace)");
     *((char*)-1) = 'x';