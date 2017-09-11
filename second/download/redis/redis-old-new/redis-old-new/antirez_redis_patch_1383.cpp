@@ -202,6 +202,10 @@ void loadServerConfigFromString(char *config) {
             if ((server.repl_serve_stale_data = yesnotoi(argv[1])) == -1) {
                 err = "argument must be 'yes' or 'no'"; goto loaderr;
             }
+        } else if (!strcasecmp(argv[0],"slave-read-only") && argc == 2) {
+            if ((server.repl_slave_ro = yesnotoi(argv[1])) == -1) {
+                err = "argument must be 'yes' or 'no'"; goto loaderr;
+            }
         } else if (!strcasecmp(argv[0],"rdbcompression") && argc == 2) {
             if ((server.rdb_compression = yesnotoi(argv[1])) == -1) {
                 err = "argument must be 'yes' or 'no'"; goto loaderr;
@@ -514,6 +518,11 @@ void configSetCommand(redisClient *c) {
 
         if (yn == -1) goto badfmt;
         server.repl_serve_stale_data = yn;
+    } else if (!strcasecmp(c->argv[2]->ptr,"slave-read-only")) {
+        int yn = yesnotoi(o->ptr);
+
+        if (yn == -1) goto badfmt;
+        server.repl_slave_ro = yn;
     } else if (!strcasecmp(c->argv[2]->ptr,"dir")) {
         if (chdir((char*)o->ptr) == -1) {
             addReplyErrorFormat(c,"Changing directory: %s", strerror(errno));
@@ -712,6 +721,8 @@ void configGetCommand(redisClient *c) {
             server.aof_no_fsync_on_rewrite);
     config_get_bool_field("slave-serve-stale-data",
             server.repl_serve_stale_data);
+    config_get_bool_field("slave-read-only",
+            server.repl_slave_ro);
     config_get_bool_field("stop-writes-on-bgsave-error",
             server.stop_writes_on_bgsave_err);
     config_get_bool_field("daemonize", server.daemonize);