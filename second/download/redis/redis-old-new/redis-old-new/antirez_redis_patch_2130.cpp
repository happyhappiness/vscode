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
@@ -6068,6 +6085,14 @@ static void hashTryConversion(robj *subject, robj **argv, int start, int end) {
     }
 }
 
+/* Encode given objects in-place when the hash uses a dict. */
+static void hashTryObjectEncoding(robj *subject, robj **o1, robj **o2) {
+    if (subject->encoding == REDIS_ENCODING_HT) {
+        if (o1) *o1 = tryObjectEncoding(*o1);
+        if (o2) *o2 = tryObjectEncoding(*o2);
+    }
+}
+
 /* Get the value from a hash identified by key. Returns either a string
  * object or NULL if the value cannot be found. The refcount of the object
  * is always increased by 1 when the value was found. */
@@ -6126,7 +6151,6 @@ static int hashSet(robj *o, robj *key, robj *value) {
         if (zipmapLen(o->ptr) > server.hash_max_zipmap_entries)
             convertToRealHash(o);
     } else {
-        value = tryObjectEncoding(value);
         if (dictReplace(o->ptr,key,value)) {
             /* Insert */
             incrRefCount(key);
@@ -6250,6 +6274,7 @@ static void hsetCommand(redisClient *c) {
 
     if ((o = hashLookupWriteOrCreate(c,c->argv[1])) == NULL) return;
     hashTryConversion(o,c->argv,2,3);
+    hashTryObjectEncoding(o,&c->argv[2], &c->argv[3]);
     update = hashSet(o,c->argv[2],c->argv[3]);
     addReply(c, update ? shared.czero : shared.cone);
     server.dirty++;
@@ -6263,6 +6288,7 @@ static void hsetnxCommand(redisClient *c) {
     if (hashExists(o, c->argv[2])) {
         addReply(c, shared.czero);
     } else {
+        hashTryObjectEncoding(o,&c->argv[2], &c->argv[3]);
         hashSet(o,c->argv[2],c->argv[3]);
         addReply(c, shared.cone);
         server.dirty++;
@@ -6281,9 +6307,11 @@ static void hmsetCommand(redisClient *c) {
     if ((o = hashLookupWriteOrCreate(c,c->argv[1])) == NULL) return;
     hashTryConversion(o,c->argv,2,c->argc-1);
     for (i = 2; i < c->argc; i += 2) {
+        hashTryObjectEncoding(o,&c->argv[i], &c->argv[i+1]);
         hashSet(o,c->argv[i],c->argv[i+1]);
     }
     addReply(c, shared.ok);
+    server.dirty++;
 }
 
 static void hincrbyCommand(redisClient *c) {
@@ -6305,7 +6333,8 @@ static void hincrbyCommand(redisClient *c) {
     }
 
     value += incr;
-    new = createObject(REDIS_STRING,sdscatprintf(sdsempty(),"%lld",value));
+    new = createStringObjectFromLongLong(value);
+    hashTryObjectEncoding(o,&c->argv[2],NULL);
     hashSet(o,c->argv[2],new);
     decrRefCount(new);
     addReplyLongLong(c,value);