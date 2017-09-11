@@ -52,17 +52,9 @@ void hashTypeTryConversion(robj *o, robj **argv, int start, int end) {
     }
 }
 
-/* Encode given objects in-place when the hash uses a dict. */
-void hashTypeTryObjectEncoding(robj *subject, robj **o1, robj **o2) {
-    if (subject->encoding == OBJ_ENCODING_HT) {
-        if (o1) *o1 = tryObjectEncoding(*o1);
-        if (o2) *o2 = tryObjectEncoding(*o2);
-    }
-}
-
 /* Get the value from a ziplist encoded hash, identified by field.
  * Returns -1 when the field cannot be found. */
-int hashTypeGetFromZiplist(robj *o, robj *field,
+int hashTypeGetFromZiplist(robj *o, sds field,
                            unsigned char **vstr,
                            unsigned int *vlen,
                            long long *vll)
@@ -72,21 +64,17 @@ int hashTypeGetFromZiplist(robj *o, robj *field,
 
     serverAssert(o->encoding == OBJ_ENCODING_ZIPLIST);
 
-    field = getDecodedObject(field);
-
     zl = o->ptr;
     fptr = ziplistIndex(zl, ZIPLIST_HEAD);
     if (fptr != NULL) {
-        fptr = ziplistFind(fptr, field->ptr, sdslen(field->ptr), 1);
+        fptr = ziplistFind(fptr, field, sdslen(field), 1);
         if (fptr != NULL) {
             /* Grab pointer to the value (fptr points to the field) */
             vptr = ziplistNext(zl, fptr);
             serverAssert(vptr != NULL);
         }
     }
 
-    decrRefCount(field);
-
     if (vptr != NULL) {
         ret = ziplistGet(vptr, vstr, vlen, vll);
         serverAssert(ret);
@@ -97,56 +85,49 @@ int hashTypeGetFromZiplist(robj *o, robj *field,
 }
 
 /* Get the value from a hash table encoded hash, identified by field.
- * Returns -1 when the field cannot be found. */
-int hashTypeGetFromHashTable(robj *o, robj *field, robj **value) {
+ * Returns NULL when the field cannot be found, otherwise the SDS value
+ * is returned. */
+sds hashTypeGetFromHashTable(robj *o, sds field) {
     dictEntry *de;
 
     serverAssert(o->encoding == OBJ_ENCODING_HT);
 
     de = dictFind(o->ptr, field);
-    if (de == NULL) return -1;
-    *value = dictGetVal(de);
-    return 0;
+    if (de == NULL) return NULL;
+    return dictGetVal(de);
 }
 
-/* Higher level function of hashTypeGet*() that always returns a Redis
- * object (either new or with refcount incremented), so that the caller
- * can retain a reference or call decrRefCount after the usage.
+/* Higher level function of hashTypeGet*() that returns the hash value
+ * associated with the specified field. If the field is found C_OK
+ * is returned, otherwise C_ERR. The returned object is returned by
+ * reference in either *vstr and *vlen if it's returned in string form,
+ * or stored in *vll if it's returned as a number.
  *
- * The lower level function can prevent copy on write so it is
- * the preferred way of doing read operations. */
-robj *hashTypeGetObject(robj *o, robj *field) {
-    robj *value = NULL;
-
+ * If *vll is populated *vstr is set to NULL, so the caller
+ * can always check the function return by checking the return value
+ * for C_OK and checking if vll (or vstr) is NULL. */
+int hashTypeGetObject(robj *o, sds field, unsigned char **vstr, unsigned int *vlen, long long *vll) {
     if (o->encoding == OBJ_ENCODING_ZIPLIST) {
-        unsigned char *vstr = NULL;
-        unsigned int vlen = UINT_MAX;
-        long long vll = LLONG_MAX;
-
-        if (hashTypeGetFromZiplist(o, field, &vstr, &vlen, &vll) == 0) {
-            if (vstr) {
-                value = createStringObject((char*)vstr, vlen);
-            } else {
-                value = createStringObjectFromLongLong(vll);
-            }
-        }
+        *vstr = NULL;
+        if (hashTypeGetFromZiplist(o, field, vstr, vlen, vll) == 0)
+            return C_OK;
     } else if (o->encoding == OBJ_ENCODING_HT) {
-        robj *aux;
-
-        if (hashTypeGetFromHashTable(o, field, &aux) == 0) {
-            incrRefCount(aux);
-            value = aux;
+        sds value;
+        if (value = hashTypeGetFromHashTable(o, field) != NULL) {
+            *vstr = value;
+            *vlen = sdslen(value);
+            return C_OK;
         }
     } else {
         serverPanic("Unknown hash encoding");
     }
-    return value;
+    return C_ERR;
 }
 
 /* Higher level function using hashTypeGet*() to return the length of the
  * object associated with the requested field, or 0 if the field does not
  * exist. */
-size_t hashTypeGetValueLength(robj *o, robj *field) {
+size_t hashTypeGetValueLength(robj *o, sds field) {
     size_t len = 0;
     if (o->encoding == OBJ_ENCODING_ZIPLIST) {
         unsigned char *vstr = NULL;
@@ -156,10 +137,10 @@ size_t hashTypeGetValueLength(robj *o, robj *field) {
         if (hashTypeGetFromZiplist(o, field, &vstr, &vlen, &vll) == 0)
             len = vstr ? vlen : sdigits10(vll);
     } else if (o->encoding == OBJ_ENCODING_HT) {
-        robj *aux;
+        sds aux;
 
-        if (hashTypeGetFromHashTable(o, field, &aux) == 0)
-            len = stringObjectLen(aux);
+        if ((aux = hashTypeGetFromHashTable(o, field)) != NULL)
+            len = sdslen(aux);
     } else {
         serverPanic("Unknown hash encoding");
     }
@@ -168,7 +149,7 @@ size_t hashTypeGetValueLength(robj *o, robj *field) {
 
 /* Test if the specified field exists in the given hash. Returns 1 if the field
  * exists, and 0 when it doesn't. */
-int hashTypeExists(robj *o, robj *field) {
+int hashTypeExists(robj *o, sds field) {
     if (o->encoding == OBJ_ENCODING_ZIPLIST) {
         unsigned char *vstr = NULL;
         unsigned int vlen = UINT_MAX;
@@ -178,30 +159,26 @@ int hashTypeExists(robj *o, robj *field) {
     } else if (o->encoding == OBJ_ENCODING_HT) {
         robj *aux;
 
-        if (hashTypeGetFromHashTable(o, field, &aux) == 0) return 1;
+        if (hashTypeGetFromHashTable(o, field) != NULL) return 1;
     } else {
         serverPanic("Unknown hash encoding");
     }
     return 0;
 }
 
-/* Add an element, discard the old if the key already exists.
- * Return 0 on insert and 1 on update.
- * This function will take care of incrementing the reference count of the
- * retained fields and value objects. */
-int hashTypeSet(robj *o, robj *field, robj *value) {
+/* Add a new field, overwrite the old with the new value if it already exists.
+ * Return 0 on insert and 1 on update. The key and value SDS strings are copied
+ * if needed, so the caller retains ownership of the strings passed. */
+int hashTypeSet(robj *o, sds field, sds value) {
     int update = 0;
 
     if (o->encoding == OBJ_ENCODING_ZIPLIST) {
         unsigned char *zl, *fptr, *vptr;
 
-        field = getDecodedObject(field);
-        value = getDecodedObject(value);
-
         zl = o->ptr;
         fptr = ziplistIndex(zl, ZIPLIST_HEAD);
         if (fptr != NULL) {
-            fptr = ziplistFind(fptr, field->ptr, sdslen(field->ptr), 1);
+            fptr = ziplistFind(fptr, field, sdslen(field), 1);
             if (fptr != NULL) {
                 /* Grab pointer to the value (fptr points to the field) */
                 vptr = ziplistNext(zl, fptr);
@@ -218,23 +195,23 @@ int hashTypeSet(robj *o, robj *field, robj *value) {
 
         if (!update) {
             /* Push new field/value pair onto the tail of the ziplist */
-            zl = ziplistPush(zl, field->ptr, sdslen(field->ptr), ZIPLIST_TAIL);
-            zl = ziplistPush(zl, value->ptr, sdslen(value->ptr), ZIPLIST_TAIL);
+            zl = ziplistPush(zl, field, sdslen(field), ZIPLIST_TAIL);
+            zl = ziplistPush(zl, value, sdslen(value), ZIPLIST_TAIL);
         }
         o->ptr = zl;
-        decrRefCount(field);
-        decrRefCount(value);
 
         /* Check if the ziplist needs to be converted to a hash table */
         if (hashTypeLength(o) > server.hash_max_ziplist_entries)
             hashTypeConvert(o, OBJ_ENCODING_HT);
     } else if (o->encoding == OBJ_ENCODING_HT) {
-        if (dictReplace(o->ptr, field, value)) { /* Insert */
-            incrRefCount(field);
-        } else { /* Update */
+        dictEntry *de = dictFind(o->ptr,field);
+        if (de) {
+            sdsfree(dictGetVal(de));
+            dictGetVal(de) = sdsdup(value);
             update = 1;
+        } else {
+            dictAdd(o->ptr,sdsdup(key),sdsdup(value));
         }
-        incrRefCount(value);
     } else {
         serverPanic("Unknown hash encoding");
     }
@@ -243,18 +220,16 @@ int hashTypeSet(robj *o, robj *field, robj *value) {
 
 /* Delete an element from a hash.
  * Return 1 on deleted and 0 on not found. */
-int hashTypeDelete(robj *o, robj *field) {
+int hashTypeDelete(robj *o, sds field) {
     int deleted = 0;
 
     if (o->encoding == OBJ_ENCODING_ZIPLIST) {
         unsigned char *zl, *fptr;
 
-        field = getDecodedObject(field);
-
         zl = o->ptr;
         fptr = ziplistIndex(zl, ZIPLIST_HEAD);
         if (fptr != NULL) {
-            fptr = ziplistFind(fptr, field->ptr, sdslen(field->ptr), 1);
+            fptr = ziplistFind(fptr, field, sdslen(field), 1);
             if (fptr != NULL) {
                 zl = ziplistDelete(zl,&fptr);
                 zl = ziplistDelete(zl,&fptr);
@@ -276,7 +251,6 @@ int hashTypeDelete(robj *o, robj *field) {
     } else {
         serverPanic("Unknown hash encoding");
     }
-
     return deleted;
 }
 
@@ -291,7 +265,6 @@ unsigned long hashTypeLength(robj *o) {
     } else {
         serverPanic("Unknown hash encoding");
     }
-
     return length;
 }
 
@@ -308,15 +281,12 @@ hashTypeIterator *hashTypeInitIterator(robj *subject) {
     } else {
         serverPanic("Unknown hash encoding");
     }
-
     return hi;
 }
 
 void hashTypeReleaseIterator(hashTypeIterator *hi) {
-    if (hi->encoding == OBJ_ENCODING_HT) {
+    if (hi->encoding == OBJ_ENCODING_HT)
         dictReleaseIterator(hi->di);
-    }
-
     zfree(hi);
 }
 
@@ -378,41 +348,51 @@ void hashTypeCurrentFromZiplist(hashTypeIterator *hi, int what,
 }
 
 /* Get the field or value at iterator cursor, for an iterator on a hash value
- * encoded as a ziplist. Prototype is similar to `hashTypeGetFromHashTable`. */
-void hashTypeCurrentFromHashTable(hashTypeIterator *hi, int what, robj **dst) {
+ * encoded as a hash table. Prototype is similar to
+ * `hashTypeGetFromHashTable`. */
+sds hashTypeCurrentFromHashTable(hashTypeIterator *hi, int what) {
     serverAssert(hi->encoding == OBJ_ENCODING_HT);
 
     if (what & OBJ_HASH_KEY) {
-        *dst = dictGetKey(hi->de);
+        return dictGetKey(hi->de);
     } else {
-        *dst = dictGetVal(hi->de);
+        return dictGetVal(hi->de);
     }
 }
 
-/* A non copy-on-write friendly but higher level version of hashTypeCurrent*()
- * that returns an object with incremented refcount (or a new object). It is up
- * to the caller to decrRefCount() the object if no reference is retained. */
-robj *hashTypeCurrentObject(hashTypeIterator *hi, int what) {
-    robj *dst;
-
+/* Higher level function of hashTypeCurrent*() that returns the hash value
+ * at current iterator position.
+ *
+ * The returned element is returned by reference in either *vstr and *vlen if
+ * it's returned in string form, or stored in *vll if it's returned as
+ * a number.
+ *
+ * If *vll is populated *vstr is set to NULL, so the caller
+ * can always check the function return by checking the return value
+ * type checking if vstr == NULL. */
+void hashTypeCurrentObject(hashTypeIterator *hi, int what, unsigned char **vstr, unsigned int *vlen, long long *vll) {
     if (hi->encoding == OBJ_ENCODING_ZIPLIST) {
-        unsigned char *vstr = NULL;
-        unsigned int vlen = UINT_MAX;
-        long long vll = LLONG_MAX;
-
-        hashTypeCurrentFromZiplist(hi, what, &vstr, &vlen, &vll);
-        if (vstr) {
-            dst = createStringObject((char*)vstr, vlen);
-        } else {
-            dst = createStringObjectFromLongLong(vll);
-        }
+        *vstr = NULL;
+        hashTypeCurrentFromZiplist(hi, what, vstr, vlen, vll);
     } else if (hi->encoding == OBJ_ENCODING_HT) {
-        hashTypeCurrentFromHashTable(hi, what, &dst);
-        incrRefCount(dst);
+        sds ele = hashTypeCurrentFromHashTable(hi, what);
+        *vstr = ele;
+        *vlen = sdslen(ele);
     } else {
         serverPanic("Unknown hash encoding");
     }
-    return dst;
+}
+
+/* Return the key or value at the current iterator position as a new
+ * SDS string. */
+sds hashTypeCurrentObjectNewSds(hashTypeIterator *hi, int what) {
+    unsigned char *vstr;
+    unsigned int vlen;
+    long long vll;
+
+    hashTypeCurrentObject(hi,what,&vstr,&vlen,&vll);
+    if (vstr) return sdsnewlen(vstr,vlen);
+    return sdsfromlonglong(vll);
 }
 
 robj *hashTypeLookupWriteOrCreate(client *c, robj *key) {
@@ -444,26 +424,24 @@ void hashTypeConvertZiplist(robj *o, int enc) {
         dict = dictCreate(&hashDictType, NULL);
 
         while (hashTypeNext(hi) != C_ERR) {
-            robj *field, *value;
+            unsigned char *vstr;
+            unsigned int vlen;
+            long long vll;
+            sds key, value;
 
-            field = hashTypeCurrentObject(hi, OBJ_HASH_KEY);
-            field = tryObjectEncoding(field);
-            value = hashTypeCurrentObject(hi, OBJ_HASH_VALUE);
-            value = tryObjectEncoding(value);
+            key = hashTypeCurrentObjectNewSds(hi,OBJ_HASH_KEY);
+            value = hashTypeCurrentObjectNewSds(hi,OBJ_HASH_VALUE);
             ret = dictAdd(dict, field, value);
             if (ret != DICT_OK) {
                 serverLogHexDump(LL_WARNING,"ziplist with dup elements dump",
                     o->ptr,ziplistBlobLen(o->ptr));
-                serverAssert(ret == DICT_OK);
+                serverPanic("Ziplist corruption detected");
             }
         }
-
         hashTypeReleaseIterator(hi);
         zfree(o->ptr);
-
         o->encoding = OBJ_ENCODING_HT;
         o->ptr = dict;
-
     } else {
         serverPanic("Unknown hash encoding");
     }
@@ -489,8 +467,7 @@ void hsetCommand(client *c) {
 
     if ((o = hashTypeLookupWriteOrCreate(c,c->argv[1])) == NULL) return;
     hashTypeTryConversion(o,c->argv,2,3);
-    hashTypeTryObjectEncoding(o,&c->argv[2], &c->argv[3]);
-    update = hashTypeSet(o,c->argv[2],c->argv[3]);
+    update = hashTypeSet(o,c->argv[2]->ptr,c->argv[3]->ptr);
     addReply(c, update ? shared.czero : shared.cone);
     signalModifiedKey(c->db,c->argv[1]);
     notifyKeyspaceEvent(NOTIFY_HASH,"hset",c->argv[1],c->db->id);
@@ -502,11 +479,10 @@ void hsetnxCommand(client *c) {
     if ((o = hashTypeLookupWriteOrCreate(c,c->argv[1])) == NULL) return;
     hashTypeTryConversion(o,c->argv,2,3);
 
-    if (hashTypeExists(o, c->argv[2])) {
+    if (hashTypeExists(o, c->argv[2]->ptr)) {
         addReply(c, shared.czero);
     } else {
-        hashTypeTryObjectEncoding(o,&c->argv[2], &c->argv[3]);
-        hashTypeSet(o,c->argv[2],c->argv[3]);
+        hashTypeSet(o,c->argv[2]->ptr,c->argv[3]->ptr);
         addReply(c, shared.cone);
         signalModifiedKey(c->db,c->argv[1]);
         notifyKeyspaceEvent(NOTIFY_HASH,"hset",c->argv[1],c->db->id);
@@ -526,8 +502,7 @@ void hmsetCommand(client *c) {
     if ((o = hashTypeLookupWriteOrCreate(c,c->argv[1])) == NULL) return;
     hashTypeTryConversion(o,c->argv,2,c->argc-1);
     for (i = 2; i < c->argc; i += 2) {
-        hashTypeTryObjectEncoding(o,&c->argv[i], &c->argv[i+1]);
-        hashTypeSet(o,c->argv[i],c->argv[i+1]);
+        hashTypeSet(o,c->argv[i]->ptr,c->argv[i+1]->ptr);
     }
     addReply(c, shared.ok);
     signalModifiedKey(c->db,c->argv[1]);
@@ -537,17 +512,20 @@ void hmsetCommand(client *c) {
 
 void hincrbyCommand(client *c) {
     long long value, incr, oldvalue;
-    robj *o, *current, *new;
+    robj *o;
+    sds new;
+    unsigned char *vstr;
+    unsigned int *lven;
 
     if (getLongLongFromObjectOrReply(c,c->argv[3],&incr,NULL) != C_OK) return;
     if ((o = hashTypeLookupWriteOrCreate(c,c->argv[1])) == NULL) return;
-    if ((current = hashTypeGetObject(o,c->argv[2])) != NULL) {
-        if (getLongLongFromObjectOrReply(c,current,&value,
-            "hash value is not an integer") != C_OK) {
-            decrRefCount(current);
-            return;
-        }
-        decrRefCount(current);
+    if (hashTypeGetObject(o,c->argv[2],&vstr,&vlen,&value) == C_OK) {
+        if (vstr) {
+            if (string2ll(vstr,vlen,&value) == 0) {
+                addReplyError(c,"hash value is not an integer");
+                return;
+            }
+        } /* Else hashTypeGetObject() already stored it into &value */
     } else {
         value = 0;
     }
@@ -559,36 +537,40 @@ void hincrbyCommand(client *c) {
         return;
     }
     value += incr;
-    new = createStringObjectFromLongLong(value);
-    hashTypeTryObjectEncoding(o,&c->argv[2],NULL);
-    hashTypeSet(o,c->argv[2],new);
-    decrRefCount(new);
+    new = sdsfromlonglong(value);
+    hashTypeSet(o,c->argv[2]->ptr,new);
     addReplyLongLong(c,value);
     signalModifiedKey(c->db,c->argv[1]);
     notifyKeyspaceEvent(NOTIFY_HASH,"hincrby",c->argv[1],c->db->id);
     server.dirty++;
 }
 
 void hincrbyfloatCommand(client *c) {
-    double long value, incr;
-    robj *o, *current, *new, *aux;
+    double value, incr;
+    long long ll;
+    robj *o, *doubleobj;
+    sds new;
+    unsigned char *vstr;
+    unsigned int *lven;
 
     if (getLongDoubleFromObjectOrReply(c,c->argv[3],&incr,NULL) != C_OK) return;
     if ((o = hashTypeLookupWriteOrCreate(c,c->argv[1])) == NULL) return;
-    if ((current = hashTypeGetObject(o,c->argv[2])) != NULL) {
-        if (getLongDoubleFromObjectOrReply(c,current,&value,
-            "hash value is not a valid float") != C_OK) {
-            decrRefCount(current);
-            return;
+    if (hashTypeGetObject(o,c->argv[2],vstr,vlen,&ll) == C_OK) {
+        if (vstr) {
+            if (string2d(vstr,vlen,&value) == 0) {
+                addReplyError(c,"hash value is not an integer");
+                return;
+            }
+        } else {
+            value = (double)ll;
         }
-        decrRefCount(current);
     } else {
         value = 0;
     }
 
     value += incr;
-    new = createStringObjectFromLongDouble(value,1);
-    hashTypeTryObjectEncoding(o,&c->argv[2],NULL);
+    doubleobj = createStringObjectFromLongDouble(value,1);
+    decrRefCount(doubleobj);
     hashTypeSet(o,c->argv[2],new);
     addReplyBulk(c,new);
     signalModifiedKey(c->db,c->argv[1]);