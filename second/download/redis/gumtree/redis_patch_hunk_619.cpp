         if (end >= llen) end = llen-1;
         ltrim = start;
         rtrim = llen-end-1;
     }
 
     /* Remove list elements to perform the trim */
-    if (o->encoding == REDIS_ENCODING_ZIPLIST) {
-        o->ptr = ziplistDeleteRange(o->ptr,0,ltrim);
-        o->ptr = ziplistDeleteRange(o->ptr,-rtrim,rtrim);
-    } else if (o->encoding == REDIS_ENCODING_LINKEDLIST) {
-        list = o->ptr;
-        for (j = 0; j < ltrim; j++) {
-            ln = listFirst(list);
-            listDelNode(list,ln);
-        }
-        for (j = 0; j < rtrim; j++) {
-            ln = listLast(list);
-            listDelNode(list,ln);
-        }
+    if (o->encoding == OBJ_ENCODING_QUICKLIST) {
+        quicklistDelRange(o->ptr,0,ltrim);
+        quicklistDelRange(o->ptr,-rtrim,rtrim);
     } else {
-        redisPanic("Unknown list encoding");
+        serverPanic("Unknown list encoding");
     }
 
-    notifyKeyspaceEvent(REDIS_NOTIFY_LIST,"ltrim",c->argv[1],c->db->id);
+    notifyKeyspaceEvent(NOTIFY_LIST,"ltrim",c->argv[1],c->db->id);
     if (listTypeLength(o) == 0) {
         dbDelete(c->db,c->argv[1]);
-        notifyKeyspaceEvent(REDIS_NOTIFY_GENERIC,"del",c->argv[1],c->db->id);
+        notifyKeyspaceEvent(NOTIFY_GENERIC,"del",c->argv[1],c->db->id);
     }
     signalModifiedKey(c->db,c->argv[1]);
     server.dirty++;
     addReply(c,shared.ok);
 }
 
-void lremCommand(redisClient *c) {
+void lremCommand(client *c) {
     robj *subject, *obj;
-    obj = c->argv[3] = tryObjectEncoding(c->argv[3]);
+    obj = c->argv[3];
     long toremove;
     long removed = 0;
-    listTypeEntry entry;
 
-    if ((getLongFromObjectOrReply(c, c->argv[2], &toremove, NULL) != REDIS_OK))
+    if ((getLongFromObjectOrReply(c, c->argv[2], &toremove, NULL) != C_OK))
         return;
 
     subject = lookupKeyWriteOrReply(c,c->argv[1],shared.czero);
-    if (subject == NULL || checkType(c,subject,REDIS_LIST)) return;
-
-    /* Make sure obj is raw when we're dealing with a ziplist */
-    if (subject->encoding == REDIS_ENCODING_ZIPLIST)
-        obj = getDecodedObject(obj);
+    if (subject == NULL || checkType(c,subject,OBJ_LIST)) return;
 
     listTypeIterator *li;
     if (toremove < 0) {
         toremove = -toremove;
-        li = listTypeInitIterator(subject,-1,REDIS_HEAD);
+        li = listTypeInitIterator(subject,-1,LIST_HEAD);
     } else {
-        li = listTypeInitIterator(subject,0,REDIS_TAIL);
+        li = listTypeInitIterator(subject,0,LIST_TAIL);
     }
 
+    listTypeEntry entry;
     while (listTypeNext(li,&entry)) {
         if (listTypeEqual(&entry,obj)) {
-            listTypeDelete(&entry);
+            listTypeDelete(li, &entry);
             server.dirty++;
             removed++;
             if (toremove && removed == toremove) break;
         }
     }
     listTypeReleaseIterator(li);
 
-    /* Clean up raw encoded object */
-    if (subject->encoding == REDIS_ENCODING_ZIPLIST)
-        decrRefCount(obj);
+    if (removed) {
+        signalModifiedKey(c->db,c->argv[1]);
+        notifyKeyspaceEvent(NOTIFY_GENERIC,"lrem",c->argv[1],c->db->id);
+    }
+
+    if (listTypeLength(subject) == 0) {
+        dbDelete(c->db,c->argv[1]);
+        notifyKeyspaceEvent(NOTIFY_GENERIC,"del",c->argv[1],c->db->id);
+    }
 
-    if (listTypeLength(subject) == 0) dbDelete(c->db,c->argv[1]);
     addReplyLongLong(c,removed);
-    if (removed) signalModifiedKey(c->db,c->argv[1]);
 }
 
 /* This is the semantic of this command:
  *  RPOPLPUSH srclist dstlist:
  *    IF LLEN(srclist) > 0
  *      element = RPOP srclist
