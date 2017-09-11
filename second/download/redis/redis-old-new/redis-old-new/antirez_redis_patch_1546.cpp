@@ -85,7 +85,7 @@ void *bioProcessBackgroundJobs(void *arg) {
         listNode *ln;
 
         /* The loop always starts with the lock hold. */
-        if (listLength(server.io_newjobs) == 0) {
+        if (listLength(bio_jobs) == 0) {
             pthread_cond_wait(&bio_condvar,&bio_mutex);
             continue;
         }
@@ -99,6 +99,7 @@ void *bioProcessBackgroundJobs(void *arg) {
 
         /* Process the job accordingly to its type. */
         if (job->type == REDIS_BIO_CLOSE_FILE) {
+            printf("Closing file...\n");
             close((long)job->data);
         } else {
             redisPanic("Wrong job type in bioProcessBackgroundJobs().");