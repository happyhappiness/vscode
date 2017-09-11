@@ -195,7 +195,7 @@ void listTypeConvert(robj *subject, int enc) {
  *----------------------------------------------------------------------------*/
 
 void pushGenericCommand(client *c, int where) {
-    int j, waiting = 0, pushed = 0;
+    int j, pushed = 0;
     robj *lobj = lookupKeyWrite(c->db,c->argv[1]);
 
     if (lobj && lobj->type != OBJ_LIST) {
@@ -214,7 +214,7 @@ void pushGenericCommand(client *c, int where) {
         listTypePush(lobj,c->argv[j],where);
         pushed++;
     }
-    addReplyLongLong(c, waiting + (lobj ? listTypeLength(lobj) : 0));
+    addReplyLongLong(c, (lobj ? listTypeLength(lobj) : 0));
     if (pushed) {
         char *event = (where == LIST_HEAD) ? "lpush" : "rpush";
 
@@ -232,68 +232,80 @@ void rpushCommand(client *c) {
     pushGenericCommand(c,LIST_TAIL);
 }
 
-void pushxGenericCommand(client *c, robj *refval, robj *val, int where) {
+void pushxGenericCommand(client *c, int where) {
+    int j, pushed = 0;
     robj *subject;
-    listTypeIterator *iter;
-    listTypeEntry entry;
-    int inserted = 0;
 
     if ((subject = lookupKeyWriteOrReply(c,c->argv[1],shared.czero)) == NULL ||
         checkType(c,subject,OBJ_LIST)) return;
 
-    if (refval != NULL) {
-        /* Seek refval from head to tail */
-        iter = listTypeInitIterator(subject,0,LIST_TAIL);
-        while (listTypeNext(iter,&entry)) {
-            if (listTypeEqual(&entry,refval)) {
-                listTypeInsert(&entry,val,where);
-                inserted = 1;
-                break;
-            }
-        }
-        listTypeReleaseIterator(iter);
+    for (j = 2; j < c->argc; j++) {
+        c->argv[j] = tryObjectEncoding(c->argv[j]);
+        listTypePush(subject,c->argv[j],where);
+        pushed++;
+    }
 
-        if (inserted) {
-            signalModifiedKey(c->db,c->argv[1]);
-            notifyKeyspaceEvent(NOTIFY_LIST,"linsert",
-                                c->argv[1],c->db->id);
-            server.dirty++;
-        } else {
-            /* Notify client of a failed insert */
-            addReply(c,shared.cnegone);
-            return;
-        }
-    } else {
-        char *event = (where == LIST_HEAD) ? "lpush" : "rpush";
+    addReplyLongLong(c,listTypeLength(subject));
 
-        listTypePush(subject,val,where);
+    if (pushed) {
+        char *event = (where == LIST_HEAD) ? "lpush" : "rpush";
         signalModifiedKey(c->db,c->argv[1]);
         notifyKeyspaceEvent(NOTIFY_LIST,event,c->argv[1],c->db->id);
-        server.dirty++;
     }
-
-    addReplyLongLong(c,listTypeLength(subject));
+    server.dirty += pushed;
 }
 
 void lpushxCommand(client *c) {
-    c->argv[2] = tryObjectEncoding(c->argv[2]);
-    pushxGenericCommand(c,NULL,c->argv[2],LIST_HEAD);
+    pushxGenericCommand(c,LIST_HEAD);
 }
 
 void rpushxCommand(client *c) {
-    c->argv[2] = tryObjectEncoding(c->argv[2]);
-    pushxGenericCommand(c,NULL,c->argv[2],LIST_TAIL);
+    pushxGenericCommand(c,LIST_TAIL);
 }
 
 void linsertCommand(client *c) {
+    int where;
+    robj *subject;
+    listTypeIterator *iter;
+    listTypeEntry entry;
+    int inserted = 0;
+
     c->argv[4] = tryObjectEncoding(c->argv[4]);
     if (strcasecmp(c->argv[2]->ptr,"after") == 0) {
-        pushxGenericCommand(c,c->argv[3],c->argv[4],LIST_TAIL);
+        where = LIST_TAIL;
     } else if (strcasecmp(c->argv[2]->ptr,"before") == 0) {
-        pushxGenericCommand(c,c->argv[3],c->argv[4],LIST_HEAD);
+        where = LIST_HEAD;
     } else {
         addReply(c,shared.syntaxerr);
+        return;
+    }
+
+    if ((subject = lookupKeyWriteOrReply(c,c->argv[1],shared.czero)) == NULL ||
+        checkType(c,subject,OBJ_LIST)) return;
+
+    /* Seek pivot from head to tail */
+    iter = listTypeInitIterator(subject,0,LIST_TAIL);
+    while (listTypeNext(iter,&entry)) {
+        if (listTypeEqual(&entry,c->argv[3])) {
+            listTypeInsert(&entry,c->argv[4],where);
+            inserted = 1;
+            break;
+        }
     }
+    listTypeReleaseIterator(iter);
+
+    if (inserted) {
+        signalModifiedKey(c->db,c->argv[1]);
+        notifyKeyspaceEvent(NOTIFY_LIST,"linsert",
+                            c->argv[1],c->db->id);
+        server.dirty++;
+    } else {
+        /* Notify client of a failed insert */
+        addReply(c,shared.cnegone);
+        return;
+    }
+
+    addReplyLongLong(c,listTypeLength(subject));
 }
 
 void llenCommand(client *c) {