         dbDelete(c->db,c->argv[1]);
         notifyKeyspaceEvent(NOTIFY_GENERIC,"del",c->argv[1],c->db->id);
     }
 
     /* Create the destination set when it doesn't exist */
     if (!dstset) {
-        dstset = setTypeCreate(ele);
+        dstset = setTypeCreate(ele->ptr);
         dbAdd(c->db,c->argv[2],dstset);
     }
 
     signalModifiedKey(c->db,c->argv[1]);
     signalModifiedKey(c->db,c->argv[2]);
     server.dirty++;
 
     /* An extra key has changed when ele was successfully added to dstset */
-    if (setTypeAdd(dstset,ele)) {
+    if (setTypeAdd(dstset,ele->ptr)) {
         server.dirty++;
         notifyKeyspaceEvent(NOTIFY_SET,"sadd",c->argv[2],c->db->id);
     }
     addReply(c,shared.cone);
 }
 
 void sismemberCommand(client *c) {
     robj *set;
 
     if ((set = lookupKeyReadOrReply(c,c->argv[1],shared.czero)) == NULL ||
         checkType(c,set,OBJ_SET)) return;
 
-    c->argv[2] = tryObjectEncoding(c->argv[2]);
-    if (setTypeIsMember(set,c->argv[2]))
+    if (setTypeIsMember(set,c->argv[2]->ptr))
         addReply(c,shared.cone);
     else
         addReply(c,shared.czero);
 }
 
 void scardCommand(client *c) {
