@@ -266,14 +266,17 @@ void saddCommand(redisClient *c) {
         c->argv[j] = tryObjectEncoding(c->argv[j]);
         if (setTypeAdd(set,c->argv[j])) added++;
     }
-    if (added) signalModifiedKey(c->db,c->argv[1]);
+    if (added) {
+        signalModifiedKey(c->db,c->argv[1]);
+        notifyKeyspaceEvent("sadd",c->argv[1],c->db->id);
+    }
     server.dirty += added;
     addReplyLongLong(c,added);
 }
 
 void sremCommand(redisClient *c) {
     robj *set;
-    int j, deleted = 0;
+    int j, deleted = 0, keyremoved = 0;
 
     if ((set = lookupKeyWriteOrReply(c,c->argv[1],shared.czero)) == NULL ||
         checkType(c,set,REDIS_SET)) return;
@@ -283,12 +286,15 @@ void sremCommand(redisClient *c) {
             deleted++;
             if (setTypeSize(set) == 0) {
                 dbDelete(c->db,c->argv[1]);
+                keyremoved = 1;
                 break;
             }
         }
     }
     if (deleted) {
         signalModifiedKey(c->db,c->argv[1]);
+        notifyKeyspaceEvent("srem",c->argv[1],c->db->id);
+        if (keyremoved) notifyKeyspaceEvent("del",c->argv[1],c->db->id);
         server.dirty += deleted;
     }
     addReplyLongLong(c,deleted);
@@ -322,9 +328,13 @@ void smoveCommand(redisClient *c) {
         addReply(c,shared.czero);
         return;
     }
+    notifyKeyspaceEvent("srem",c->argv[1],c->db->id);
 
     /* Remove the src set from the database when empty */
-    if (setTypeSize(srcset) == 0) dbDelete(c->db,c->argv[1]);
+    if (setTypeSize(srcset) == 0) {
+        dbDelete(c->db,c->argv[1]);
+        notifyKeyspaceEvent("del",c->argv[1],c->db->id);
+    }
     signalModifiedKey(c->db,c->argv[1]);
     signalModifiedKey(c->db,c->argv[2]);
     server.dirty++;
@@ -336,7 +346,10 @@ void smoveCommand(redisClient *c) {
     }
 
     /* An extra key has changed when ele was successfully added to dstset */
-    if (setTypeAdd(dstset,ele)) server.dirty++;
+    if (setTypeAdd(dstset,ele)) {
+        server.dirty++;
+        notifyKeyspaceEvent("sadd",c->argv[2],c->db->id);
+    }
     addReply(c,shared.cone);
 }
 
@@ -378,6 +391,7 @@ void spopCommand(redisClient *c) {
         incrRefCount(ele);
         setTypeRemove(set,ele);
     }
+    notifyKeyspaceEvent("spop",c->argv[1],c->db->id);
 
     /* Replicate/AOF this command as an SREM operation */
     aux = createStringObject("SREM",4);
@@ -386,7 +400,10 @@ void spopCommand(redisClient *c) {
     decrRefCount(aux);
 
     addReplyBulk(c,ele);
-    if (setTypeSize(set) == 0) dbDelete(c->db,c->argv[1]);
+    if (setTypeSize(set) == 0) {
+        dbDelete(c->db,c->argv[1]);
+        notifyKeyspaceEvent("del",c->argv[1],c->db->id);
+    }
     signalModifiedKey(c->db,c->argv[1]);
     server.dirty++;
 }
@@ -691,6 +708,7 @@ void sinterGenericCommand(redisClient *c, robj **setkeys, unsigned long setnum,
         if (setTypeSize(dstset) > 0) {
             dbAdd(c->db,dstkey,dstset);
             addReplyLongLong(c,setTypeSize(dstset));
+            notifyKeyspaceEvent("sinterstore",dstkey,c->db->id);
         } else {
             decrRefCount(dstset);
             addReply(c,shared.czero);
@@ -856,6 +874,9 @@ void sunionDiffGenericCommand(redisClient *c, robj **setkeys, int setnum, robj *
         if (setTypeSize(dstset) > 0) {
             dbAdd(c->db,dstkey,dstset);
             addReplyLongLong(c,setTypeSize(dstset));
+            notifyKeyspaceEvent(
+                op == REDIS_OP_UNION ? "sunionstore" : "sdiffstore",
+                dstkey,c->db->id);
         } else {
             decrRefCount(dstset);
             addReply(c,shared.czero);