     zfree(objects);
 
     /* Store the computed value into the target key */
     if (maxlen) {
         o = createObject(REDIS_STRING,res);
         setKey(c->db,targetkey,o);
+        notifyKeyspaceEvent(REDIS_NOTIFY_STRING,"set",targetkey,c->db->id);
         decrRefCount(o);
     } else if (dbDelete(c->db,targetkey)) {
         signalModifiedKey(c->db,targetkey);
+        notifyKeyspaceEvent(REDIS_NOTIFY_GENERIC,"del",targetkey,c->db->id);
     }
     server.dirty++;
     addReplyLongLong(c,maxlen); /* Return the output string length in bytes. */
 }
 
 /* BITCOUNT key [start end] */
