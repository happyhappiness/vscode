@@ -62,6 +62,8 @@ void setGenericCommand(redisClient *c, int nx, robj *key, robj *val, robj *expir
     setKey(c->db,key,val);
     server.dirty++;
     if (expire) setExpire(c->db,key,mstime()+milliseconds);
+    notifyKeyspaceEvent("set",key,c->db->id);
+    if (expire) notifyKeyspaceEvent("expire",key,c->db->id);
     addReply(c, nx ? shared.cone : shared.ok);
 }
 
@@ -253,6 +255,7 @@ void msetGenericCommand(redisClient *c, int nx) {
     for (j = 1; j < c->argc; j += 2) {
         c->argv[j+1] = tryObjectEncoding(c->argv[j+1]);
         setKey(c->db,c->argv[j],c->argv[j+1]);
+        notifyKeyspaceEvent("set",c->argv[j+1],c->db->id);
     }
     server.dirty += (c->argc-1)/2;
     addReply(c, nx ? shared.cone : shared.ok);
@@ -287,6 +290,7 @@ void incrDecrCommand(redisClient *c, long long incr) {
     else
         dbAdd(c->db,c->argv[1],new);
     signalModifiedKey(c->db,c->argv[1]);
+    notifyKeyspaceEvent("incrby",c->argv[1],c->db->id);
     server.dirty++;
     addReply(c,shared.colon);
     addReply(c,new);
@@ -336,6 +340,7 @@ void incrbyfloatCommand(redisClient *c) {
     else
         dbAdd(c->db,c->argv[1],new);
     signalModifiedKey(c->db,c->argv[1]);
+    notifyKeyspaceEvent("incrbyfloat",c->argv[1],c->db->id);
     server.dirty++;
     addReplyBulk(c,new);
 
@@ -383,6 +388,7 @@ void appendCommand(redisClient *c) {
         totlen = sdslen(o->ptr);
     }
     signalModifiedKey(c->db,c->argv[1]);
+    notifyKeyspaceEvent("append",c->argv[1],c->db->id);
     server.dirty++;
     addReplyLongLong(c,totlen);
 }