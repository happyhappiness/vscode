@@ -43,6 +43,7 @@
 #define RDB_LOAD_NONE   0
 #define RDB_LOAD_ENC    (1<<0)
 #define RDB_LOAD_PLAIN  (1<<1)
+#define RDB_LOAD_SDS    (1<<2)
 
 #define rdbExitReportCorruptRDB(reason) rdbCheckThenExit(reason, __LINE__);
 
@@ -179,6 +180,7 @@ int rdbEncodeInteger(long long value, unsigned char *enc) {
  * rdbGenerincLoadStringObject() for more info. */
 void *rdbLoadIntegerObject(rio *rdb, int enctype, int flags) {
     int plain = flags & RDB_LOAD_PLAIN;
+    int sds = flags & RDB_LOAD_SDS;
     int encode = flags & RDB_LOAD_ENC;
     unsigned char enc[4];
     long long val;
@@ -200,10 +202,10 @@ void *rdbLoadIntegerObject(rio *rdb, int enctype, int flags) {
         val = 0; /* anti-warning */
         rdbExitReportCorruptRDB("Unknown RDB integer encoding type");
     }
-    if (plain) {
+    if (plain || sds) {
         char buf[LONG_STR_SIZE], *p;
         int len = ll2string(buf,sizeof(buf),val);
-        p = zmalloc(len);
+        p = plain ? zmalloc(len) : sdsnewlen(NULL,len);
         memcpy(p,buf,len);
         return p;
     } else if (encode) {
@@ -280,9 +282,10 @@ ssize_t rdbSaveLzfStringObject(rio *rdb, unsigned char *s, size_t len) {
  * rdbGenericLoadStringObject() function. */
 void *rdbLoadLzfStringObject(rio *rdb, int flags) {
     int plain = flags & RDB_LOAD_PLAIN;
+    int sds = flags & RDB_LOAD_SDS;
     unsigned int len, clen;
     unsigned char *c = NULL;
-    sds val = NULL;
+    char *val = NULL;
 
     if ((clen = rdbLoadLen(rdb,NULL)) == RDB_LENERR) return NULL;
     if ((len = rdbLoadLen(rdb,NULL)) == RDB_LENERR) return NULL;
@@ -292,18 +295,19 @@ void *rdbLoadLzfStringObject(rio *rdb, int flags) {
     if (plain) {
         val = zmalloc(len);
     } else {
-        if ((val = sdsnewlen(NULL,len)) == NULL) goto err;
+        val = sdsnewlen(NULL,len);
     }
 
     /* Load the compressed representation and uncompress it to target. */
     if (rioRead(rdb,c,clen) == 0) goto err;
     if (lzf_decompress(c,clen,val,len) == 0) goto err;
     zfree(c);
 
-    if (plain)
+    if (plain || sds) {
         return val;
-    else
+    } else {
         return createObject(OBJ_STRING,val);
+    }
 err:
     zfree(c);
     if (plain)
@@ -366,7 +370,7 @@ ssize_t rdbSaveLongLongAsStringObject(rio *rdb, long long value) {
     return nwritten;
 }
 
-/* Like rdbSaveStringObjectRaw() but handle encoded objects */
+/* Like rdbSaveRawString() gets a Redis object instead. */
 int rdbSaveStringObject(rio *rdb, robj *obj) {
     /* Avoid to decode the object, then encode it again, if the
      * object is already integer encoded. */
@@ -387,10 +391,12 @@ int rdbSaveStringObject(rio *rdb, robj *obj) {
  *               no longer guarantees that obj->ptr is an SDS string.
  * RDB_LOAD_PLAIN: Return a plain string allocated with zmalloc()
  *                 instead of a Redis object.
+ * RDB_LOAD_SDS: Return an SDS string instead of a Redis object.
  */
 void *rdbGenericLoadStringObject(rio *rdb, int flags) {
     int encode = flags & RDB_LOAD_ENC;
     int plain = flags & RDB_LOAD_PLAIN;
+    int sds = flags & RDB_LOAD_SDS;
     int isencoded;
     uint32_t len;
 
@@ -409,21 +415,24 @@ void *rdbGenericLoadStringObject(rio *rdb, int flags) {
     }
 
     if (len == RDB_LENERR) return NULL;
-    if (!plain) {
+    if (plain || sds) {
+        void *buf = plain ? zmalloc(len) : sdsnewlen(NULL,len);
+        if (len && rioRead(rdb,buf,len) == 0) {
+            if (plain)
+                zfree(buf);
+            else
+                sdsfree(buf);
+            return NULL;
+        }
+        return buf;
+    } else {
         robj *o = encode ? createStringObject(NULL,len) :
                            createRawStringObject(NULL,len);
         if (len && rioRead(rdb,o->ptr,len) == 0) {
             decrRefCount(o);
             return NULL;
         }
         return o;
-    } else {
-        void *buf = zmalloc(len);
-        if (len && rioRead(rdb,buf,len) == 0) {
-            zfree(buf);
-            return NULL;
-        }
-        return buf;
     }
 }
 
@@ -583,8 +592,9 @@ ssize_t rdbSaveObject(rio *rdb, robj *o) {
             nwritten += n;
 
             while((de = dictNext(di)) != NULL) {
-                robj *eleobj = dictGetKey(de);
-                if ((n = rdbSaveStringObject(rdb,eleobj)) == -1) return -1;
+                sds ele = dictGetKey(de);
+                if ((n = rdbSaveRawString(rdb,(unsigned char*)ele,sdslen(ele)))
+                    == -1) return -1;
                 nwritten += n;
             }
             dictReleaseIterator(di);
@@ -959,7 +969,7 @@ robj *rdbLoadObject(int rdbtype, rio *rdb) {
             decrRefCount(ele);
         }
     } else if (rdbtype == RDB_TYPE_SET) {
-        /* Read list/set value */
+        /* Read Set value */
         if ((len = rdbLoadLen(rdb,NULL)) == RDB_LENERR) return NULL;
 
         /* Use a regular set when there are too many entries. */
@@ -973,15 +983,17 @@ robj *rdbLoadObject(int rdbtype, rio *rdb) {
             o = createIntsetObject();
         }
 
-        /* Load every single element of the list/set */
+        /* Load every single element of the set */
         for (i = 0; i < len; i++) {
             long long llval;
-            if ((ele = rdbLoadEncodedStringObject(rdb)) == NULL) return NULL;
-            ele = tryObjectEncoding(ele);
+            sds sdsele;
+
+            if ((sdsele = rdbGenericLoadStringObject(rdb,RDB_LOAD_SDS)) == NULL)
+                return NULL;
 
             if (o->encoding == OBJ_ENCODING_INTSET) {
                 /* Fetch integer value from element */
-                if (isObjectRepresentableAsLongLong(ele,&llval) == C_OK) {
+                if (isSdsRepresentableAsLongLong(sdsele,&llval) == C_OK) {
                     o->ptr = intsetAdd(o->ptr,llval,NULL);
                 } else {
                     setTypeConvert(o,OBJ_ENCODING_HT);
@@ -992,9 +1004,9 @@ robj *rdbLoadObject(int rdbtype, rio *rdb) {
             /* This will also be called when the set was just converted
              * to a regular hash table encoded set */
             if (o->encoding == OBJ_ENCODING_HT) {
-                dictAdd((dict*)o->ptr,ele,NULL);
+                dictAdd((dict*)o->ptr,sdsele,NULL);
             } else {
-                decrRefCount(ele);
+                sdsfree(sdsele);
             }
         }
     } else if (rdbtype == RDB_TYPE_ZSET) {