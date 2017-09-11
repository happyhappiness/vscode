@@ -210,6 +210,10 @@ void loadServerConfigFromString(char *config) {
             if ((server.rdb_compression = yesnotoi(argv[1])) == -1) {
                 err = "argument must be 'yes' or 'no'"; goto loaderr;
             }
+        } else if (!strcasecmp(argv[0],"rdbchecksum") && argc == 2) {
+            if ((server.rdb_checksum = yesnotoi(argv[1])) == -1) {
+                err = "argument must be 'yes' or 'no'"; goto loaderr;
+            }
         } else if (!strcasecmp(argv[0],"activerehashing") && argc == 2) {
             if ((server.activerehashing = yesnotoi(argv[1])) == -1) {
                 err = "argument must be 'yes' or 'no'"; goto loaderr;
@@ -633,6 +637,16 @@ void configSetCommand(redisClient *c) {
             enableWatchdog(ll);
         else
             disableWatchdog();
+    } else if (!strcasecmp(c->argv[2]->ptr,"rdbcompression")) {
+        int yn = yesnotoi(o->ptr);
+
+        if (yn == -1) goto badfmt;
+        server.rdb_compression = yn;
+    } else if (!strcasecmp(c->argv[2]->ptr,"rdbchecksum")) {
+        int yn = yesnotoi(o->ptr);
+
+        if (yn == -1) goto badfmt;
+        server.rdb_checksum = yn;
     } else {
         addReplyErrorFormat(c,"Unsupported CONFIG parameter: %s",
             (char*)c->argv[2]->ptr);
@@ -734,6 +748,7 @@ void configGetCommand(redisClient *c) {
             server.stop_writes_on_bgsave_err);
     config_get_bool_field("daemonize", server.daemonize);
     config_get_bool_field("rdbcompression", server.rdb_compression);
+    config_get_bool_field("rdbchecksum", server.rdb_checksum);
     config_get_bool_field("activerehashing", server.activerehashing);
 
     /* Everything we can't handle with macros follows. */