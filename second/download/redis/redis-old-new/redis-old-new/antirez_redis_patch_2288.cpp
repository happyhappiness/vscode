@@ -190,6 +190,11 @@
 #define ZSKIPLIST_MAXLEVEL 32 /* Should be enough for 2^32 elements */
 #define ZSKIPLIST_P 0.25      /* Skiplist P = 1/4 */
 
+/* Append only defines */
+#define APPENDFSYNC_NO 0
+#define APPENDFSYNC_ALWAYS 1
+#define APPENDFSYNC_EVERYSEC 2
+
 /*================================= Data types ============================== */
 
 /* A redis object, that is a type able to hold a string / list / set */
@@ -262,6 +267,8 @@ struct redisServer {
     int dbnum;
     int daemonize;
     int appendonly;
+    int appendfsync;
+    time_t lastfsync;
     int appendfd;
     int appendseldb;
     char *pidfile;
@@ -1029,6 +1036,8 @@ static void initServerConfig() {
     server.glueoutputbuf = 1;
     server.daemonize = 0;
     server.appendonly = 0;
+    server.appendfsync = APPENDFSYNC_EVERYSEC;
+    server.lastfsync = time(NULL);
     server.appendfd = -1;
     server.appendseldb = -1; /* Make sure the first time will not match */
     server.pidfile = "/var/run/redis.pid";
@@ -1245,6 +1254,17 @@ static void loadServerConfig(char *filename) {
             if ((server.appendonly = yesnotoi(argv[1])) == -1) {
                 err = "argument must be 'yes' or 'no'"; goto loaderr;
             }
+        } else if (!strcasecmp(argv[0],"appendfsync") && argc == 2) {
+            if (strcasecmp(argv[1],"no")) {
+                server.appendfsync = APPENDFSYNC_NO;
+            } else if (strcasecmp(argv[1],"always")) {
+                server.appendfsync = APPENDFSYNC_ALWAYS;
+            } else if (strcasecmp(argv[1],"everysec")) {
+                server.appendfsync = APPENDFSYNC_EVERYSEC;
+            } else {
+                err = "argument must be 'no', 'always' or 'everysec'";
+                goto loaderr;
+            }
         } else if (!strcasecmp(argv[0],"requirepass") && argc == 2) {
           server.requirepass = zstrdup(argv[1]);
         } else if (!strcasecmp(argv[0],"pidfile") && argc == 2) {
@@ -1651,6 +1671,7 @@ static void feedAppendOnlyFile(struct redisCommand *cmd, int dictid, robj **argv
     sds buf = sdsempty();
     int j;
     ssize_t nwritten;
+    time_t now;
 
     /* The DB this command was targetting is not the same as the last command
      * we appendend. To issue a SELECT command is needed. */
@@ -1691,8 +1712,15 @@ static void feedAppendOnlyFile(struct redisCommand *cmd, int dictid, robj **argv
             redisLog(REDIS_WARNING,"Aborting on short write while writing to the append-only file: %s",strerror(errno));
          }
          abort();
-     }
-     fsync(server.appendfd); /* Let's try to get this data on the disk */
+    }
+    now = time(NULL);
+    if (server.appendfsync == APPENDFSYNC_ALWAYS ||
+        (server.appendfsync == APPENDFSYNC_EVERYSEC &&
+         now-server.lastfsync > 1))
+    {
+        fsync(server.appendfd); /* Let's try to get this data on the disk */
+        server.lastfsync = now;
+    }
 }
 
 static void processInputBuffer(redisClient *c) {