@@ -6790,7 +6790,7 @@ static void zrevrankCommand(redisClient *c) {
 /* Check the length of a number of objects to see if we need to convert a
  * zipmap to a real hash. Note that we only check string encoded objects
  * as their string length can be queried in constant time. */
-static void hashTryConversion(robj *subject, robj **argv, int start, int end) {
+static void hashTypeTryConversion(robj *subject, robj **argv, int start, int end) {
     int i;
     if (subject->encoding != REDIS_ENCODING_ZIPMAP) return;
 
@@ -6805,7 +6805,7 @@ static void hashTryConversion(robj *subject, robj **argv, int start, int end) {
 }
 
 /* Encode given objects in-place when the hash uses a dict. */
-static void hashTryObjectEncoding(robj *subject, robj **o1, robj **o2) {
+static void hashTypeTryObjectEncoding(robj *subject, robj **o1, robj **o2) {
     if (subject->encoding == REDIS_ENCODING_HT) {
         if (o1) *o1 = tryObjectEncoding(*o1);
         if (o2) *o2 = tryObjectEncoding(*o2);
@@ -6815,7 +6815,7 @@ static void hashTryObjectEncoding(robj *subject, robj **o1, robj **o2) {
 /* Get the value from a hash identified by key. Returns either a string
  * object or NULL if the value cannot be found. The refcount of the object
  * is always increased by 1 when the value was found. */
-static robj *hashGet(robj *o, robj *key) {
+static robj *hashTypeGet(robj *o, robj *key) {
     robj *value = NULL;
     if (o->encoding == REDIS_ENCODING_ZIPMAP) {
         unsigned char *v;
@@ -6837,7 +6837,7 @@ static robj *hashGet(robj *o, robj *key) {
 
 /* Test if the key exists in the given hash. Returns 1 if the key
  * exists and 0 when it doesn't. */
-static int hashExists(robj *o, robj *key) {
+static int hashTypeExists(robj *o, robj *key) {
     if (o->encoding == REDIS_ENCODING_ZIPMAP) {
         key = getDecodedObject(key);
         if (zipmapExists(o->ptr,key->ptr,sdslen(key->ptr))) {
@@ -6855,7 +6855,7 @@ static int hashExists(robj *o, robj *key) {
 
 /* Add an element, discard the old if the key already exists.
  * Return 0 on insert and 1 on update. */
-static int hashSet(robj *o, robj *key, robj *value) {
+static int hashTypeSet(robj *o, robj *key, robj *value) {
     int update = 0;
     if (o->encoding == REDIS_ENCODING_ZIPMAP) {
         key = getDecodedObject(key);
@@ -6884,7 +6884,7 @@ static int hashSet(robj *o, robj *key, robj *value) {
 
 /* Delete an element from a hash.
  * Return 1 on deleted and 0 on not found. */
-static int hashDelete(robj *o, robj *key) {
+static int hashTypeDelete(robj *o, robj *key) {
     int deleted = 0;
     if (o->encoding == REDIS_ENCODING_ZIPMAP) {
         key = getDecodedObject(key);
@@ -6899,7 +6899,7 @@ static int hashDelete(robj *o, robj *key) {
 }
 
 /* Return the number of elements in a hash. */
-static unsigned long hashLength(robj *o) {
+static unsigned long hashTypeLength(robj *o) {
     return (o->encoding == REDIS_ENCODING_ZIPMAP) ?
         zipmapLen((unsigned char*)o->ptr) : dictSize((dict*)o->ptr);
 }
@@ -6916,10 +6916,10 @@ typedef struct {
 
     dictIterator *di;
     dictEntry *de;
-} hashIterator;
+} hashTypeIterator;
 
-static hashIterator *hashInitIterator(robj *subject) {
-    hashIterator *hi = zmalloc(sizeof(hashIterator));
+static hashTypeIterator *hashTypeInitIterator(robj *subject) {
+    hashTypeIterator *hi = zmalloc(sizeof(hashTypeIterator));
     hi->encoding = subject->encoding;
     if (hi->encoding == REDIS_ENCODING_ZIPMAP) {
         hi->zi = zipmapRewind(subject->ptr);
@@ -6931,7 +6931,7 @@ static hashIterator *hashInitIterator(robj *subject) {
     return hi;
 }
 
-static void hashReleaseIterator(hashIterator *hi) {
+static void hashTypeReleaseIterator(hashTypeIterator *hi) {
     if (hi->encoding == REDIS_ENCODING_HT) {
         dictReleaseIterator(hi->di);
     }
@@ -6940,7 +6940,7 @@ static void hashReleaseIterator(hashIterator *hi) {
 
 /* Move to the next entry in the hash. Return REDIS_OK when the next entry
  * could be found and REDIS_ERR when the iterator reaches the end. */
-static int hashNext(hashIterator *hi) {
+static int hashTypeNext(hashTypeIterator *hi) {
     if (hi->encoding == REDIS_ENCODING_ZIPMAP) {
         if ((hi->zi = zipmapNext(hi->zi, &hi->zk, &hi->zklen,
             &hi->zv, &hi->zvlen)) == NULL) return REDIS_ERR;
@@ -6952,7 +6952,7 @@ static int hashNext(hashIterator *hi) {
 
 /* Get key or value object at current iteration position.
  * This increases the refcount of the field object by 1. */
-static robj *hashCurrent(hashIterator *hi, int what) {
+static robj *hashTypeCurrent(hashTypeIterator *hi, int what) {
     robj *o;
     if (hi->encoding == REDIS_ENCODING_ZIPMAP) {
         if (what & REDIS_HASH_KEY) {
@@ -6971,7 +6971,7 @@ static robj *hashCurrent(hashIterator *hi, int what) {
     return o;
 }
 
-static robj *hashLookupWriteOrCreate(redisClient *c, robj *key) {
+static robj *hashTypeLookupWriteOrCreate(redisClient *c, robj *key) {
     robj *o = lookupKeyWrite(c->db,key);
     if (o == NULL) {
         o = createHashObject();
@@ -6990,24 +6990,24 @@ static void hsetCommand(redisClient *c) {
     int update;
     robj *o;
 
-    if ((o = hashLookupWriteOrCreate(c,c->argv[1])) == NULL) return;
-    hashTryConversion(o,c->argv,2,3);
-    hashTryObjectEncoding(o,&c->argv[2], &c->argv[3]);
-    update = hashSet(o,c->argv[2],c->argv[3]);
+    if ((o = hashTypeLookupWriteOrCreate(c,c->argv[1])) == NULL) return;
+    hashTypeTryConversion(o,c->argv,2,3);
+    hashTypeTryObjectEncoding(o,&c->argv[2], &c->argv[3]);
+    update = hashTypeSet(o,c->argv[2],c->argv[3]);
     addReply(c, update ? shared.czero : shared.cone);
     server.dirty++;
 }
 
 static void hsetnxCommand(redisClient *c) {
     robj *o;
-    if ((o = hashLookupWriteOrCreate(c,c->argv[1])) == NULL) return;
-    hashTryConversion(o,c->argv,2,3);
+    if ((o = hashTypeLookupWriteOrCreate(c,c->argv[1])) == NULL) return;
+    hashTypeTryConversion(o,c->argv,2,3);
 
-    if (hashExists(o, c->argv[2])) {
+    if (hashTypeExists(o, c->argv[2])) {
         addReply(c, shared.czero);
     } else {
-        hashTryObjectEncoding(o,&c->argv[2], &c->argv[3]);
-        hashSet(o,c->argv[2],c->argv[3]);
+        hashTypeTryObjectEncoding(o,&c->argv[2], &c->argv[3]);
+        hashTypeSet(o,c->argv[2],c->argv[3]);
         addReply(c, shared.cone);
         server.dirty++;
     }
@@ -7022,11 +7022,11 @@ static void hmsetCommand(redisClient *c) {
         return;
     }
 
-    if ((o = hashLookupWriteOrCreate(c,c->argv[1])) == NULL) return;
-    hashTryConversion(o,c->argv,2,c->argc-1);
+    if ((o = hashTypeLookupWriteOrCreate(c,c->argv[1])) == NULL) return;
+    hashTypeTryConversion(o,c->argv,2,c->argc-1);
     for (i = 2; i < c->argc; i += 2) {
-        hashTryObjectEncoding(o,&c->argv[i], &c->argv[i+1]);
-        hashSet(o,c->argv[i],c->argv[i+1]);
+        hashTypeTryObjectEncoding(o,&c->argv[i], &c->argv[i+1]);
+        hashTypeSet(o,c->argv[i],c->argv[i+1]);
     }
     addReply(c, shared.ok);
     server.dirty++;
@@ -7037,8 +7037,8 @@ static void hincrbyCommand(redisClient *c) {
     robj *o, *current, *new;
 
     if (getLongLongFromObjectOrReply(c,c->argv[3],&incr,NULL) != REDIS_OK) return;
-    if ((o = hashLookupWriteOrCreate(c,c->argv[1])) == NULL) return;
-    if ((current = hashGet(o,c->argv[2])) != NULL) {
+    if ((o = hashTypeLookupWriteOrCreate(c,c->argv[1])) == NULL) return;
+    if ((current = hashTypeGet(o,c->argv[2])) != NULL) {
         if (getLongLongFromObjectOrReply(c,current,&value,
             "hash value is not an integer") != REDIS_OK) {
             decrRefCount(current);
@@ -7051,8 +7051,8 @@ static void hincrbyCommand(redisClient *c) {
 
     value += incr;
     new = createStringObjectFromLongLong(value);
-    hashTryObjectEncoding(o,&c->argv[2],NULL);
-    hashSet(o,c->argv[2],new);
+    hashTypeTryObjectEncoding(o,&c->argv[2],NULL);
+    hashTypeSet(o,c->argv[2],new);
     decrRefCount(new);
     addReplyLongLong(c,value);
     server.dirty++;
@@ -7063,7 +7063,7 @@ static void hgetCommand(redisClient *c) {
     if ((o = lookupKeyReadOrReply(c,c->argv[1],shared.nullbulk)) == NULL ||
         checkType(c,o,REDIS_HASH)) return;
 
-    if ((value = hashGet(o,c->argv[2])) != NULL) {
+    if ((value = hashTypeGet(o,c->argv[2])) != NULL) {
         addReplyBulk(c,value);
         decrRefCount(value);
     } else {
@@ -7084,7 +7084,7 @@ static void hmgetCommand(redisClient *c) {
      * an empty hash. The reply should then be a series of NULLs. */
     addReplySds(c,sdscatprintf(sdsempty(),"*%d\r\n",c->argc-2));
     for (i = 2; i < c->argc; i++) {
-        if (o != NULL && (value = hashGet(o,c->argv[i])) != NULL) {
+        if (o != NULL && (value = hashTypeGet(o,c->argv[i])) != NULL) {
             addReplyBulk(c,value);
             decrRefCount(value);
         } else {
@@ -7098,8 +7098,8 @@ static void hdelCommand(redisClient *c) {
     if ((o = lookupKeyWriteOrReply(c,c->argv[1],shared.czero)) == NULL ||
         checkType(c,o,REDIS_HASH)) return;
 
-    if (hashDelete(o,c->argv[2])) {
-        if (hashLength(o) == 0) dbDelete(c->db,c->argv[1]);
+    if (hashTypeDelete(o,c->argv[2])) {
+        if (hashTypeLength(o) == 0) dbDelete(c->db,c->argv[1]);
         addReply(c,shared.cone);
         server.dirty++;
     } else {
@@ -7112,13 +7112,13 @@ static void hlenCommand(redisClient *c) {
     if ((o = lookupKeyReadOrReply(c,c->argv[1],shared.czero)) == NULL ||
         checkType(c,o,REDIS_HASH)) return;
 
-    addReplyUlong(c,hashLength(o));
+    addReplyUlong(c,hashTypeLength(o));
 }
 
 static void genericHgetallCommand(redisClient *c, int flags) {
     robj *o, *lenobj, *obj;
     unsigned long count = 0;
-    hashIterator *hi;
+    hashTypeIterator *hi;
 
     if ((o = lookupKeyReadOrReply(c,c->argv[1],shared.emptymultibulk)) == NULL
         || checkType(c,o,REDIS_HASH)) return;
@@ -7127,22 +7127,22 @@ static void genericHgetallCommand(redisClient *c, int flags) {
     addReply(c,lenobj);
     decrRefCount(lenobj);
 
-    hi = hashInitIterator(o);
-    while (hashNext(hi) != REDIS_ERR) {
+    hi = hashTypeInitIterator(o);
+    while (hashTypeNext(hi) != REDIS_ERR) {
         if (flags & REDIS_HASH_KEY) {
-            obj = hashCurrent(hi,REDIS_HASH_KEY);
+            obj = hashTypeCurrent(hi,REDIS_HASH_KEY);
             addReplyBulk(c,obj);
             decrRefCount(obj);
             count++;
         }
         if (flags & REDIS_HASH_VALUE) {
-            obj = hashCurrent(hi,REDIS_HASH_VALUE);
+            obj = hashTypeCurrent(hi,REDIS_HASH_VALUE);
             addReplyBulk(c,obj);
             decrRefCount(obj);
             count++;
         }
     }
-    hashReleaseIterator(hi);
+    hashTypeReleaseIterator(hi);
 
     lenobj->ptr = sdscatprintf(sdsempty(),"*%lu\r\n",count);
 }
@@ -7164,7 +7164,7 @@ static void hexistsCommand(redisClient *c) {
     if ((o = lookupKeyReadOrReply(c,c->argv[1],shared.czero)) == NULL ||
         checkType(c,o,REDIS_HASH)) return;
 
-    addReply(c, hashExists(o,c->argv[2]) ? shared.cone : shared.czero);
+    addReply(c, hashTypeExists(o,c->argv[2]) ? shared.cone : shared.czero);
 }
 
 static void convertToRealHash(robj *o) {
@@ -7285,7 +7285,7 @@ static robj *lookupKeyByPattern(redisDb *db, robj *pattern, robj *subst) {
         /* Retrieve value from hash by the field name. This operation
          * already increases the refcount of the returned object. */
         initStaticStringObject(fieldobj,((char*)&fieldname)+(sizeof(long)*2));
-        o = hashGet(o, &fieldobj);
+        o = hashTypeGet(o, &fieldobj);
     } else {
         if (o->type != REDIS_STRING) return NULL;
 
@@ -11115,23 +11115,23 @@ static void computeDatasetDigest(unsigned char *final) {
                 }
                 dictReleaseIterator(di);
             } else if (o->type == REDIS_HASH) {
-                hashIterator *hi;
+                hashTypeIterator *hi;
                 robj *obj;
 
-                hi = hashInitIterator(o);
-                while (hashNext(hi) != REDIS_ERR) {
+                hi = hashTypeInitIterator(o);
+                while (hashTypeNext(hi) != REDIS_ERR) {
                     unsigned char eledigest[20];
 
                     memset(eledigest,0,20);
-                    obj = hashCurrent(hi,REDIS_HASH_KEY);
+                    obj = hashTypeCurrent(hi,REDIS_HASH_KEY);
                     mixObjectDigest(eledigest,obj);
                     decrRefCount(obj);
-                    obj = hashCurrent(hi,REDIS_HASH_VALUE);
+                    obj = hashTypeCurrent(hi,REDIS_HASH_VALUE);
                     mixObjectDigest(eledigest,obj);
                     decrRefCount(obj);
                     xorDigest(digest,eledigest,20);
                 }
-                hashReleaseIterator(hi);
+                hashTypeReleaseIterator(hi);
             } else {
                 redisPanic("Unknown object type");
             }