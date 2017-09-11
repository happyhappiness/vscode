@@ -213,9 +213,12 @@ void loadServerConfigFromString(char *config) {
                 err = "argument must be 'yes' or 'no'"; goto loaderr;
             }
         } else if (!strcasecmp(argv[0],"appendonly") && argc == 2) {
-            if ((server.appendonly = yesnotoi(argv[1])) == -1) {
+            int yes;
+
+            if ((yes = yesnotoi(argv[1])) == -1) {
                 err = "argument must be 'yes' or 'no'"; goto loaderr;
             }
+            server.aof_state = yes ? REDIS_AOF_ON : REDIS_AOF_OFF;
         } else if (!strcasecmp(argv[0],"appendfilename") && argc == 2) {
             zfree(server.appendfilename);
             server.appendfilename = zstrdup(argv[1]);
@@ -426,19 +429,16 @@ void configSetCommand(redisClient *c) {
         if (yn == -1) goto badfmt;
         server.no_appendfsync_on_rewrite = yn;
     } else if (!strcasecmp(c->argv[2]->ptr,"appendonly")) {
-        int old = server.appendonly;
-        int new = yesnotoi(o->ptr);
-
-        if (new == -1) goto badfmt;
-        if (old != new) {
-            if (new == 0) {
-                stopAppendOnly();
-            } else {
-                if (startAppendOnly() == REDIS_ERR) {
-                    addReplyError(c,
-                        "Unable to turn on AOF. Check server logs.");
-                    return;
-                }
+        int enable = yesnotoi(o->ptr);
+
+        if (enable == -1) goto badfmt;
+        if (enable == 0 && server.aof_state != REDIS_AOF_OFF) {
+            stopAppendOnly();
+        } else if (enable && server.aof_state == REDIS_AOF_OFF) {
+            if (startAppendOnly() == REDIS_ERR) {
+                addReplyError(c,
+                    "Unable to turn on AOF. Check server logs.");
+                return;
             }
         }
     } else if (!strcasecmp(c->argv[2]->ptr,"auto-aof-rewrite-percentage")) {
@@ -616,7 +616,7 @@ void configGetCommand(redisClient *c) {
     }
     if (stringmatch(pattern,"appendonly",0)) {
         addReplyBulkCString(c,"appendonly");
-        addReplyBulkCString(c,server.appendonly ? "yes" : "no");
+        addReplyBulkCString(c,server.aof_state == REDIS_AOF_OFF ? "no" : "yes");
         matches++;
     }
     if (stringmatch(pattern,"no-appendfsync-on-rewrite",0)) {