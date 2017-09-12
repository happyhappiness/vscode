@@ -2775,6 +2775,23 @@ static robj *createStringObject(char *ptr, size_t len) {
     return createObject(REDIS_STRING,sdsnewlen(ptr,len));
 }
 
+static robj *createStringObjectFromLongLong(long long value) {
+    robj *o;
+    if (value >= 0 && value < REDIS_SHARED_INTEGERS) {
+        incrRefCount(shared.integers[value]);
+        o = shared.integers[value];
+    } else {
+        o = createObject(REDIS_STRING, NULL);
+        if (value >= LONG_MIN && value <= LONG_MAX) {
+            o->encoding = REDIS_ENCODING_INT;
+            o->ptr = (void*)((long)value);
+        } else {
+            o->ptr = sdscatprintf(sdsempty(),"%lld",value);
+        }
+    }
+    return o;
+}
+
 static robj *dupStringObject(robj *o) {
     assert(o->encoding == REDIS_ENCODING_RAW);
     return createStringObject(o->ptr,sdslen(o->ptr));
@@ -6071,8 +6088,8 @@ static void hashTryConversion(robj *subject, robj **argv, int start, int end) {
 /* Encode given objects in-place when the hash uses a dict. */
 static void hashTryObjectEncoding(robj *subject, robj **o1, robj **o2) {
     if (subject->encoding == REDIS_ENCODING_HT) {
-        *o1 = tryObjectEncoding(*o1);
-        *o2 = tryObjectEncoding(*o2);
+        if (o1) *o1 = tryObjectEncoding(*o1);
+        if (o2) *o2 = tryObjectEncoding(*o2);
     }
 }
 
@@ -6316,7 +6333,8 @@ static void hincrbyCommand(redisClient *c) {
     }
 
     value += incr;
-    new = createObject(REDIS_STRING,sdscatprintf(sdsempty(),"%lld",value));
+    new = createStringObjectFromLongLong(value);
+    hashTryObjectEncoding(o,&c->argv[2],NULL);
     hashSet(o,c->argv[2],new);
     decrRefCount(new);
     addReplyLongLong(c,value);