@@ -367,7 +367,7 @@ static struct redisCommand cmdTable[] = {
     {"get",getCommand,2,REDIS_CMD_INLINE},
     {"set",setCommand,3,REDIS_CMD_BULK},
     {"setnx",setnxCommand,3,REDIS_CMD_BULK},
-    {"del",delCommand,2,REDIS_CMD_INLINE},
+    {"del",delCommand,-2,REDIS_CMD_INLINE},
     {"exists",existsCommand,2,REDIS_CMD_INLINE},
     {"incr",incrCommand,2,REDIS_CMD_INLINE},
     {"decr",decrCommand,2,REDIS_CMD_INLINE},
@@ -2012,6 +2012,7 @@ static robj *rdbLoadLzfStringObject(FILE*fp, int rdbver) {
     if ((val = sdsnewlen(NULL,len)) == NULL) goto err;
     if (fread(c,clen,1,fp) == 0) goto err;
     if (lzf_decompress(c,clen,val,len) == 0) goto err;
+    zfree(c);
     return createObject(REDIS_STRING,val);
 err:
     zfree(c);
@@ -2305,11 +2306,24 @@ static void decrbyCommand(redisClient *c) {
 /* ========================= Type agnostic commands ========================= */
 
 static void delCommand(redisClient *c) {
-    if (deleteKey(c->db,c->argv[1])) {
-        server.dirty++;
-        addReply(c,shared.cone);
-    } else {
+    int deleted = 0, j;
+
+    for (j = 1; j < c->argc; j++) {
+        if (deleteKey(c->db,c->argv[j])) {
+            server.dirty++;
+            deleted++;
+        }
+    }
+    switch(deleted) {
+    case 0:
         addReply(c,shared.czero);
+        break;
+    case 1:
+        addReply(c,shared.cone);
+        break;
+    default:
+        addReplySds(c,sdscatprintf(sdsempty(),":%d\r\n",deleted));
+        break;
     }
 }
 