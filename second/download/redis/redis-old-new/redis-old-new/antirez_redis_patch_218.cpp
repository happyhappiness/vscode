@@ -233,19 +233,26 @@ void rpushCommand(client *c) {
 }
 
 void pushxGenericCommand(client *c, int where) {
+    int j, pushed = 0;
     robj *subject;
 
     if ((subject = lookupKeyWriteOrReply(c,c->argv[1],shared.czero)) == NULL ||
         checkType(c,subject,OBJ_LIST)) return;
 
-    char *event = (where == LIST_HEAD) ? "lpush" : "rpush";
-    c->argv[2] = tryObjectEncoding(c->argv[2]);
-    listTypePush(subject,c->argv[2],where);
-    signalModifiedKey(c->db,c->argv[1]);
-    notifyKeyspaceEvent(NOTIFY_LIST,event,c->argv[1],c->db->id);
-    server.dirty++;
+    for (j = 2; j < c->argc; j++) {
+        c->argv[j] = tryObjectEncoding(c->argv[j]);
+        listTypePush(subject,c->argv[j],where);
+        pushed++;
+    }
 
     addReplyLongLong(c,listTypeLength(subject));
+
+    if (pushed) {
+        char *event = (where == LIST_HEAD) ? "lpush" : "rpush";
+        signalModifiedKey(c->db,c->argv[1]);
+        notifyKeyspaceEvent(NOTIFY_LIST,event,c->argv[1],c->db->id);
+    }
+    server.dirty += pushed;
 }
 
 void lpushxCommand(client *c) {