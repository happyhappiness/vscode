@@ -319,6 +319,106 @@ void keysCommand(redisClient *c) {
     setDeferredMultiBulkLength(c,replylen,numkeys);
 }
 
+void scanCallback(void *privdata, const dictEntry *de) {
+    list *keys = (list *)privdata;
+    sds key = dictGetKey(de);
+    robj *kobj = createStringObject(key, sdslen(key));
+    listAddNodeTail(keys, kobj);
+}
+
+void scanCommand(redisClient *c) {
+    int rv;
+    int i, j;
+    char buf[32];
+    list *keys = listCreate();
+    listNode *ln, *ln_;
+    unsigned long cursor = 0;
+    long count = 1;
+    sds pat;
+    int patlen, patnoop = 1;
+
+    /* Use sscanf because we need an *unsigned* long */
+    rv = sscanf(c->argv[1]->ptr, "%lu", &cursor);
+    if (rv != 1) {
+        addReplyError(c, "invalid cursor");
+        goto cleanup;
+    }
+
+    i = 2;
+    while (i < c->argc) {
+        j = c->argc - i;
+        if (!strcasecmp(c->argv[i]->ptr, "count") && j >= 2) {
+            if (getLongFromObjectOrReply(c, c->argv[i+1], &count, NULL) != REDIS_OK) {
+                goto cleanup;
+            }
+
+            if (count < 1) {
+                addReply(c,shared.syntaxerr);
+                goto cleanup;
+            }
+
+            i += 2;
+        } else if (!strcasecmp(c->argv[i]->ptr, "pattern") && j >= 2) {
+            pat = c->argv[i+1]->ptr;
+            patlen = sdslen(pat);
+
+            /* The pattern is a no-op iff == "*" */
+            patnoop = (pat[0] == '*' && patlen == 1);
+
+            i += 2;
+        } else {
+            addReply(c,shared.syntaxerr);
+            goto cleanup;
+        }
+    }
+
+    do {
+        cursor = dictScan(c->db->dict, cursor, scanCallback, keys);
+    } while (cursor && listLength(keys) < count);
+
+    /* Filter keys */
+    ln = listFirst(keys);
+    while (ln) {
+        robj *kobj = listNodeValue(ln);
+        ln_ = listNextNode(ln);
+
+        /* Keep key iff pattern matches and it hasn't expired */
+        if ((patnoop || stringmatchlen(pat, patlen, kobj->ptr, sdslen(kobj->ptr), 0)) &&
+            (expireIfNeeded(c->db, kobj) == 0))
+        {
+            /* Keep */
+        } else {
+            decrRefCount(kobj);
+            listDelNode(keys, ln);
+        }
+
+        ln = ln_;
+    }
+
+    addReplyMultiBulkLen(c, 2);
+
+    rv = snprintf(buf, sizeof(buf), "%lu", cursor);
+    redisAssert(rv < sizeof(buf));
+    addReplyBulkCBuffer(c, buf, rv);
+
+    addReplyMultiBulkLen(c, listLength(keys));
+    while ((ln = listFirst(keys)) != NULL) {
+        robj *kobj = listNodeValue(ln);
+        addReplyBulk(c, kobj);
+        decrRefCount(kobj);
+        listDelNode(keys, ln);
+    }
+
+cleanup:
+    while ((ln = listFirst(keys)) != NULL) {
+        robj *kobj = listNodeValue(ln);
+        decrRefCount(kobj);
+        listDelNode(keys, ln);
+    }
+
+    listRelease(keys);
+}
+
 void dbsizeCommand(redisClient *c) {
     addReplyLongLong(c,dictSize(c->db->dict));
 }