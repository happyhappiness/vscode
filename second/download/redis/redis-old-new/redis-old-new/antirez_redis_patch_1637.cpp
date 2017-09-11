@@ -93,10 +93,20 @@ robj *createHashObject(void) {
 
 robj *createZsetObject(void) {
     zset *zs = zmalloc(sizeof(*zs));
+    robj *o;
 
     zs->dict = dictCreate(&zsetDictType,NULL);
     zs->zsl = zslCreate();
-    return createObject(REDIS_ZSET,zs);
+    o = createObject(REDIS_ZSET,zs);
+    o->encoding = REDIS_ENCODING_SKIPLIST;
+    return o;
+}
+
+robj *createZsetZiplistObject(void) {
+    unsigned char *zl = ziplistNew();
+    robj *o = createObject(REDIS_ZSET,zl);
+    o->encoding = REDIS_ENCODING_ZIPLIST;
+    return o;
 }
 
 void freeStringObject(robj *o) {
@@ -132,11 +142,20 @@ void freeSetObject(robj *o) {
 }
 
 void freeZsetObject(robj *o) {
-    zset *zs = o->ptr;
-
-    dictRelease(zs->dict);
-    zslFree(zs->zsl);
-    zfree(zs);
+    zset *zs;
+    switch (o->encoding) {
+    case REDIS_ENCODING_SKIPLIST:
+        zs = o->ptr;
+        dictRelease(zs->dict);
+        zslFree(zs->zsl);
+        zfree(zs);
+        break;
+    case REDIS_ENCODING_ZIPLIST:
+        zfree(o->ptr);
+        break;
+    default:
+        redisPanic("Unknown sorted set encoding");
+    }
 }
 
 void freeHashObject(robj *o) {
@@ -183,6 +202,16 @@ int checkType(redisClient *c, robj *o, int type) {
     return 0;
 }
 
+int isObjectRepresentableAsLongLong(robj *o, long long *llval) {
+    redisAssert(o->type == REDIS_STRING);
+    if (o->encoding == REDIS_ENCODING_INT) {
+        if (llval) *llval = (long) o->ptr;
+        return REDIS_OK;
+    } else {
+        return string2ll(o->ptr,sdslen(o->ptr),llval) ? REDIS_OK : REDIS_ERR;
+    }
+}
+
 /* Try to encode a string object in order to save space */
 robj *tryObjectEncoding(robj *o) {
     long value;
@@ -200,7 +229,7 @@ robj *tryObjectEncoding(robj *o) {
     redisAssert(o->type == REDIS_STRING);
 
     /* Check if we can represent this string as a long integer */
-    if (isStringRepresentableAsLong(s,&value) == REDIS_ERR) return o;
+    if (!string2l(s,sdslen(s),&value)) return o;
 
     /* Ok, this object can be encoded...
      *
@@ -402,6 +431,7 @@ char *strEncoding(int encoding) {
     case REDIS_ENCODING_LINKEDLIST: return "linkedlist";
     case REDIS_ENCODING_ZIPLIST: return "ziplist";
     case REDIS_ENCODING_INTSET: return "intset";
+    case REDIS_ENCODING_SKIPLIST: return "skiplist";
     default: return "unknown";
     }
 }
@@ -416,3 +446,42 @@ unsigned long estimateObjectIdleTime(robj *o) {
                     REDIS_LRU_CLOCK_RESOLUTION;
     }
 }
+
+/* This is an helper function for the DEBUG command. We need to lookup keys
+ * without any modification of LRU or other parameters. */
+robj *objectCommandLookup(redisClient *c, robj *key) {
+    dictEntry *de;
+
+    if ((de = dictFind(c->db->dict,key->ptr)) == NULL) return NULL;
+    return (robj*) dictGetEntryVal(de);
+}
+
+robj *objectCommandLookupOrReply(redisClient *c, robj *key, robj *reply) {
+    robj *o = objectCommandLookup(c,key);
+
+    if (!o) addReply(c, reply);
+    return o;
+}
+
+/* Object command allows to inspect the internals of an Redis Object.
+ * Usage: OBJECT <verb> ... arguments ... */
+void objectCommand(redisClient *c) {
+    robj *o;
+
+    if (!strcasecmp(c->argv[1]->ptr,"refcount") && c->argc == 3) {
+        if ((o = objectCommandLookupOrReply(c,c->argv[2],shared.nullbulk))
+                == NULL) return;
+        addReplyLongLong(c,o->refcount);
+    } else if (!strcasecmp(c->argv[1]->ptr,"encoding") && c->argc == 3) {
+        if ((o = objectCommandLookupOrReply(c,c->argv[2],shared.nullbulk))
+                == NULL) return;
+        addReplyBulkCString(c,strEncoding(o->encoding));
+    } else if (!strcasecmp(c->argv[1]->ptr,"idletime") && c->argc == 3) {
+        if ((o = objectCommandLookupOrReply(c,c->argv[2],shared.nullbulk))
+                == NULL) return;
+        addReplyLongLong(c,estimateObjectIdleTime(o));
+    } else {
+        addReplyError(c,"Syntax error. Try OBJECT (refcount|encoding|idletime)");
+    }
+}
+