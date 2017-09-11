@@ -1100,12 +1100,12 @@ unsigned char *zzlDeleteRangeByRank(unsigned char *zl, unsigned int start, unsig
  * Common sorted set API
  *----------------------------------------------------------------------------*/
 
-unsigned int zsetLength(robj *zobj) {
+unsigned int zsetLength(const robj *zobj) {
     int length = -1;
     if (zobj->encoding == OBJ_ENCODING_ZIPLIST) {
         length = zzlLength(zobj->ptr);
     } else if (zobj->encoding == OBJ_ENCODING_SKIPLIST) {
-        length = ((zset*)zobj->ptr)->zsl->length;
+        length = ((const zset*)zobj->ptr)->zsl->length;
     } else {
         serverPanic("Unknown sorted set encoding");
     }
@@ -2327,25 +2327,25 @@ void zunionInterGenericCommand(client *c, robj *dstkey, int op) {
         serverPanic("Unknown operator");
     }
 
-    if (dbDelete(c->db,dstkey)) {
-        signalModifiedKey(c->db,dstkey);
+    if (dbDelete(c->db,dstkey))
         touched = 1;
-        server.dirty++;
-    }
     if (dstzset->zsl->length) {
         zsetConvertToZiplistIfNeeded(dstobj,maxelelen);
         dbAdd(c->db,dstkey,dstobj);
         addReplyLongLong(c,zsetLength(dstobj));
-        if (!touched) signalModifiedKey(c->db,dstkey);
+        signalModifiedKey(c->db,dstkey);
         notifyKeyspaceEvent(NOTIFY_ZSET,
             (op == SET_OP_UNION) ? "zunionstore" : "zinterstore",
             dstkey,c->db->id);
         server.dirty++;
     } else {
         decrRefCount(dstobj);
         addReply(c,shared.czero);
-        if (touched)
+        if (touched) {
+            signalModifiedKey(c->db,dstkey);
             notifyKeyspaceEvent(NOTIFY_GENERIC,"del",dstkey,c->db->id);
+            server.dirty++;
+        }
     }
     zfree(src);
 }