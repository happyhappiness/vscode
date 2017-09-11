@@ -474,6 +474,7 @@ void hsetCommand(redisClient *c) {
     update = hashTypeSet(o,c->argv[2],c->argv[3]);
     addReply(c, update ? shared.czero : shared.cone);
     signalModifiedKey(c->db,c->argv[1]);
+    notifyKeyspaceEvent("hset",c->argv[1],c->db->id);
     server.dirty++;
 }
 
@@ -489,6 +490,7 @@ void hsetnxCommand(redisClient *c) {
         hashTypeSet(o,c->argv[2],c->argv[3]);
         addReply(c, shared.cone);
         signalModifiedKey(c->db,c->argv[1]);
+        notifyKeyspaceEvent("hset",c->argv[1],c->db->id);
         server.dirty++;
     }
 }
@@ -510,6 +512,7 @@ void hmsetCommand(redisClient *c) {
     }
     addReply(c, shared.ok);
     signalModifiedKey(c->db,c->argv[1]);
+    notifyKeyspaceEvent("hset",c->argv[1],c->db->id);
     server.dirty++;
 }
 
@@ -543,6 +546,7 @@ void hincrbyCommand(redisClient *c) {
     decrRefCount(new);
     addReplyLongLong(c,value);
     signalModifiedKey(c->db,c->argv[1]);
+    notifyKeyspaceEvent("hincrby",c->argv[1],c->db->id);
     server.dirty++;
 }
 
@@ -569,6 +573,7 @@ void hincrbyfloatCommand(redisClient *c) {
     hashTypeSet(o,c->argv[2],new);
     addReplyBulk(c,new);
     signalModifiedKey(c->db,c->argv[1]);
+    notifyKeyspaceEvent("hincrbyfloat",c->argv[1],c->db->id);
     server.dirty++;
 
     /* Always replicate HINCRBYFLOAT as an HSET command with the final value
@@ -649,7 +654,7 @@ void hmgetCommand(redisClient *c) {
 
 void hdelCommand(redisClient *c) {
     robj *o;
-    int j, deleted = 0;
+    int j, deleted = 0, keyremoved = 0;
 
     if ((o = lookupKeyWriteOrReply(c,c->argv[1],shared.czero)) == NULL ||
         checkType(c,o,REDIS_HASH)) return;
@@ -659,12 +664,15 @@ void hdelCommand(redisClient *c) {
             deleted++;
             if (hashTypeLength(o) == 0) {
                 dbDelete(c->db,c->argv[1]);
+                keyremoved = 1;
                 break;
             }
         }
     }
     if (deleted) {
         signalModifiedKey(c->db,c->argv[1]);
+        notifyKeyspaceEvent("hdel",c->argv[1],c->db->id);
+        if (keyremoved) notifyKeyspaceEvent("del",c->argv[1],c->db->id);
         server.dirty += deleted;
     }
     addReplyLongLong(c,deleted);