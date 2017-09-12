@@ -1085,11 +1085,7 @@ int prepareForShutdown() {
         if (server.vm_enabled) unlink(server.vm_swap_file);
     } else {
         /* Snapshotting. Perform a SYNC SAVE and exit */
-        if (rdbSave(server.dbfilename) == REDIS_OK) {
-            if (server.daemonize)
-                unlink(server.pidfile);
-            redisLog(REDIS_WARNING,"%zu bytes used at exit",zmalloc_used_memory());
-        } else {
+        if (rdbSave(server.dbfilename) != REDIS_OK) {
             /* Ooops.. error saving! The best we can do is to continue
              * operating. Note that if there was a background saving process,
              * in the next cron() Redis will be notified that the background
@@ -1099,6 +1095,7 @@ int prepareForShutdown() {
             return REDIS_ERR;
         }
     }
+    if (server.daemonize) unlink(server.pidfile);
     redisLog(REDIS_WARNING,"Server exit now, bye bye...");
     return REDIS_OK;
 }
@@ -1371,9 +1368,17 @@ void linuxOvercommitMemoryWarning(void) {
 }
 #endif /* __linux__ */
 
+void createPidFile(void) {
+    /* Try to write the pid file in a best-effort way. */
+    FILE *fp = fopen(server.pidfile,"w");
+    if (fp) {
+        fprintf(fp,"%d\n",getpid());
+        fclose(fp);
+    }
+}
+
 void daemonize(void) {
     int fd;
-    FILE *fp;
 
     if (fork() != 0) exit(0); /* parent exits */
     setsid(); /* create a new session */
@@ -1387,12 +1392,6 @@ void daemonize(void) {
         dup2(fd, STDERR_FILENO);
         if (fd > STDERR_FILENO) close(fd);
     }
-    /* Try to write the pid file */
-    fp = fopen(server.pidfile,"w");
-    if (fp) {
-        fprintf(fp,"%d\n",getpid());
-        fclose(fp);
-    }
 }
 
 void version() {
@@ -1425,6 +1424,7 @@ int main(int argc, char **argv) {
     }
     if (server.daemonize) daemonize();
     initServer();
+    if (server.daemonize) createPidFile();
     redisLog(REDIS_NOTICE,"Server started, Redis version " REDIS_VERSION);
 #ifdef __linux__
     linuxOvercommitMemoryWarning();
@@ -1501,6 +1501,7 @@ void segvHandler(int sig, siginfo_t *info, void *secret) {
         redisLog(REDIS_WARNING,"%s", messages[i]);
 
     /* free(messages); Don't call free() with possibly corrupted memory. */
+    if (server.daemonize) unlink(server.pidfile);
     _exit(0);
 }
 