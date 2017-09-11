@@ -67,7 +67,7 @@ int hashTypeGetFromZiplist(robj *o, sds field,
     zl = o->ptr;
     fptr = ziplistIndex(zl, ZIPLIST_HEAD);
     if (fptr != NULL) {
-        fptr = ziplistFind(fptr, field, sdslen(field), 1);
+        fptr = ziplistFind(fptr, (unsigned char*)field, sdslen(field), 1);
         if (fptr != NULL) {
             /* Grab pointer to the value (fptr points to the field) */
             vptr = ziplistNext(zl, fptr);
@@ -106,15 +106,15 @@ sds hashTypeGetFromHashTable(robj *o, sds field) {
  * If *vll is populated *vstr is set to NULL, so the caller
  * can always check the function return by checking the return value
  * for C_OK and checking if vll (or vstr) is NULL. */
-int hashTypeGetObject(robj *o, sds field, unsigned char **vstr, unsigned int *vlen, long long *vll) {
+int hashTypeGetValue(robj *o, sds field, unsigned char **vstr, unsigned int *vlen, long long *vll) {
     if (o->encoding == OBJ_ENCODING_ZIPLIST) {
         *vstr = NULL;
         if (hashTypeGetFromZiplist(o, field, vstr, vlen, vll) == 0)
             return C_OK;
     } else if (o->encoding == OBJ_ENCODING_HT) {
         sds value;
-        if (value = hashTypeGetFromHashTable(o, field) != NULL) {
-            *vstr = value;
+        if ((value = hashTypeGetFromHashTable(o, field)) != NULL) {
+            *vstr = (unsigned char*) value;
             *vlen = sdslen(value);
             return C_OK;
         }
@@ -124,6 +124,20 @@ int hashTypeGetObject(robj *o, sds field, unsigned char **vstr, unsigned int *vl
     return C_ERR;
 }
 
+/* Like hashTypeGetValue() but returns a Redis object, which is useful for
+ * interaction with the hash type outside t_hash.c.
+ * The function returns NULL if the field is not found in the hash. Otherwise
+ * a newly allocated string object with the value is returned. */
+robj *hashTypeGetValueObject(robj *o, sds field) {
+    unsigned char *vstr;
+    unsigned int vlen;
+    long long vll;
+
+    if (hashTypeGetValue(o,field,&vstr,&vlen,&vll) == C_ERR) return NULL;
+    if (vstr) return createStringObject((char*)vstr,vlen);
+    else return createStringObjectFromLongLong(vll);
+}
+
 /* Higher level function using hashTypeGet*() to return the length of the
  * object associated with the requested field, or 0 if the field does not
  * exist. */
@@ -157,8 +171,6 @@ int hashTypeExists(robj *o, sds field) {
 
         if (hashTypeGetFromZiplist(o, field, &vstr, &vlen, &vll) == 0) return 1;
     } else if (o->encoding == OBJ_ENCODING_HT) {
-        robj *aux;
-
         if (hashTypeGetFromHashTable(o, field) != NULL) return 1;
     } else {
         serverPanic("Unknown hash encoding");
@@ -178,7 +190,7 @@ int hashTypeSet(robj *o, sds field, sds value) {
         zl = o->ptr;
         fptr = ziplistIndex(zl, ZIPLIST_HEAD);
         if (fptr != NULL) {
-            fptr = ziplistFind(fptr, field, sdslen(field), 1);
+            fptr = ziplistFind(fptr, (unsigned char*)field, sdslen(field), 1);
             if (fptr != NULL) {
                 /* Grab pointer to the value (fptr points to the field) */
                 vptr = ziplistNext(zl, fptr);
@@ -189,14 +201,17 @@ int hashTypeSet(robj *o, sds field, sds value) {
                 zl = ziplistDelete(zl, &vptr);
 
                 /* Insert new value */
-                zl = ziplistInsert(zl, vptr, value->ptr, sdslen(value->ptr));
+                zl = ziplistInsert(zl, vptr, (unsigned char*)value,
+                        sdslen(value));
             }
         }
 
         if (!update) {
             /* Push new field/value pair onto the tail of the ziplist */
-            zl = ziplistPush(zl, field, sdslen(field), ZIPLIST_TAIL);
-            zl = ziplistPush(zl, value, sdslen(value), ZIPLIST_TAIL);
+            zl = ziplistPush(zl, (unsigned char*)field, sdslen(field),
+                    ZIPLIST_TAIL);
+            zl = ziplistPush(zl, (unsigned char*)value, sdslen(value),
+                    ZIPLIST_TAIL);
         }
         o->ptr = zl;
 
@@ -210,7 +225,7 @@ int hashTypeSet(robj *o, sds field, sds value) {
             dictGetVal(de) = sdsdup(value);
             update = 1;
         } else {
-            dictAdd(o->ptr,sdsdup(key),sdsdup(value));
+            dictAdd(o->ptr,sdsdup(field),sdsdup(value));
         }
     } else {
         serverPanic("Unknown hash encoding");
@@ -229,17 +244,14 @@ int hashTypeDelete(robj *o, sds field) {
         zl = o->ptr;
         fptr = ziplistIndex(zl, ZIPLIST_HEAD);
         if (fptr != NULL) {
-            fptr = ziplistFind(fptr, field, sdslen(field), 1);
+            fptr = ziplistFind(fptr, (unsigned char*)field, sdslen(field), 1);
             if (fptr != NULL) {
                 zl = ziplistDelete(zl,&fptr);
                 zl = ziplistDelete(zl,&fptr);
                 o->ptr = zl;
                 deleted = 1;
             }
         }
-
-        decrRefCount(field);
-
     } else if (o->encoding == OBJ_ENCODING_HT) {
         if (dictDelete((dict*)o->ptr, field) == C_OK) {
             deleted = 1;
@@ -376,7 +388,7 @@ void hashTypeCurrentObject(hashTypeIterator *hi, int what, unsigned char **vstr,
         hashTypeCurrentFromZiplist(hi, what, vstr, vlen, vll);
     } else if (hi->encoding == OBJ_ENCODING_HT) {
         sds ele = hashTypeCurrentFromHashTable(hi, what);
-        *vstr = ele;
+        *vstr = (unsigned char*) ele;
         *vlen = sdslen(ele);
     } else {
         serverPanic("Unknown hash encoding");
@@ -424,14 +436,11 @@ void hashTypeConvertZiplist(robj *o, int enc) {
         dict = dictCreate(&hashDictType, NULL);
 
         while (hashTypeNext(hi) != C_ERR) {
-            unsigned char *vstr;
-            unsigned int vlen;
-            long long vll;
             sds key, value;
 
             key = hashTypeCurrentObjectNewSds(hi,OBJ_HASH_KEY);
             value = hashTypeCurrentObjectNewSds(hi,OBJ_HASH_VALUE);
-            ret = dictAdd(dict, field, value);
+            ret = dictAdd(dict, key, value);
             if (ret != DICT_OK) {
                 serverLogHexDump(LL_WARNING,"ziplist with dup elements dump",
                     o->ptr,ziplistBlobLen(o->ptr));
@@ -515,17 +524,17 @@ void hincrbyCommand(client *c) {
     robj *o;
     sds new;
     unsigned char *vstr;
-    unsigned int *lven;
+    unsigned int vlen;
 
     if (getLongLongFromObjectOrReply(c,c->argv[3],&incr,NULL) != C_OK) return;
     if ((o = hashTypeLookupWriteOrCreate(c,c->argv[1])) == NULL) return;
-    if (hashTypeGetObject(o,c->argv[2],&vstr,&vlen,&value) == C_OK) {
+    if (hashTypeGetValue(o,c->argv[2]->ptr,&vstr,&vlen,&value) == C_OK) {
         if (vstr) {
-            if (string2ll(vstr,vlen,&value) == 0) {
+            if (string2ll((char*)vstr,vlen,&value) == 0) {
                 addReplyError(c,"hash value is not an integer");
                 return;
             }
-        } /* Else hashTypeGetObject() already stored it into &value */
+        } /* Else hashTypeGetValue() already stored it into &value */
     } else {
         value = 0;
     }
@@ -551,13 +560,13 @@ void hincrbyfloatCommand(client *c) {
     robj *o;
     sds new;
     unsigned char *vstr;
-    unsigned int *lven;
+    unsigned int vlen;
 
-    if (getLongDoubleFromObjectOrReply(c,c->argv[3],&incr,NULL) != C_OK) return;
+    if (getDoubleFromObjectOrReply(c,c->argv[3],&incr,NULL) != C_OK) return;
     if ((o = hashTypeLookupWriteOrCreate(c,c->argv[1])) == NULL) return;
-    if (hashTypeGetObject(o,c->argv[2],vstr,vlen,&ll) == C_OK) {
+    if (hashTypeGetValue(o,c->argv[2]->ptr,&vstr,&vlen,&ll) == C_OK) {
         if (vstr) {
-            if (string2d(vstr,vlen,&value) == 0) {
+            if (string2d((char*)vstr,vlen,&value) == 0) {
                 addReplyError(c,"hash value is not an integer");
                 return;
             }
@@ -571,9 +580,9 @@ void hincrbyfloatCommand(client *c) {
     value += incr;
 
     char buf[256];
-    int len = ld2string(buf,sizeof(buf),value,humanfriendly);
+    int len = ld2string(buf,sizeof(buf),value,1);
     new = sdsnewlen(buf,len);
-    hashTypeSet(o,c->argv[2],new);
+    hashTypeSet(o,c->argv[2]->ptr,new);
     addReplyBulkSds(c,new);
     signalModifiedKey(c->db,c->argv[1]);
     notifyKeyspaceEvent(NOTIFY_HASH,"hincrbyfloat",c->argv[1],c->db->id);
@@ -587,12 +596,10 @@ void hincrbyfloatCommand(client *c) {
     newobj = createRawStringObject(buf,len);
     rewriteClientCommandArgument(c,0,aux);
     decrRefCount(aux);
-    rewriteClientCommandArgument(c,3,new);
+    rewriteClientCommandArgument(c,3,newobj);
     decrRefCount(newobj);
 }
 
-/* XXX From here. */
-
 static void addHashFieldToReply(client *c, robj *o, sds field) {
     int ret;
 