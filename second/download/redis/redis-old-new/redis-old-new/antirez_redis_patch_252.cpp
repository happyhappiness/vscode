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