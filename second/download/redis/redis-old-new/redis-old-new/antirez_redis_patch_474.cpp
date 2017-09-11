@@ -70,7 +70,7 @@ int hashTypeGetFromZiplist(robj *o, robj *field,
     unsigned char *zl, *fptr = NULL, *vptr = NULL;
     int ret;
 
-    redisAssert(o->encoding == OBJ_ENCODING_ZIPLIST);
+    serverAssert(o->encoding == OBJ_ENCODING_ZIPLIST);
 
     field = getDecodedObject(field);
 
@@ -81,15 +81,15 @@ int hashTypeGetFromZiplist(robj *o, robj *field,
         if (fptr != NULL) {
             /* Grab pointer to the value (fptr points to the field) */
             vptr = ziplistNext(zl, fptr);
-            redisAssert(vptr != NULL);
+            serverAssert(vptr != NULL);
         }
     }
 
     decrRefCount(field);
 
     if (vptr != NULL) {
         ret = ziplistGet(vptr, vstr, vlen, vll);
-        redisAssert(ret);
+        serverAssert(ret);
         return 0;
     }
 
@@ -101,7 +101,7 @@ int hashTypeGetFromZiplist(robj *o, robj *field,
 int hashTypeGetFromHashTable(robj *o, robj *field, robj **value) {
     dictEntry *de;
 
-    redisAssert(o->encoding == OBJ_ENCODING_HT);
+    serverAssert(o->encoding == OBJ_ENCODING_HT);
 
     de = dictFind(o->ptr, field);
     if (de == NULL) return -1;
@@ -205,7 +205,7 @@ int hashTypeSet(robj *o, robj *field, robj *value) {
             if (fptr != NULL) {
                 /* Grab pointer to the value (fptr points to the field) */
                 vptr = ziplistNext(zl, fptr);
-                redisAssert(vptr != NULL);
+                serverAssert(vptr != NULL);
                 update = 1;
 
                 /* Delete value */
@@ -333,18 +333,18 @@ int hashTypeNext(hashTypeIterator *hi) {
 
         if (fptr == NULL) {
             /* Initialize cursor */
-            redisAssert(vptr == NULL);
+            serverAssert(vptr == NULL);
             fptr = ziplistIndex(zl, 0);
         } else {
             /* Advance cursor */
-            redisAssert(vptr != NULL);
+            serverAssert(vptr != NULL);
             fptr = ziplistNext(zl, vptr);
         }
         if (fptr == NULL) return REDIS_ERR;
 
         /* Grab pointer to the value (fptr points to the field) */
         vptr = ziplistNext(zl, fptr);
-        redisAssert(vptr != NULL);
+        serverAssert(vptr != NULL);
 
         /* fptr, vptr now point to the first or next pair */
         hi->fptr = fptr;
@@ -366,21 +366,21 @@ void hashTypeCurrentFromZiplist(hashTypeIterator *hi, int what,
 {
     int ret;
 
-    redisAssert(hi->encoding == OBJ_ENCODING_ZIPLIST);
+    serverAssert(hi->encoding == OBJ_ENCODING_ZIPLIST);
 
     if (what & OBJ_HASH_KEY) {
         ret = ziplistGet(hi->fptr, vstr, vlen, vll);
-        redisAssert(ret);
+        serverAssert(ret);
     } else {
         ret = ziplistGet(hi->vptr, vstr, vlen, vll);
-        redisAssert(ret);
+        serverAssert(ret);
     }
 }
 
 /* Get the field or value at iterator cursor, for an iterator on a hash value
  * encoded as a ziplist. Prototype is similar to `hashTypeGetFromHashTable`. */
 void hashTypeCurrentFromHashTable(hashTypeIterator *hi, int what, robj **dst) {
-    redisAssert(hi->encoding == OBJ_ENCODING_HT);
+    serverAssert(hi->encoding == OBJ_ENCODING_HT);
 
     if (what & OBJ_HASH_KEY) {
         *dst = dictGetKey(hi->de);
@@ -430,7 +430,7 @@ robj *hashTypeLookupWriteOrCreate(client *c, robj *key) {
 }
 
 void hashTypeConvertZiplist(robj *o, int enc) {
-    redisAssert(o->encoding == OBJ_ENCODING_ZIPLIST);
+    serverAssert(o->encoding == OBJ_ENCODING_ZIPLIST);
 
     if (enc == OBJ_ENCODING_ZIPLIST) {
         /* Nothing to do... */
@@ -454,7 +454,7 @@ void hashTypeConvertZiplist(robj *o, int enc) {
             if (ret != DICT_OK) {
                 serverLogHexDump(REDIS_WARNING,"ziplist with dup elements dump",
                     o->ptr,ziplistBlobLen(o->ptr));
-                redisAssert(ret == DICT_OK);
+                serverAssert(ret == DICT_OK);
             }
         }
 
@@ -768,7 +768,7 @@ void genericHgetallCommand(client *c, int flags) {
     }
 
     hashTypeReleaseIterator(hi);
-    redisAssert(count == length);
+    serverAssert(count == length);
 }
 
 void hkeysCommand(client *c) {