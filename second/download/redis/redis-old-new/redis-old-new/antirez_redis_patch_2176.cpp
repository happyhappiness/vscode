@@ -682,6 +682,7 @@ static void zrevrankCommand(redisClient *c);
 static void hsetCommand(redisClient *c);
 static void hgetCommand(redisClient *c);
 static void hdelCommand(redisClient *c);
+static void hlenCommand(redisClient *c);
 static void zremrangebyrankCommand(redisClient *c);
 static void zunionCommand(redisClient *c);
 static void zinterCommand(redisClient *c);
@@ -746,6 +747,7 @@ static struct redisCommand cmdTable[] = {
     {"hset",hsetCommand,4,REDIS_CMD_BULK|REDIS_CMD_DENYOOM,1,1,1},
     {"hget",hgetCommand,3,REDIS_CMD_BULK,1,1,1},
     {"hdel",hdelCommand,3,REDIS_CMD_BULK,1,1,1},
+    {"hlen",hlenCommand,2,REDIS_CMD_INLINE,1,1,1},
     {"incrby",incrbyCommand,3,REDIS_CMD_INLINE|REDIS_CMD_DENYOOM,1,1,1},
     {"decrby",decrbyCommand,3,REDIS_CMD_INLINE|REDIS_CMD_DENYOOM,1,1,1},
     {"getset",getsetCommand,3,REDIS_CMD_BULK|REDIS_CMD_DENYOOM,1,1,1},
@@ -2480,6 +2482,14 @@ static void addReplyLong(redisClient *c, long l) {
     addReplySds(c,sdsnewlen(buf,len));
 }
 
+static void addReplyUlong(redisClient *c, unsigned long ul) {
+    char buf[128];
+    size_t len;
+
+    len = snprintf(buf,sizeof(buf),":%lu\r\n",ul);
+    addReplySds(c,sdsnewlen(buf,len));
+}
+
 static void addReplyBulkLen(redisClient *c, robj *obj) {
     size_t len;
 
@@ -2739,6 +2749,26 @@ static robj *lookupKeyWrite(redisDb *db, robj *key) {
     return lookupKey(db,key);
 }
 
+static robj *lookupKeyReadOrReply(redisClient *c, robj *key, robj *reply) {
+    robj *o = lookupKeyRead(c->db, key);
+    if (!o) addReply(c,reply);
+    return o;
+}
+
+static robj *lookupKeyWriteOrReply(redisClient *c, robj *key, robj *reply) {
+    robj *o = lookupKeyWrite(c->db, key);
+    if (!o) addReply(c,reply);
+    return o;
+}
+
+static int checkType(redisClient *c, robj *o, int type) {
+    if (o->type != type) {
+        addReply(c,shared.wrongtypeerr);
+        return 1;
+    }
+    return 0;
+}
+
 static int deleteKey(redisDb *db, robj *key) {
     int retval;
 
@@ -6019,7 +6049,7 @@ static void hgetCommand(redisClient *c) {
 }
 
 static void hdelCommand(redisClient *c) {
-    robj *o = lookupKeyRead(c->db,c->argv[1]);
+    robj *o = lookupKeyWrite(c->db,c->argv[1]);
 
     if (o == NULL) {
         addReply(c,shared.czero);
@@ -6043,6 +6073,18 @@ static void hdelCommand(redisClient *c) {
     }
 }
 
+static void hlenCommand(redisClient *c) {
+    robj *o;
+    unsigned long len;
+
+    if ((o = lookupKeyWriteOrReply(c,c->argv[1],shared.czero)) == NULL ||
+        checkType(c,o,REDIS_HASH)) return;
+
+    len = (o->encoding == REDIS_ENCODING_ZIPMAP) ?
+            zipmapLen((unsigned char*)o->ptr) : dictSize((dict*)o->ptr);
+    addReplyUlong(c,len);
+}
+
 static void convertToRealHash(robj *o) {
     unsigned char *key, *val, *p, *zm = o->ptr;
     unsigned int klen, vlen;