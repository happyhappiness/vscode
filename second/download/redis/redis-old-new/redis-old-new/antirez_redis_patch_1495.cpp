@@ -12,16 +12,17 @@ static int checkStringLength(redisClient *c, long long size) {
     return REDIS_OK;
 }
 
-void setGenericCommand(redisClient *c, int nx, robj *key, robj *val, robj *expire) {
-    long seconds = 0; /* initialized to avoid an harmness warning */
+void setGenericCommand(redisClient *c, int nx, robj *key, robj *val, robj *expire, int unit) {
+    long long milliseconds = 0; /* initialized to avoid an harmness warning */
 
     if (expire) {
-        if (getLongFromObjectOrReply(c, expire, &seconds, NULL) != REDIS_OK)
+        if (getLongLongFromObjectOrReply(c, expire, &milliseconds, NULL) != REDIS_OK)
             return;
-        if (seconds <= 0) {
+        if (milliseconds <= 0) {
             addReplyError(c,"invalid expire time in SETEX");
             return;
         }
+        if (unit == UNIT_SECONDS) milliseconds *= 1000;
     }
 
     if (lookupKeyWrite(c->db,key) != NULL && nx) {
@@ -30,23 +31,28 @@ void setGenericCommand(redisClient *c, int nx, robj *key, robj *val, robj *expir
     }
     setKey(c->db,key,val);
     server.dirty++;
-    if (expire) setExpire(c->db,key,(time(NULL)+seconds)*1000);
+    if (expire) setExpire(c->db,key,mstime()+milliseconds);
     addReply(c, nx ? shared.cone : shared.ok);
 }
 
 void setCommand(redisClient *c) {
     c->argv[2] = tryObjectEncoding(c->argv[2]);
-    setGenericCommand(c,0,c->argv[1],c->argv[2],NULL);
+    setGenericCommand(c,0,c->argv[1],c->argv[2],NULL,0);
 }
 
 void setnxCommand(redisClient *c) {
     c->argv[2] = tryObjectEncoding(c->argv[2]);
-    setGenericCommand(c,1,c->argv[1],c->argv[2],NULL);
+    setGenericCommand(c,1,c->argv[1],c->argv[2],NULL,0);
 }
 
 void setexCommand(redisClient *c) {
     c->argv[3] = tryObjectEncoding(c->argv[3]);
-    setGenericCommand(c,0,c->argv[1],c->argv[3],c->argv[2]);
+    setGenericCommand(c,0,c->argv[1],c->argv[3],c->argv[2],UNIT_SECONDS);
+}
+
+void psetexCommand(redisClient *c) {
+    c->argv[3] = tryObjectEncoding(c->argv[3]);
+    setGenericCommand(c,0,c->argv[1],c->argv[3],c->argv[2],UNIT_MILLISECONDS);
 }
 
 int getGenericCommand(redisClient *c) {