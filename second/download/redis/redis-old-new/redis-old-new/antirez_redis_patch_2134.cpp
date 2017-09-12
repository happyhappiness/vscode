@@ -6174,7 +6174,8 @@ typedef struct {
     dictEntry *de;
 } hashIterator;
 
-static void hashInitIterator(robj *subject, hashIterator *hi) {
+static hashIterator *hashInitIterator(robj *subject) {
+    hashIterator *hi = zmalloc(sizeof(hashIterator));
     hi->encoding = subject->encoding;
     if (hi->encoding == REDIS_ENCODING_ZIPMAP) {
         hi->zi = zipmapRewind(subject->ptr);
@@ -6183,12 +6184,14 @@ static void hashInitIterator(robj *subject, hashIterator *hi) {
     } else {
         redisAssert(NULL);
     }
+    return hi;
 }
 
 static void hashReleaseIterator(hashIterator *hi) {
     if (hi->encoding == REDIS_ENCODING_HT) {
         dictReleaseIterator(hi->di);
     }
+    zfree(hi);
 }
 
 /* Move to the next entry in the hash. Return REDIS_OK when the next entry
@@ -6372,7 +6375,7 @@ static void hlenCommand(redisClient *c) {
 static void genericHgetallCommand(redisClient *c, int flags) {
     robj *o, *lenobj, *obj;
     unsigned long count = 0;
-    hashIterator hi;
+    hashIterator *hi;
 
     if ((o = lookupKeyReadOrReply(c,c->argv[1],shared.emptymultibulk)) == NULL
         || checkType(c,o,REDIS_HASH)) return;
@@ -6381,20 +6384,20 @@ static void genericHgetallCommand(redisClient *c, int flags) {
     addReply(c,lenobj);
     decrRefCount(lenobj);
 
-    hashInitIterator(o, &hi);
-    while (hashNext(&hi) != REDIS_ERR) {
+    hi = hashInitIterator(o);
+    while (hashNext(hi) != REDIS_ERR) {
         if (flags & REDIS_HASH_KEY) {
-            obj = hashCurrent(&hi,REDIS_HASH_KEY);
+            obj = hashCurrent(hi,REDIS_HASH_KEY);
             addReplyBulk(c,obj);
             count++;
         }
         if (flags & REDIS_HASH_VALUE) {
-            obj = hashCurrent(&hi,REDIS_HASH_VALUE);
+            obj = hashCurrent(hi,REDIS_HASH_VALUE);
             addReplyBulk(c,obj);
             count++;
         }
     }
-    hashReleaseIterator(&hi);
+    hashReleaseIterator(hi);
 
     lenobj->ptr = sdscatprintf(sdsempty(),"*%lu\r\n",count);
 }