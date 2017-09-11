@@ -261,6 +261,10 @@ void loadServerConfig(char *filename) {
             server.list_max_ziplist_value = memtoll(argv[1], NULL);
         } else if (!strcasecmp(argv[0],"set-max-intset-entries") && argc == 2) {
             server.set_max_intset_entries = memtoll(argv[1], NULL);
+        } else if (!strcasecmp(argv[0],"zset-max-ziplist-entries") && argc == 2) {
+            server.zset_max_ziplist_entries = memtoll(argv[1], NULL);
+        } else if (!strcasecmp(argv[0],"zset-max-ziplist-value") && argc == 2) {
+            server.zset_max_ziplist_value = memtoll(argv[1], NULL);
         } else if (!strcasecmp(argv[0],"rename-command") && argc == 3) {
             struct redisCommand *cmd = lookupCommand(argv[1]);
             int retval;
@@ -285,6 +289,13 @@ void loadServerConfig(char *filename) {
                     err = "Target command name already exists"; goto loaderr;
                 }
             }
+        } else if (!strcasecmp(argv[0],"cluster-enabled") && argc == 2) {
+            if ((server.cluster_enabled = yesnotoi(argv[1])) == -1) {
+                err = "argument must be 'yes' or 'no'"; goto loaderr;
+            }
+        } else if (!strcasecmp(argv[0],"cluster-config-file") && argc == 2) {
+            zfree(server.cluster.configfile);
+            server.cluster.configfile = zstrdup(argv[1]);
         } else {
             err = "Bad directive or wrong number of arguments"; goto loaderr;
         }
@@ -443,6 +454,12 @@ void configSetCommand(redisClient *c) {
     } else if (!strcasecmp(c->argv[2]->ptr,"set-max-intset-entries")) {
         if (getLongLongFromObject(o,&ll) == REDIS_ERR || ll < 0) goto badfmt;
         server.set_max_intset_entries = ll;
+    } else if (!strcasecmp(c->argv[2]->ptr,"zset-max-ziplist-entries")) {
+        if (getLongLongFromObject(o,&ll) == REDIS_ERR || ll < 0) goto badfmt;
+        server.zset_max_ziplist_entries = ll;
+    } else if (!strcasecmp(c->argv[2]->ptr,"zset-max-ziplist-value")) {
+        if (getLongLongFromObject(o,&ll) == REDIS_ERR || ll < 0) goto badfmt;
+        server.zset_max_ziplist_value = ll;
     } else {
         addReplyErrorFormat(c,"Unsupported CONFIG parameter: %s",
             (char*)c->argv[2]->ptr);
@@ -594,6 +611,16 @@ void configGetCommand(redisClient *c) {
         addReplyBulkLongLong(c,server.set_max_intset_entries);
         matches++;
     }
+    if (stringmatch(pattern,"zset-max-ziplist-entries",0)) {
+        addReplyBulkCString(c,"zset-max-ziplist-entries");
+        addReplyBulkLongLong(c,server.zset_max_ziplist_entries);
+        matches++;
+    }
+    if (stringmatch(pattern,"zset-max-ziplist-value",0)) {
+        addReplyBulkCString(c,"zset-max-ziplist-value");
+        addReplyBulkLongLong(c,server.zset_max_ziplist_value);
+        matches++;
+    }
     setDeferredMultiBulkLength(c,replylen,matches*2);
 }
 