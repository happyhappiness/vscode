@@ -61,17 +61,17 @@
 #include "server.h"
 #include "bio.h"
 
-static pthread_t bio_threads[REDIS_BIO_NUM_OPS];
-static pthread_mutex_t bio_mutex[REDIS_BIO_NUM_OPS];
-static pthread_cond_t bio_condvar[REDIS_BIO_NUM_OPS];
-static list *bio_jobs[REDIS_BIO_NUM_OPS];
+static pthread_t bio_threads[BIO_NUM_OPS];
+static pthread_mutex_t bio_mutex[BIO_NUM_OPS];
+static pthread_cond_t bio_condvar[BIO_NUM_OPS];
+static list *bio_jobs[BIO_NUM_OPS];
 /* The following array is used to hold the number of pending jobs for every
  * OP type. This allows us to export the bioPendingJobsOfType() API that is
  * useful when the main thread wants to perform some operation that may involve
  * objects shared with the background thread. The main thread will just wait
  * that there are no longer jobs of this type to be executed before performing
  * the sensible operation. This data is also useful for reporting. */
-static unsigned long long bio_pending[REDIS_BIO_NUM_OPS];
+static unsigned long long bio_pending[BIO_NUM_OPS];
 
 /* This structure represents a background Job. It is only used locally to this
  * file as the API does not expose the internals at all. */
@@ -96,7 +96,7 @@ void bioInit(void) {
     int j;
 
     /* Initialization of state vars and objects */
-    for (j = 0; j < REDIS_BIO_NUM_OPS; j++) {
+    for (j = 0; j < BIO_NUM_OPS; j++) {
         pthread_mutex_init(&bio_mutex[j],NULL);
         pthread_cond_init(&bio_condvar[j],NULL);
         bio_jobs[j] = listCreate();
@@ -113,7 +113,7 @@ void bioInit(void) {
     /* Ready to spawn our threads. We use the single argument the thread
      * function accepts in order to pass the job ID the thread is
      * responsible of. */
-    for (j = 0; j < REDIS_BIO_NUM_OPS; j++) {
+    for (j = 0; j < BIO_NUM_OPS; j++) {
         void *arg = (void*)(unsigned long) j;
         if (pthread_create(&thread,&attr,bioProcessBackgroundJobs,arg) != 0) {
             serverLog(LL_WARNING,"Fatal: Can't initialize Background Jobs.");
@@ -143,7 +143,7 @@ void *bioProcessBackgroundJobs(void *arg) {
     sigset_t sigset;
 
     /* Check that the type is within the right interval. */
-    if (type >= REDIS_BIO_NUM_OPS) {
+    if (type >= BIO_NUM_OPS) {
         serverLog(LL_WARNING,
             "Warning: bio thread started with wrong type %lu",type);
         return NULL;
@@ -179,9 +179,9 @@ void *bioProcessBackgroundJobs(void *arg) {
         pthread_mutex_unlock(&bio_mutex[type]);
 
         /* Process the job accordingly to its type. */
-        if (type == REDIS_BIO_CLOSE_FILE) {
+        if (type == BIO_CLOSE_FILE) {
             close((long)job->arg1);
-        } else if (type == REDIS_BIO_AOF_FSYNC) {
+        } else if (type == BIO_AOF_FSYNC) {
             aof_fsync((long)job->arg1);
         } else {
             serverPanic("Wrong job type in bioProcessBackgroundJobs().");
@@ -212,7 +212,7 @@ unsigned long long bioPendingJobsOfType(int type) {
 void bioKillThreads(void) {
     int err, j;
 
-    for (j = 0; j < REDIS_BIO_NUM_OPS; j++) {
+    for (j = 0; j < BIO_NUM_OPS; j++) {
         if (pthread_cancel(bio_threads[j]) == 0) {
             if ((err = pthread_join(bio_threads[j],NULL)) != 0) {
                 serverLog(LL_WARNING,