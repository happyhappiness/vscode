         /* Store the resulting set into the target, if the intersection
          * is not an empty set. */
         int deleted = dbDelete(c->db,dstkey);
         if (setTypeSize(dstset) > 0) {
             dbAdd(c->db,dstkey,dstset);
             addReplyLongLong(c,setTypeSize(dstset));
-            notifyKeyspaceEvent(REDIS_NOTIFY_SET,"sinterstore",
+            notifyKeyspaceEvent(NOTIFY_SET,"sinterstore",
                 dstkey,c->db->id);
         } else {
             decrRefCount(dstset);
             addReply(c,shared.czero);
             if (deleted)
-                notifyKeyspaceEvent(REDIS_NOTIFY_GENERIC,"del",
+                notifyKeyspaceEvent(NOTIFY_GENERIC,"del",
                     dstkey,c->db->id);
         }
         signalModifiedKey(c->db,dstkey);
         server.dirty++;
     } else {
         setDeferredMultiBulkLength(c,replylen,cardinality);
     }
     zfree(sets);
 }
 
-void sinterCommand(redisClient *c) {
+void sinterCommand(client *c) {
     sinterGenericCommand(c,c->argv+1,c->argc-1,NULL);
 }
 
-void sinterstoreCommand(redisClient *c) {
+void sinterstoreCommand(client *c) {
     sinterGenericCommand(c,c->argv+2,c->argc-2,c->argv[1]);
 }
 
-#define REDIS_OP_UNION 0
-#define REDIS_OP_DIFF 1
-#define REDIS_OP_INTER 2
+#define SET_OP_UNION 0
+#define SET_OP_DIFF 1
+#define SET_OP_INTER 2
 
-void sunionDiffGenericCommand(redisClient *c, robj **setkeys, int setnum, robj *dstkey, int op) {
+void sunionDiffGenericCommand(client *c, robj **setkeys, int setnum,
+                              robj *dstkey, int op) {
     robj **sets = zmalloc(sizeof(robj*)*setnum);
     setTypeIterator *si;
     robj *ele, *dstset = NULL;
     int j, cardinality = 0;
     int diff_algo = 1;
 
