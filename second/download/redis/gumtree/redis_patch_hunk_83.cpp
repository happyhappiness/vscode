         if (inserted) {
             /* Check if the length exceeds the ziplist length threshold. */
             if (subject->encoding == REDIS_ENCODING_ZIPLIST &&
                 ziplistLen(subject->ptr) > server.list_max_ziplist_entries)
                     listTypeConvert(subject,REDIS_ENCODING_LINKEDLIST);
             signalModifiedKey(c->db,c->argv[1]);
+            notifyKeyspaceEvent(REDIS_NOTIFY_LIST,"linsert",
+                                c->argv[1],c->db->id);
             server.dirty++;
         } else {
             /* Notify client of a failed insert */
             addReply(c,shared.cnegone);
             return;
         }
     } else {
+        char *event = (where == REDIS_HEAD) ? "lpush" : "rpush";
+
         listTypePush(subject,val,where);
         signalModifiedKey(c->db,c->argv[1]);
+        notifyKeyspaceEvent(REDIS_NOTIFY_LIST,event,c->argv[1],c->db->id);
         server.dirty++;
     }
 
     addReplyLongLong(c,listTypeLength(subject));
 }
 
