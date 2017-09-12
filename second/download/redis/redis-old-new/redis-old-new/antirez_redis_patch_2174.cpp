@@ -686,6 +686,9 @@ static void hlenCommand(redisClient *c);
 static void zremrangebyrankCommand(redisClient *c);
 static void zunionCommand(redisClient *c);
 static void zinterCommand(redisClient *c);
+static void hkeysCommand(redisClient *c);
+static void hvalsCommand(redisClient *c);
+static void hgetallCommand(redisClient *c);
 
 /*================================= Globals ================================= */
 
@@ -748,6 +751,9 @@ static struct redisCommand cmdTable[] = {
     {"hget",hgetCommand,3,REDIS_CMD_BULK,1,1,1},
     {"hdel",hdelCommand,3,REDIS_CMD_BULK,1,1,1},
     {"hlen",hlenCommand,2,REDIS_CMD_INLINE,1,1,1},
+    {"hkeys",hkeysCommand,2,REDIS_CMD_INLINE,1,1,1},
+    {"hvals",hvalsCommand,2,REDIS_CMD_INLINE,1,1,1},
+    {"hgetall",hgetallCommand,2,REDIS_CMD_INLINE,1,1,1},
     {"incrby",incrbyCommand,3,REDIS_CMD_INLINE|REDIS_CMD_DENYOOM,1,1,1},
     {"decrby",decrbyCommand,3,REDIS_CMD_INLINE|REDIS_CMD_DENYOOM,1,1,1},
     {"getset",getsetCommand,3,REDIS_CMD_BULK|REDIS_CMD_DENYOOM,1,1,1},
@@ -2714,7 +2720,7 @@ static void decrRefCount(void *obj) {
         case REDIS_SET: freeSetObject(o); break;
         case REDIS_ZSET: freeZsetObject(o); break;
         case REDIS_HASH: freeHashObject(o); break;
-        default: redisAssert(0 != 0); break;
+        default: redisAssert(0); break;
         }
         if (server.vm_enabled) pthread_mutex_lock(&server.obj_freelist_mutex);
         if (listLength(server.objfreelist) > REDIS_OBJFREELIST_MAX ||
@@ -3212,7 +3218,7 @@ static int rdbSaveObject(FILE *fp, robj *o) {
             dictReleaseIterator(di);
         }
     } else {
-        redisAssert(0 != 0);
+        redisAssert(0);
     }
     return 0;
 }
@@ -3432,7 +3438,7 @@ static robj *rdbLoadIntegerObject(FILE *fp, int enctype) {
         val = (int32_t)v;
     } else {
         val = 0; /* anti-warning */
-        redisAssert(0!=0);
+        redisAssert(0);
     }
     return createObject(REDIS_STRING,sdscatprintf(sdsempty(),"%lld",val));
 }
@@ -3471,7 +3477,7 @@ static robj *rdbLoadStringObject(FILE*fp) {
         case REDIS_RDB_ENC_LZF:
             return tryObjectSharing(rdbLoadLzfStringObject(fp));
         default:
-            redisAssert(0!=0);
+            redisAssert(0);
         }
     }
 
@@ -3593,7 +3599,7 @@ static robj *rdbLoadObject(int type, FILE *fp) {
             }
         }
     } else {
-        redisAssert(0 != 0);
+        redisAssert(0);
     }
     return o;
 }
@@ -5917,6 +5923,74 @@ static void hlenCommand(redisClient *c) {
     addReplyUlong(c,len);
 }
 
+#define REDIS_GETALL_KEYS 1
+#define REDIS_GETALL_VALS 2
+static void genericHgetallCommand(redisClient *c, int flags) {
+    robj *o, *lenobj;
+    unsigned long count = 0;
+
+    if ((o = lookupKeyReadOrReply(c,c->argv[1],shared.nullmultibulk)) == NULL
+        || checkType(c,o,REDIS_HASH)) return;
+
+    lenobj = createObject(REDIS_STRING,NULL);
+    addReply(c,lenobj);
+    decrRefCount(lenobj);
+
+    if (o->encoding == REDIS_ENCODING_ZIPMAP) {
+        unsigned char *p = zipmapRewind(o->ptr);
+        unsigned char *field, *val;
+        unsigned int flen, vlen;
+
+        while((p = zipmapNext(p,&field,&flen,&val,&vlen)) != NULL) {
+            robj *aux;
+
+            if (flags & REDIS_GETALL_KEYS) {
+                aux = createStringObject((char*)field,flen);
+                addReplyBulk(c,aux);
+                decrRefCount(aux);
+                count++;
+            }
+            if (flags & REDIS_GETALL_VALS) {
+                aux = createStringObject((char*)val,vlen);
+                addReplyBulk(c,aux);
+                decrRefCount(aux);
+                count++;
+            }
+        }
+    } else {
+        dictIterator *di = dictGetIterator(o->ptr);
+        dictEntry *de;
+
+        while((de = dictNext(di)) != NULL) {
+            robj *fieldobj = dictGetEntryKey(de);
+            robj *valobj = dictGetEntryVal(de);
+
+            if (flags & REDIS_GETALL_KEYS) {
+                addReplyBulk(c,fieldobj);
+                count++;
+            }
+            if (flags & REDIS_GETALL_VALS) {
+                addReplyBulk(c,valobj);
+                count++;
+            }
+        }
+        dictReleaseIterator(di);
+    }
+    lenobj->ptr = sdscatprintf(sdsempty(),"*%lu\r\n",count);
+}
+
+static void hkeysCommand(redisClient *c) {
+    genericHgetallCommand(c,REDIS_GETALL_KEYS);
+}
+
+static void hvalsCommand(redisClient *c) {
+    genericHgetallCommand(c,REDIS_GETALL_VALS);
+}
+
+static void hgetallCommand(redisClient *c) {
+    genericHgetallCommand(c,REDIS_GETALL_KEYS|REDIS_GETALL_VALS);
+}
+
 static void convertToRealHash(robj *o) {
     unsigned char *key, *val, *p, *zm = o->ptr;
     unsigned int klen, vlen;
@@ -7675,7 +7749,7 @@ static int rewriteAppendOnlyFile(char *filename) {
                     dictReleaseIterator(di);
                 }
             } else {
-                redisAssert(0 != 0);
+                redisAssert(0);
             }
             /* Save the expire time */
             if (expiretime != -1) {