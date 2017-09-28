         /* If we have a target key where to store the resulting set
          * create this key with the result set inside */
         int deleted = dbDelete(c->db,dstkey);
         if (setTypeSize(dstset) > 0) {
             dbAdd(c->db,dstkey,dstset);
             addReplyLongLong(c,setTypeSize(dstset));
-            notifyKeyspaceEvent(REDIS_NOTIFY_SET,
-                op == REDIS_OP_UNION ? "sunionstore" : "sdiffstore",
+            notifyKeyspaceEvent(NOTIFY_SET,
+                op == SET_OP_UNION ? "sunionstore" : "sdiffstore",
                 dstkey,c->db->id);
         } else {
             decrRefCount(dstset);
             addReply(c,shared.czero);
             if (deleted)
-                notifyKeyspaceEvent(REDIS_NOTIFY_GENERIC,"del",
+                notifyKeyspaceEvent(NOTIFY_GENERIC,"del",
                     dstkey,c->db->id);
         }
         signalModifiedKey(c->db,dstkey);
         server.dirty++;
     }
     zfree(sets);
 }
 
-void sunionCommand(redisClient *c) {
-    sunionDiffGenericCommand(c,c->argv+1,c->argc-1,NULL,REDIS_OP_UNION);
+void sunionCommand(client *c) {
+    sunionDiffGenericCommand(c,c->argv+1,c->argc-1,NULL,SET_OP_UNION);
 }
 
-void sunionstoreCommand(redisClient *c) {
-    sunionDiffGenericCommand(c,c->argv+2,c->argc-2,c->argv[1],REDIS_OP_UNION);
+void sunionstoreCommand(client *c) {
+    sunionDiffGenericCommand(c,c->argv+2,c->argc-2,c->argv[1],SET_OP_UNION);
 }
 
-void sdiffCommand(redisClient *c) {
-    sunionDiffGenericCommand(c,c->argv+1,c->argc-1,NULL,REDIS_OP_DIFF);
+void sdiffCommand(client *c) {
+    sunionDiffGenericCommand(c,c->argv+1,c->argc-1,NULL,SET_OP_DIFF);
 }
 
-void sdiffstoreCommand(redisClient *c) {
-    sunionDiffGenericCommand(c,c->argv+2,c->argc-2,c->argv[1],REDIS_OP_DIFF);
+void sdiffstoreCommand(client *c) {
+    sunionDiffGenericCommand(c,c->argv+2,c->argc-2,c->argv[1],SET_OP_DIFF);
 }
 
-void sscanCommand(redisClient *c) {
+void sscanCommand(client *c) {
     robj *set;
     unsigned long cursor;
 
-    if (parseScanCursorOrReply(c,c->argv[2],&cursor) == REDIS_ERR) return;
+    if (parseScanCursorOrReply(c,c->argv[2],&cursor) == C_ERR) return;
     if ((set = lookupKeyReadOrReply(c,c->argv[1],shared.emptyscan)) == NULL ||
-        checkType(c,set,REDIS_SET)) return;
+        checkType(c,set,OBJ_SET)) return;
     scanGenericCommand(c,set,cursor);
 }
