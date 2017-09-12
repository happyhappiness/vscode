@@ -127,6 +127,10 @@
 #define REDIS_ENCODING_ZIPMAP 2 /* Encoded as zipmap */
 #define REDIS_ENCODING_HT 3     /* Encoded as an hash table */
 
+static char* strencoding[] = {
+    "raw", "int", "zipmap", "hashtable"
+};
+
 /* Object types only used for dumping to disk */
 #define REDIS_EXPIRETIME 253
 #define REDIS_SELECTDB 254
@@ -677,6 +681,7 @@ static void zrankCommand(redisClient *c);
 static void zrevrankCommand(redisClient *c);
 static void hsetCommand(redisClient *c);
 static void hgetCommand(redisClient *c);
+static void hdelCommand(redisClient *c);
 static void zremrangebyrankCommand(redisClient *c);
 static void zunionCommand(redisClient *c);
 static void zinterCommand(redisClient *c);
@@ -740,6 +745,7 @@ static struct redisCommand cmdTable[] = {
     {"zrevrank",zrevrankCommand,3,REDIS_CMD_INLINE,1,1,1},
     {"hset",hsetCommand,4,REDIS_CMD_BULK|REDIS_CMD_DENYOOM,1,1,1},
     {"hget",hgetCommand,3,REDIS_CMD_BULK,1,1,1},
+    {"hdel",hdelCommand,3,REDIS_CMD_BULK,1,1,1},
     {"incrby",incrbyCommand,3,REDIS_CMD_INLINE|REDIS_CMD_DENYOOM,1,1,1},
     {"decrby",decrbyCommand,3,REDIS_CMD_INLINE|REDIS_CMD_DENYOOM,1,1,1},
     {"getset",getsetCommand,3,REDIS_CMD_BULK|REDIS_CMD_DENYOOM,1,1,1},
@@ -5989,6 +5995,31 @@ static void hgetCommand(redisClient *c) {
     }
 }
 
+static void hdelCommand(redisClient *c) {
+    robj *o = lookupKeyRead(c->db,c->argv[1]);
+
+    if (o == NULL) {
+        addReply(c,shared.czero);
+        return;
+    } else {
+        int deleted = 0;
+
+        if (o->type != REDIS_HASH) {
+            addReply(c,shared.wrongtypeerr);
+            return;
+        }
+
+        if (o->encoding == REDIS_ENCODING_ZIPMAP) {
+            o->ptr = zipmapDel((unsigned char*) o->ptr,
+                (unsigned char*) c->argv[2]->ptr,
+                sdslen(c->argv[2]->ptr), &deleted);
+        } else {
+            deleted = dictDelete((dict*)o->ptr,c->argv[2]) == DICT_OK;
+        }
+        addReply(c,deleted ? shared.cone : shared.czero);
+    }
+}
+
 static void convertToRealHash(robj *o) {
     unsigned char *key, *val, *p, *zm = o->ptr;
     unsigned int klen, vlen;
@@ -8929,11 +8960,20 @@ static void debugCommand(redisClient *c) {
         val = dictGetEntryVal(de);
         if (!server.vm_enabled || (key->storage == REDIS_VM_MEMORY ||
                                    key->storage == REDIS_VM_SWAPPING)) {
+            char *strenc;
+            char buf[128];
+
+            if (val->encoding < (sizeof(strencoding)/sizeof(char*))) {
+                strenc = strencoding[val->encoding];
+            } else {
+                snprintf(buf,64,"unknown encoding %d\n", val->encoding);
+                strenc = buf;
+            }
             addReplySds(c,sdscatprintf(sdsempty(),
                 "+Key at:%p refcount:%d, value at:%p refcount:%d "
-                "encoding:%d serializedlength:%lld\r\n",
+                "encoding:%s serializedlength:%lld\r\n",
                 (void*)key, key->refcount, (void*)val, val->refcount,
-                val->encoding, (long long) rdbSavedObjectLen(val,NULL)));
+                strenc, (long long) rdbSavedObjectLen(val,NULL)));
         } else {
             addReplySds(c,sdscatprintf(sdsempty(),
                 "+Key at:%p refcount:%d, value swapped at: page %llu "