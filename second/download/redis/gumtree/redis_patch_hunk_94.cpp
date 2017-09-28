         }
         setTypeReleaseIterator(si);
         decrRefCount(dstset);
     } else {
         /* If we have a target key where to store the resulting set
          * create this key with the result set inside */
-        dbDelete(c->db,dstkey);
+        int deleted = dbDelete(c->db,dstkey);
         if (setTypeSize(dstset) > 0) {
             dbAdd(c->db,dstkey,dstset);
             addReplyLongLong(c,setTypeSize(dstset));
+            notifyKeyspaceEvent(REDIS_NOTIFY_SET,
+                op == REDIS_OP_UNION ? "sunionstore" : "sdiffstore",
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
     }
     zfree(sets);
 }
