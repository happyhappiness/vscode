@@ -428,6 +428,21 @@ void configSetCommand(redisClient *c) {
             addReplyErrorFormat(c,"Changing directory: %s", strerror(errno));
             return;
         }
+    } else if (!strcasecmp(c->argv[2]->ptr,"hash-max-zipmap-entries")) {
+        if (getLongLongFromObject(o,&ll) == REDIS_ERR || ll < 0) goto badfmt;
+        server.hash_max_zipmap_entries = ll;
+    } else if (!strcasecmp(c->argv[2]->ptr,"hash-max-zipmap-value")) {
+        if (getLongLongFromObject(o,&ll) == REDIS_ERR || ll < 0) goto badfmt;
+        server.hash_max_zipmap_value = ll;
+    } else if (!strcasecmp(c->argv[2]->ptr,"list-max-ziplist-entries")) {
+        if (getLongLongFromObject(o,&ll) == REDIS_ERR || ll < 0) goto badfmt;
+        server.list_max_ziplist_entries = ll;
+    } else if (!strcasecmp(c->argv[2]->ptr,"list-max-ziplist-value")) {
+        if (getLongLongFromObject(o,&ll) == REDIS_ERR || ll < 0) goto badfmt;
+        server.list_max_ziplist_value = ll;
+    } else if (!strcasecmp(c->argv[2]->ptr,"set-max-intset-entries")) {
+        if (getLongLongFromObject(o,&ll) == REDIS_ERR || ll < 0) goto badfmt;
+        server.set_max_intset_entries = ll;
     } else {
         addReplyErrorFormat(c,"Unsupported CONFIG parameter: %s",
             (char*)c->argv[2]->ptr);
@@ -552,6 +567,31 @@ void configGetCommand(redisClient *c) {
         addReplyBulkCString(c,server.repl_serve_stale_data ? "yes" : "no");
         matches++;
     }
+    if (stringmatch(pattern,"hash-max-zipmap-entries",0)) {
+        addReplyBulkCString(c,"hash-max-zipmap-entries");
+        addReplyBulkLongLong(c,server.hash_max_zipmap_entries);
+        matches++;
+    }
+    if (stringmatch(pattern,"hash-max-zipmap-value",0)) {
+        addReplyBulkCString(c,"hash-max-zipmap-value");
+        addReplyBulkLongLong(c,server.hash_max_zipmap_value);
+        matches++;
+    }
+    if (stringmatch(pattern,"list-max-ziplist-entries",0)) {
+        addReplyBulkCString(c,"list-max-ziplist-entries");
+        addReplyBulkLongLong(c,server.list_max_ziplist_entries);
+        matches++;
+    }
+    if (stringmatch(pattern,"list-max-ziplist-value",0)) {
+        addReplyBulkCString(c,"list-max-ziplist-value");
+        addReplyBulkLongLong(c,server.list_max_ziplist_value);
+        matches++;
+    }
+    if (stringmatch(pattern,"set-max-intset-entries",0)) {
+        addReplyBulkCString(c,"set-max-intset-entries");
+        addReplyBulkLongLong(c,server.set_max_intset_entries);
+        matches++;
+    }
     setDeferredMultiBulkLength(c,replylen,matches*2);
 }
 