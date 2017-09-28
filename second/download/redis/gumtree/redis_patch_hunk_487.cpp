         rdbSave(server.rdb_filename);
         server.dirty = saved_dirty;
     }
     server.dirty++;
 }
 
-void delCommand(redisClient *c) {
+void delCommand(client *c) {
     int deleted = 0, j;
 
     for (j = 1; j < c->argc; j++) {
         expireIfNeeded(c->db,c->argv[j]);
         if (dbDelete(c->db,c->argv[j])) {
             signalModifiedKey(c->db,c->argv[j]);
-            notifyKeyspaceEvent(REDIS_NOTIFY_GENERIC,
+            notifyKeyspaceEvent(NOTIFY_GENERIC,
                 "del",c->argv[j],c->db->id);
             server.dirty++;
             deleted++;
         }
     }
     addReplyLongLong(c,deleted);
 }
 
 /* EXISTS key1 key2 ... key_N.
  * Return value is the number of keys existing. */
-void existsCommand(redisClient *c) {
+void existsCommand(client *c) {
     long long count = 0;
     int j;
 
     for (j = 1; j < c->argc; j++) {
         expireIfNeeded(c->db,c->argv[j]);
         if (dbExists(c->db,c->argv[j])) count++;
     }
     addReplyLongLong(c,count);
 }
 
-void selectCommand(redisClient *c) {
+void selectCommand(client *c) {
     long id;
 
     if (getLongFromObjectOrReply(c, c->argv[1], &id,
-        "invalid DB index") != REDIS_OK)
+        "invalid DB index") != C_OK)
         return;
 
     if (server.cluster_enabled && id != 0) {
         addReplyError(c,"SELECT is not allowed in cluster mode");
         return;
     }
-    if (selectDb(c,id) == REDIS_ERR) {
+    if (selectDb(c,id) == C_ERR) {
         addReplyError(c,"invalid DB index");
     } else {
         addReply(c,shared.ok);
     }
 }
 
-void randomkeyCommand(redisClient *c) {
+void randomkeyCommand(client *c) {
     robj *key;
 
     if ((key = dbRandomKey(c->db)) == NULL) {
         addReply(c,shared.nullbulk);
         return;
     }
 
     addReplyBulk(c,key);
     decrRefCount(key);
 }
 
-void keysCommand(redisClient *c) {
+void keysCommand(client *c) {
     dictIterator *di;
     dictEntry *de;
     sds pattern = c->argv[1]->ptr;
     int plen = sdslen(pattern), allkeys;
     unsigned long numkeys = 0;
     void *replylen = addDeferredMultiBulkLength(c);
