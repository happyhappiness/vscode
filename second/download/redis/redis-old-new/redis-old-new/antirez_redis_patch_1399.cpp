@@ -263,9 +263,15 @@ void loadServerConfigFromString(char *config) {
             zfree(server.rdb_filename);
             server.rdb_filename = zstrdup(argv[1]);
         } else if (!strcasecmp(argv[0],"hash-max-zipmap-entries") && argc == 2) {
-            server.hash_max_zipmap_entries = memtoll(argv[1], NULL);
+            redisLog(REDIS_WARNING, "Deprecated configuration directive: \"%s\"", argv[0]);
+            server.hash_max_ziplist_entries = memtoll(argv[1], NULL);
         } else if (!strcasecmp(argv[0],"hash-max-zipmap-value") && argc == 2) {
-            server.hash_max_zipmap_value = memtoll(argv[1], NULL);
+            redisLog(REDIS_WARNING, "Deprecated configuration directive: \"%s\"", argv[0]);
+            server.hash_max_ziplist_value = memtoll(argv[1], NULL);
+        } else if (!strcasecmp(argv[0],"hash-max-ziplist-entries") && argc == 2) {
+            server.hash_max_ziplist_entries = memtoll(argv[1], NULL);
+        } else if (!strcasecmp(argv[0],"hash-max-ziplist-value") && argc == 2) {
+            server.hash_max_ziplist_value = memtoll(argv[1], NULL);
         } else if (!strcasecmp(argv[0],"list-max-ziplist-entries") && argc == 2){
             server.list_max_ziplist_entries = memtoll(argv[1], NULL);
         } else if (!strcasecmp(argv[0],"list-max-ziplist-value") && argc == 2) {
@@ -521,12 +527,12 @@ void configSetCommand(redisClient *c) {
             addReplyErrorFormat(c,"Changing directory: %s", strerror(errno));
             return;
         }
-    } else if (!strcasecmp(c->argv[2]->ptr,"hash-max-zipmap-entries")) {
+    } else if (!strcasecmp(c->argv[2]->ptr,"hash-max-ziplist-entries")) {
         if (getLongLongFromObject(o,&ll) == REDIS_ERR || ll < 0) goto badfmt;
-        server.hash_max_zipmap_entries = ll;
-    } else if (!strcasecmp(c->argv[2]->ptr,"hash-max-zipmap-value")) {
+        server.hash_max_ziplist_entries = ll;
+    } else if (!strcasecmp(c->argv[2]->ptr,"hash-max-ziplist-value")) {
         if (getLongLongFromObject(o,&ll) == REDIS_ERR || ll < 0) goto badfmt;
-        server.hash_max_zipmap_value = ll;
+        server.hash_max_ziplist_value = ll;
     } else if (!strcasecmp(c->argv[2]->ptr,"list-max-ziplist-entries")) {
         if (getLongLongFromObject(o,&ll) == REDIS_ERR || ll < 0) goto badfmt;
         server.list_max_ziplist_entries = ll;
@@ -684,10 +690,10 @@ void configGetCommand(redisClient *c) {
             server.aof_rewrite_perc);
     config_get_numerical_field("auto-aof-rewrite-min-size",
             server.aof_rewrite_min_size);
-    config_get_numerical_field("hash-max-zipmap-entries",
-            server.hash_max_zipmap_entries);
-    config_get_numerical_field("hash-max-zipmap-value",
-            server.hash_max_zipmap_value);
+    config_get_numerical_field("hash-max-ziplist-entries",
+            server.hash_max_ziplist_entries);
+    config_get_numerical_field("hash-max-ziplist-value",
+            server.hash_max_ziplist_value);
     config_get_numerical_field("list-max-ziplist-entries",
             server.list_max_ziplist_entries);
     config_get_numerical_field("list-max-ziplist-value",