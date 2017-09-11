@@ -61,6 +61,7 @@
 #include "redis.h"
 #include "bio.h"
 
+static pthread_t bio_threads[REDIS_BIO_NUM_OPS];
 static pthread_mutex_t bio_mutex[REDIS_BIO_NUM_OPS];
 static pthread_cond_t bio_condvar[REDIS_BIO_NUM_OPS];
 static list *bio_jobs[REDIS_BIO_NUM_OPS];
@@ -118,6 +119,7 @@ void bioInit(void) {
             redisLog(REDIS_WARNING,"Fatal: Can't initialize Background Jobs.");
             exit(1);
         }
+        bio_threads[j] = thread;
     }
 }
 
@@ -140,7 +142,11 @@ void *bioProcessBackgroundJobs(void *arg) {
     unsigned long type = (unsigned long) arg;
     sigset_t sigset;
 
-    pthread_detach(pthread_self());
+    /* Make the thread killable at any time, so that bioKillThreads()
+     * can work reliably. */
+    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
+    pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
+
     pthread_mutex_lock(&bio_mutex[type]);
     /* Block SIGALRM so we are sure that only the main thread will
      * receive the watchdog signal. */
@@ -192,56 +198,23 @@ unsigned long long bioPendingJobsOfType(int type) {
     return val;
 }
 
-#if 0 /* We don't use the following code for now, and bioWaitPendingJobsLE
-         probably needs a rewrite using conditional variables instead of the
-         current implementation. */
-         
-
-/* Wait until the number of pending jobs of the specified type are
- * less or equal to the specified number.
- *
- * This function may block for long time, it should only be used to perform
- * the following tasks:
- *
- * 1) To avoid that the main thread is pushing jobs of a given time so fast
- *    that the background thread can't process them at the same speed.
- *    So before creating a new job of a given type the main thread should
- *    call something like: bioWaitPendingJobsLE(job_type,10000);
- * 2) In order to perform special operations that make it necessary to be sure
- *    no one is touching shared resourced in the background.
- */
-void bioWaitPendingJobsLE(int type, unsigned long long num) {
-    unsigned long long iteration = 0;
+/* Kill the running bio threads in an unclean way. This function should be
+ * used only when it's critical to stop the threads for some reason.
+ * Currently Redis does this only on crash (for instance on SIGSEGV) in order
+ * to perform a fast memory check without other threads messing with memory. */
+void bioKillThreads(void) {
+    int err, j;
 
-    /* We poll the jobs queue aggressively to start, and gradually relax
-     * the polling speed if it is going to take too much time. */
-    while(1) {
-        iteration++;
-        if (iteration > 1000 && iteration <= 10000) {
-            usleep(100);
-        } else if (iteration > 10000) {
-            usleep(1000);
+    for (j = 0; j < REDIS_BIO_NUM_OPS; j++) {
+        if (pthread_cancel(bio_threads[j]) == 0) {
+            if ((err = pthread_join(bio_threads[j],NULL)) != 0) {
+                redisLog(REDIS_WARNING,
+                    "Bio thread for job type #%d can be joined: %s",
+                        j, strerror(err));
+            } else {
+                redisLog(REDIS_WARNING,
+                    "Bio thread for job type #%d terminated",j);
+            }
         }
-        if (bioPendingJobsOfType(type) <= num) break;
-    }
-}
-
-/* Return the older job of the specified type. */
-time_t bioOlderJobOfType(int type) {
-    time_t time;
-    listNode *ln;
-    struct bio_job *job;
-
-    pthread_mutex_lock(&bio_mutex[type]);
-    ln = listFirst(bio_jobs[type]);
-    if (ln == NULL) {
-        pthread_mutex_unlock(&bio_mutex[type]);
-        return 0;
     }
-    job = ln->value;
-    time = job->time;
-    pthread_mutex_unlock(&bio_mutex[type]);
-    return time;
 }
-
-#endif