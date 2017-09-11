@@ -110,6 +110,7 @@ void getsetCommand(redisClient *c) {
     if (getGenericCommand(c) == REDIS_ERR) return;
     c->argv[2] = tryObjectEncoding(c->argv[2]);
     setKey(c->db,c->argv[1],c->argv[2]);
+    notifyKeyspaceEvent("set",c->argv[1],c->db->id);
     server.dirty++;
 }
 
@@ -171,6 +172,7 @@ void setrangeCommand(redisClient *c) {
         o->ptr = sdsgrowzero(o->ptr,offset+sdslen(value));
         memcpy((char*)o->ptr+offset,value,sdslen(value));
         signalModifiedKey(c->db,c->argv[1]);
+        notifyKeyspaceEvent("setrange",c->argv[1],c->db->id);
         server.dirty++;
     }
     addReplyLongLong(c,sdslen(o->ptr));
@@ -255,7 +257,7 @@ void msetGenericCommand(redisClient *c, int nx) {
     for (j = 1; j < c->argc; j += 2) {
         c->argv[j+1] = tryObjectEncoding(c->argv[j+1]);
         setKey(c->db,c->argv[j],c->argv[j+1]);
-        notifyKeyspaceEvent("set",c->argv[j+1],c->db->id);
+        notifyKeyspaceEvent("set",c->argv[j],c->db->id);
     }
     server.dirty += (c->argc-1)/2;
     addReply(c, nx ? shared.cone : shared.ok);