@@ -7385,10 +7385,6 @@ static void vmThreadedIOCompletedJob(aeEventLoop *el, int fd, void *privdata,
         /* Post process it in the main thread, as there are things we
          * can do just here to avoid race conditions and/or invasive locks */
         redisLog(REDIS_DEBUG,"Job type: %d, key at %p (%s) refcount: %d\n", j->type, (void*)j->key, (char*)j->key->ptr, j->key->refcount);
-        if (j->key->refcount <= 0) {
-            printf("Ooops ref count is <= 0!\n");
-            exit(1);
-        }
         de = dictFind(j->db->dict,j->key);
         assert(de != NULL);
         key = dictGetEntryKey(de);
@@ -7523,7 +7519,7 @@ static void *IOThreadEntryPoint(void *arg) {
         lockThreadedIO();
         if (listLength(server.io_newjobs) == 0) {
             /* No new jobs in queue, exit. */
-            printf("Thread %lld exiting, nothing to do\n",
+            redisLog(REDIS_DEBUG,"Thread %lld exiting, nothing to do\n",
                 (long long) pthread_self());
             server.io_active_threads--;
             unlockThreadedIO();
@@ -7537,7 +7533,7 @@ static void *IOThreadEntryPoint(void *arg) {
         listAddNodeTail(server.io_processing,j);
         ln = listLast(server.io_processing); /* We use ln later to remove it */
         unlockThreadedIO();
-        printf("Thread %lld got a new job: %p about key '%s'\n",
+        redisLog(REDIS_DEBUG,"Thread %lld got a new job: %p about key '%s'\n",
             (long long) pthread_self(), (void*)j, (char*)j->key->ptr);
 
         /* Process the Job */
@@ -7550,7 +7546,7 @@ static void *IOThreadEntryPoint(void *arg) {
         }
 
         /* Done: insert the job into the processed queue */
-        printf("Thread %lld completed the job: %p\n",
+        redisLog(REDIS_DEBUG,"Thread %lld completed the job: %p\n",
             (long long) pthread_self(), (void*)j);
         lockThreadedIO();
         listDelNode(server.io_processing,ln);
@@ -7721,7 +7717,6 @@ static void daemonize(void) {
     FILE *fp;
 
     if (fork() != 0) exit(0); /* parent exits */
-    printf("New pid: %d\n", getpid());
     setsid(); /* create a new session */
 
     /* Every output goes to /dev/null. If Redis is daemonized but