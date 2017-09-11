@@ -219,11 +219,11 @@ int setTypeRandomElement(robj *setobj, sds *sdsele, int64_t *llele) {
     return setobj->encoding;
 }
 
-unsigned long setTypeSize(robj *subject) {
+unsigned long setTypeSize(const robj *subject) {
     if (subject->encoding == OBJ_ENCODING_HT) {
-        return dictSize((dict*)subject->ptr);
+        return dictSize((const dict*)subject->ptr);
     } else if (subject->encoding == OBJ_ENCODING_INTSET) {
-        return intsetLen((intset*)subject->ptr);
+        return intsetLen((const intset*)subject->ptr);
     } else {
         serverPanic("Unknown set encoding");
     }
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