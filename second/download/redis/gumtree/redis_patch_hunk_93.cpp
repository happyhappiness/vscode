     }
     setTypeReleaseIterator(si);
 
     if (dstkey) {
         /* Store the resulting set into the target, if the intersection
          * is not an empty set. */
-        dbDelete(c->db,dstkey);
+        int deleted = dbDelete(c->db,dstkey);
         if (setTypeSize(dstset) > 0) {
             dbAdd(c->db,dstkey,dstset);
             addReplyLongLong(c,setTypeSize(dstset));
+            notifyKeyspaceEvent(REDIS_NOTIFY_SET,"sinterstore",
+                dstkey,c->db->id);
         } else {
             decrRefCount(dstset);
             addReply(c,shared.czero);
+            if (deleted)
+                notifyKeyspaceEvent(REDIS_NOTIFY_GENERIC,"del",
+                    dstkey,c->db->id);
         }
         signalModifiedKey(c->db,dstkey);
         server.dirty++;
     } else {
         setDeferredMultiBulkLength(c,replylen,cardinality);
     }
