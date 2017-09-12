@@ -2601,6 +2601,21 @@ static void addReplyLong(redisClient *c, long l) {
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
@@ -6088,7 +6103,7 @@ static void hincrbyCommand(redisClient *c) {
     }
 
     server.dirty++;
-    addReplyLong(c, value);
+    addReplyLongLong(c, value);
 }
 
 static void hgetCommand(redisClient *c) {