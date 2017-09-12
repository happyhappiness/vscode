@@ -349,11 +349,16 @@ void dsFlushDb(int dbid) {
     }
 }
 
-int dsRdbSave(char *filename) {
-    char tmpfile[256];
+void *dsRdbSave_thread(void *arg) {
+    char tmpfile[256], *filename = (char*)arg;
     int j, i;
     time_t now = time(NULL);
 
+    /* Change state to ACTIVE, to signal there is a saving thead working. */
+    pthread_mutex_lock(&server.bgsavethread_mutex);
+    server.bgsavethread_state = REDIS_BGSAVE_THREAD_ACTIVE;
+    pthread_mutex_unlock(&server.bgsavethread_mutex);
+
     snprintf(tmpfile,256,"temp-%d.rdb", (int) getpid());
     fp = fopen(tmpfile,"w");
     if (!fp) {
@@ -377,6 +382,7 @@ int dsRdbSave(char *filename) {
     fflush(fp);
     fsync(fileno(fp));
     fclose(fp);
+    zfree(filename);
 
     /* Use RENAME to make sure the DB file is changed atomically only
      * if the generate DB file is ok. */
@@ -386,12 +392,24 @@ int dsRdbSave(char *filename) {
         return REDIS_ERR;
     }
     redisLog(REDIS_NOTICE,"DB saved on disk");
-    server.dirty = 0;
-    server.lastsave = time(NULL);
     return REDIS_OK;
 
 werr:
+    zfree(filename);
     fclose(fp);
     unlink(tmpfile);
     redisLog(REDIS_WARNING,"Write error saving DB on disk: %s", strerror(errno));
 }
+
+int dsRdbSave(char *filename) {
+    pthread_t thread;
+
+    if (pthread_create(&thread,NULL,dsRdbSave_thread,zstrdup(filename)) != 0) {
+        redisLog(REDIS_WARNING,"Can't create diskstore BGSAVE thread: %s",
+            strerror(errno));
+        return REDIS_ERR;
+    } else {
+        server.bgsavethread = thread;
+        return REDIS_OK;
+    }
+}