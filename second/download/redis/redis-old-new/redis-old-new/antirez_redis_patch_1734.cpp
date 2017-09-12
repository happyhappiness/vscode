@@ -349,10 +349,17 @@ void dsFlushDb(int dbid) {
     }
 }
 
+void dsRdbSaveSetState(int state) {
+    pthread_mutex_lock(&server.bgsavethread_mutex);
+    server.bgsavethread_state = state;
+    pthread_mutex_unlock(&server.bgsavethread_mutex);
+}
+
 void *dsRdbSave_thread(void *arg) {
     char tmpfile[256], *filename = (char*)arg;
     int j, i;
     time_t now = time(NULL);
+    FILE *fp;
 
     /* Change state to ACTIVE, to signal there is a saving thead working. */
     pthread_mutex_lock(&server.bgsavethread_mutex);
@@ -362,11 +369,16 @@ void *dsRdbSave_thread(void *arg) {
     snprintf(tmpfile,256,"temp-%d.rdb", (int) getpid());
     fp = fopen(tmpfile,"w");
     if (!fp) {
-        redisLog(REDIS_WARNING, "Failed saving the DB: %s", strerror(errno));
-        return REDIS_ERR;
+        redisLog(REDIS_WARNING, "Failed opening .rdb for saving: %s",
+            strerror(errno));
+        dsRdbSaveSetState(REDIS_BGSAVE_THREAD_DONE_ERR);
+        return NULL;
     }
     if (fwrite("REDIS0001",9,1,fp) == 0) goto werr;
 
+    sleep(5);
+
+#if 0
     /* Scan all diskstore dirs looking for keys */
     for (j = 0; j < 256; j++) {
         for (i = 0; i < 256; i++) {
@@ -377,6 +389,7 @@ void *dsRdbSave_thread(void *arg) {
             if (rdbSaveLen(fp,j) == -1) goto werr;
         }
     }
+#endif
 
     /* Make sure data will not remain on the OS's output buffers */
     fflush(fp);
@@ -389,16 +402,20 @@ void *dsRdbSave_thread(void *arg) {
     if (rename(tmpfile,filename) == -1) {
         redisLog(REDIS_WARNING,"Error moving temp DB file on the final destination: %s", strerror(errno));
         unlink(tmpfile);
-        return REDIS_ERR;
+        dsRdbSaveSetState(REDIS_BGSAVE_THREAD_DONE_ERR);
+        return NULL;
     }
     redisLog(REDIS_NOTICE,"DB saved on disk");
-    return REDIS_OK;
+    dsRdbSaveSetState(REDIS_BGSAVE_THREAD_DONE_OK);
+    return NULL;
 
 werr:
     zfree(filename);
     fclose(fp);
     unlink(tmpfile);
+    dsRdbSaveSetState(REDIS_BGSAVE_THREAD_DONE_ERR);
     redisLog(REDIS_WARNING,"Write error saving DB on disk: %s", strerror(errno));
+    return NULL;
 }
 
 int dsRdbSave(char *filename) {