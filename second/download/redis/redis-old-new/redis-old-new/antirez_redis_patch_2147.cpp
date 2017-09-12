@@ -2602,6 +2602,21 @@ static void addReplyLong(redisClient *c, long l) {
     addReplySds(c,sdsnewlen(buf,len));
 }
 
+static void addReplyLongLong(redisClient *c, long long ll) {
+    char buf[128];
+    size_t len;
+
+    if (ll == 0) {
+        addReply(c,shared.czero);
+        return;
+    } else if (ll == 1) {
+        addReply(c,shared.cone);
+        return;
+    }
+    len = snprintf(buf,sizeof(buf),":%lld\r\n",ll);
+    addReplySds(c,sdsnewlen(buf,len));
+}
+
 static void addReplyUlong(redisClient *c, unsigned long ul) {
     char buf[128];
     size_t len;
@@ -6038,10 +6053,7 @@ static void hincrbyCommand(redisClient *c) {
         }
     }
 
-    robj *o_incr = getDecodedObject(c->argv[3]);
-    incr = strtoll(o_incr->ptr, NULL, 10);
-    decrRefCount(o_incr);
-
+    incr = strtoll(c->argv[3]->ptr, NULL, 10);
     if (o->encoding == REDIS_ENCODING_ZIPMAP) {
         unsigned char *zm = o->ptr;
         unsigned char *zval;
@@ -6092,7 +6104,7 @@ static void hincrbyCommand(redisClient *c) {
     }
 
     server.dirty++;
-    addReplyLong(c, value);
+    addReplyLongLong(c, value);
 }
 
 static void hgetCommand(redisClient *c) {