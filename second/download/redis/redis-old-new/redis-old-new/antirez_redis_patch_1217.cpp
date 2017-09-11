@@ -240,7 +240,8 @@ void delCommand(redisClient *c) {
     for (j = 1; j < c->argc; j++) {
         if (dbDelete(c->db,c->argv[j])) {
             signalModifiedKey(c->db,c->argv[j]);
-            notifyKeyspaceEvent("del",c->argv[j],c->db->id);
+            notifyKeyspaceEvent(REDIS_NOTIFY_GENERIC,
+                "del",c->argv[j],c->db->id);
             server.dirty++;
             deleted++;
         }
@@ -392,8 +393,10 @@ void renameGenericCommand(redisClient *c, int nx) {
     dbDelete(c->db,c->argv[1]);
     signalModifiedKey(c->db,c->argv[1]);
     signalModifiedKey(c->db,c->argv[2]);
-    notifyKeyspaceEvent("rename_from",c->argv[1],c->db->id);
-    notifyKeyspaceEvent("rename_to",c->argv[2],c->db->id);
+    notifyKeyspaceEvent(REDIS_NOTIFY_GENERIC,"rename_from",
+        c->argv[1],c->db->id);
+    notifyKeyspaceEvent(REDIS_NOTIFY_GENERIC,"rename_to",
+        c->argv[2],c->db->id);
     server.dirty++;
     addReply(c,nx ? shared.cone : shared.ok);
 }
@@ -587,14 +590,14 @@ void expireGenericCommand(redisClient *c, long long basetime, int unit) {
         rewriteClientCommandVector(c,2,aux,key);
         decrRefCount(aux);
         signalModifiedKey(c->db,key);
-        notifyKeyspaceEvent("del",key,c->db->id);
+        notifyKeyspaceEvent(REDIS_NOTIFY_GENERIC,"del",key,c->db->id);
         addReply(c, shared.cone);
         return;
     } else {
         setExpire(c->db,key,when);
         addReply(c,shared.cone);
         signalModifiedKey(c->db,key);
-        notifyKeyspaceEvent("expire",key,c->db->id);
+        notifyKeyspaceEvent(REDIS_NOTIFY_GENERIC,"expire",key,c->db->id);
         server.dirty++;
         return;
     }