@@ -245,7 +245,7 @@ int rdbSaveDoubleValue(FILE *fp, double val) {
     return rdbWriteRaw(fp,buf,len);
 }
 
-/* Save a Redis object. */
+/* Save a Redis object. Returns -1 on error, 0 on success. */
 int rdbSaveObject(FILE *fp, robj *o) {
     int n, nwritten = 0;
 
@@ -302,24 +302,33 @@ int rdbSaveObject(FILE *fp, robj *o) {
             redisPanic("Unknown set encoding");
         }
     } else if (o->type == REDIS_ZSET) {
-        /* Save a set value */
-        zset *zs = o->ptr;
-        dictIterator *di = dictGetIterator(zs->dict);
-        dictEntry *de;
-
-        if ((n = rdbSaveLen(fp,dictSize(zs->dict))) == -1) return -1;
-        nwritten += n;
-
-        while((de = dictNext(di)) != NULL) {
-            robj *eleobj = dictGetEntryKey(de);
-            double *score = dictGetEntryVal(de);
+        /* Save a sorted set value */
+        if (o->encoding == REDIS_ENCODING_ZIPLIST) {
+            size_t l = ziplistBlobLen((unsigned char*)o->ptr);
 
-            if ((n = rdbSaveStringObject(fp,eleobj)) == -1) return -1;
+            if ((n = rdbSaveRawString(fp,o->ptr,l)) == -1) return -1;
             nwritten += n;
-            if ((n = rdbSaveDoubleValue(fp,*score)) == -1) return -1;
+        } else if (o->encoding == REDIS_ENCODING_SKIPLIST) {
+            zset *zs = o->ptr;
+            dictIterator *di = dictGetIterator(zs->dict);
+            dictEntry *de;
+
+            if ((n = rdbSaveLen(fp,dictSize(zs->dict))) == -1) return -1;
             nwritten += n;
+
+            while((de = dictNext(di)) != NULL) {
+                robj *eleobj = dictGetEntryKey(de);
+                double *score = dictGetEntryVal(de);
+
+                if ((n = rdbSaveStringObject(fp,eleobj)) == -1) return -1;
+                nwritten += n;
+                if ((n = rdbSaveDoubleValue(fp,*score)) == -1) return -1;
+                nwritten += n;
+            }
+            dictReleaseIterator(di);
+        } else {
+            redisPanic("Unknown sorted set encoding");
         }
-        dictReleaseIterator(di);
     } else if (o->type == REDIS_HASH) {
         /* Save a hash value */
         if (o->encoding == REDIS_ENCODING_ZIPMAP) {
@@ -386,6 +395,8 @@ int rdbSaveKeyValuePair(FILE *fp, robj *key, robj *val,
         vtype = REDIS_LIST_ZIPLIST;
     else if (vtype == REDIS_SET && val->encoding == REDIS_ENCODING_INTSET)
         vtype = REDIS_SET_INTSET;
+    else if (vtype == REDIS_ZSET && val->encoding == REDIS_ENCODING_ZIPLIST)
+        vtype = REDIS_ZSET_ZIPLIST;
     /* Save type, key, value */
     if (rdbSaveType(fp,vtype) == -1) return -1;
     if (rdbSaveStringObject(fp,key) == -1) return -1;
@@ -414,7 +425,7 @@ int rdbSave(char *filename) {
             strerror(errno));
         return REDIS_ERR;
     }
-    if (fwrite("REDIS0001",9,1,fp) == 0) goto werr;
+    if (fwrite("REDIS0002",9,1,fp) == 0) goto werr;
     for (j = 0; j < server.dbnum; j++) {
         redisDb *db = server.db+j;
         dict *d = db->dict;
@@ -745,11 +756,13 @@ robj *rdbLoadObject(int type, FILE *fp) {
     } else if (type == REDIS_ZSET) {
         /* Read list/set value */
         size_t zsetlen;
+        size_t maxelelen = 0;
         zset *zs;
 
         if ((zsetlen = rdbLoadLen(fp,NULL)) == REDIS_RDB_LENERR) return NULL;
         o = createZsetObject();
         zs = o->ptr;
+
         /* Load every single element of the list/set */
         while(zsetlen--) {
             robj *ele;
@@ -759,10 +772,21 @@ robj *rdbLoadObject(int type, FILE *fp) {
             if ((ele = rdbLoadEncodedStringObject(fp)) == NULL) return NULL;
             ele = tryObjectEncoding(ele);
             if (rdbLoadDoubleValue(fp,&score) == -1) return NULL;
+
+            /* Don't care about integer-encoded strings. */
+            if (ele->encoding == REDIS_ENCODING_RAW &&
+                sdslen(ele->ptr) > maxelelen)
+                    maxelelen = sdslen(ele->ptr);
+
             znode = zslInsert(zs->zsl,score,ele);
             dictAdd(zs->dict,ele,&znode->score);
             incrRefCount(ele); /* added to skiplist */
         }
+
+        /* Convert *after* loading, since sorted sets are not stored ordered. */
+        if (zsetLength(o) <= server.zset_max_ziplist_entries &&
+            maxelelen <= server.zset_max_ziplist_value)
+                zsetConvert(o,REDIS_ENCODING_ZIPLIST);
     } else if (type == REDIS_HASH) {
         size_t hashlen;
 
@@ -811,7 +835,8 @@ robj *rdbLoadObject(int type, FILE *fp) {
         }
     } else if (type == REDIS_HASH_ZIPMAP ||
                type == REDIS_LIST_ZIPLIST ||
-               type == REDIS_SET_INTSET)
+               type == REDIS_SET_INTSET ||
+               type == REDIS_ZSET_ZIPLIST)
     {
         robj *aux = rdbLoadStringObject(fp);
 
@@ -846,8 +871,14 @@ robj *rdbLoadObject(int type, FILE *fp) {
                 if (intsetLen(o->ptr) > server.set_max_intset_entries)
                     setTypeConvert(o,REDIS_ENCODING_HT);
                 break;
+            case REDIS_ZSET_ZIPLIST:
+                o->type = REDIS_ZSET;
+                o->encoding = REDIS_ENCODING_ZIPLIST;
+                if (zsetLength(o) > server.zset_max_ziplist_entries)
+                    zsetConvert(o,REDIS_ENCODING_SKIPLIST);
+                break;
             default:
-                redisPanic("Unknown enoding");
+                redisPanic("Unknown encoding");
                 break;
         }
     } else {
@@ -900,7 +931,7 @@ int rdbLoad(char *filename) {
         return REDIS_ERR;
     }
     rdbver = atoi(buf+5);
-    if (rdbver != 1) {
+    if (rdbver < 1 || rdbver > 2) {
         fclose(fp);
         redisLog(REDIS_WARNING,"Can't handle RDB format version %d",rdbver);
         return REDIS_ERR;