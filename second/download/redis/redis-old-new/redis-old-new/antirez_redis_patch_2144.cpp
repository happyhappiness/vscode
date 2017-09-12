@@ -704,8 +704,9 @@ static void substrCommand(redisClient *c);
 static void zrankCommand(redisClient *c);
 static void zrevrankCommand(redisClient *c);
 static void hsetCommand(redisClient *c);
-static void hmsetCommand(redisClient *c);
 static void hgetCommand(redisClient *c);
+static void hmsetCommand(redisClient *c);
+static void hmgetCommand(redisClient *c);
 static void hdelCommand(redisClient *c);
 static void hlenCommand(redisClient *c);
 static void zremrangebyrankCommand(redisClient *c);
@@ -781,9 +782,10 @@ static struct redisCommand cmdTable[] = {
     {"zrank",zrankCommand,3,REDIS_CMD_BULK,NULL,1,1,1},
     {"zrevrank",zrevrankCommand,3,REDIS_CMD_BULK,NULL,1,1,1},
     {"hset",hsetCommand,4,REDIS_CMD_BULK|REDIS_CMD_DENYOOM,NULL,1,1,1},
+    {"hget",hgetCommand,3,REDIS_CMD_BULK,NULL,1,1,1},
     {"hmset",hmsetCommand,-4,REDIS_CMD_BULK|REDIS_CMD_DENYOOM,NULL,1,1,1},
+    {"hmget",hmgetCommand,-3,REDIS_CMD_BULK,NULL,1,1,1},
     {"hincrby",hincrbyCommand,4,REDIS_CMD_INLINE|REDIS_CMD_DENYOOM,NULL,1,1,1},
-    {"hget",hgetCommand,3,REDIS_CMD_BULK,NULL,1,1,1},
     {"hdel",hdelCommand,3,REDIS_CMD_BULK,NULL,1,1,1},
     {"hlen",hlenCommand,2,REDIS_CMD_INLINE,NULL,1,1,1},
     {"hkeys",hkeysCommand,2,REDIS_CMD_INLINE,NULL,1,1,1},
@@ -6177,6 +6179,55 @@ static void hgetCommand(redisClient *c) {
     }
 }
 
+static void hmgetCommand(redisClient *c) {
+    int i;
+
+    robj *o = lookupKeyRead(c->db, c->argv[1]);
+    if (o == NULL) {
+        addReplySds(c,sdscatprintf(sdsempty(),"*%d\r\n",c->argc-2));
+        for (i = 2; i < c->argc; i++) {
+            addReply(c,shared.nullbulk);
+        }
+        return;
+    } else {
+        if (o->type != REDIS_HASH) {
+            addReply(c,shared.wrongtypeerr);
+            return;
+        }
+    }
+
+    addReplySds(c,sdscatprintf(sdsempty(),"*%d\r\n",c->argc-2));
+    if (o->encoding == REDIS_ENCODING_ZIPMAP) {
+        unsigned char *zm = o->ptr;
+        unsigned char *v;
+        unsigned int vlen;
+        robj *field;
+
+        for (i = 2; i < c->argc; i++) {
+            field = getDecodedObject(c->argv[i]);
+            if (zipmapGet(zm,field->ptr,sdslen(field->ptr),&v,&vlen)) {
+                addReplySds(c,sdscatprintf(sdsempty(),"$%u\r\n", vlen));
+                addReplySds(c,sdsnewlen(v,vlen));
+                addReply(c,shared.crlf);
+            } else {
+                addReply(c,shared.nullbulk);
+            }
+            decrRefCount(field);
+        }
+    } else {
+        dictEntry *de;
+
+        for (i = 2; i < c->argc; i++) {
+            de = dictFind(o->ptr,c->argv[i]);
+            if (de != NULL) {
+                addReplyBulk(c,(robj*)dictGetEntryVal(de));
+            } else {
+                addReply(c,shared.nullbulk);
+            }
+        }
+    }
+}
+
 static void hdelCommand(redisClient *c) {
     robj *o;
     int deleted = 0;