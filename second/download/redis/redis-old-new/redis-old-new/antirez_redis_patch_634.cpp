@@ -209,43 +209,49 @@ int rdbTryIntegerEncoding(char *s, size_t len, unsigned char *enc) {
     return rdbEncodeInteger(value,enc);
 }
 
-int rdbSaveLzfStringObject(rio *rdb, unsigned char *s, size_t len) {
-    size_t comprlen, outlen;
+int rdbSaveLzfBlob(rio *rdb, void *data, size_t compress_len,
+                   size_t original_len) {
     unsigned char byte;
     int n, nwritten = 0;
-    void *out;
 
-    /* We require at least four bytes compression for this to be worth it */
-    if (len <= 4) return 0;
-    outlen = len-4;
-    if ((out = zmalloc(outlen+1)) == NULL) return 0;
-    comprlen = lzf_compress(s, len, out, outlen);
-    if (comprlen == 0) {
-        zfree(out);
-        return 0;
-    }
     /* Data compressed! Let's save it on disk */
     byte = (REDIS_RDB_ENCVAL<<6)|REDIS_RDB_ENC_LZF;
     if ((n = rdbWriteRaw(rdb,&byte,1)) == -1) goto writeerr;
     nwritten += n;
 
-    if ((n = rdbSaveLen(rdb,comprlen)) == -1) goto writeerr;
+    if ((n = rdbSaveLen(rdb,compress_len)) == -1) goto writeerr;
     nwritten += n;
 
-    if ((n = rdbSaveLen(rdb,len)) == -1) goto writeerr;
+    if ((n = rdbSaveLen(rdb,original_len)) == -1) goto writeerr;
     nwritten += n;
 
-    if ((n = rdbWriteRaw(rdb,out,comprlen)) == -1) goto writeerr;
+    if ((n = rdbWriteRaw(rdb,data,compress_len)) == -1) goto writeerr;
     nwritten += n;
 
-    zfree(out);
     return nwritten;
 
 writeerr:
-    zfree(out);
     return -1;
 }
 
+int rdbSaveLzfStringObject(rio *rdb, unsigned char *s, size_t len) {
+    size_t comprlen, outlen;
+    void *out;
+
+    /* We require at least four bytes compression for this to be worth it */
+    if (len <= 4) return 0;
+    outlen = len-4;
+    if ((out = zmalloc(outlen+1)) == NULL) return 0;
+    comprlen = lzf_compress(s, len, out, outlen);
+    if (comprlen == 0) {
+        zfree(out);
+        return 0;
+    }
+    size_t nwritten = rdbSaveLzfBlob(rdb, out, comprlen, len);
+    zfree(out);
+    return nwritten;
+}
+
 robj *rdbLoadLzfStringObject(rio *rdb) {
     unsigned int len, clen;
     unsigned char *c = NULL;
@@ -433,10 +439,8 @@ int rdbSaveObjectType(rio *rdb, robj *o) {
     case REDIS_STRING:
         return rdbSaveType(rdb,REDIS_RDB_TYPE_STRING);
     case REDIS_LIST:
-        if (o->encoding == REDIS_ENCODING_ZIPLIST)
-            return rdbSaveType(rdb,REDIS_RDB_TYPE_LIST_ZIPLIST);
-        else if (o->encoding == REDIS_ENCODING_LINKEDLIST)
-            return rdbSaveType(rdb,REDIS_RDB_TYPE_LIST);
+        if (o->encoding == REDIS_ENCODING_QUICKLIST)
+            return rdbSaveType(rdb,REDIS_RDB_TYPE_LIST_QUICKLIST);
         else
             redisPanic("Unknown list encoding");
     case REDIS_SET:
@@ -477,33 +481,32 @@ int rdbLoadObjectType(rio *rdb) {
 
 /* Save a Redis object. Returns -1 on error, number of bytes written on success. */
 int rdbSaveObject(rio *rdb, robj *o) {
-    int n, nwritten = 0;
+    int n = 0, nwritten = 0;
 
     if (o->type == REDIS_STRING) {
         /* Save a string value */
         if ((n = rdbSaveStringObject(rdb,o)) == -1) return -1;
         nwritten += n;
     } else if (o->type == REDIS_LIST) {
         /* Save a list value */
-        if (o->encoding == REDIS_ENCODING_ZIPLIST) {
-            size_t l = ziplistBlobLen((unsigned char*)o->ptr);
-
-            if ((n = rdbSaveRawString(rdb,o->ptr,l)) == -1) return -1;
-            nwritten += n;
-        } else if (o->encoding == REDIS_ENCODING_LINKEDLIST) {
-            list *list = o->ptr;
-            listIter li;
-            listNode *ln;
+        if (o->encoding == REDIS_ENCODING_QUICKLIST) {
+            quicklist *ql = o->ptr;
+            quicklistNode *node = ql->head;
 
-            if ((n = rdbSaveLen(rdb,listLength(list))) == -1) return -1;
+            if ((n = rdbSaveLen(rdb,ql->len)) == -1) return -1;
             nwritten += n;
 
-            listRewind(list,&li);
-            while((ln = listNext(&li))) {
-                robj *eleobj = listNodeValue(ln);
-                if ((n = rdbSaveStringObject(rdb,eleobj)) == -1) return -1;
-                nwritten += n;
-            }
+            do {
+                if (quicklistNodeIsCompressed(node)) {
+                    void *data;
+                    size_t compress_len = quicklistGetLzf(node, &data);
+                    if ((n = rdbSaveLzfBlob(rdb,data,compress_len,node->sz)) == -1) return -1;
+                    nwritten += n;
+                } else {
+                    if ((n = rdbSaveRawString(rdb,node->zl,node->sz)) == -1) return -1;
+                    nwritten += n;
+                }
+            } while ((node = node->next));
         } else {
             redisPanic("Unknown list encoding");
         }
@@ -720,7 +723,7 @@ int rdbSave(char *filename) {
     char tmpfile[256];
     FILE *fp;
     rio rdb;
-    int error;
+    int error = 0;
 
     snprintf(tmpfile,256,"temp-%d.rdb", (int) getpid());
     fp = fopen(tmpfile,"w");
@@ -831,33 +834,18 @@ robj *rdbLoadObject(int rdbtype, rio *rdb) {
         /* Read list value */
         if ((len = rdbLoadLen(rdb,NULL)) == REDIS_RDB_LENERR) return NULL;
 
-        /* Use a real list when there are too many entries */
-        if (len > server.list_max_ziplist_entries) {
-            o = createListObject();
-        } else {
-            o = createZiplistObject();
-        }
+        o = createQuicklistObject();
+        quicklistSetOptions(o->ptr, server.list_max_ziplist_size,
+                            server.list_compress_depth);
 
         /* Load every single element of the list */
         while(len--) {
             if ((ele = rdbLoadEncodedStringObject(rdb)) == NULL) return NULL;
-
-            /* If we are using a ziplist and the value is too big, convert
-             * the object to a real list. */
-            if (o->encoding == REDIS_ENCODING_ZIPLIST &&
-                sdsEncodedObject(ele) &&
-                sdslen(ele->ptr) > server.list_max_ziplist_value)
-                    listTypeConvert(o,REDIS_ENCODING_LINKEDLIST);
-
-            if (o->encoding == REDIS_ENCODING_ZIPLIST) {
-                dec = getDecodedObject(ele);
-                o->ptr = ziplistPush(o->ptr,dec->ptr,sdslen(dec->ptr),REDIS_TAIL);
-                decrRefCount(dec);
-                decrRefCount(ele);
-            } else {
-                ele = tryObjectEncoding(ele);
-                listAddNodeTail(o->ptr,ele);
-            }
+            dec = getDecodedObject(ele);
+            size_t len = sdslen(dec->ptr);
+            quicklistPushTail(o->ptr, dec->ptr, len);
+            decrRefCount(dec);
+            decrRefCount(ele);
         }
     } else if (rdbtype == REDIS_RDB_TYPE_SET) {
         /* Read list/set value */
@@ -994,20 +982,30 @@ robj *rdbLoadObject(int rdbtype, rio *rdb) {
 
         /* All pairs should be read by now */
         redisAssert(len == 0);
-
+    } else if (rdbtype == REDIS_RDB_TYPE_LIST_QUICKLIST) {
+        if ((len = rdbLoadLen(rdb,NULL)) == REDIS_RDB_LENERR) return NULL;
+        o = createQuicklistObject();
+        quicklistSetOptions(o->ptr, server.list_max_ziplist_size,
+                            server.list_compress_depth);
+
+        while (len--) {
+            if ((ele = rdbLoadStringObject(rdb)) == NULL) return NULL;
+            /* 'ele' contains a sds of the ziplist, but we need to extract
+             * the actual ziplist for future usage. We must copy the
+             * sds contents to a new buffer. */
+            unsigned char *zl = (unsigned char *)sdsnative(ele->ptr);
+            zfree(ele); /* free robj container since we keep the ziplist */
+            quicklistAppendZiplist(o->ptr, zl);
+        }
     } else if (rdbtype == REDIS_RDB_TYPE_HASH_ZIPMAP  ||
                rdbtype == REDIS_RDB_TYPE_LIST_ZIPLIST ||
                rdbtype == REDIS_RDB_TYPE_SET_INTSET   ||
                rdbtype == REDIS_RDB_TYPE_ZSET_ZIPLIST ||
                rdbtype == REDIS_RDB_TYPE_HASH_ZIPLIST)
     {
-        robj *aux = rdbLoadStringObject(rdb);
-
-        if (aux == NULL) return NULL;
-        o = createObject(REDIS_STRING,NULL); /* string is just placeholder */
-        o->ptr = zmalloc(sdslen(aux->ptr));
-        memcpy(o->ptr,aux->ptr,sdslen(aux->ptr));
-        decrRefCount(aux);
+        o = rdbLoadStringObject(rdb);
+        if (o == NULL) return NULL;
+        o->ptr = sdsnative(o->ptr);
 
         /* Fix the object encoding, and make sure to convert the encoded
          * data type into the base type if accordingly to the current
@@ -1048,8 +1046,7 @@ robj *rdbLoadObject(int rdbtype, rio *rdb) {
             case REDIS_RDB_TYPE_LIST_ZIPLIST:
                 o->type = REDIS_LIST;
                 o->encoding = REDIS_ENCODING_ZIPLIST;
-                if (ziplistLen(o->ptr) > server.list_max_ziplist_entries)
-                    listTypeConvert(o,REDIS_ENCODING_LINKEDLIST);
+                listTypeConvert(o,REDIS_ENCODING_QUICKLIST);
                 break;
             case REDIS_RDB_TYPE_SET_INTSET:
                 o->type = REDIS_SET;