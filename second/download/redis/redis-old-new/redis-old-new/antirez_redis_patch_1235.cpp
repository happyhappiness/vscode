@@ -240,6 +240,7 @@ void delCommand(redisClient *c) {
     for (j = 1; j < c->argc; j++) {
         if (dbDelete(c->db,c->argv[j])) {
             signalModifiedKey(c->db,c->argv[j]);
+            notifyKeyspaceEvent("del",c->argv[j],c->db->id);
             server.dirty++;
             deleted++;
         }
@@ -391,6 +392,8 @@ void renameGenericCommand(redisClient *c, int nx) {
     dbDelete(c->db,c->argv[1]);
     signalModifiedKey(c->db,c->argv[1]);
     signalModifiedKey(c->db,c->argv[2]);
+    notifyKeyspaceEvent("rename_from",c->argv[1],c->db->id);
+    notifyKeyspaceEvent("rename_to",c->argv[2],c->db->id);
     server.dirty++;
     addReply(c,nx ? shared.cone : shared.ok);
 }