@@ -268,7 +268,7 @@ void saddCommand(redisClient *c) {
     }
     if (added) {
         signalModifiedKey(c->db,c->argv[1]);
-        notifyKeyspaceEvent("sadd",c->argv[1],c->db->id);
+        notifyKeyspaceEvent(REDIS_NOTIFY_SET,"sadd",c->argv[1],c->db->id);
     }
     server.dirty += added;
     addReplyLongLong(c,added);
@@ -293,8 +293,10 @@ void sremCommand(redisClient *c) {
     }
     if (deleted) {
         signalModifiedKey(c->db,c->argv[1]);
-        notifyKeyspaceEvent("srem",c->argv[1],c->db->id);
-        if (keyremoved) notifyKeyspaceEvent("del",c->argv[1],c->db->id);
+        notifyKeyspaceEvent(REDIS_NOTIFY_SET,"srem",c->argv[1],c->db->id);
+        if (keyremoved)
+            notifyKeyspaceEvent(REDIS_NOTIFY_GENERIC,"del",c->argv[1],
+                                c->db->id);
         server.dirty += deleted;
     }
     addReplyLongLong(c,deleted);
@@ -328,12 +330,12 @@ void smoveCommand(redisClient *c) {
         addReply(c,shared.czero);
         return;
     }
-    notifyKeyspaceEvent("srem",c->argv[1],c->db->id);
+    notifyKeyspaceEvent(REDIS_NOTIFY_SET,"srem",c->argv[1],c->db->id);
 
     /* Remove the src set from the database when empty */
     if (setTypeSize(srcset) == 0) {
         dbDelete(c->db,c->argv[1]);
-        notifyKeyspaceEvent("del",c->argv[1],c->db->id);
+        notifyKeyspaceEvent(REDIS_NOTIFY_GENERIC,"del",c->argv[1],c->db->id);
     }
     signalModifiedKey(c->db,c->argv[1]);
     signalModifiedKey(c->db,c->argv[2]);
@@ -348,7 +350,7 @@ void smoveCommand(redisClient *c) {
     /* An extra key has changed when ele was successfully added to dstset */
     if (setTypeAdd(dstset,ele)) {
         server.dirty++;
-        notifyKeyspaceEvent("sadd",c->argv[2],c->db->id);
+        notifyKeyspaceEvent(REDIS_NOTIFY_SET,"sadd",c->argv[2],c->db->id);
     }
     addReply(c,shared.cone);
 }
@@ -391,7 +393,7 @@ void spopCommand(redisClient *c) {
         incrRefCount(ele);
         setTypeRemove(set,ele);
     }
-    notifyKeyspaceEvent("spop",c->argv[1],c->db->id);
+    notifyKeyspaceEvent(REDIS_NOTIFY_SET,"spop",c->argv[1],c->db->id);
 
     /* Replicate/AOF this command as an SREM operation */
     aux = createStringObject("SREM",4);
@@ -402,7 +404,7 @@ void spopCommand(redisClient *c) {
     addReplyBulk(c,ele);
     if (setTypeSize(set) == 0) {
         dbDelete(c->db,c->argv[1]);
-        notifyKeyspaceEvent("del",c->argv[1],c->db->id);
+        notifyKeyspaceEvent(REDIS_NOTIFY_GENERIC,"del",c->argv[1],c->db->id);
     }
     signalModifiedKey(c->db,c->argv[1]);
     server.dirty++;
@@ -708,7 +710,8 @@ void sinterGenericCommand(redisClient *c, robj **setkeys, unsigned long setnum,
         if (setTypeSize(dstset) > 0) {
             dbAdd(c->db,dstkey,dstset);
             addReplyLongLong(c,setTypeSize(dstset));
-            notifyKeyspaceEvent("sinterstore",dstkey,c->db->id);
+            notifyKeyspaceEvent(REDIS_NOTIFY_SET,"sinterstore",
+                dstkey,c->db->id);
         } else {
             decrRefCount(dstset);
             addReply(c,shared.czero);
@@ -874,7 +877,7 @@ void sunionDiffGenericCommand(redisClient *c, robj **setkeys, int setnum, robj *
         if (setTypeSize(dstset) > 0) {
             dbAdd(c->db,dstkey,dstset);
             addReplyLongLong(c,setTypeSize(dstset));
-            notifyKeyspaceEvent(
+            notifyKeyspaceEvent(REDIS_NOTIFY_SET,
                 op == REDIS_OP_UNION ? "sunionstore" : "sdiffstore",
                 dstkey,c->db->id);
         } else {