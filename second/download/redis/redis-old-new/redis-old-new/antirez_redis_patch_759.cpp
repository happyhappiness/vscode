@@ -358,7 +358,12 @@ void loadServerConfigFromString(char *config) {
         } else if (!strcasecmp(argv[0],"aof-rewrite-incremental-fsync") &&
                    argc == 2)
         {
-            if ((server.aof_rewrite_incremental_fsync = yesnotoi(argv[1])) == -1) {
+            if ((server.aof_rewrite_incremental_fsync =
+                 yesnotoi(argv[1])) == -1) {
+                err = "argument must be 'yes' or 'no'"; goto loaderr;
+            }
+        } else if (!strcasecmp(argv[0],"aof-load-truncated") && argc == 2) {
+            if ((server.aof_load_truncated = yesnotoi(argv[1])) == -1) {
                 err = "argument must be 'yes' or 'no'"; goto loaderr;
             }
         } else if (!strcasecmp(argv[0],"requirepass") && argc == 2) {
@@ -713,6 +718,11 @@ void configSetCommand(redisClient *c) {
 
         if (yn == -1) goto badfmt;
         server.aof_rewrite_incremental_fsync = yn;
+    } else if (!strcasecmp(c->argv[2]->ptr,"aof-load-truncated")) {
+        int yn = yesnotoi(o->ptr);
+
+        if (yn == -1) goto badfmt;
+        server.aof_load_truncated = yn;
     } else if (!strcasecmp(c->argv[2]->ptr,"save")) {
         int vlen, j;
         sds *v = sdssplitlen(o->ptr,sdslen(o->ptr)," ",1,&vlen);
@@ -1045,6 +1055,8 @@ void configGetCommand(redisClient *c) {
             server.repl_disable_tcp_nodelay);
     config_get_bool_field("aof-rewrite-incremental-fsync",
             server.aof_rewrite_incremental_fsync);
+    config_get_bool_field("aof-load-truncated",
+            server.aof_load_truncated);
 
     /* Everything we can't handle with macros follows. */
 
@@ -1813,6 +1825,7 @@ int rewriteConfig(char *path) {
     rewriteConfigClientoutputbufferlimitOption(state);
     rewriteConfigNumericalOption(state,"hz",server.hz,REDIS_DEFAULT_HZ);
     rewriteConfigYesNoOption(state,"aof-rewrite-incremental-fsync",server.aof_rewrite_incremental_fsync,REDIS_DEFAULT_AOF_REWRITE_INCREMENTAL_FSYNC);
+    rewriteConfigYesNoOption(state,"aof-load-truncated",server.aof_load_truncated,REDIS_DEFAULT_AOF_LOAD_TRUNCATED);
     if (server.sentinel_mode) rewriteConfigSentinelOption(state);
 
     /* Step 3: remove all the orphaned lines in the old file, that is, lines