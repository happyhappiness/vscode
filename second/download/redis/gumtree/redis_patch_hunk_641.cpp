         }
         dictReleaseIterator(di);
 
         /* We can free the accumulator dictionary now. */
         dictRelease(accumulator);
     } else {
-        redisPanic("Unknown operator");
+        serverPanic("Unknown operator");
     }
 
     if (dbDelete(c->db,dstkey)) {
         signalModifiedKey(c->db,dstkey);
         touched = 1;
         server.dirty++;
     }
     if (dstzset->zsl->length) {
-        /* Convert to ziplist when in limits. */
-        if (dstzset->zsl->length <= server.zset_max_ziplist_entries &&
-            maxelelen <= server.zset_max_ziplist_value)
-                zsetConvert(dstobj,REDIS_ENCODING_ZIPLIST);
-
+        zsetConvertToZiplistIfNeeded(dstobj,maxelelen);
         dbAdd(c->db,dstkey,dstobj);
         addReplyLongLong(c,zsetLength(dstobj));
         if (!touched) signalModifiedKey(c->db,dstkey);
-        notifyKeyspaceEvent(REDIS_NOTIFY_ZSET,
-            (op == REDIS_OP_UNION) ? "zunionstore" : "zinterstore",
+        notifyKeyspaceEvent(NOTIFY_ZSET,
+            (op == SET_OP_UNION) ? "zunionstore" : "zinterstore",
             dstkey,c->db->id);
         server.dirty++;
     } else {
         decrRefCount(dstobj);
         addReply(c,shared.czero);
         if (touched)
-            notifyKeyspaceEvent(REDIS_NOTIFY_GENERIC,"del",dstkey,c->db->id);
+            notifyKeyspaceEvent(NOTIFY_GENERIC,"del",dstkey,c->db->id);
     }
     zfree(src);
 }
 
-void zunionstoreCommand(redisClient *c) {
-    zunionInterGenericCommand(c,c->argv[1], REDIS_OP_UNION);
+void zunionstoreCommand(client *c) {
+    zunionInterGenericCommand(c,c->argv[1], SET_OP_UNION);
 }
 
-void zinterstoreCommand(redisClient *c) {
-    zunionInterGenericCommand(c,c->argv[1], REDIS_OP_INTER);
+void zinterstoreCommand(client *c) {
+    zunionInterGenericCommand(c,c->argv[1], SET_OP_INTER);
 }
 
-void zrangeGenericCommand(redisClient *c, int reverse) {
+void zrangeGenericCommand(client *c, int reverse) {
     robj *key = c->argv[1];
     robj *zobj;
     int withscores = 0;
     long start;
     long end;
     int llen;
     int rangelen;
 
-    if ((getLongFromObjectOrReply(c, c->argv[2], &start, NULL) != REDIS_OK) ||
-        (getLongFromObjectOrReply(c, c->argv[3], &end, NULL) != REDIS_OK)) return;
+    if ((getLongFromObjectOrReply(c, c->argv[2], &start, NULL) != C_OK) ||
+        (getLongFromObjectOrReply(c, c->argv[3], &end, NULL) != C_OK)) return;
 
     if (c->argc == 5 && !strcasecmp(c->argv[4]->ptr,"withscores")) {
         withscores = 1;
     } else if (c->argc >= 5) {
         addReply(c,shared.syntaxerr);
         return;
     }
 
     if ((zobj = lookupKeyReadOrReply(c,key,shared.emptymultibulk)) == NULL
-         || checkType(c,zobj,REDIS_ZSET)) return;
+         || checkType(c,zobj,OBJ_ZSET)) return;
 
     /* Sanitize indexes. */
     llen = zsetLength(zobj);
     if (start < 0) start = llen+start;
     if (end < 0) end = llen+end;
     if (start < 0) start = 0;
