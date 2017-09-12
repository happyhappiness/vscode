@@ -2419,6 +2419,10 @@ static robj *createObject(int type, void *ptr) {
     o->ptr = ptr;
     o->refcount = 1;
     if (server.vm_enabled) {
+        /* Note that this code may run in the context of an I/O thread
+         * and accessing to server.unixtime in theory is an error
+         * (no locks). But in practice this is safe, and even if we read
+         * garbage Redis will not fail, as it's just a statistical info */
         o->vm.atime = server.unixtime;
         o->storage = REDIS_VM_MEMORY;
     }
@@ -5631,6 +5635,7 @@ static sds genRedisInfoString(void) {
         );
     }
     if (server.vm_enabled) {
+        lockThreadedIO();
         info = sdscatprintf(info,
             "vm_conf_max_memory:%llu\r\n"
             "vm_conf_page_size:%llu\r\n"
@@ -5657,6 +5662,7 @@ static sds genRedisInfoString(void) {
             (unsigned long) listLength(server.io_clients),
             (unsigned long) server.io_active_threads
         );
+        unlockThreadedIO();
     }
     for (j = 0; j < server.dbnum; j++) {
         long long keys, vkeys;
@@ -7355,7 +7361,14 @@ static int vmSwapOneObject(int usethreads) {
             de = dictGetRandomKey(db->dict);
             key = dictGetEntryKey(de);
             val = dictGetEntryVal(de);
-            if (key->storage != REDIS_VM_MEMORY) {
+            /* Only swap objects that are currently in memory.
+             *
+             * Also don't swap shared objects if threaded VM is on, as we
+             * try to ensure that the main thread does not touch the
+             * object while the I/O thread is using it, but we can't
+             * control other keys without adding additional mutex. */
+            if (key->storage != REDIS_VM_MEMORY ||
+                (server.vm_max_threads != 0 && val->refcount != 1)) {
                 if (maxtries) i--; /* don't count this try */
                 continue;
             }
@@ -7457,10 +7470,10 @@ static void vmThreadedIOCompletedJob(aeEventLoop *el, int fd, void *privdata,
         struct dictEntry *de;
 
         redisLog(REDIS_DEBUG,"Processing I/O completed job");
-        assert(listLength(server.io_processed) != 0);
 
         /* Get the processed element (the oldest one) */
         lockThreadedIO();
+        assert(listLength(server.io_processed) != 0);
         ln = listFirst(server.io_processed);
         j = ln->value;
         listDelNode(server.io_processed,ln);