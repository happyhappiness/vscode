@@ -474,7 +474,7 @@ void hsetCommand(redisClient *c) {
     update = hashTypeSet(o,c->argv[2],c->argv[3]);
     addReply(c, update ? shared.czero : shared.cone);
     signalModifiedKey(c->db,c->argv[1]);
-    notifyKeyspaceEvent("hset",c->argv[1],c->db->id);
+    notifyKeyspaceEvent(REDIS_NOTIFY_HASH,"hset",c->argv[1],c->db->id);
     server.dirty++;
 }
 
@@ -490,7 +490,7 @@ void hsetnxCommand(redisClient *c) {
         hashTypeSet(o,c->argv[2],c->argv[3]);
         addReply(c, shared.cone);
         signalModifiedKey(c->db,c->argv[1]);
-        notifyKeyspaceEvent("hset",c->argv[1],c->db->id);
+        notifyKeyspaceEvent(REDIS_NOTIFY_HASH,"hset",c->argv[1],c->db->id);
         server.dirty++;
     }
 }
@@ -512,7 +512,7 @@ void hmsetCommand(redisClient *c) {
     }
     addReply(c, shared.ok);
     signalModifiedKey(c->db,c->argv[1]);
-    notifyKeyspaceEvent("hset",c->argv[1],c->db->id);
+    notifyKeyspaceEvent(REDIS_NOTIFY_HASH,"hset",c->argv[1],c->db->id);
     server.dirty++;
 }
 
@@ -546,7 +546,7 @@ void hincrbyCommand(redisClient *c) {
     decrRefCount(new);
     addReplyLongLong(c,value);
     signalModifiedKey(c->db,c->argv[1]);
-    notifyKeyspaceEvent("hincrby",c->argv[1],c->db->id);
+    notifyKeyspaceEvent(REDIS_NOTIFY_HASH,"hincrby",c->argv[1],c->db->id);
     server.dirty++;
 }
 
@@ -573,7 +573,7 @@ void hincrbyfloatCommand(redisClient *c) {
     hashTypeSet(o,c->argv[2],new);
     addReplyBulk(c,new);
     signalModifiedKey(c->db,c->argv[1]);
-    notifyKeyspaceEvent("hincrbyfloat",c->argv[1],c->db->id);
+    notifyKeyspaceEvent(REDIS_NOTIFY_HASH,"hincrbyfloat",c->argv[1],c->db->id);
     server.dirty++;
 
     /* Always replicate HINCRBYFLOAT as an HSET command with the final value
@@ -671,8 +671,10 @@ void hdelCommand(redisClient *c) {
     }
     if (deleted) {
         signalModifiedKey(c->db,c->argv[1]);
-        notifyKeyspaceEvent("hdel",c->argv[1],c->db->id);
-        if (keyremoved) notifyKeyspaceEvent("del",c->argv[1],c->db->id);
+        notifyKeyspaceEvent(REDIS_NOTIFY_HASH,"hdel",c->argv[1],c->db->id);
+        if (keyremoved)
+            notifyKeyspaceEvent(REDIS_NOTIFY_GENERIC,"del",c->argv[1],
+                                c->db->id);
         server.dirty += deleted;
     }
     addReplyLongLong(c,deleted);