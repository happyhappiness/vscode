@@ -259,9 +259,15 @@ void loadServerConfigFromString(char *config) {
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
@@ -491,12 +497,12 @@ void configSetCommand(redisClient *c) {
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
@@ -668,14 +674,14 @@ void configGetCommand(redisClient *c) {
         addReplyBulkCString(c,server.repl_serve_stale_data ? "yes" : "no");
         matches++;
     }
-    if (stringmatch(pattern,"hash-max-zipmap-entries",0)) {
-        addReplyBulkCString(c,"hash-max-zipmap-entries");
-        addReplyBulkLongLong(c,server.hash_max_zipmap_entries);
+    if (stringmatch(pattern,"hash-max-ziplist-entries",0)) {
+        addReplyBulkCString(c,"hash-max-ziplist-entries");
+        addReplyBulkLongLong(c,server.hash_max_ziplist_entries);
         matches++;
     }
-    if (stringmatch(pattern,"hash-max-zipmap-value",0)) {
-        addReplyBulkCString(c,"hash-max-zipmap-value");
-        addReplyBulkLongLong(c,server.hash_max_zipmap_value);
+    if (stringmatch(pattern,"hash-max-ziplist-value",0)) {
+        addReplyBulkCString(c,"hash-max-ziplist-value");
+        addReplyBulkLongLong(c,server.hash_max_ziplist_value);
         matches++;
     }
     if (stringmatch(pattern,"list-max-ziplist-entries",0)) {