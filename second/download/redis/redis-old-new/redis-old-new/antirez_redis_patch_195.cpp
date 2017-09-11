@@ -41,11 +41,6 @@
 #include <sys/stat.h>
 #include <sys/param.h>
 
-#define RDB_LOAD_NONE   0
-#define RDB_LOAD_ENC    (1<<0)
-#define RDB_LOAD_PLAIN  (1<<1)
-#define RDB_LOAD_SDS    (1<<2)
-
 #define rdbExitReportCorruptRDB(reason) rdbCheckThenExit(reason, __LINE__);
 
 void rdbCheckThenExit(char *reason, int where) {
@@ -95,7 +90,7 @@ long long rdbLoadMillisecondTime(rio *rdb) {
 /* Saves an encoded length. The first two bits in the first byte are used to
  * hold the encoding type. See the RDB_* definitions for more information
  * on the types of encoding. */
-int rdbSaveLen(rio *rdb, uint32_t len) {
+int rdbSaveLen(rio *rdb, uint64_t len) {
     unsigned char buf[2];
     size_t nwritten;
 
@@ -110,44 +105,78 @@ int rdbSaveLen(rio *rdb, uint32_t len) {
         buf[1] = len&0xFF;
         if (rdbWriteRaw(rdb,buf,2) == -1) return -1;
         nwritten = 2;
-    } else {
+    } else if (len <= UINT32_MAX) {
         /* Save a 32 bit len */
-        buf[0] = (RDB_32BITLEN<<6);
+        buf[0] = RDB_32BITLEN;
         if (rdbWriteRaw(rdb,buf,1) == -1) return -1;
-        len = htonl(len);
-        if (rdbWriteRaw(rdb,&len,4) == -1) return -1;
+        uint32_t len32 = htonl(len);
+        if (rdbWriteRaw(rdb,&len32,4) == -1) return -1;
         nwritten = 1+4;
+    } else {
+        /* Save a 64 bit len */
+        buf[0] = RDB_64BITLEN;
+        if (rdbWriteRaw(rdb,buf,1) == -1) return -1;
+        len = htonu64(len);
+        if (rdbWriteRaw(rdb,&len,8) == -1) return -1;
+        nwritten = 1+8;
     }
     return nwritten;
 }
 
-/* Load an encoded length. The "isencoded" argument is set to 1 if the length
- * is not actually a length but an "encoding type". See the RDB_ENC_*
- * definitions in rdb.h for more information. */
-uint32_t rdbLoadLen(rio *rdb, int *isencoded) {
+
+/* Load an encoded length. If the loaded length is a normal length as stored
+ * with rdbSaveLen(), the read length is set to '*lenptr'. If instead the
+ * loaded length describes a special encoding that follows, then '*isencoded'
+ * is set to 1 and the encoding format is stored at '*lenptr'.
+ *
+ * See the RDB_ENC_* definitions in rdb.h for more information on special
+ * encodings.
+ *
+ * The function returns -1 on error, 0 on success. */
+int rdbLoadLenByRef(rio *rdb, int *isencoded, uint64_t *lenptr) {
     unsigned char buf[2];
-    uint32_t len;
     int type;
 
     if (isencoded) *isencoded = 0;
-    if (rioRead(rdb,buf,1) == 0) return RDB_LENERR;
+    if (rioRead(rdb,buf,1) == 0) return -1;
     type = (buf[0]&0xC0)>>6;
     if (type == RDB_ENCVAL) {
         /* Read a 6 bit encoding type. */
         if (isencoded) *isencoded = 1;
-        return buf[0]&0x3F;
+        *lenptr = buf[0]&0x3F;
     } else if (type == RDB_6BITLEN) {
         /* Read a 6 bit len. */
-        return buf[0]&0x3F;
+        *lenptr = buf[0]&0x3F;
     } else if (type == RDB_14BITLEN) {
         /* Read a 14 bit len. */
-        if (rioRead(rdb,buf+1,1) == 0) return RDB_LENERR;
-        return ((buf[0]&0x3F)<<8)|buf[1];
-    } else {
+        if (rioRead(rdb,buf+1,1) == 0) return -1;
+        *lenptr = ((buf[0]&0x3F)<<8)|buf[1];
+    } else if (buf[0] == RDB_32BITLEN) {
         /* Read a 32 bit len. */
-        if (rioRead(rdb,&len,4) == 0) return RDB_LENERR;
-        return ntohl(len);
+        uint32_t len;
+        if (rioRead(rdb,&len,4) == 0) return -1;
+        *lenptr = ntohl(len);
+    } else if (buf[0] == RDB_64BITLEN) {
+        /* Read a 64 bit len. */
+        uint64_t len;
+        if (rioRead(rdb,&len,8) == 0) return -1;
+        *lenptr = ntohu64(len);
+    } else {
+        rdbExitReportCorruptRDB("Unknown length encoding in rdbLoadLen()");
+        return -1; /* Never reached. */
     }
+    return 0;
+}
+
+/* This is like rdbLoadLenByRef() but directly returns the value read
+ * from the RDB stream, signaling an error by returning RDB_LENERR
+ * (since it is a too large count to be applicable in any Redis data
+ * structure). */
+uint64_t rdbLoadLen(rio *rdb, int *isencoded) {
+    uint64_t len;
+
+    if (rdbLoadLenByRef(rdb,isencoded,&len) == -1) return RDB_LENERR;
+    return len;
 }
 
 /* Encodes the "value" argument as integer when it fits in the supported ranges
@@ -179,7 +208,7 @@ int rdbEncodeInteger(long long value, unsigned char *enc) {
 /* Loads an integer-encoded object with the specified encoding type "enctype".
  * The returned value changes according to the flags, see
  * rdbGenerincLoadStringObject() for more info. */
-void *rdbLoadIntegerObject(rio *rdb, int enctype, int flags) {
+void *rdbLoadIntegerObject(rio *rdb, int enctype, int flags, size_t *lenptr) {
     int plain = flags & RDB_LOAD_PLAIN;
     int sds = flags & RDB_LOAD_SDS;
     int encode = flags & RDB_LOAD_ENC;
@@ -206,6 +235,7 @@ void *rdbLoadIntegerObject(rio *rdb, int enctype, int flags) {
     if (plain || sds) {
         char buf[LONG_STR_SIZE], *p;
         int len = ll2string(buf,sizeof(buf),val);
+        if (lenptr) *lenptr = len;
         p = plain ? zmalloc(len) : sdsnewlen(NULL,len);
         memcpy(p,buf,len);
         return p;
@@ -281,10 +311,10 @@ ssize_t rdbSaveLzfStringObject(rio *rdb, unsigned char *s, size_t len) {
 /* Load an LZF compressed string in RDB format. The returned value
  * changes according to 'flags'. For more info check the
  * rdbGenericLoadStringObject() function. */
-void *rdbLoadLzfStringObject(rio *rdb, int flags) {
+void *rdbLoadLzfStringObject(rio *rdb, int flags, size_t *lenptr) {
     int plain = flags & RDB_LOAD_PLAIN;
     int sds = flags & RDB_LOAD_SDS;
-    unsigned int len, clen;
+    uint64_t len, clen;
     unsigned char *c = NULL;
     char *val = NULL;
 
@@ -295,6 +325,7 @@ void *rdbLoadLzfStringObject(rio *rdb, int flags) {
     /* Allocate our target according to the uncompressed size. */
     if (plain) {
         val = zmalloc(len);
+        if (lenptr) *lenptr = len;
     } else {
         val = sdsnewlen(NULL,len);
     }
@@ -393,23 +424,25 @@ int rdbSaveStringObject(rio *rdb, robj *obj) {
  * RDB_LOAD_PLAIN: Return a plain string allocated with zmalloc()
  *                 instead of a Redis object with an sds in it.
  * RDB_LOAD_SDS: Return an SDS string instead of a Redis object.
-*/
-void *rdbGenericLoadStringObject(rio *rdb, int flags) {
+ *
+ * On I/O error NULL is returned.
+ */
+void *rdbGenericLoadStringObject(rio *rdb, int flags, size_t *lenptr) {
     int encode = flags & RDB_LOAD_ENC;
     int plain = flags & RDB_LOAD_PLAIN;
     int sds = flags & RDB_LOAD_SDS;
     int isencoded;
-    uint32_t len;
+    uint64_t len;
 
     len = rdbLoadLen(rdb,&isencoded);
     if (isencoded) {
         switch(len) {
         case RDB_ENC_INT8:
         case RDB_ENC_INT16:
         case RDB_ENC_INT32:
-            return rdbLoadIntegerObject(rdb,len,flags);
+            return rdbLoadIntegerObject(rdb,len,flags,lenptr);
         case RDB_ENC_LZF:
-            return rdbLoadLzfStringObject(rdb,flags);
+            return rdbLoadLzfStringObject(rdb,flags,lenptr);
         default:
             rdbExitReportCorruptRDB("Unknown RDB encoding type");
         }
@@ -418,6 +451,7 @@ void *rdbGenericLoadStringObject(rio *rdb, int flags) {
     if (len == RDB_LENERR) return NULL;
     if (plain || sds) {
         void *buf = plain ? zmalloc(len) : sdsnewlen(NULL,len);
+        if (lenptr) *lenptr = len;
         if (len && rioRead(rdb,buf,len) == 0) {
             if (plain)
                 zfree(buf);
@@ -438,11 +472,11 @@ void *rdbGenericLoadStringObject(rio *rdb, int flags) {
 }
 
 robj *rdbLoadStringObject(rio *rdb) {
-    return rdbGenericLoadStringObject(rdb,RDB_LOAD_NONE);
+    return rdbGenericLoadStringObject(rdb,RDB_LOAD_NONE,NULL);
 }
 
 robj *rdbLoadEncodedStringObject(rio *rdb) {
-    return rdbGenericLoadStringObject(rdb,RDB_LOAD_ENC);
+    return rdbGenericLoadStringObject(rdb,RDB_LOAD_ENC,NULL);
 }
 
 /* Save a double value. Doubles are saved as strings prefixed by an unsigned
@@ -505,6 +539,24 @@ int rdbLoadDoubleValue(rio *rdb, double *val) {
     }
 }
 
+/* Saves a double for RDB 8 or greater, where IE754 binary64 format is assumed.
+ * We just make sure the integer is always stored in little endian, otherwise
+ * the value is copied verbatim from memory to disk.
+ *
+ * Return -1 on error, the size of the serialized value on success. */
+int rdbSaveBinaryDoubleValue(rio *rdb, double val) {
+    memrev64ifbe(&val);
+    return rdbWriteRaw(rdb,&val,8);
+}
+
+/* Loads a double from RDB 8 or greater. See rdbSaveBinaryDoubleValue() for
+ * more info. On error -1 is returned, otherwise 0. */
+int rdbLoadBinaryDoubleValue(rio *rdb, double *val) {
+    if (rioRead(rdb,val,8) == 0) return -1;
+    memrev64ifbe(val);
+    return 0;
+}
+
 /* Save the object type of object "o". */
 int rdbSaveObjectType(rio *rdb, robj *o) {
     switch (o->type) {
@@ -526,7 +578,7 @@ int rdbSaveObjectType(rio *rdb, robj *o) {
         if (o->encoding == OBJ_ENCODING_ZIPLIST)
             return rdbSaveType(rdb,RDB_TYPE_ZSET_ZIPLIST);
         else if (o->encoding == OBJ_ENCODING_SKIPLIST)
-            return rdbSaveType(rdb,RDB_TYPE_ZSET);
+            return rdbSaveType(rdb,RDB_TYPE_ZSET_2);
         else
             serverPanic("Unknown sorted set encoding");
     case OBJ_HASH:
@@ -536,6 +588,8 @@ int rdbSaveObjectType(rio *rdb, robj *o) {
             return rdbSaveType(rdb,RDB_TYPE_HASH);
         else
             serverPanic("Unknown hash encoding");
+    case OBJ_MODULE:
+        return rdbSaveType(rdb,RDB_TYPE_MODULE);
     default:
         serverPanic("Unknown object type");
     }
@@ -629,7 +683,7 @@ ssize_t rdbSaveObject(rio *rdb, robj *o) {
                 if ((n = rdbSaveRawString(rdb,(unsigned char*)ele,sdslen(ele)))
                     == -1) return -1;
                 nwritten += n;
-                if ((n = rdbSaveDoubleValue(rdb,*score)) == -1) return -1;
+                if ((n = rdbSaveBinaryDoubleValue(rdb,*score)) == -1) return -1;
                 nwritten += n;
             }
             dictReleaseIterator(di);
@@ -667,6 +721,22 @@ ssize_t rdbSaveObject(rio *rdb, robj *o) {
             serverPanic("Unknown hash encoding");
         }
 
+    } else if (o->type == OBJ_MODULE) {
+        /* Save a module-specific value. */
+        RedisModuleIO io;
+        moduleValue *mv = o->ptr;
+        moduleType *mt = mv->type;
+        moduleInitIOContext(io,mt,rdb);
+
+        /* Write the "module" identifier as prefix, so that we'll be able
+         * to call the right module during loading. */
+        int retval = rdbSaveLen(rdb,mt->id);
+        if (retval == -1) return -1;
+        io.bytes += retval;
+
+        /* Then write the module-specific representation. */
+        mt->rdb_save(&io,mv->value);
+        return io.error ? -1 : (ssize_t)io.bytes;
     } else {
         serverPanic("Unknown object type");
     }
@@ -1005,8 +1075,8 @@ robj *rdbLoadObject(int rdbtype, rio *rdb) {
             long long llval;
             sds sdsele;
 
-            if ((sdsele = rdbGenericLoadStringObject(rdb,RDB_LOAD_SDS)) == NULL)
-                return NULL;
+            if ((sdsele = rdbGenericLoadStringObject(rdb,RDB_LOAD_SDS,NULL))
+                == NULL) return NULL;
 
             if (o->encoding == OBJ_ENCODING_INTSET) {
                 /* Fetch integer value from element. */
@@ -1026,7 +1096,7 @@ robj *rdbLoadObject(int rdbtype, rio *rdb) {
                 sdsfree(sdsele);
             }
         }
-    } else if (rdbtype == RDB_TYPE_ZSET) {
+    } else if (rdbtype == RDB_TYPE_ZSET_2 || rdbtype == RDB_TYPE_ZSET) {
         /* Read list/set value. */
         size_t zsetlen;
         size_t maxelelen = 0;
@@ -1042,9 +1112,14 @@ robj *rdbLoadObject(int rdbtype, rio *rdb) {
             double score;
             zskiplistNode *znode;
 
-            if ((sdsele = rdbGenericLoadStringObject(rdb,RDB_LOAD_SDS)) == NULL)
-                return NULL;
-            if (rdbLoadDoubleValue(rdb,&score) == -1) return NULL;
+            if ((sdsele = rdbGenericLoadStringObject(rdb,RDB_LOAD_SDS,NULL))
+                == NULL) return NULL;
+
+            if (rdbtype == RDB_TYPE_ZSET_2) {
+                if (rdbLoadBinaryDoubleValue(rdb,&score) == -1) return NULL;
+            } else {
+                if (rdbLoadDoubleValue(rdb,&score) == -1) return NULL;
+            }
 
             /* Don't care about integer-encoded strings. */
             if (sdslen(sdsele) > maxelelen) maxelelen = sdslen(sdsele);
@@ -1075,10 +1150,10 @@ robj *rdbLoadObject(int rdbtype, rio *rdb) {
         while (o->encoding == OBJ_ENCODING_ZIPLIST && len > 0) {
             len--;
             /* Load raw strings */
-            if ((field = rdbGenericLoadStringObject(rdb,RDB_LOAD_SDS)) == NULL)
-                return NULL;
-            if ((value = rdbGenericLoadStringObject(rdb,RDB_LOAD_SDS)) == NULL)
-                return NULL;
+            if ((field = rdbGenericLoadStringObject(rdb,RDB_LOAD_SDS,NULL))
+                == NULL) return NULL;
+            if ((value = rdbGenericLoadStringObject(rdb,RDB_LOAD_SDS,NULL))
+                == NULL) return NULL;
 
             /* Add pair to ziplist */
             o->ptr = ziplistPush(o->ptr, (unsigned char*)field,
@@ -1103,10 +1178,10 @@ robj *rdbLoadObject(int rdbtype, rio *rdb) {
         while (o->encoding == OBJ_ENCODING_HT && len > 0) {
             len--;
             /* Load encoded strings */
-            if ((field = rdbGenericLoadStringObject(rdb,RDB_LOAD_SDS)) == NULL)
-                return NULL;
-            if ((value = rdbGenericLoadStringObject(rdb,RDB_LOAD_SDS)) == NULL)
-                return NULL;
+            if ((field = rdbGenericLoadStringObject(rdb,RDB_LOAD_SDS,NULL))
+                == NULL) return NULL;
+            if ((value = rdbGenericLoadStringObject(rdb,RDB_LOAD_SDS,NULL))
+                == NULL) return NULL;
 
             /* Add pair to hash table */
             ret = dictAdd((dict*)o->ptr, field, value);
@@ -1124,7 +1199,8 @@ robj *rdbLoadObject(int rdbtype, rio *rdb) {
                             server.list_compress_depth);
 
         while (len--) {
-            unsigned char *zl = rdbGenericLoadStringObject(rdb,RDB_LOAD_PLAIN);
+            unsigned char *zl =
+                rdbGenericLoadStringObject(rdb,RDB_LOAD_PLAIN,NULL);
             if (zl == NULL) return NULL;
             quicklistAppendZiplist(o->ptr, zl);
         }
@@ -1134,7 +1210,8 @@ robj *rdbLoadObject(int rdbtype, rio *rdb) {
                rdbtype == RDB_TYPE_ZSET_ZIPLIST ||
                rdbtype == RDB_TYPE_HASH_ZIPLIST)
     {
-        unsigned char *encoded = rdbGenericLoadStringObject(rdb,RDB_LOAD_PLAIN);
+        unsigned char *encoded =
+            rdbGenericLoadStringObject(rdb,RDB_LOAD_PLAIN,NULL);
         if (encoded == NULL) return NULL;
         o = createObject(OBJ_STRING,encoded); /* Obj type fixed below. */
 
@@ -1201,6 +1278,27 @@ robj *rdbLoadObject(int rdbtype, rio *rdb) {
                 rdbExitReportCorruptRDB("Unknown encoding");
                 break;
         }
+    } else if (rdbtype == RDB_TYPE_MODULE) {
+        uint64_t moduleid = rdbLoadLen(rdb,NULL);
+        moduleType *mt = moduleTypeLookupModuleByID(moduleid);
+        char name[10];
+
+        if (mt == NULL) {
+            moduleTypeNameByID(name,moduleid);
+            serverLog(LL_WARNING,"The RDB file contains module data I can't load: no matching module '%s'", name);
+            exit(1);
+        }
+        RedisModuleIO io;
+        moduleInitIOContext(io,mt,rdb);
+        /* Call the rdb_load method of the module providing the 10 bit
+         * encoding version in the lower 10 bits of the module ID. */
+        void *ptr = mt->rdb_load(&io,moduleid&1023);
+        if (ptr == NULL) {
+            moduleTypeNameByID(name,moduleid);
+            serverLog(LL_WARNING,"The RDB file contains module data for the module type '%s', that the responsible module is not able to load. Check for modules log above for additional clues.", name);
+            exit(1);
+        }
+        o = createModuleObject(mt,ptr);
     } else {
         rdbExitReportCorruptRDB("Unknown object type");
     }
@@ -1255,7 +1353,7 @@ void rdbLoadProgressCallback(rio *r, const void *buf, size_t len) {
 }
 
 int rdbLoad(char *filename) {
-    uint32_t dbid;
+    uint64_t dbid;
     int type, rdbver;
     redisDb *db = server.db+0;
     char buf[1024];
@@ -1328,7 +1426,7 @@ int rdbLoad(char *filename) {
         } else if (type == RDB_OPCODE_RESIZEDB) {
             /* RESIZEDB: Hint about the size of the keys in the currently
              * selected data base, in order to avoid useless rehashing. */
-            uint32_t db_size, expires_size;
+            uint64_t db_size, expires_size;
             if ((db_size = rdbLoadLen(&rdb,NULL)) == RDB_LENERR)
                 goto eoferr;
             if ((expires_size = rdbLoadLen(&rdb,NULL)) == RDB_LENERR)