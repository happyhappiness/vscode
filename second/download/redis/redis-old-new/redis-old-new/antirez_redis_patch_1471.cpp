@@ -954,6 +954,43 @@ void initServerConfig() {
     server.bug_report_start = 0;
 }
 
+/* This function will try to raise the max number of open files accordingly to
+ * the configured max number of clients. It will also account for 32 additional
+ * file descriptors as we need a few more for persistence, listening
+ * sockets, log files and so forth.
+ *
+ * If it will not be possible to set the limit accordingly to the configured
+ * max number of clients, the function will do the reverse setting
+ * server.maxclients to the value that we can actually handle. */
+void adjustOpenFilesLimit(void) {
+    rlim_t maxfiles = server.maxclients+32;
+    struct rlimit limit;
+
+    if (maxfiles < 1024) maxfiles = 1024;
+    if (getrlimit(RLIMIT_NOFILE,&limit) == -1) {
+        redisLog(REDIS_WARNING,"Unable to obtain the current NOFILE limit (%s), assuming 1024 and setting the max clients configuration accordingly.",
+            strerror(errno));
+        server.maxclients = 1024-32;
+    } else {
+        rlim_t oldlimit = limit.rlim_cur;
+
+        /* Set the max number of files if the current limit is not enough
+         * for our needs. */
+        if (oldlimit < maxfiles) {
+            limit.rlim_cur = maxfiles;
+            limit.rlim_max = maxfiles;
+            if (setrlimit(RLIMIT_NOFILE,&limit) == -1) {
+                server.maxclients = oldlimit-32;
+                redisLog(REDIS_WARNING,"Unable to set the max number of files limit to %d (%s), setting the max clients configuration to %d.",
+                    (int) maxfiles, strerror(errno), (int) server.maxclients);
+            } else {
+                redisLog(REDIS_NOTICE,"Max number of open files set to %d",
+                    (int) maxfiles);
+            }
+        }
+    }
+}
+
 void initServer() {
     int j;
 
@@ -972,7 +1009,8 @@ void initServer() {
     server.unblocked_clients = listCreate();
 
     createSharedObjects();
-    server.el = aeCreateEventLoop();
+    adjustOpenFilesLimit();
+    server.el = aeCreateEventLoop(server.maxclients+1024);
     server.db = zmalloc(sizeof(redisDb)*server.dbnum);
 
     if (server.port != 0) {
@@ -1045,38 +1083,6 @@ void initServer() {
     bioInit();
     srand(time(NULL)^getpid());
 
-    /* Try to raise the max number of open files accordingly to the
-     * configured max number of clients. Also account for 32 additional
-     * file descriptors as we need a few more for persistence, listening
-     * sockets, log files and so forth. */
-    {
-        rlim_t maxfiles = server.maxclients+32;
-        struct rlimit limit;
-
-        if (maxfiles < 1024) maxfiles = 1024;
-        if (getrlimit(RLIMIT_NOFILE,&limit) == -1) {
-            redisLog(REDIS_WARNING,"Unable to obtain the current NOFILE limit (%s), assuming 1024 and setting the max clients configuration accordingly.",
-                strerror(errno));
-            server.maxclients = 1024-32;
-        } else {
-            rlim_t oldlimit = limit.rlim_cur;
-
-            /* Set the max number of files if the current limit is not enough
-             * for our needs. */
-            if (oldlimit < maxfiles) {
-                limit.rlim_cur = maxfiles;
-                limit.rlim_max = maxfiles;
-                if (setrlimit(RLIMIT_NOFILE,&limit) == -1) {
-                    server.maxclients = oldlimit-32;
-                    redisLog(REDIS_WARNING,"Unable to set the max number of files limit to %d (%s), setting the max clients configuration to %d.",
-                        (int) maxfiles, strerror(errno), (int) server.maxclients);
-                } else {
-                    redisLog(REDIS_NOTICE,"Max number of open files set to %d",
-                        (int) maxfiles);
-                }
-            }
-        }
-    }
 }
 
 /* Populates the Redis Command Table starting from the hard coded list