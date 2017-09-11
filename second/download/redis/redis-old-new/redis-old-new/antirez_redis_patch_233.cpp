@@ -351,16 +351,17 @@ void smoveCommand(client *c) {
         dbDelete(c->db,c->argv[1]);
         notifyKeyspaceEvent(NOTIFY_GENERIC,"del",c->argv[1],c->db->id);
     }
-    signalModifiedKey(c->db,c->argv[1]);
-    signalModifiedKey(c->db,c->argv[2]);
-    server.dirty++;
 
     /* Create the destination set when it doesn't exist */
     if (!dstset) {
         dstset = setTypeCreate(ele->ptr);
         dbAdd(c->db,c->argv[2],dstset);
     }
 
+    signalModifiedKey(c->db,c->argv[1]);
+    signalModifiedKey(c->db,c->argv[2]);
+    server.dirty++;
+
     /* An extra key has changed when ele was successfully added to dstset */
     if (setTypeAdd(dstset,ele->ptr)) {
         server.dirty++;
@@ -547,6 +548,8 @@ void spopWithCountCommand(client *c) {
      * the alsoPropagate() API. */
     decrRefCount(propargv[0]);
     preventCommandPropagation(c);
+    signalModifiedKey(c->db,c->argv[1]);
+    server.dirty++;
 }
 
 void spopCommand(client *c) {