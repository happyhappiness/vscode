@@ -1,66 +1,103 @@
-#include "redis.h"
-#include "lzf.h"    /* LZF compression library */
-
 #include <math.h>
 #include <sys/types.h>
 #include <sys/time.h>
 #include <sys/resource.h>
 #include <sys/wait.h>
 #include <arpa/inet.h>
 #include <sys/stat.h>
+#include "rdb.h"
+#include "lzf.h" /* LZF compression library */
 
-/* Convenience wrapper around fwrite, that returns the number of bytes written
- * to the file instead of the number of objects (see fwrite(3)) and -1 in the
- * case of an error. It also supports a NULL *fp to skip writing altogether
- * instead of writing to /dev/null. */
-static int rdbWriteRaw(FILE *fp, void *p, size_t len) {
-    if (fp != NULL && fwrite(p,len,1,fp) == 0) return -1;
+static int rdbWriteRaw(rio *rdb, void *p, size_t len) {
+    if (rdb && rioWrite(rdb,p,len) == 0)
+        return -1;
     return len;
 }
 
-int rdbSaveType(FILE *fp, unsigned char type) {
-    return rdbWriteRaw(fp,&type,1);
+int rdbSaveType(rio *rdb, unsigned char type) {
+    return rdbWriteRaw(rdb,&type,1);
+}
+
+int rdbLoadType(rio *rdb) {
+    unsigned char type;
+    if (rioRead(rdb,&type,1) == 0) return -1;
+    return type;
 }
 
-int rdbSaveTime(FILE *fp, time_t t) {
+int rdbSaveTime(rio *rdb, time_t t) {
     int32_t t32 = (int32_t) t;
-    return rdbWriteRaw(fp,&t32,4);
+    return rdbWriteRaw(rdb,&t32,4);
+}
+
+time_t rdbLoadTime(rio *rdb) {
+    int32_t t32;
+    if (rioRead(rdb,&t32,4) == 0) return -1;
+    return (time_t)t32;
 }
 
-/* check rdbLoadLen() comments for more info */
-int rdbSaveLen(FILE *fp, uint32_t len) {
+/* Saves an encoded length. The first two bits in the first byte are used to
+ * hold the encoding type. See the REDIS_RDB_* definitions for more information
+ * on the types of encoding. */
+int rdbSaveLen(rio *rdb, uint32_t len) {
     unsigned char buf[2];
-    int nwritten;
+    size_t nwritten;
 
     if (len < (1<<6)) {
         /* Save a 6 bit len */
         buf[0] = (len&0xFF)|(REDIS_RDB_6BITLEN<<6);
-        if (rdbWriteRaw(fp,buf,1) == -1) return -1;
+        if (rdbWriteRaw(rdb,buf,1) == -1) return -1;
         nwritten = 1;
     } else if (len < (1<<14)) {
         /* Save a 14 bit len */
         buf[0] = ((len>>8)&0xFF)|(REDIS_RDB_14BITLEN<<6);
         buf[1] = len&0xFF;
-        if (rdbWriteRaw(fp,buf,2) == -1) return -1;
+        if (rdbWriteRaw(rdb,buf,2) == -1) return -1;
         nwritten = 2;
     } else {
         /* Save a 32 bit len */
         buf[0] = (REDIS_RDB_32BITLEN<<6);
-        if (rdbWriteRaw(fp,buf,1) == -1) return -1;
+        if (rdbWriteRaw(rdb,buf,1) == -1) return -1;
         len = htonl(len);
-        if (rdbWriteRaw(fp,&len,4) == -1) return -1;
+        if (rdbWriteRaw(rdb,&len,4) == -4) return -1;
         nwritten = 1+4;
     }
     return nwritten;
 }
 
-/* Encode 'value' as an integer if possible (if integer will fit the
- * supported range). If the function sucessful encoded the integer
- * then the (up to 5 bytes) encoded representation is written in the
- * string pointed by 'enc' and the length is returned. Otherwise
- * 0 is returned. */
+/* Load an encoded length. The "isencoded" argument is set to 1 if the length
+ * is not actually a length but an "encoding type". See the REDIS_RDB_ENC_*
+ * definitions in rdb.h for more information. */
+uint32_t rdbLoadLen(rio *rdb, int *isencoded) {
+    unsigned char buf[2];
+    uint32_t len;
+    int type;
+
+    if (isencoded) *isencoded = 0;
+    if (rioRead(rdb,buf,1) == 0) return REDIS_RDB_LENERR;
+    type = (buf[0]&0xC0)>>6;
+    if (type == REDIS_RDB_ENCVAL) {
+        /* Read a 6 bit encoding type. */
+        if (isencoded) *isencoded = 1;
+        return buf[0]&0x3F;
+    } else if (type == REDIS_RDB_6BITLEN) {
+        /* Read a 6 bit len. */
+        return buf[0]&0x3F;
+    } else if (type == REDIS_RDB_14BITLEN) {
+        /* Read a 14 bit len. */
+        if (rioRead(rdb,buf+1,1) == 0) return REDIS_RDB_LENERR;
+        return ((buf[0]&0x3F)<<8)|buf[1];
+    } else {
+        /* Read a 32 bit len. */
+        if (rioRead(rdb,&len,4) == 0) return REDIS_RDB_LENERR;
+        return ntohl(len);
+    }
+}
+
+/* Encodes the "value" argument as integer when it fits in the supported ranges
+ * for encoded types. If the function successfully encodes the integer, the
+ * representation is stored in the buffer pointer to by "enc" and the string
+ * length is returned. Otherwise 0 is returned. */
 int rdbEncodeInteger(long long value, unsigned char *enc) {
-    /* Finally check if it fits in our ranges */
     if (value >= -(1<<7) && value <= (1<<7)-1) {
         enc[0] = (REDIS_RDB_ENCVAL<<6)|REDIS_RDB_ENC_INT8;
         enc[1] = value&0xFF;
@@ -82,6 +119,36 @@ int rdbEncodeInteger(long long value, unsigned char *enc) {
     }
 }
 
+/* Loads an integer-encoded object with the specified encoding type "enctype".
+ * If the "encode" argument is set the function may return an integer-encoded
+ * string object, otherwise it always returns a raw string object. */
+robj *rdbLoadIntegerObject(rio *rdb, int enctype, int encode) {
+    unsigned char enc[4];
+    long long val;
+
+    if (enctype == REDIS_RDB_ENC_INT8) {
+        if (rioRead(rdb,enc,1) == 0) return NULL;
+        val = (signed char)enc[0];
+    } else if (enctype == REDIS_RDB_ENC_INT16) {
+        uint16_t v;
+        if (rioRead(rdb,enc,2) == 0) return NULL;
+        v = enc[0]|(enc[1]<<8);
+        val = (int16_t)v;
+    } else if (enctype == REDIS_RDB_ENC_INT32) {
+        uint32_t v;
+        if (rioRead(rdb,enc,4) == 0) return NULL;
+        v = enc[0]|(enc[1]<<8)|(enc[2]<<16)|(enc[3]<<24);
+        val = (int32_t)v;
+    } else {
+        val = 0; /* anti-warning */
+        redisPanic("Unknown RDB integer encoding type");
+    }
+    if (encode)
+        return createStringObjectFromLongLong(val);
+    else
+        return createObject(REDIS_STRING,sdsfromlonglong(val));
+}
+
 /* String objects in the form "2391" "-100" without any space and with a
  * range of values that can fit in an 8, 16 or 32 bit signed value can be
  * encoded as integers to save space */
@@ -101,7 +168,7 @@ int rdbTryIntegerEncoding(char *s, size_t len, unsigned char *enc) {
     return rdbEncodeInteger(value,enc);
 }
 
-int rdbSaveLzfStringObject(FILE *fp, unsigned char *s, size_t len) {
+int rdbSaveLzfStringObject(rio *rdb, unsigned char *s, size_t len) {
     size_t comprlen, outlen;
     unsigned char byte;
     int n, nwritten = 0;
@@ -118,16 +185,16 @@ int rdbSaveLzfStringObject(FILE *fp, unsigned char *s, size_t len) {
     }
     /* Data compressed! Let's save it on disk */
     byte = (REDIS_RDB_ENCVAL<<6)|REDIS_RDB_ENC_LZF;
-    if ((n = rdbWriteRaw(fp,&byte,1)) == -1) goto writeerr;
+    if ((n = rdbWriteRaw(rdb,&byte,1)) == -1) goto writeerr;
     nwritten += n;
 
-    if ((n = rdbSaveLen(fp,comprlen)) == -1) goto writeerr;
+    if ((n = rdbSaveLen(rdb,comprlen)) == -1) goto writeerr;
     nwritten += n;
 
-    if ((n = rdbSaveLen(fp,len)) == -1) goto writeerr;
+    if ((n = rdbSaveLen(rdb,len)) == -1) goto writeerr;
     nwritten += n;
 
-    if ((n = rdbWriteRaw(fp,out,comprlen)) == -1) goto writeerr;
+    if ((n = rdbWriteRaw(rdb,out,comprlen)) == -1) goto writeerr;
     nwritten += n;
 
     zfree(out);
@@ -138,71 +205,126 @@ int rdbSaveLzfStringObject(FILE *fp, unsigned char *s, size_t len) {
     return -1;
 }
 
+robj *rdbLoadLzfStringObject(rio *rdb) {
+    unsigned int len, clen;
+    unsigned char *c = NULL;
+    sds val = NULL;
+
+    if ((clen = rdbLoadLen(rdb,NULL)) == REDIS_RDB_LENERR) return NULL;
+    if ((len = rdbLoadLen(rdb,NULL)) == REDIS_RDB_LENERR) return NULL;
+    if ((c = zmalloc(clen)) == NULL) goto err;
+    if ((val = sdsnewlen(NULL,len)) == NULL) goto err;
+    if (rioRead(rdb,c,clen) == 0) goto err;
+    if (lzf_decompress(c,clen,val,len) == 0) goto err;
+    zfree(c);
+    return createObject(REDIS_STRING,val);
+err:
+    zfree(c);
+    sdsfree(val);
+    return NULL;
+}
+
 /* Save a string objet as [len][data] on disk. If the object is a string
  * representation of an integer value we try to save it in a special form */
-int rdbSaveRawString(FILE *fp, unsigned char *s, size_t len) {
+int rdbSaveRawString(rio *rdb, unsigned char *s, size_t len) {
     int enclen;
     int n, nwritten = 0;
 
     /* Try integer encoding */
     if (len <= 11) {
         unsigned char buf[5];
         if ((enclen = rdbTryIntegerEncoding((char*)s,len,buf)) > 0) {
-            if (rdbWriteRaw(fp,buf,enclen) == -1) return -1;
+            if (rdbWriteRaw(rdb,buf,enclen) == -1) return -1;
             return enclen;
         }
     }
 
     /* Try LZF compression - under 20 bytes it's unable to compress even
      * aaaaaaaaaaaaaaaaaa so skip it */
     if (server.rdbcompression && len > 20) {
-        n = rdbSaveLzfStringObject(fp,s,len);
+        n = rdbSaveLzfStringObject(rdb,s,len);
         if (n == -1) return -1;
         if (n > 0) return n;
         /* Return value of 0 means data can't be compressed, save the old way */
     }
 
     /* Store verbatim */
-    if ((n = rdbSaveLen(fp,len)) == -1) return -1;
+    if ((n = rdbSaveLen(rdb,len)) == -1) return -1;
     nwritten += n;
     if (len > 0) {
-        if (rdbWriteRaw(fp,s,len) == -1) return -1;
+        if (rdbWriteRaw(rdb,s,len) == -1) return -1;
         nwritten += len;
     }
     return nwritten;
 }
 
 /* Save a long long value as either an encoded string or a string. */
-int rdbSaveLongLongAsStringObject(FILE *fp, long long value) {
+int rdbSaveLongLongAsStringObject(rio *rdb, long long value) {
     unsigned char buf[32];
     int n, nwritten = 0;
     int enclen = rdbEncodeInteger(value,buf);
     if (enclen > 0) {
-        return rdbWriteRaw(fp,buf,enclen);
+        return rdbWriteRaw(rdb,buf,enclen);
     } else {
         /* Encode as string */
         enclen = ll2string((char*)buf,32,value);
         redisAssert(enclen < 32);
-        if ((n = rdbSaveLen(fp,enclen)) == -1) return -1;
+        if ((n = rdbSaveLen(rdb,enclen)) == -1) return -1;
         nwritten += n;
-        if ((n = rdbWriteRaw(fp,buf,enclen)) == -1) return -1;
+        if ((n = rdbWriteRaw(rdb,buf,enclen)) == -1) return -1;
         nwritten += n;
     }
     return nwritten;
 }
 
 /* Like rdbSaveStringObjectRaw() but handle encoded objects */
-int rdbSaveStringObject(FILE *fp, robj *obj) {
+int rdbSaveStringObject(rio *rdb, robj *obj) {
     /* Avoid to decode the object, then encode it again, if the
      * object is alrady integer encoded. */
     if (obj->encoding == REDIS_ENCODING_INT) {
-        return rdbSaveLongLongAsStringObject(fp,(long)obj->ptr);
+        return rdbSaveLongLongAsStringObject(rdb,(long)obj->ptr);
     } else {
         redisAssert(obj->encoding == REDIS_ENCODING_RAW);
-        return rdbSaveRawString(fp,obj->ptr,sdslen(obj->ptr));
+        return rdbSaveRawString(rdb,obj->ptr,sdslen(obj->ptr));
     }
 }
 
+robj *rdbGenericLoadStringObject(rio *rdb, int encode) {
+    int isencoded;
+    uint32_t len;
+    sds val;
+
+    len = rdbLoadLen(rdb,&isencoded);
+    if (isencoded) {
+        switch(len) {
+        case REDIS_RDB_ENC_INT8:
+        case REDIS_RDB_ENC_INT16:
+        case REDIS_RDB_ENC_INT32:
+            return rdbLoadIntegerObject(rdb,len,encode);
+        case REDIS_RDB_ENC_LZF:
+            return rdbLoadLzfStringObject(rdb);
+        default:
+            redisPanic("Unknown RDB encoding type");
+        }
+    }
+
+    if (len == REDIS_RDB_LENERR) return NULL;
+    val = sdsnewlen(NULL,len);
+    if (len && rioRead(rdb,val,len) == 0) {
+        sdsfree(val);
+        return NULL;
+    }
+    return createObject(REDIS_STRING,val);
+}
+
+robj *rdbLoadStringObject(rio *rdb) {
+    return rdbGenericLoadStringObject(rdb,0);
+}
+
+robj *rdbLoadEncodedStringObject(rio *rdb) {
+    return rdbGenericLoadStringObject(rdb,1);
+}
+
 /* Save a double value. Doubles are saved as strings prefixed by an unsigned
  * 8 bit integer specifing the length of the representation.
  * This 8 bit integer has special values in order to specify the following
@@ -211,7 +333,7 @@ int rdbSaveStringObject(FILE *fp, robj *obj) {
  * 254: + inf
  * 255: - inf
  */
-int rdbSaveDoubleValue(FILE *fp, double val) {
+int rdbSaveDoubleValue(rio *rdb, double val) {
     unsigned char buf[128];
     int len;
 
@@ -242,36 +364,101 @@ int rdbSaveDoubleValue(FILE *fp, double val) {
         buf[0] = strlen((char*)buf+1);
         len = buf[0]+1;
     }
-    return rdbWriteRaw(fp,buf,len);
+    return rdbWriteRaw(rdb,buf,len);
+}
+
+/* For information about double serialization check rdbSaveDoubleValue() */
+int rdbLoadDoubleValue(rio *rdb, double *val) {
+    char buf[128];
+    unsigned char len;
+
+    if (rioRead(rdb,&len,1) == 0) return -1;
+    switch(len) {
+    case 255: *val = R_NegInf; return 0;
+    case 254: *val = R_PosInf; return 0;
+    case 253: *val = R_Nan; return 0;
+    default:
+        if (rioRead(rdb,buf,len) == 0) return -1;
+        buf[len] = '\0';
+        sscanf(buf, "%lg", val);
+        return 0;
+    }
+}
+
+/* Save the object type of object "o". */
+int rdbSaveObjectType(rio *rdb, robj *o) {
+    switch (o->type) {
+    case REDIS_STRING:
+        return rdbSaveType(rdb,REDIS_RDB_TYPE_STRING);
+    case REDIS_LIST:
+        if (o->encoding == REDIS_ENCODING_ZIPLIST)
+            return rdbSaveType(rdb,REDIS_RDB_TYPE_LIST_ZIPLIST);
+        else if (o->encoding == REDIS_ENCODING_LINKEDLIST)
+            return rdbSaveType(rdb,REDIS_RDB_TYPE_LIST);
+        else
+            redisPanic("Unknown list encoding");
+    case REDIS_SET:
+        if (o->encoding == REDIS_ENCODING_INTSET)
+            return rdbSaveType(rdb,REDIS_RDB_TYPE_SET_INTSET);
+        else if (o->encoding == REDIS_ENCODING_HT)
+            return rdbSaveType(rdb,REDIS_RDB_TYPE_SET);
+        else
+            redisPanic("Unknown set encoding");
+    case REDIS_ZSET:
+        if (o->encoding == REDIS_ENCODING_ZIPLIST)
+            return rdbSaveType(rdb,REDIS_RDB_TYPE_ZSET_ZIPLIST);
+        else if (o->encoding == REDIS_ENCODING_SKIPLIST)
+            return rdbSaveType(rdb,REDIS_RDB_TYPE_ZSET);
+        else
+            redisPanic("Unknown sorted set encoding");
+    case REDIS_HASH:
+        if (o->encoding == REDIS_ENCODING_ZIPMAP)
+            return rdbSaveType(rdb,REDIS_RDB_TYPE_HASH_ZIPMAP);
+        else if (o->encoding == REDIS_ENCODING_HT)
+            return rdbSaveType(rdb,REDIS_RDB_TYPE_HASH);
+        else
+            redisPanic("Unknown hash encoding");
+    default:
+        redisPanic("Unknown object type");
+    }
+    return -1; /* avoid warning */
+}
+
+/* Load object type. Return -1 when the byte doesn't contain an object type. */
+int rdbLoadObjectType(rio *rdb) {
+    int type;
+    if ((type = rdbLoadType(rdb)) == -1) return -1;
+    if (!rdbIsObjectType(type)) return -1;
+    return type;
 }
 
 /* Save a Redis object. Returns -1 on error, 0 on success. */
-int rdbSaveObject(FILE *fp, robj *o) {
+int rdbSaveObject(rio *rdb, robj *o) {
     int n, nwritten = 0;
 
     if (o->type == REDIS_STRING) {
         /* Save a string value */
-        if ((n = rdbSaveStringObject(fp,o)) == -1) return -1;
+        if ((n = rdbSaveStringObject(rdb,o)) == -1) return -1;
         nwritten += n;
     } else if (o->type == REDIS_LIST) {
         /* Save a list value */
         if (o->encoding == REDIS_ENCODING_ZIPLIST) {
             size_t l = ziplistBlobLen((unsigned char*)o->ptr);
 
-            if ((n = rdbSaveRawString(fp,o->ptr,l)) == -1) return -1;
+            if ((n = rdbSaveRawString(rdb,o->ptr,l)) == -1) return -1;
             nwritten += n;
         } else if (o->encoding == REDIS_ENCODING_LINKEDLIST) {
             list *list = o->ptr;
             listIter li;
             listNode *ln;
 
-            if ((n = rdbSaveLen(fp,listLength(list))) == -1) return -1;
+            if ((n = rdbSaveLen(rdb,listLength(list))) == -1) return -1;
             nwritten += n;
 
             listRewind(list,&li);
             while((ln = listNext(&li))) {
                 robj *eleobj = listNodeValue(ln);
-                if ((n = rdbSaveStringObject(fp,eleobj)) == -1) return -1;
+                if ((n = rdbSaveStringObject(rdb,eleobj)) == -1) return -1;
                 nwritten += n;
             }
         } else {
@@ -284,19 +471,19 @@ int rdbSaveObject(FILE *fp, robj *o) {
             dictIterator *di = dictGetIterator(set);
             dictEntry *de;
 
-            if ((n = rdbSaveLen(fp,dictSize(set))) == -1) return -1;
+            if ((n = rdbSaveLen(rdb,dictSize(set))) == -1) return -1;
             nwritten += n;
 
             while((de = dictNext(di)) != NULL) {
                 robj *eleobj = dictGetEntryKey(de);
-                if ((n = rdbSaveStringObject(fp,eleobj)) == -1) return -1;
+                if ((n = rdbSaveStringObject(rdb,eleobj)) == -1) return -1;
                 nwritten += n;
             }
             dictReleaseIterator(di);
         } else if (o->encoding == REDIS_ENCODING_INTSET) {
             size_t l = intsetBlobLen((intset*)o->ptr);
 
-            if ((n = rdbSaveRawString(fp,o->ptr,l)) == -1) return -1;
+            if ((n = rdbSaveRawString(rdb,o->ptr,l)) == -1) return -1;
             nwritten += n;
         } else {
             redisPanic("Unknown set encoding");
@@ -306,23 +493,23 @@ int rdbSaveObject(FILE *fp, robj *o) {
         if (o->encoding == REDIS_ENCODING_ZIPLIST) {
             size_t l = ziplistBlobLen((unsigned char*)o->ptr);
 
-            if ((n = rdbSaveRawString(fp,o->ptr,l)) == -1) return -1;
+            if ((n = rdbSaveRawString(rdb,o->ptr,l)) == -1) return -1;
             nwritten += n;
         } else if (o->encoding == REDIS_ENCODING_SKIPLIST) {
             zset *zs = o->ptr;
             dictIterator *di = dictGetIterator(zs->dict);
             dictEntry *de;
 
-            if ((n = rdbSaveLen(fp,dictSize(zs->dict))) == -1) return -1;
+            if ((n = rdbSaveLen(rdb,dictSize(zs->dict))) == -1) return -1;
             nwritten += n;
 
             while((de = dictNext(di)) != NULL) {
                 robj *eleobj = dictGetEntryKey(de);
                 double *score = dictGetEntryVal(de);
 
-                if ((n = rdbSaveStringObject(fp,eleobj)) == -1) return -1;
+                if ((n = rdbSaveStringObject(rdb,eleobj)) == -1) return -1;
                 nwritten += n;
-                if ((n = rdbSaveDoubleValue(fp,*score)) == -1) return -1;
+                if ((n = rdbSaveDoubleValue(rdb,*score)) == -1) return -1;
                 nwritten += n;
             }
             dictReleaseIterator(di);
@@ -334,22 +521,22 @@ int rdbSaveObject(FILE *fp, robj *o) {
         if (o->encoding == REDIS_ENCODING_ZIPMAP) {
             size_t l = zipmapBlobLen((unsigned char*)o->ptr);
 
-            if ((n = rdbSaveRawString(fp,o->ptr,l)) == -1) return -1;
+            if ((n = rdbSaveRawString(rdb,o->ptr,l)) == -1) return -1;
             nwritten += n;
         } else {
             dictIterator *di = dictGetIterator(o->ptr);
             dictEntry *de;
 
-            if ((n = rdbSaveLen(fp,dictSize((dict*)o->ptr))) == -1) return -1;
+            if ((n = rdbSaveLen(rdb,dictSize((dict*)o->ptr))) == -1) return -1;
             nwritten += n;
 
             while((de = dictNext(di)) != NULL) {
                 robj *key = dictGetEntryKey(de);
                 robj *val = dictGetEntryVal(de);
 
-                if ((n = rdbSaveStringObject(fp,key)) == -1) return -1;
+                if ((n = rdbSaveStringObject(rdb,key)) == -1) return -1;
                 nwritten += n;
-                if ((n = rdbSaveStringObject(fp,val)) == -1) return -1;
+                if ((n = rdbSaveStringObject(rdb,val)) == -1) return -1;
                 nwritten += n;
             }
             dictReleaseIterator(di);
@@ -374,44 +561,33 @@ off_t rdbSavedObjectLen(robj *o) {
  * On error -1 is returned.
  * On success if the key was actaully saved 1 is returned, otherwise 0
  * is returned (the key was already expired). */
-int rdbSaveKeyValuePair(FILE *fp, robj *key, robj *val,
+int rdbSaveKeyValuePair(rio *rdb, robj *key, robj *val,
                         time_t expiretime, time_t now)
 {
-    int vtype;
-
     /* Save the expire time */
     if (expiretime != -1) {
         /* If this key is already expired skip it */
         if (expiretime < now) return 0;
-        if (rdbSaveType(fp,REDIS_EXPIRETIME) == -1) return -1;
-        if (rdbSaveTime(fp,expiretime) == -1) return -1;
+        if (rdbSaveType(rdb,REDIS_RDB_OPCODE_EXPIRETIME) == -1) return -1;
+        if (rdbSaveTime(rdb,expiretime) == -1) return -1;
     }
-    /* Fix the object type if needed, to support saving zipmaps, ziplists,
-     * and intsets, directly as blobs of bytes: they are already serialized. */
-    vtype = val->type;
-    if (vtype == REDIS_HASH && val->encoding == REDIS_ENCODING_ZIPMAP)
-        vtype = REDIS_HASH_ZIPMAP;
-    else if (vtype == REDIS_LIST && val->encoding == REDIS_ENCODING_ZIPLIST)
-        vtype = REDIS_LIST_ZIPLIST;
-    else if (vtype == REDIS_SET && val->encoding == REDIS_ENCODING_INTSET)
-        vtype = REDIS_SET_INTSET;
-    else if (vtype == REDIS_ZSET && val->encoding == REDIS_ENCODING_ZIPLIST)
-        vtype = REDIS_ZSET_ZIPLIST;
+
     /* Save type, key, value */
-    if (rdbSaveType(fp,vtype) == -1) return -1;
-    if (rdbSaveStringObject(fp,key) == -1) return -1;
-    if (rdbSaveObject(fp,val) == -1) return -1;
+    if (rdbSaveObjectType(rdb,val) == -1) return -1;
+    if (rdbSaveStringObject(rdb,key) == -1) return -1;
+    if (rdbSaveObject(rdb,val) == -1) return -1;
     return 1;
 }
 
 /* Save the DB on disk. Return REDIS_ERR on error, REDIS_OK on success */
 int rdbSave(char *filename) {
     dictIterator *di = NULL;
     dictEntry *de;
-    FILE *fp;
     char tmpfile[256];
     int j;
     time_t now = time(NULL);
+    FILE *fp;
+    rio rdb;
 
     snprintf(tmpfile,256,"temp-%d.rdb", (int) getpid());
     fp = fopen(tmpfile,"w");
@@ -420,7 +596,10 @@ int rdbSave(char *filename) {
             strerror(errno));
         return REDIS_ERR;
     }
-    if (fwrite("REDIS0002",9,1,fp) == 0) goto werr;
+
+    rdb = rioInitWithFile(fp);
+    if (rdbWriteRaw(&rdb,"REDIS0002",9) == -1) goto werr;
+
     for (j = 0; j < server.dbnum; j++) {
         redisDb *db = server.db+j;
         dict *d = db->dict;
@@ -432,8 +611,8 @@ int rdbSave(char *filename) {
         }
 
         /* Write the SELECT DB opcode */
-        if (rdbSaveType(fp,REDIS_SELECTDB) == -1) goto werr;
-        if (rdbSaveLen(fp,j) == -1) goto werr;
+        if (rdbSaveType(&rdb,REDIS_RDB_OPCODE_SELECTDB) == -1) goto werr;
+        if (rdbSaveLen(&rdb,j) == -1) goto werr;
 
         /* Iterate this DB writing every entry */
         while((de = dictNext(di)) != NULL) {
@@ -443,12 +622,12 @@ int rdbSave(char *filename) {
             
             initStaticStringObject(key,keystr);
             expire = getExpire(db,&key);
-            if (rdbSaveKeyValuePair(fp,&key,o,expire,now) == -1) goto werr;
+            if (rdbSaveKeyValuePair(&rdb,&key,o,expire,now) == -1) goto werr;
         }
         dictReleaseIterator(di);
     }
     /* EOF opcode */
-    if (rdbSaveType(fp,REDIS_EOF) == -1) goto werr;
+    if (rdbSaveType(&rdb,REDIS_RDB_OPCODE_EOF) == -1) goto werr;
 
     /* Make sure data will not remain on the OS's output buffers */
     fflush(fp);
@@ -515,168 +694,21 @@ void rdbRemoveTempFile(pid_t childpid) {
     unlink(tmpfile);
 }
 
-int rdbLoadType(FILE *fp) {
-    unsigned char type;
-    if (fread(&type,1,1,fp) == 0) return -1;
-    return type;
-}
-
-time_t rdbLoadTime(FILE *fp) {
-    int32_t t32;
-    if (fread(&t32,4,1,fp) == 0) return -1;
-    return (time_t) t32;
-}
-
-/* Load an encoded length from the DB, see the REDIS_RDB_* defines on the top
- * of this file for a description of how this are stored on disk.
- *
- * isencoded is set to 1 if the readed length is not actually a length but
- * an "encoding type", check the above comments for more info */
-uint32_t rdbLoadLen(FILE *fp, int *isencoded) {
-    unsigned char buf[2];
-    uint32_t len;
-    int type;
-
-    if (isencoded) *isencoded = 0;
-    if (fread(buf,1,1,fp) == 0) return REDIS_RDB_LENERR;
-    type = (buf[0]&0xC0)>>6;
-    if (type == REDIS_RDB_6BITLEN) {
-        /* Read a 6 bit len */
-        return buf[0]&0x3F;
-    } else if (type == REDIS_RDB_ENCVAL) {
-        /* Read a 6 bit len encoding type */
-        if (isencoded) *isencoded = 1;
-        return buf[0]&0x3F;
-    } else if (type == REDIS_RDB_14BITLEN) {
-        /* Read a 14 bit len */
-        if (fread(buf+1,1,1,fp) == 0) return REDIS_RDB_LENERR;
-        return ((buf[0]&0x3F)<<8)|buf[1];
-    } else {
-        /* Read a 32 bit len */
-        if (fread(&len,4,1,fp) == 0) return REDIS_RDB_LENERR;
-        return ntohl(len);
-    }
-}
-
-/* Load an integer-encoded object from file 'fp', with the specified
- * encoding type 'enctype'. If encode is true the function may return
- * an integer-encoded object as reply, otherwise the returned object
- * will always be encoded as a raw string. */
-robj *rdbLoadIntegerObject(FILE *fp, int enctype, int encode) {
-    unsigned char enc[4];
-    long long val;
-
-    if (enctype == REDIS_RDB_ENC_INT8) {
-        if (fread(enc,1,1,fp) == 0) return NULL;
-        val = (signed char)enc[0];
-    } else if (enctype == REDIS_RDB_ENC_INT16) {
-        uint16_t v;
-        if (fread(enc,2,1,fp) == 0) return NULL;
-        v = enc[0]|(enc[1]<<8);
-        val = (int16_t)v;
-    } else if (enctype == REDIS_RDB_ENC_INT32) {
-        uint32_t v;
-        if (fread(enc,4,1,fp) == 0) return NULL;
-        v = enc[0]|(enc[1]<<8)|(enc[2]<<16)|(enc[3]<<24);
-        val = (int32_t)v;
-    } else {
-        val = 0; /* anti-warning */
-        redisPanic("Unknown RDB integer encoding type");
-    }
-    if (encode)
-        return createStringObjectFromLongLong(val);
-    else
-        return createObject(REDIS_STRING,sdsfromlonglong(val));
-}
-
-robj *rdbLoadLzfStringObject(FILE*fp) {
-    unsigned int len, clen;
-    unsigned char *c = NULL;
-    sds val = NULL;
-
-    if ((clen = rdbLoadLen(fp,NULL)) == REDIS_RDB_LENERR) return NULL;
-    if ((len = rdbLoadLen(fp,NULL)) == REDIS_RDB_LENERR) return NULL;
-    if ((c = zmalloc(clen)) == NULL) goto err;
-    if ((val = sdsnewlen(NULL,len)) == NULL) goto err;
-    if (fread(c,clen,1,fp) == 0) goto err;
-    if (lzf_decompress(c,clen,val,len) == 0) goto err;
-    zfree(c);
-    return createObject(REDIS_STRING,val);
-err:
-    zfree(c);
-    sdsfree(val);
-    return NULL;
-}
-
-robj *rdbGenericLoadStringObject(FILE*fp, int encode) {
-    int isencoded;
-    uint32_t len;
-    sds val;
-
-    len = rdbLoadLen(fp,&isencoded);
-    if (isencoded) {
-        switch(len) {
-        case REDIS_RDB_ENC_INT8:
-        case REDIS_RDB_ENC_INT16:
-        case REDIS_RDB_ENC_INT32:
-            return rdbLoadIntegerObject(fp,len,encode);
-        case REDIS_RDB_ENC_LZF:
-            return rdbLoadLzfStringObject(fp);
-        default:
-            redisPanic("Unknown RDB encoding type");
-        }
-    }
-
-    if (len == REDIS_RDB_LENERR) return NULL;
-    val = sdsnewlen(NULL,len);
-    if (len && fread(val,len,1,fp) == 0) {
-        sdsfree(val);
-        return NULL;
-    }
-    return createObject(REDIS_STRING,val);
-}
-
-robj *rdbLoadStringObject(FILE *fp) {
-    return rdbGenericLoadStringObject(fp,0);
-}
-
-robj *rdbLoadEncodedStringObject(FILE *fp) {
-    return rdbGenericLoadStringObject(fp,1);
-}
-
-/* For information about double serialization check rdbSaveDoubleValue() */
-int rdbLoadDoubleValue(FILE *fp, double *val) {
-    char buf[128];
-    unsigned char len;
-
-    if (fread(&len,1,1,fp) == 0) return -1;
-    switch(len) {
-    case 255: *val = R_NegInf; return 0;
-    case 254: *val = R_PosInf; return 0;
-    case 253: *val = R_Nan; return 0;
-    default:
-        if (fread(buf,len,1,fp) == 0) return -1;
-        buf[len] = '\0';
-        sscanf(buf, "%lg", val);
-        return 0;
-    }
-}
-
 /* Load a Redis object of the specified type from the specified file.
  * On success a newly allocated object is returned, otherwise NULL. */
-robj *rdbLoadObject(int type, FILE *fp) {
+robj *rdbLoadObject(int rdbtype, rio *rdb) {
     robj *o, *ele, *dec;
     size_t len;
     unsigned int i;
 
-    redisLog(REDIS_DEBUG,"LOADING OBJECT %d (at %d)\n",type,ftell(fp));
-    if (type == REDIS_STRING) {
+    redisLog(REDIS_DEBUG,"LOADING OBJECT %d (at %d)\n",rdbtype,rdb->tell(rdb));
+    if (rdbtype == REDIS_RDB_TYPE_STRING) {
         /* Read string value */
-        if ((o = rdbLoadEncodedStringObject(fp)) == NULL) return NULL;
+        if ((o = rdbLoadEncodedStringObject(rdb)) == NULL) return NULL;
         o = tryObjectEncoding(o);
-    } else if (type == REDIS_LIST) {
+    } else if (rdbtype == REDIS_RDB_TYPE_LIST) {
         /* Read list value */
-        if ((len = rdbLoadLen(fp,NULL)) == REDIS_RDB_LENERR) return NULL;
+        if ((len = rdbLoadLen(rdb,NULL)) == REDIS_RDB_LENERR) return NULL;
 
         /* Use a real list when there are too many entries */
         if (len > server.list_max_ziplist_entries) {
@@ -687,7 +719,7 @@ robj *rdbLoadObject(int type, FILE *fp) {
 
         /* Load every single element of the list */
         while(len--) {
-            if ((ele = rdbLoadEncodedStringObject(fp)) == NULL) return NULL;
+            if ((ele = rdbLoadEncodedStringObject(rdb)) == NULL) return NULL;
 
             /* If we are using a ziplist and the value is too big, convert
              * the object to a real list. */
@@ -706,9 +738,9 @@ robj *rdbLoadObject(int type, FILE *fp) {
                 listAddNodeTail(o->ptr,ele);
             }
         }
-    } else if (type == REDIS_SET) {
+    } else if (rdbtype == REDIS_RDB_TYPE_SET) {
         /* Read list/set value */
-        if ((len = rdbLoadLen(fp,NULL)) == REDIS_RDB_LENERR) return NULL;
+        if ((len = rdbLoadLen(rdb,NULL)) == REDIS_RDB_LENERR) return NULL;
 
         /* Use a regular set when there are too many entries. */
         if (len > server.set_max_intset_entries) {
@@ -724,7 +756,7 @@ robj *rdbLoadObject(int type, FILE *fp) {
         /* Load every single element of the list/set */
         for (i = 0; i < len; i++) {
             long long llval;
-            if ((ele = rdbLoadEncodedStringObject(fp)) == NULL) return NULL;
+            if ((ele = rdbLoadEncodedStringObject(rdb)) == NULL) return NULL;
             ele = tryObjectEncoding(ele);
 
             if (o->encoding == REDIS_ENCODING_INTSET) {
@@ -745,13 +777,13 @@ robj *rdbLoadObject(int type, FILE *fp) {
                 decrRefCount(ele);
             }
         }
-    } else if (type == REDIS_ZSET) {
+    } else if (rdbtype == REDIS_RDB_TYPE_ZSET) {
         /* Read list/set value */
         size_t zsetlen;
         size_t maxelelen = 0;
         zset *zs;
 
-        if ((zsetlen = rdbLoadLen(fp,NULL)) == REDIS_RDB_LENERR) return NULL;
+        if ((zsetlen = rdbLoadLen(rdb,NULL)) == REDIS_RDB_LENERR) return NULL;
         o = createZsetObject();
         zs = o->ptr;
 
@@ -761,9 +793,9 @@ robj *rdbLoadObject(int type, FILE *fp) {
             double score;
             zskiplistNode *znode;
 
-            if ((ele = rdbLoadEncodedStringObject(fp)) == NULL) return NULL;
+            if ((ele = rdbLoadEncodedStringObject(rdb)) == NULL) return NULL;
             ele = tryObjectEncoding(ele);
-            if (rdbLoadDoubleValue(fp,&score) == -1) return NULL;
+            if (rdbLoadDoubleValue(rdb,&score) == -1) return NULL;
 
             /* Don't care about integer-encoded strings. */
             if (ele->encoding == REDIS_ENCODING_RAW &&
@@ -779,10 +811,10 @@ robj *rdbLoadObject(int type, FILE *fp) {
         if (zsetLength(o) <= server.zset_max_ziplist_entries &&
             maxelelen <= server.zset_max_ziplist_value)
                 zsetConvert(o,REDIS_ENCODING_ZIPLIST);
-    } else if (type == REDIS_HASH) {
+    } else if (rdbtype == REDIS_RDB_TYPE_HASH) {
         size_t hashlen;
 
-        if ((hashlen = rdbLoadLen(fp,NULL)) == REDIS_RDB_LENERR) return NULL;
+        if ((hashlen = rdbLoadLen(rdb,NULL)) == REDIS_RDB_LENERR) return NULL;
         o = createHashObject();
         /* Too many entries? Use an hash table. */
         if (hashlen > server.hash_max_zipmap_entries)
@@ -792,8 +824,8 @@ robj *rdbLoadObject(int type, FILE *fp) {
         while(hashlen--) {
             robj *key, *val;
 
-            if ((key = rdbLoadEncodedStringObject(fp)) == NULL) return NULL;
-            if ((val = rdbLoadEncodedStringObject(fp)) == NULL) return NULL;
+            if ((key = rdbLoadEncodedStringObject(rdb)) == NULL) return NULL;
+            if ((val = rdbLoadEncodedStringObject(rdb)) == NULL) return NULL;
             /* If we are using a zipmap and there are too big values
              * the object is converted to real hash table encoding. */
             if (o->encoding != REDIS_ENCODING_HT &&
@@ -825,12 +857,12 @@ robj *rdbLoadObject(int type, FILE *fp) {
                 dictAdd((dict*)o->ptr,key,val);
             }
         }
-    } else if (type == REDIS_HASH_ZIPMAP ||
-               type == REDIS_LIST_ZIPLIST ||
-               type == REDIS_SET_INTSET ||
-               type == REDIS_ZSET_ZIPLIST)
+    } else if (rdbtype == REDIS_RDB_TYPE_HASH_ZIPMAP  ||
+               rdbtype == REDIS_RDB_TYPE_LIST_ZIPLIST ||
+               rdbtype == REDIS_RDB_TYPE_SET_INTSET   ||
+               rdbtype == REDIS_RDB_TYPE_ZSET_ZIPLIST)
     {
-        robj *aux = rdbLoadStringObject(fp);
+        robj *aux = rdbLoadStringObject(rdb);
 
         if (aux == NULL) return NULL;
         o = createObject(REDIS_STRING,NULL); /* string is just placeholder */
@@ -844,26 +876,26 @@ robj *rdbLoadObject(int type, FILE *fp) {
          * type. Note that we only check the length and not max element
          * size as this is an O(N) scan. Eventually everything will get
          * converted. */
-        switch(type) {
-            case REDIS_HASH_ZIPMAP:
+        switch(rdbtype) {
+            case REDIS_RDB_TYPE_HASH_ZIPMAP:
                 o->type = REDIS_HASH;
                 o->encoding = REDIS_ENCODING_ZIPMAP;
                 if (zipmapLen(o->ptr) > server.hash_max_zipmap_entries)
                     convertToRealHash(o);
                 break;
-            case REDIS_LIST_ZIPLIST:
+            case REDIS_RDB_TYPE_LIST_ZIPLIST:
                 o->type = REDIS_LIST;
                 o->encoding = REDIS_ENCODING_ZIPLIST;
                 if (ziplistLen(o->ptr) > server.list_max_ziplist_entries)
                     listTypeConvert(o,REDIS_ENCODING_LINKEDLIST);
                 break;
-            case REDIS_SET_INTSET:
+            case REDIS_RDB_TYPE_SET_INTSET:
                 o->type = REDIS_SET;
                 o->encoding = REDIS_ENCODING_INTSET;
                 if (intsetLen(o->ptr) > server.set_max_intset_entries)
                     setTypeConvert(o,REDIS_ENCODING_HT);
                 break;
-            case REDIS_ZSET_ZIPLIST:
+            case REDIS_RDB_TYPE_ZSET_ZIPLIST:
                 o->type = REDIS_ZSET;
                 o->encoding = REDIS_ENCODING_ZIPLIST;
                 if (zsetLength(o) > server.zset_max_ziplist_entries)
@@ -905,17 +937,19 @@ void stopLoading(void) {
 }
 
 int rdbLoad(char *filename) {
-    FILE *fp;
     uint32_t dbid;
     int type, rdbver;
     redisDb *db = server.db+0;
     char buf[1024];
     time_t expiretime, now = time(NULL);
     long loops = 0;
+    FILE *fp;
+    rio rdb;
 
     fp = fopen(filename,"r");
     if (!fp) return REDIS_ERR;
-    if (fread(buf,9,1,fp) == 0) goto eoferr;
+    rdb = rioInitWithFile(fp);
+    if (rioRead(&rdb,buf,9) == 0) goto eoferr;
     buf[9] = '\0';
     if (memcmp(buf,"REDIS",5) != 0) {
         fclose(fp);
@@ -936,21 +970,24 @@ int rdbLoad(char *filename) {
 
         /* Serve the clients from time to time */
         if (!(loops++ % 1000)) {
-            loadingProgress(ftello(fp));
+            loadingProgress(rdb.tell(&rdb));
             aeProcessEvents(server.el, AE_FILE_EVENTS|AE_DONT_WAIT);
         }
 
         /* Read type. */
-        if ((type = rdbLoadType(fp)) == -1) goto eoferr;
-        if (type == REDIS_EXPIRETIME) {
-            if ((expiretime = rdbLoadTime(fp)) == -1) goto eoferr;
-            /* We read the time so we need to read the object type again */
-            if ((type = rdbLoadType(fp)) == -1) goto eoferr;
+        if ((type = rdbLoadType(&rdb)) == -1) goto eoferr;
+        if (type == REDIS_RDB_OPCODE_EXPIRETIME) {
+            if ((expiretime = rdbLoadTime(&rdb)) == -1) goto eoferr;
+            /* We read the time so we need to read the object type again. */
+            if ((type = rdbLoadType(&rdb)) == -1) goto eoferr;
         }
-        if (type == REDIS_EOF) break;
+
+        if (type == REDIS_RDB_OPCODE_EOF)
+            break;
+
         /* Handle SELECT DB opcode as a special case */
-        if (type == REDIS_SELECTDB) {
-            if ((dbid = rdbLoadLen(fp,NULL)) == REDIS_RDB_LENERR)
+        if (type == REDIS_RDB_OPCODE_SELECTDB) {
+            if ((dbid = rdbLoadLen(&rdb,NULL)) == REDIS_RDB_LENERR)
                 goto eoferr;
             if (dbid >= (unsigned)server.dbnum) {
                 redisLog(REDIS_WARNING,"FATAL: Data file was created with a Redis server configured to handle more than %d databases. Exiting\n", server.dbnum);
@@ -960,9 +997,9 @@ int rdbLoad(char *filename) {
             continue;
         }
         /* Read key */
-        if ((key = rdbLoadStringObject(fp)) == NULL) goto eoferr;
+        if ((key = rdbLoadStringObject(&rdb)) == NULL) goto eoferr;
         /* Read value */
-        if ((val = rdbLoadObject(type,fp)) == NULL) goto eoferr;
+        if ((val = rdbLoadObject(type,&rdb)) == NULL) goto eoferr;
         /* Check if the key already expired */
         if (expiretime != -1 && expiretime < now) {
             decrRefCount(key);