@@ -429,8 +429,10 @@ int rdbSave(char *filename) {
     int j;
     time_t now = time(NULL);
 
-    /* FIXME: implement .rdb save for disk store properly */
-    redisAssert(server.ds_enabled == 0);
+    if (server.ds_enabled) {
+        cacheForcePointInTime();
+        return dsRdbSave(filename);
+    }
 
     snprintf(tmpfile,256,"temp-%d.rdb", (int) getpid());
     fp = fopen(tmpfile,"w");
@@ -495,17 +497,22 @@ int rdbSaveBackground(char *filename) {
     pid_t childpid;
 
     if (server.bgsavechildpid != -1) return REDIS_ERR;
-    redisAssert(server.ds_enabled == 0);
+
     server.dirty_before_bgsave = server.dirty;
+
     if ((childpid = fork()) == 0) {
+        int retval;
+
         /* Child */
         if (server.ipfd > 0) close(server.ipfd);
         if (server.sofd > 0) close(server.sofd);
-        if (rdbSave(filename) == REDIS_OK) {
-            _exit(0);
+        if (server.ds_enabled) {
+            cacheForcePointInTime();
+            dsRdbSave(filename);
         } else {
-            _exit(1);
+            rdbSave(filename);
         }
+        _exit((retval == REDIS_OK) ? 0 : 1);
     } else {
         /* Parent */
         if (childpid == -1) {