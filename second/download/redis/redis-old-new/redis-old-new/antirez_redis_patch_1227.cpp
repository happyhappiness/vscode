@@ -153,6 +153,7 @@ void setbitCommand(redisClient *c) {
     byteval |= ((on & 0x1) << bit);
     ((uint8_t*)o->ptr)[byte] = byteval;
     signalModifiedKey(c->db,c->argv[1]);
+    notifyKeyspaceEvent("setbit",c->argv[1],c->db->id);
     server.dirty++;
     addReply(c, bitval ? shared.cone : shared.czero);
 }
@@ -346,9 +347,11 @@ void bitopCommand(redisClient *c) {
     if (maxlen) {
         o = createObject(REDIS_STRING,res);
         setKey(c->db,targetkey,o);
+        notifyKeyspaceEvent("set",targetkey,c->db->id);
         decrRefCount(o);
     } else if (dbDelete(c->db,targetkey)) {
         signalModifiedKey(c->db,targetkey);
+        notifyKeyspaceEvent("del",targetkey,c->db->id);
     }
     server.dirty++;
     addReplyLongLong(c,maxlen); /* Return the output string length in bytes. */