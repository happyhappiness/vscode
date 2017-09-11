@@ -306,6 +306,10 @@ void loadServerConfigFromString(char *config) {
             }
             server.aof_state = yes ? REDIS_AOF_ON : REDIS_AOF_OFF;
         } else if (!strcasecmp(argv[0],"appendfilename") && argc == 2) {
+            if (!pathIsBaseName(argv[1])) {
+                err = "appendfilename can't be a path, just a filename";
+                goto loaderr;
+            }
             zfree(server.aof_filename);
             server.aof_filename = zstrdup(argv[1]);
         } else if (!strcasecmp(argv[0],"no-appendfsync-on-rewrite")
@@ -352,6 +356,10 @@ void loadServerConfigFromString(char *config) {
             zfree(server.pidfile);
             server.pidfile = zstrdup(argv[1]);
         } else if (!strcasecmp(argv[0],"dbfilename") && argc == 2) {
+            if (!pathIsBaseName(argv[1])) {
+                err = "dbfilename can't be a path, just a filename";
+                goto loaderr;
+            }
             zfree(server.rdb_filename);
             server.rdb_filename = zstrdup(argv[1]);
         } else if (!strcasecmp(argv[0],"hash-max-ziplist-entries") && argc == 2) {
@@ -540,6 +548,10 @@ void configSetCommand(redisClient *c) {
     o = c->argv[3];
 
     if (!strcasecmp(c->argv[2]->ptr,"dbfilename")) {
+        if (!pathIsBaseName(o->ptr)) {
+            addReplyError(c, "dbfilename can't be a path, just a filename");
+            return;
+        }
         zfree(server.rdb_filename);
         server.rdb_filename = zstrdup(o->ptr);
     } else if (!strcasecmp(c->argv[2]->ptr,"requirepass")) {