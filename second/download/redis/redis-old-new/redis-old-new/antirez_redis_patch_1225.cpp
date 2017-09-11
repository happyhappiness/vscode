@@ -62,8 +62,9 @@ void setGenericCommand(redisClient *c, int nx, robj *key, robj *val, robj *expir
     setKey(c->db,key,val);
     server.dirty++;
     if (expire) setExpire(c->db,key,mstime()+milliseconds);
-    notifyKeyspaceEvent("set",key,c->db->id);
-    if (expire) notifyKeyspaceEvent("expire",key,c->db->id);
+    notifyKeyspaceEvent(REDIS_NOTIFY_STRING,"set",key,c->db->id);
+    if (expire) notifyKeyspaceEvent(REDIS_NOTIFY_GENERIC,
+        "expire",key,c->db->id);
     addReply(c, nx ? shared.cone : shared.ok);
 }
 
@@ -110,7 +111,7 @@ void getsetCommand(redisClient *c) {
     if (getGenericCommand(c) == REDIS_ERR) return;
     c->argv[2] = tryObjectEncoding(c->argv[2]);
     setKey(c->db,c->argv[1],c->argv[2]);
-    notifyKeyspaceEvent("set",c->argv[1],c->db->id);
+    notifyKeyspaceEvent(REDIS_NOTIFY_STRING,"set",c->argv[1],c->db->id);
     server.dirty++;
 }
 
@@ -172,7 +173,8 @@ void setrangeCommand(redisClient *c) {
         o->ptr = sdsgrowzero(o->ptr,offset+sdslen(value));
         memcpy((char*)o->ptr+offset,value,sdslen(value));
         signalModifiedKey(c->db,c->argv[1]);
-        notifyKeyspaceEvent("setrange",c->argv[1],c->db->id);
+        notifyKeyspaceEvent(REDIS_NOTIFY_STRING,
+            "setrange",c->argv[1],c->db->id);
         server.dirty++;
     }
     addReplyLongLong(c,sdslen(o->ptr));
@@ -257,7 +259,7 @@ void msetGenericCommand(redisClient *c, int nx) {
     for (j = 1; j < c->argc; j += 2) {
         c->argv[j+1] = tryObjectEncoding(c->argv[j+1]);
         setKey(c->db,c->argv[j],c->argv[j+1]);
-        notifyKeyspaceEvent("set",c->argv[j],c->db->id);
+        notifyKeyspaceEvent(REDIS_NOTIFY_STRING,"set",c->argv[j],c->db->id);
     }
     server.dirty += (c->argc-1)/2;
     addReply(c, nx ? shared.cone : shared.ok);
@@ -292,7 +294,7 @@ void incrDecrCommand(redisClient *c, long long incr) {
     else
         dbAdd(c->db,c->argv[1],new);
     signalModifiedKey(c->db,c->argv[1]);
-    notifyKeyspaceEvent("incrby",c->argv[1],c->db->id);
+    notifyKeyspaceEvent(REDIS_NOTIFY_STRING,"incrby",c->argv[1],c->db->id);
     server.dirty++;
     addReply(c,shared.colon);
     addReply(c,new);
@@ -342,7 +344,7 @@ void incrbyfloatCommand(redisClient *c) {
     else
         dbAdd(c->db,c->argv[1],new);
     signalModifiedKey(c->db,c->argv[1]);
-    notifyKeyspaceEvent("incrbyfloat",c->argv[1],c->db->id);
+    notifyKeyspaceEvent(REDIS_NOTIFY_STRING,"incrbyfloat",c->argv[1],c->db->id);
     server.dirty++;
     addReplyBulk(c,new);
 
@@ -390,7 +392,7 @@ void appendCommand(redisClient *c) {
         totlen = sdslen(o->ptr);
     }
     signalModifiedKey(c->db,c->argv[1]);
-    notifyKeyspaceEvent("append",c->argv[1],c->db->id);
+    notifyKeyspaceEvent(REDIS_NOTIFY_STRING,"append",c->argv[1],c->db->id);
     server.dirty++;
     addReplyLongLong(c,totlen);
 }