     addReplySds(c,sdscatprintf(sdsempty(),"$%lu\r\n",
         (unsigned long)sdslen(info)));
     addReplySds(c,info);
     addReply(c,shared.crlf);
 }
 
+/* Implements Sentinel verison of the ROLE command. The output is
+ * "sentinel" and the list of currently monitored master names. */
+void sentinelRoleCommand(redisClient *c) {
+    dictIterator *di;
+    dictEntry *de;
+
+    addReplyMultiBulkLen(c,2);
+    addReplyBulkCBuffer(c,"sentinel",8);
+    addReplyMultiBulkLen(c,dictSize(sentinel.masters));
+
+    di = dictGetIterator(sentinel.masters);
+    while((de = dictNext(di)) != NULL) {
+        sentinelRedisInstance *ri = dictGetVal(de);
+
+        addReplyBulkCString(c,ri->name);
+    }
+    dictReleaseIterator(di);
+}
+
 /* SENTINEL SET <mastername> [<option> <value> ...] */
 void sentinelSetCommand(redisClient *c) {
     sentinelRedisInstance *ri;
     int j, changes = 0;
     char *option, *value;
 
