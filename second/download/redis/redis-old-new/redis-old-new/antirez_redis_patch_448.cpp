@@ -86,8 +86,8 @@ void setGenericCommand(client *c, int flags, robj *key, robj *val, robj *expire,
     setKey(c->db,key,val);
     server.dirty++;
     if (expire) setExpire(c->db,key,mstime()+milliseconds);
-    notifyKeyspaceEvent(REDIS_NOTIFY_STRING,"set",key,c->db->id);
-    if (expire) notifyKeyspaceEvent(REDIS_NOTIFY_GENERIC,
+    notifyKeyspaceEvent(NOTIFY_STRING,"set",key,c->db->id);
+    if (expire) notifyKeyspaceEvent(NOTIFY_GENERIC,
         "expire",key,c->db->id);
     addReply(c, ok_reply ? ok_reply : shared.ok);
 }
@@ -177,7 +177,7 @@ void getsetCommand(client *c) {
     if (getGenericCommand(c) == C_ERR) return;
     c->argv[2] = tryObjectEncoding(c->argv[2]);
     setKey(c->db,c->argv[1],c->argv[2]);
-    notifyKeyspaceEvent(REDIS_NOTIFY_STRING,"set",c->argv[1],c->db->id);
+    notifyKeyspaceEvent(NOTIFY_STRING,"set",c->argv[1],c->db->id);
     server.dirty++;
 }
 
@@ -234,7 +234,7 @@ void setrangeCommand(client *c) {
         o->ptr = sdsgrowzero(o->ptr,offset+sdslen(value));
         memcpy((char*)o->ptr+offset,value,sdslen(value));
         signalModifiedKey(c->db,c->argv[1]);
-        notifyKeyspaceEvent(REDIS_NOTIFY_STRING,
+        notifyKeyspaceEvent(NOTIFY_STRING,
             "setrange",c->argv[1],c->db->id);
         server.dirty++;
     }
@@ -320,7 +320,7 @@ void msetGenericCommand(client *c, int nx) {
     for (j = 1; j < c->argc; j += 2) {
         c->argv[j+1] = tryObjectEncoding(c->argv[j+1]);
         setKey(c->db,c->argv[j],c->argv[j+1]);
-        notifyKeyspaceEvent(REDIS_NOTIFY_STRING,"set",c->argv[j],c->db->id);
+        notifyKeyspaceEvent(NOTIFY_STRING,"set",c->argv[j],c->db->id);
     }
     server.dirty += (c->argc-1)/2;
     addReply(c, nx ? shared.cone : shared.ok);
@@ -351,7 +351,7 @@ void incrDecrCommand(client *c, long long incr) {
     value += incr;
 
     if (o && o->refcount == 1 && o->encoding == OBJ_ENCODING_INT &&
-        (value < 0 || value >= REDIS_SHARED_INTEGERS) &&
+        (value < 0 || value >= OBJ_SHARED_INTEGERS) &&
         value >= LONG_MIN && value <= LONG_MAX)
     {
         new = o;
@@ -365,7 +365,7 @@ void incrDecrCommand(client *c, long long incr) {
         }
     }
     signalModifiedKey(c->db,c->argv[1]);
-    notifyKeyspaceEvent(REDIS_NOTIFY_STRING,"incrby",c->argv[1],c->db->id);
+    notifyKeyspaceEvent(NOTIFY_STRING,"incrby",c->argv[1],c->db->id);
     server.dirty++;
     addReply(c,shared.colon);
     addReply(c,new);
@@ -415,7 +415,7 @@ void incrbyfloatCommand(client *c) {
     else
         dbAdd(c->db,c->argv[1],new);
     signalModifiedKey(c->db,c->argv[1]);
-    notifyKeyspaceEvent(REDIS_NOTIFY_STRING,"incrbyfloat",c->argv[1],c->db->id);
+    notifyKeyspaceEvent(NOTIFY_STRING,"incrbyfloat",c->argv[1],c->db->id);
     server.dirty++;
     addReplyBulk(c,new);
 
@@ -456,7 +456,7 @@ void appendCommand(client *c) {
         totlen = sdslen(o->ptr);
     }
     signalModifiedKey(c->db,c->argv[1]);
-    notifyKeyspaceEvent(REDIS_NOTIFY_STRING,"append",c->argv[1],c->db->id);
+    notifyKeyspaceEvent(NOTIFY_STRING,"append",c->argv[1],c->db->id);
     server.dirty++;
     addReplyLongLong(c,totlen);
 }