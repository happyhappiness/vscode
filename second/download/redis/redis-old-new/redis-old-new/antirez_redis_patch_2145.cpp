@@ -704,6 +704,7 @@ static void substrCommand(redisClient *c);
 static void zrankCommand(redisClient *c);
 static void zrevrankCommand(redisClient *c);
 static void hsetCommand(redisClient *c);
+static void hmsetCommand(redisClient *c);
 static void hgetCommand(redisClient *c);
 static void hdelCommand(redisClient *c);
 static void hlenCommand(redisClient *c);
@@ -780,6 +781,7 @@ static struct redisCommand cmdTable[] = {
     {"zrank",zrankCommand,3,REDIS_CMD_BULK,NULL,1,1,1},
     {"zrevrank",zrevrankCommand,3,REDIS_CMD_BULK,NULL,1,1,1},
     {"hset",hsetCommand,4,REDIS_CMD_BULK|REDIS_CMD_DENYOOM,NULL,1,1,1},
+    {"hmset",hmsetCommand,-4,REDIS_CMD_BULK|REDIS_CMD_DENYOOM,NULL,1,1,1},
     {"hincrby",hincrbyCommand,4,REDIS_CMD_INLINE|REDIS_CMD_DENYOOM,NULL,1,1,1},
     {"hget",hgetCommand,3,REDIS_CMD_BULK,NULL,1,1,1},
     {"hdel",hdelCommand,3,REDIS_CMD_BULK,NULL,1,1,1},
@@ -6004,6 +6006,70 @@ static void hsetCommand(redisClient *c) {
     addReplySds(c,sdscatprintf(sdsempty(),":%d\r\n",update == 0));
 }
 
+static void hmsetCommand(redisClient *c) {
+    int i;
+    robj *o, *key, *val;
+
+    if ((c->argc % 2) == 1) {
+        addReplySds(c,sdsnew("-ERR wrong number of arguments for HMSET\r\n"));
+        return;
+    }
+
+    if ((o = lookupKeyWrite(c->db,c->argv[1])) == NULL) {
+        o = createHashObject();
+        dictAdd(c->db->dict,c->argv[1],o);
+        incrRefCount(c->argv[1]);
+    } else {
+        if (o->type != REDIS_HASH) {
+            addReply(c,shared.wrongtypeerr);
+            return;
+        }
+    }
+
+    /* We want to convert the zipmap into an hash table right now if the
+     * entry to be added is too big. */
+    if (o->encoding == REDIS_ENCODING_ZIPMAP) {
+        for (i = 2; i < c->argc; i+=2) {
+            if ((c->argv[i]->encoding == REDIS_ENCODING_RAW &&
+                  sdslen(c->argv[i]->ptr) > server.hash_max_zipmap_value) ||
+                (c->argv[i+1]->encoding == REDIS_ENCODING_RAW &&
+                  sdslen(c->argv[i+1]->ptr) > server.hash_max_zipmap_value)) {
+                convertToRealHash(o);
+                break;
+            }
+        }
+    }
+
+    if (o->encoding == REDIS_ENCODING_ZIPMAP) {
+        unsigned char *zm = o->ptr;
+
+        for (i = 2; i < c->argc; i+=2) {
+            key = getDecodedObject(c->argv[i]);
+            val = getDecodedObject(c->argv[i+1]);
+            zm = zipmapSet(zm,key->ptr,sdslen(key->ptr),
+                              val->ptr,sdslen(val->ptr),NULL);
+            decrRefCount(key);
+            decrRefCount(val);
+            o->ptr = zm;
+        }
+
+        /* And here there is the second check for hash conversion. */
+        if (zipmapLen(zm) > server.hash_max_zipmap_entries)
+            convertToRealHash(o);
+    } else {
+        for (i = 2; i < c->argc; i+=2) {
+            key = tryObjectEncoding(c->argv[i]);
+            val = tryObjectEncoding(c->argv[i+1]);
+            if (dictReplace(o->ptr,key,val)) {
+                incrRefCount(key);
+            }
+            incrRefCount(val);
+        }
+    }
+
+    addReply(c, shared.ok);
+}
+
 static void hincrbyCommand(redisClient *c) {
     long long value = 0, incr = 0;
     robj *o = lookupKeyWrite(c->db,c->argv[1]);