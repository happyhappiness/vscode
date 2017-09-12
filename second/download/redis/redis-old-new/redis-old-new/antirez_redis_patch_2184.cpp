@@ -666,6 +666,8 @@ static void brpopCommand(redisClient *c);
 static void appendCommand(redisClient *c);
 static void substrCommand(redisClient *c);
 static void zrankCommand(redisClient *c);
+static void hsetCommand(redisClient *c);
+static void hgetCommand(redisClient *c);
 
 /*================================= Globals ================================= */
 
@@ -720,6 +722,8 @@ static struct redisCommand cmdTable[] = {
     {"zcard",zcardCommand,2,REDIS_CMD_INLINE,1,1,1},
     {"zscore",zscoreCommand,3,REDIS_CMD_BULK|REDIS_CMD_DENYOOM,1,1,1},
     {"zrank",zrankCommand,3,REDIS_CMD_INLINE,1,1,1},
+    {"hset",hsetCommand,4,REDIS_CMD_BULK|REDIS_CMD_DENYOOM,1,1,1},
+    {"hget",hgetCommand,3,REDIS_CMD_BULK,1,1,1},
     {"incrby",incrbyCommand,3,REDIS_CMD_INLINE|REDIS_CMD_DENYOOM,1,1,1},
     {"decrby",decrbyCommand,3,REDIS_CMD_INLINE|REDIS_CMD_DENYOOM,1,1,1},
     {"getset",getsetCommand,3,REDIS_CMD_BULK|REDIS_CMD_DENYOOM,1,1,1},
@@ -5573,6 +5577,76 @@ static void zrankCommand(redisClient *c) {
     }
 }
 
+/* ==================================== Hash ================================ */
+static void hsetCommand(redisClient *c) {
+    int update = 0;
+    robj *o = lookupKeyWrite(c->db,c->argv[1]);
+
+    if (o == NULL) {
+        o = createHashObject();
+        dictAdd(c->db->dict,c->argv[1],o);
+        incrRefCount(c->argv[1]);
+    } else {
+        if (o->type != REDIS_HASH) {
+            addReply(c,shared.wrongtypeerr);
+            return;
+        }
+    }
+    if (o->encoding == REDIS_ENCODING_ZIPMAP) {
+        unsigned char *zm = o->ptr;
+
+        zm = zipmapSet(zm,c->argv[2]->ptr,sdslen(c->argv[2]->ptr),
+            c->argv[3]->ptr,sdslen(c->argv[3]->ptr),&update);
+    } else {
+        if (dictAdd(o->ptr,c->argv[2],c->argv[3]) == DICT_OK) {
+            incrRefCount(c->argv[2]);
+        } else {
+            update = 1;
+        }
+        incrRefCount(c->argv[3]);
+    }
+    server.dirty++;
+    addReplySds(c,sdscatprintf(sdsempty(),":%d\r\n",update == 0));
+}
+
+static void hgetCommand(redisClient *c) {
+    robj *o = lookupKeyRead(c->db,c->argv[1]);
+
+    if (o == NULL) {
+        addReply(c,shared.nullbulk);
+        return;
+    } else {
+        if (o->encoding == REDIS_ENCODING_ZIPMAP) {
+            unsigned char *zm = o->ptr;
+            unsigned char *val;
+            unsigned int vlen;
+
+            if (zipmapGet(zm,c->argv[2]->ptr,sdslen(c->argv[2]->ptr), &val,&vlen)) {
+                addReplySds(c,sdscatprintf(sdsempty(),"$%u\r\n", vlen));
+                addReplySds(c,sdsnewlen(val,vlen));
+                addReply(c,shared.crlf);
+                return;
+            } else {
+                addReply(c,shared.nullbulk);
+                return;
+            }
+        } else {
+            struct dictEntry *de;
+
+            de = dictFind(o->ptr,c->argv[2]);
+            if (de == NULL) {
+                addReply(c,shared.nullbulk);
+            } else {
+                robj *e = dictGetEntryVal(de);
+
+                addReplyBulkLen(c,e);
+                addReply(c,e);
+                addReply(c,shared.crlf);
+            }
+        }
+    }
+}
+
 /* ========================= Non type-specific commands  ==================== */
 
 static void flushdbCommand(redisClient *c) {