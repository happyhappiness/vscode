@@ -2895,35 +2895,29 @@ static time_t rdbLoadTime(FILE *fp) {
  *
  * isencoded is set to 1 if the readed length is not actually a length but
  * an "encoding type", check the above comments for more info */
-static uint32_t rdbLoadLen(FILE *fp, int rdbver, int *isencoded) {
+static uint32_t rdbLoadLen(FILE *fp, int *isencoded) {
     unsigned char buf[2];
     uint32_t len;
+    int type;
 
     if (isencoded) *isencoded = 0;
-    if (rdbver == 0) {
+    if (fread(buf,1,1,fp) == 0) return REDIS_RDB_LENERR;
+    type = (buf[0]&0xC0)>>6;
+    if (type == REDIS_RDB_6BITLEN) {
+        /* Read a 6 bit len */
+        return buf[0]&0x3F;
+    } else if (type == REDIS_RDB_ENCVAL) {
+        /* Read a 6 bit len encoding type */
+        if (isencoded) *isencoded = 1;
+        return buf[0]&0x3F;
+    } else if (type == REDIS_RDB_14BITLEN) {
+        /* Read a 14 bit len */
+        if (fread(buf+1,1,1,fp) == 0) return REDIS_RDB_LENERR;
+        return ((buf[0]&0x3F)<<8)|buf[1];
+    } else {
+        /* Read a 32 bit len */
         if (fread(&len,4,1,fp) == 0) return REDIS_RDB_LENERR;
         return ntohl(len);
-    } else {
-        int type;
-
-        if (fread(buf,1,1,fp) == 0) return REDIS_RDB_LENERR;
-        type = (buf[0]&0xC0)>>6;
-        if (type == REDIS_RDB_6BITLEN) {
-            /* Read a 6 bit len */
-            return buf[0]&0x3F;
-        } else if (type == REDIS_RDB_ENCVAL) {
-            /* Read a 6 bit len encoding type */
-            if (isencoded) *isencoded = 1;
-            return buf[0]&0x3F;
-        } else if (type == REDIS_RDB_14BITLEN) {
-            /* Read a 14 bit len */
-            if (fread(buf+1,1,1,fp) == 0) return REDIS_RDB_LENERR;
-            return ((buf[0]&0x3F)<<8)|buf[1];
-        } else {
-            /* Read a 32 bit len */
-            if (fread(&len,4,1,fp) == 0) return REDIS_RDB_LENERR;
-            return ntohl(len);
-        }
     }
 }
 
@@ -2951,13 +2945,13 @@ static robj *rdbLoadIntegerObject(FILE *fp, int enctype) {
     return createObject(REDIS_STRING,sdscatprintf(sdsempty(),"%lld",val));
 }
 
-static robj *rdbLoadLzfStringObject(FILE*fp, int rdbver) {
+static robj *rdbLoadLzfStringObject(FILE*fp) {
     unsigned int len, clen;
     unsigned char *c = NULL;
     sds val = NULL;
 
-    if ((clen = rdbLoadLen(fp,rdbver,NULL)) == REDIS_RDB_LENERR) return NULL;
-    if ((len = rdbLoadLen(fp,rdbver,NULL)) == REDIS_RDB_LENERR) return NULL;
+    if ((clen = rdbLoadLen(fp,NULL)) == REDIS_RDB_LENERR) return NULL;
+    if ((len = rdbLoadLen(fp,NULL)) == REDIS_RDB_LENERR) return NULL;
     if ((c = zmalloc(clen)) == NULL) goto err;
     if ((val = sdsnewlen(NULL,len)) == NULL) goto err;
     if (fread(c,clen,1,fp) == 0) goto err;
@@ -2970,20 +2964,20 @@ static robj *rdbLoadLzfStringObject(FILE*fp, int rdbver) {
     return NULL;
 }
 
-static robj *rdbLoadStringObject(FILE*fp, int rdbver) {
+static robj *rdbLoadStringObject(FILE*fp) {
     int isencoded;
     uint32_t len;
     sds val;
 
-    len = rdbLoadLen(fp,rdbver,&isencoded);
+    len = rdbLoadLen(fp,&isencoded);
     if (isencoded) {
         switch(len) {
         case REDIS_RDB_ENC_INT8:
         case REDIS_RDB_ENC_INT16:
         case REDIS_RDB_ENC_INT32:
             return tryObjectSharing(rdbLoadIntegerObject(fp,len));
         case REDIS_RDB_ENC_LZF:
-            return tryObjectSharing(rdbLoadLzfStringObject(fp,rdbver));
+            return tryObjectSharing(rdbLoadLzfStringObject(fp));
         default:
             redisAssert(0!=0);
         }
@@ -3016,6 +3010,59 @@ static int rdbLoadDoubleValue(FILE *fp, double *val) {
     }
 }
 
+/* Load a Redis object of the specified type from the specified file.
+ * On success a newly allocated object is returned, otherwise NULL. */
+static robj *rdbLoadObject(int type, FILE *fp) {
+    robj *o;
+
+    if (type == REDIS_STRING) {
+        /* Read string value */
+        if ((o = rdbLoadStringObject(fp)) == NULL) return NULL;
+        tryObjectEncoding(o);
+    } else if (type == REDIS_LIST || type == REDIS_SET) {
+        /* Read list/set value */
+        uint32_t listlen;
+
+        if ((listlen = rdbLoadLen(fp,NULL)) == REDIS_RDB_LENERR) return NULL;
+        o = (type == REDIS_LIST) ? createListObject() : createSetObject();
+        /* Load every single element of the list/set */
+        while(listlen--) {
+            robj *ele;
+
+            if ((ele = rdbLoadStringObject(fp)) == NULL) return NULL;
+            tryObjectEncoding(ele);
+            if (type == REDIS_LIST) {
+                listAddNodeTail((list*)o->ptr,ele);
+            } else {
+                dictAdd((dict*)o->ptr,ele,NULL);
+            }
+        }
+    } else if (type == REDIS_ZSET) {
+        /* Read list/set value */
+        uint32_t zsetlen;
+        zset *zs;
+
+        if ((zsetlen = rdbLoadLen(fp,NULL)) == REDIS_RDB_LENERR) return NULL;
+        o = createZsetObject();
+        zs = o->ptr;
+        /* Load every single element of the list/set */
+        while(zsetlen--) {
+            robj *ele;
+            double *score = zmalloc(sizeof(double));
+
+            if ((ele = rdbLoadStringObject(fp)) == NULL) return NULL;
+            tryObjectEncoding(ele);
+            if (rdbLoadDoubleValue(fp,score) == -1) return NULL;
+            dictAdd(zs->dict,ele,score);
+            zslInsert(zs->zsl,*score,ele);
+            incrRefCount(ele); /* added to skiplist */
+        }
+    } else {
+        redisAssert(0 != 0);
+    }
+    return o;
+}
+
 static int rdbLoad(char *filename) {
     FILE *fp;
     robj *keyobj = NULL;
@@ -3036,7 +3083,7 @@ static int rdbLoad(char *filename) {
         return REDIS_ERR;
     }
     rdbver = atoi(buf+5);
-    if (rdbver > 1) {
+    if (rdbver != 1) {
         fclose(fp);
         redisLog(REDIS_WARNING,"Can't handle RDB format version %d",rdbver);
         return REDIS_ERR;
@@ -3054,7 +3101,7 @@ static int rdbLoad(char *filename) {
         if (type == REDIS_EOF) break;
         /* Handle SELECT DB opcode as a special case */
         if (type == REDIS_SELECTDB) {
-            if ((dbid = rdbLoadLen(fp,rdbver,NULL)) == REDIS_RDB_LENERR)
+            if ((dbid = rdbLoadLen(fp,NULL)) == REDIS_RDB_LENERR)
                 goto eoferr;
             if (dbid >= (unsigned)server.dbnum) {
                 redisLog(REDIS_WARNING,"FATAL: Data file was created with a Redis server configured to handle more than %d databases. Exiting\n", server.dbnum);
@@ -3065,55 +3112,9 @@ static int rdbLoad(char *filename) {
             continue;
         }
         /* Read key */
-        if ((keyobj = rdbLoadStringObject(fp,rdbver)) == NULL) goto eoferr;
-
-        if (type == REDIS_STRING) {
-            /* Read string value */
-            if ((o = rdbLoadStringObject(fp,rdbver)) == NULL) goto eoferr;
-            tryObjectEncoding(o);
-        } else if (type == REDIS_LIST || type == REDIS_SET) {
-            /* Read list/set value */
-            uint32_t listlen;
-
-            if ((listlen = rdbLoadLen(fp,rdbver,NULL)) == REDIS_RDB_LENERR)
-                goto eoferr;
-            o = (type == REDIS_LIST) ? createListObject() : createSetObject();
-            /* Load every single element of the list/set */
-            while(listlen--) {
-                robj *ele;
-
-                if ((ele = rdbLoadStringObject(fp,rdbver)) == NULL) goto eoferr;
-                tryObjectEncoding(ele);
-                if (type == REDIS_LIST) {
-                    listAddNodeTail((list*)o->ptr,ele);
-                } else {
-                    dictAdd((dict*)o->ptr,ele,NULL);
-                }
-            }
-        } else if (type == REDIS_ZSET) {
-            /* Read list/set value */
-            uint32_t zsetlen;
-            zset *zs;
-
-            if ((zsetlen = rdbLoadLen(fp,rdbver,NULL)) == REDIS_RDB_LENERR)
-                goto eoferr;
-            o = createZsetObject();
-            zs = o->ptr;
-            /* Load every single element of the list/set */
-            while(zsetlen--) {
-                robj *ele;
-                double *score = zmalloc(sizeof(double));
-
-                if ((ele = rdbLoadStringObject(fp,rdbver)) == NULL) goto eoferr;
-                tryObjectEncoding(ele);
-                if (rdbLoadDoubleValue(fp,score) == -1) goto eoferr;
-                dictAdd(zs->dict,ele,score);
-                zslInsert(zs->zsl,*score,ele);
-                incrRefCount(ele); /* added to skiplist */
-            }
-        } else {
-            redisAssert(0 != 0);
-        }
+        if ((keyobj = rdbLoadStringObject(fp)) == NULL) goto eoferr;
+        /* Read value */
+        if ((o = rdbLoadObject(type,fp)) == NULL) goto eoferr;
         /* Add the new object in the hash table */
         retval = dictAdd(d,keyobj,o);
         if (retval == DICT_ERR) {