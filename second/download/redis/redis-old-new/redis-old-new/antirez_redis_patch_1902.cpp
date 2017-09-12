@@ -74,7 +74,16 @@ robj *createZiplistObject(void) {
 
 robj *createSetObject(void) {
     dict *d = dictCreate(&setDictType,NULL);
-    return createObject(REDIS_SET,d);
+    robj *o = createObject(REDIS_SET,d);
+    o->encoding = REDIS_ENCODING_HT;
+    return o;
+}
+
+robj *createIntsetObject(void) {
+    intset *is = intsetNew();
+    robj *o = createObject(REDIS_SET,is);
+    o->encoding = REDIS_ENCODING_INTSET;
+    return o;
 }
 
 robj *createHashObject(void) {
@@ -115,7 +124,16 @@ void freeListObject(robj *o) {
 }
 
 void freeSetObject(robj *o) {
-    dictRelease((dict*) o->ptr);
+    switch (o->encoding) {
+    case REDIS_ENCODING_HT:
+        dictRelease((dict*) o->ptr);
+        break;
+    case REDIS_ENCODING_INTSET:
+        zfree(o->ptr);
+        break;
+    default:
+        redisPanic("Unknown set encoding type");
+    }
 }
 
 void freeZsetObject(robj *o) {
@@ -336,9 +354,9 @@ int getDoubleFromObjectOrReply(redisClient *c, robj *o, double *target, const ch
     double value;
     if (getDoubleFromObject(o, &value) != REDIS_OK) {
         if (msg != NULL) {
-            addReplySds(c, sdscatprintf(sdsempty(), "-ERR %s\r\n", msg));
+            addReplyError(c,(char*)msg);
         } else {
-            addReplySds(c, sdsnew("-ERR value is not a double\r\n"));
+            addReplyError(c,"value is not a double");
         }
         return REDIS_ERR;
     }
@@ -358,24 +376,26 @@ int getLongLongFromObject(robj *o, long long *target) {
         if (o->encoding == REDIS_ENCODING_RAW) {
             value = strtoll(o->ptr, &eptr, 10);
             if (eptr[0] != '\0') return REDIS_ERR;
+            if (errno == ERANGE && (value == LLONG_MIN || value == LLONG_MAX))
+                return REDIS_ERR;
         } else if (o->encoding == REDIS_ENCODING_INT) {
             value = (long)o->ptr;
         } else {
             redisPanic("Unknown string encoding");
         }
     }
 
-    *target = value;
+    if (target) *target = value;
     return REDIS_OK;
 }
 
 int getLongLongFromObjectOrReply(redisClient *c, robj *o, long long *target, const char *msg) {
     long long value;
     if (getLongLongFromObject(o, &value) != REDIS_OK) {
         if (msg != NULL) {
-            addReplySds(c, sdscatprintf(sdsempty(), "-ERR %s\r\n", msg));
+            addReplyError(c,(char*)msg);
         } else {
-            addReplySds(c, sdsnew("-ERR value is not an integer\r\n"));
+            addReplyError(c,"value is not an integer or out of range");
         }
         return REDIS_ERR;
     }
@@ -390,9 +410,9 @@ int getLongFromObjectOrReply(redisClient *c, robj *o, long *target, const char *
     if (getLongLongFromObjectOrReply(c, o, &value, msg) != REDIS_OK) return REDIS_ERR;
     if (value < LONG_MIN || value > LONG_MAX) {
         if (msg != NULL) {
-            addReplySds(c, sdscatprintf(sdsempty(), "-ERR %s\r\n", msg));
+            addReplyError(c,(char*)msg);
         } else {
-            addReplySds(c, sdsnew("-ERR value is out of range\r\n"));
+            addReplyError(c,"value is out of range");
         }
         return REDIS_ERR;
     }
@@ -409,6 +429,7 @@ char *strEncoding(int encoding) {
     case REDIS_ENCODING_ZIPMAP: return "zipmap";
     case REDIS_ENCODING_LINKEDLIST: return "linkedlist";
     case REDIS_ENCODING_ZIPLIST: return "ziplist";
+    case REDIS_ENCODING_INTSET: return "intset";
     default: return "unknown";
     }
 }