@@ -482,6 +482,7 @@ int rdbSave(char *filename) {
 
 int rdbSaveBackground(char *filename) {
     pid_t childpid;
+    long long start;
 
     if (server.bgsavechildpid != -1 ||
         server.bgsavethread != (pthread_t) -1) return REDIS_ERR;
@@ -493,6 +494,7 @@ int rdbSaveBackground(char *filename) {
         return dsRdbSaveBackground(filename);
     }
 
+    start = ustime();
     if ((childpid = fork()) == 0) {
         int retval;
 
@@ -503,6 +505,7 @@ int rdbSaveBackground(char *filename) {
         _exit((retval == REDIS_OK) ? 0 : 1);
     } else {
         /* Parent */
+        server.stat_fork_time = ustime()-start;
         if (childpid == -1) {
             redisLog(REDIS_WARNING,"Can't save in background: fork: %s",
                 strerror(errno));