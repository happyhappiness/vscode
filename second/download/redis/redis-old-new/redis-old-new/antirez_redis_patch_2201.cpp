@@ -7406,7 +7406,7 @@ static int vmWriteObjectOnSwap(robj *o, off_t page) {
     if (fseeko(server.vm_fp,page*server.vm_page_size,SEEK_SET) == -1) {
         if (server.vm_enabled) pthread_mutex_unlock(&server.io_swapfile_mutex);
         redisLog(REDIS_WARNING,
-            "Critical VM problem in vmSwapObjectBlocking(): can't seek: %s",
+            "Critical VM problem in vmWriteObjectOnSwap(): can't seek: %s",
             strerror(errno));
         return REDIS_ERR;
     }
@@ -7922,8 +7922,8 @@ static void *IOThreadEntryPoint(void *arg) {
         lockThreadedIO();
         if (listLength(server.io_newjobs) == 0) {
             /* No new jobs in queue, exit. */
-            redisLog(REDIS_DEBUG,"Thread %lld exiting, nothing to do",
-                (long long) pthread_self());
+            redisLog(REDIS_DEBUG,"Thread %ld exiting, nothing to do",
+                (long) pthread_self());
             server.io_active_threads--;
             unlockThreadedIO();
             return NULL;
@@ -7936,8 +7936,8 @@ static void *IOThreadEntryPoint(void *arg) {
         listAddNodeTail(server.io_processing,j);
         ln = listLast(server.io_processing); /* We use ln later to remove it */
         unlockThreadedIO();
-        redisLog(REDIS_DEBUG,"Thread %lld got a new job (type %d): %p about key '%s'",
-            (long long) pthread_self(), j->type, (void*)j, (char*)j->key->ptr);
+        redisLog(REDIS_DEBUG,"Thread %ld got a new job (type %d): %p about key '%s'",
+            (long) pthread_self(), j->type, (void*)j, (char*)j->key->ptr);
 
         /* Process the Job */
         if (j->type == REDIS_IOJOB_LOAD) {
@@ -7952,8 +7952,8 @@ static void *IOThreadEntryPoint(void *arg) {
         }
 
         /* Done: insert the job into the processed queue */
-        redisLog(REDIS_DEBUG,"Thread %lld completed the job: %p (key %s)",
-            (long long) pthread_self(), (void*)j, (char*)j->key->ptr);
+        redisLog(REDIS_DEBUG,"Thread %ld completed the job: %p (key %s)",
+            (long) pthread_self(), (void*)j, (char*)j->key->ptr);
         lockThreadedIO();
         listDelNode(server.io_processing,ln);
         listAddNodeTail(server.io_processed,j);