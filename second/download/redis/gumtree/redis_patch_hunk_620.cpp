  *
  * The idea is to be able to get an element from a list in a reliable way
  * since the element is not just returned but pushed against another list
  * as well. This command was originally proposed by Ezra Zygmuntowicz.
  */
 
-void rpoplpushHandlePush(redisClient *c, robj *dstkey, robj *dstobj, robj *value) {
+void rpoplpushHandlePush(client *c, robj *dstkey, robj *dstobj, robj *value) {
     /* Create the list if the key does not exist */
     if (!dstobj) {
-        dstobj = createZiplistObject();
+        dstobj = createQuicklistObject();
+        quicklistSetOptions(dstobj->ptr, server.list_max_ziplist_size,
+                            server.list_compress_depth);
         dbAdd(c->db,dstkey,dstobj);
     }
     signalModifiedKey(c->db,dstkey);
-    listTypePush(dstobj,value,REDIS_HEAD);
-    notifyKeyspaceEvent(REDIS_NOTIFY_LIST,"lpush",dstkey,c->db->id);
+    listTypePush(dstobj,value,LIST_HEAD);
+    notifyKeyspaceEvent(NOTIFY_LIST,"lpush",dstkey,c->db->id);
     /* Always send the pushed value to the client. */
     addReplyBulk(c,value);
 }
 
-void rpoplpushCommand(redisClient *c) {
+void rpoplpushCommand(client *c) {
     robj *sobj, *value;
     if ((sobj = lookupKeyWriteOrReply(c,c->argv[1],shared.nullbulk)) == NULL ||
-        checkType(c,sobj,REDIS_LIST)) return;
+        checkType(c,sobj,OBJ_LIST)) return;
 
     if (listTypeLength(sobj) == 0) {
         /* This may only happen after loading very old RDB files. Recent
          * versions of Redis delete keys of empty lists. */
         addReply(c,shared.nullbulk);
     } else {
         robj *dobj = lookupKeyWrite(c->db,c->argv[2]);
         robj *touchedkey = c->argv[1];
 
-        if (dobj && checkType(c,dobj,REDIS_LIST)) return;
-        value = listTypePop(sobj,REDIS_TAIL);
+        if (dobj && checkType(c,dobj,OBJ_LIST)) return;
+        value = listTypePop(sobj,LIST_TAIL);
         /* We saved touched key, and protect it, since rpoplpushHandlePush
          * may change the client command argument vector (it does not
          * currently). */
         incrRefCount(touchedkey);
         rpoplpushHandlePush(c,c->argv[2],dobj,value);
 
         /* listTypePop returns an object with its refcount incremented */
         decrRefCount(value);
 
         /* Delete the source list when it is empty */
-        notifyKeyspaceEvent(REDIS_NOTIFY_LIST,"rpop",touchedkey,c->db->id);
+        notifyKeyspaceEvent(NOTIFY_LIST,"rpop",touchedkey,c->db->id);
         if (listTypeLength(sobj) == 0) {
             dbDelete(c->db,touchedkey);
-            notifyKeyspaceEvent(REDIS_NOTIFY_GENERIC,"del",
+            notifyKeyspaceEvent(NOTIFY_GENERIC,"del",
                                 touchedkey,c->db->id);
         }
         signalModifiedKey(c->db,touchedkey);
         decrRefCount(touchedkey);
         server.dirty++;
     }
