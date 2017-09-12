@@ -221,7 +221,7 @@
 #define APPENDFSYNC_EVERYSEC 2
 
 /* We can print the stacktrace, so our assert is defined this way: */
-#define redisAssert(_e) ((_e)?(void)0 : (_redisAssert(#_e,__FILE__,__LINE__),exit(1)))
+#define redisAssert(_e) ((_e)?(void)0 : (_redisAssert(#_e,__FILE__,__LINE__),_exit(1)))
 static void _redisAssert(char *estr, char *file, int line);
 
 /*================================= Data types ============================== */
@@ -3163,9 +3163,9 @@ static int rdbSaveBackground(char *filename) {
         if (server.vm_enabled) vmReopenSwapFile();
         close(server.fd);
         if (rdbSave(filename) == REDIS_OK) {
-            exit(0);
+            _exit(0);
         } else {
-            exit(1);
+            _exit(1);
         }
     } else {
         /* Parent */
@@ -6992,9 +6992,9 @@ static int rewriteAppendOnlyFileBackground(void) {
         close(server.fd);
         snprintf(tmpfile,256,"temp-rewriteaof-bg-%d.aof", (int) getpid());
         if (rewriteAppendOnlyFile(tmpfile) == REDIS_OK) {
-            exit(0);
+            _exit(0);
         } else {
-            exit(1);
+            _exit(1);
         }
     } else {
         /* Parent */
@@ -7315,12 +7315,12 @@ static robj *vmReadObjectFromSwap(off_t page, int type) {
         redisLog(REDIS_WARNING,
             "Unrecoverable VM problem in vmReadObjectFromSwap(): can't seek: %s",
             strerror(errno));
-        exit(1);
+        _exit(1);
     }
     o = rdbLoadObject(type,server.vm_fp);
     if (o == NULL) {
         redisLog(REDIS_WARNING, "Unrecoverable VM problem in vmReadObjectFromSwap(): can't load object from swap file: %s", strerror(errno));
-        exit(1);
+        _exit(1);
     }
     if (server.vm_enabled) pthread_mutex_unlock(&server.io_swapfile_mutex);
     return o;
@@ -7835,8 +7835,15 @@ static void *IOThreadEntryPoint(void *arg) {
 
 static void spawnIOThread(void) {
     pthread_t thread;
+    sigset_t mask, omask;
 
+    sigemptyset(&mask);
+    sigaddset(&mask,SIGCHLD);
+    sigaddset(&mask,SIGHUP);
+    sigaddset(&mask,SIGPIPE);
+    pthread_sigmask(SIG_SETMASK, &mask, &omask);
     pthread_create(&thread,&server.io_threads_attr,IOThreadEntryPoint,NULL);
+    pthread_sigmask(SIG_SETMASK, &omask, NULL);
     server.io_active_threads++;
 }
 
@@ -7870,12 +7877,13 @@ static void waitEmptyIOJobsQueue(void) {
 }
 
 static void vmReopenSwapFile(void) {
-    fclose(server.vm_fp);
+    /* Note: we don't close the old one as we are in the child process
+     * and don't want to mess at all with the original file object. */
     server.vm_fp = fopen(server.vm_swap_file,"r+b");
     if (server.vm_fp == NULL) {
         redisLog(REDIS_WARNING,"Can't re-open the VM swap file: %s. Exiting.",
             server.vm_swap_file);
-        exit(1);
+        _exit(1);
     }
     server.vm_fd = fileno(server.vm_fp);
 }
@@ -8299,7 +8307,7 @@ static void segvHandler(int sig, siginfo_t *info, void *secret) {
         }
     }
     /* free(messages); Don't call free() with possibly corrupted memory. */
-    exit(0);
+    _exit(0);
 }
 
 static void setupSigSegvAction(void) {