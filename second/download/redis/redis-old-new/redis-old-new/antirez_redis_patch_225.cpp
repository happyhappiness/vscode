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
@@ -213,7 +208,7 @@ int rdbEncodeInteger(long long value, unsigned char *enc) {
 /* Loads an integer-encoded object with the specified encoding type "enctype".
  * The returned value changes according to the flags, see
  * rdbGenerincLoadStringObject() for more info. */
-void *rdbLoadIntegerObject(rio *rdb, int enctype, int flags) {
+void *rdbLoadIntegerObject(rio *rdb, int enctype, int flags, size_t *lenptr) {
     int plain = flags & RDB_LOAD_PLAIN;
     int sds = flags & RDB_LOAD_SDS;
     int encode = flags & RDB_LOAD_ENC;
@@ -240,6 +235,7 @@ void *rdbLoadIntegerObject(rio *rdb, int enctype, int flags) {
     if (plain || sds) {
         char buf[LONG_STR_SIZE], *p;
         int len = ll2string(buf,sizeof(buf),val);
+        if (lenptr) *lenptr = len;
         p = plain ? zmalloc(len) : sdsnewlen(NULL,len);
         memcpy(p,buf,len);
         return p;
@@ -315,7 +311,7 @@ ssize_t rdbSaveLzfStringObject(rio *rdb, unsigned char *s, size_t len) {
 /* Load an LZF compressed string in RDB format. The returned value
  * changes according to 'flags'. For more info check the
  * rdbGenericLoadStringObject() function. */
-void *rdbLoadLzfStringObject(rio *rdb, int flags) {
+void *rdbLoadLzfStringObject(rio *rdb, int flags, size_t *lenptr) {
     int plain = flags & RDB_LOAD_PLAIN;
     int sds = flags & RDB_LOAD_SDS;
     uint64_t len, clen;
@@ -329,6 +325,7 @@ void *rdbLoadLzfStringObject(rio *rdb, int flags) {
     /* Allocate our target according to the uncompressed size. */
     if (plain) {
         val = zmalloc(len);
+        if (lenptr) *lenptr = len;
     } else {
         val = sdsnewlen(NULL,len);
     }
@@ -427,8 +424,10 @@ int rdbSaveStringObject(rio *rdb, robj *obj) {
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
@@ -441,9 +440,9 @@ void *rdbGenericLoadStringObject(rio *rdb, int flags) {
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
@@ -452,6 +451,7 @@ void *rdbGenericLoadStringObject(rio *rdb, int flags) {
     if (len == RDB_LENERR) return NULL;
     if (plain || sds) {
         void *buf = plain ? zmalloc(len) : sdsnewlen(NULL,len);
+        if (lenptr) *lenptr = len;
         if (len && rioRead(rdb,buf,len) == 0) {
             if (plain)
                 zfree(buf);
@@ -472,11 +472,11 @@ void *rdbGenericLoadStringObject(rio *rdb, int flags) {
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
@@ -541,14 +541,16 @@ int rdbLoadDoubleValue(rio *rdb, double *val) {
 
 /* Saves a double for RDB 8 or greater, where IE754 binary64 format is assumed.
  * We just make sure the integer is always stored in little endian, otherwise
- * the value is copied verbatim from memory to disk. */
+ * the value is copied verbatim from memory to disk.
+ *
+ * Return -1 on error, the size of the serialized value on success. */
 int rdbSaveBinaryDoubleValue(rio *rdb, double val) {
     memrev64ifbe(&val);
     return rdbWriteRaw(rdb,&val,8);
 }
 
 /* Loads a double from RDB 8 or greater. See rdbSaveBinaryDoubleValue() for
- * more info. */
+ * more info. On error -1 is returned, otherwise 0. */
 int rdbLoadBinaryDoubleValue(rio *rdb, double *val) {
     if (rioRead(rdb,val,8) == 0) return -1;
     memrev64ifbe(val);
@@ -586,6 +588,8 @@ int rdbSaveObjectType(rio *rdb, robj *o) {
             return rdbSaveType(rdb,RDB_TYPE_HASH);
         else
             serverPanic("Unknown hash encoding");
+    case OBJ_MODULE:
+        return rdbSaveType(rdb,RDB_TYPE_MODULE);
     default:
         serverPanic("Unknown object type");
     }
@@ -717,6 +721,22 @@ ssize_t rdbSaveObject(rio *rdb, robj *o) {
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
+        return io.error ? -1 : io.bytes;
     } else {
         serverPanic("Unknown object type");
     }
@@ -1055,8 +1075,8 @@ robj *rdbLoadObject(int rdbtype, rio *rdb) {
             long long llval;
             sds sdsele;
 
-            if ((sdsele = rdbGenericLoadStringObject(rdb,RDB_LOAD_SDS)) == NULL)
-                return NULL;
+            if ((sdsele = rdbGenericLoadStringObject(rdb,RDB_LOAD_SDS,NULL))
+                == NULL) return NULL;
 
             if (o->encoding == OBJ_ENCODING_INTSET) {
                 /* Fetch integer value from element. */
@@ -1092,8 +1112,8 @@ robj *rdbLoadObject(int rdbtype, rio *rdb) {
             double score;
             zskiplistNode *znode;
 
-            if ((sdsele = rdbGenericLoadStringObject(rdb,RDB_LOAD_SDS)) == NULL)
-                return NULL;
+            if ((sdsele = rdbGenericLoadStringObject(rdb,RDB_LOAD_SDS,NULL))
+                == NULL) return NULL;
 
             if (rdbtype == RDB_TYPE_ZSET_2) {
                 if (rdbLoadBinaryDoubleValue(rdb,&score) == -1) return NULL;
@@ -1130,10 +1150,10 @@ robj *rdbLoadObject(int rdbtype, rio *rdb) {
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
@@ -1158,10 +1178,10 @@ robj *rdbLoadObject(int rdbtype, rio *rdb) {
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
@@ -1179,7 +1199,8 @@ robj *rdbLoadObject(int rdbtype, rio *rdb) {
                             server.list_compress_depth);
 
         while (len--) {
-            unsigned char *zl = rdbGenericLoadStringObject(rdb,RDB_LOAD_PLAIN);
+            unsigned char *zl =
+                rdbGenericLoadStringObject(rdb,RDB_LOAD_PLAIN,NULL);
             if (zl == NULL) return NULL;
             quicklistAppendZiplist(o->ptr, zl);
         }
@@ -1189,7 +1210,8 @@ robj *rdbLoadObject(int rdbtype, rio *rdb) {
                rdbtype == RDB_TYPE_ZSET_ZIPLIST ||
                rdbtype == RDB_TYPE_HASH_ZIPLIST)
     {
-        unsigned char *encoded = rdbGenericLoadStringObject(rdb,RDB_LOAD_PLAIN);
+        unsigned char *encoded =
+            rdbGenericLoadStringObject(rdb,RDB_LOAD_PLAIN,NULL);
         if (encoded == NULL) return NULL;
         o = createObject(OBJ_STRING,encoded); /* Obj type fixed below. */
 
@@ -1256,6 +1278,27 @@ robj *rdbLoadObject(int rdbtype, rio *rdb) {
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