@@ -195,7 +195,7 @@ long redisBitpos(void *s, unsigned long count, int bit) {
 
     /* If we reached this point, there is a bug in the algorithm, since
      * the case of no match is handled as a special case before. */
-    redisPanic("End of redisBitpos() reached.");
+    serverPanic("End of redisBitpos() reached.");
     return 0; /* Just to avoid warnings. */
 }
 
@@ -250,7 +250,7 @@ void setbitCommand(client *c) {
     byteval |= ((on & 0x1) << bit);
     ((uint8_t*)o->ptr)[byte] = byteval;
     signalModifiedKey(c->db,c->argv[1]);
-    notifyKeyspaceEvent(REDIS_NOTIFY_STRING,"setbit",c->argv[1],c->db->id);
+    notifyKeyspaceEvent(NOTIFY_STRING,"setbit",c->argv[1],c->db->id);
     server.dirty++;
     addReply(c, bitval ? shared.cone : shared.czero);
 }
@@ -446,11 +446,11 @@ void bitopCommand(client *c) {
     if (maxlen) {
         o = createObject(OBJ_STRING,res);
         setKey(c->db,targetkey,o);
-        notifyKeyspaceEvent(REDIS_NOTIFY_STRING,"set",targetkey,c->db->id);
+        notifyKeyspaceEvent(NOTIFY_STRING,"set",targetkey,c->db->id);
         decrRefCount(o);
     } else if (dbDelete(c->db,targetkey)) {
         signalModifiedKey(c->db,targetkey);
-        notifyKeyspaceEvent(REDIS_NOTIFY_GENERIC,"del",targetkey,c->db->id);
+        notifyKeyspaceEvent(NOTIFY_GENERIC,"del",targetkey,c->db->id);
     }
     server.dirty++;
     addReplyLongLong(c,maxlen); /* Return the output string length in bytes. */