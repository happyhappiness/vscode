@@ -511,19 +511,6 @@ void hashTypeConvert(robj *o, int enc) {
  * Hash type commands
  *----------------------------------------------------------------------------*/
 
-void hsetCommand(client *c) {
-    int update;
-    robj *o;
-
-    if ((o = hashTypeLookupWriteOrCreate(c,c->argv[1])) == NULL) return;
-    hashTypeTryConversion(o,c->argv,2,3);
-    update = hashTypeSet(o,c->argv[2]->ptr,c->argv[3]->ptr,HASH_SET_COPY);
-    addReply(c, update ? shared.czero : shared.cone);
-    signalModifiedKey(c->db,c->argv[1]);
-    notifyKeyspaceEvent(NOTIFY_HASH,"hset",c->argv[1],c->db->id);
-    server.dirty++;
-}
-
 void hsetnxCommand(client *c) {
     robj *o;
     if ((o = hashTypeLookupWriteOrCreate(c,c->argv[1])) == NULL) return;
@@ -540,8 +527,8 @@ void hsetnxCommand(client *c) {
     }
 }
 
-void hmsetCommand(client *c) {
-    int i;
+void hsetCommand(client *c) {
+    int i, created = 0;
     robj *o;
 
     if ((c->argc % 2) == 1) {
@@ -551,10 +538,19 @@ void hmsetCommand(client *c) {
 
     if ((o = hashTypeLookupWriteOrCreate(c,c->argv[1])) == NULL) return;
     hashTypeTryConversion(o,c->argv,2,c->argc-1);
-    for (i = 2; i < c->argc; i += 2) {
-        hashTypeSet(o,c->argv[i]->ptr,c->argv[i+1]->ptr,HASH_SET_COPY);
+
+    for (i = 2; i < c->argc; i += 2)
+        created += !hashTypeSet(o,c->argv[i]->ptr,c->argv[i+1]->ptr,HASH_SET_COPY);
+
+    /* HMSET (deprecated) and HSET return value is different. */
+    char *cmdname = c->argv[0]->ptr;
+    if (cmdname[1] == 's' || cmdname[1] == 'S') {
+        /* HSET */
+        addReplyLongLong(c, created);
+    } else {
+        /* HMSET */
+        addReply(c, shared.ok);
     }
-    addReply(c, shared.ok);
     signalModifiedKey(c->db,c->argv[1]);
     notifyKeyspaceEvent(NOTIFY_HASH,"hset",c->argv[1],c->db->id);
     server.dirty++;