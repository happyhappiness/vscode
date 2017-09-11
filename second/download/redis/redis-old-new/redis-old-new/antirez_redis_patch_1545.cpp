@@ -100,7 +100,6 @@ void *bioProcessBackgroundJobs(void *arg) {
 
         /* Process the job accordingly to its type. */
         if (job->type == REDIS_BIO_CLOSE_FILE) {
-            printf("Closing file...\n");
             close((long)job->data);
         } else {
             redisPanic("Wrong job type in bioProcessBackgroundJobs().");