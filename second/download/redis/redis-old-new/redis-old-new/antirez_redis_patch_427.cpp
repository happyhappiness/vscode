@@ -116,7 +116,7 @@ void bioInit(void) {
     for (j = 0; j < REDIS_BIO_NUM_OPS; j++) {
         void *arg = (void*)(unsigned long) j;
         if (pthread_create(&thread,&attr,bioProcessBackgroundJobs,arg) != 0) {
-            serverLog(REDIS_WARNING,"Fatal: Can't initialize Background Jobs.");
+            serverLog(LL_WARNING,"Fatal: Can't initialize Background Jobs.");
             exit(1);
         }
         bio_threads[j] = thread;
@@ -144,7 +144,7 @@ void *bioProcessBackgroundJobs(void *arg) {
 
     /* Check that the type is within the right interval. */
     if (type >= REDIS_BIO_NUM_OPS) {
-        serverLog(REDIS_WARNING,
+        serverLog(LL_WARNING,
             "Warning: bio thread started with wrong type %lu",type);
         return NULL;
     }
@@ -160,7 +160,7 @@ void *bioProcessBackgroundJobs(void *arg) {
     sigemptyset(&sigset);
     sigaddset(&sigset, SIGALRM);
     if (pthread_sigmask(SIG_BLOCK, &sigset, NULL))
-        serverLog(REDIS_WARNING,
+        serverLog(LL_WARNING,
             "Warning: can't mask SIGALRM in bio.c thread: %s", strerror(errno));
 
     while(1) {
@@ -184,7 +184,7 @@ void *bioProcessBackgroundJobs(void *arg) {
         } else if (type == REDIS_BIO_AOF_FSYNC) {
             aof_fsync((long)job->arg1);
         } else {
-            redisPanic("Wrong job type in bioProcessBackgroundJobs().");
+            serverPanic("Wrong job type in bioProcessBackgroundJobs().");
         }
         zfree(job);
 
@@ -215,11 +215,11 @@ void bioKillThreads(void) {
     for (j = 0; j < REDIS_BIO_NUM_OPS; j++) {
         if (pthread_cancel(bio_threads[j]) == 0) {
             if ((err = pthread_join(bio_threads[j],NULL)) != 0) {
-                serverLog(REDIS_WARNING,
+                serverLog(LL_WARNING,
                     "Bio thread for job type #%d can be joined: %s",
                         j, strerror(err));
             } else {
-                serverLog(REDIS_WARNING,
+                serverLog(LL_WARNING,
                     "Bio thread for job type #%d terminated",j);
             }
         }