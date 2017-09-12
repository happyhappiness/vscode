@@ -1509,6 +1509,7 @@ static int rdbSaveType(FILE *fp, unsigned char type) {
     return 0;
 }
 
+/* check rdbLoadLen() comments for more info */
 static int rdbSaveLen(FILE *fp, uint32_t len) {
     unsigned char buf[2];
 
@@ -1531,9 +1532,57 @@ static int rdbSaveLen(FILE *fp, uint32_t len) {
     return 0;
 }
 
+/* String objects in the form "2391" "-100" without any space and with a
+ * range of values that can fit in an 8, 16 or 32 bit signed value can be
+ * encoded as integers to save space */
+int rdbTryIntegerEncoding(sds s, unsigned char *enc) {
+    long long value;
+    char *endptr, buf[32];
+
+    /* Check if it's possible to encode this value as a number */
+    value = strtoll(s, &endptr, 10);
+    if (endptr[0] != '\0') return 0;
+    snprintf(buf,32,"%lld",value);
+
+    /* If the number converted back into a string is not identical
+     * then it's not possible to encode the string as integer */
+    if (strlen(buf) != sdslen(s) || memcmp(buf,s,sdslen(s))) return 0;
+
+    /* Finally check if it fits in our ranges */
+    if (value >= -(1<<7) && value <= (1<<7)-1) {
+        enc[0] = (REDIS_RDB_ENCVAL<<6)|REDIS_RDB_ENC_INT8;
+        enc[1] = value&0xFF;
+        return 2;
+    } else if (value >= -(1<<15) && value <= (1<<15)-1) {
+        enc[0] = (REDIS_RDB_ENCVAL<<6)|REDIS_RDB_ENC_INT16;
+        enc[1] = value&0xFF;
+        enc[2] = (value>>8)&0xFF;
+        return 3;
+    } else if (value >= -((long long)1<<31) && value <= ((long long)1<<31)-1) {
+        enc[0] = (REDIS_RDB_ENCVAL<<6)|REDIS_RDB_ENC_INT32;
+        enc[1] = value&0xFF;
+        enc[2] = (value>>8)&0xFF;
+        enc[3] = (value>>16)&0xFF;
+        enc[4] = (value>>24)&0xFF;
+        return 5;
+    } else {
+        return 0;
+    }
+}
+
+/* Save a string objet as [len][data] on disk. If the object is a string
+ * representation of an integer value we try to safe it in a special form */
 static int rdbSaveStringObject(FILE *fp, robj *obj) {
     size_t len = sdslen(obj->ptr);
+    int enclen;
 
+    if (len <= 11) {
+        unsigned char buf[5];
+        if ((enclen = rdbTryIntegerEncoding(obj->ptr,buf)) > 0) {
+            if (fwrite(buf,enclen,1,fp) == 0) return -1;
+            return 0;
+        }
+    }
     if (rdbSaveLen(fp,len) == -1) return -1;
     if (len && fwrite(obj->ptr,len,1,fp) == 0) return -1;
     return 0;
@@ -1664,10 +1713,16 @@ static int rdbLoadType(FILE *fp) {
     return type;
 }
 
-static uint32_t rdbLoadLen(FILE *fp, int rdbver) {
+/* Load an encoded length from the DB, see the REDIS_RDB_* defines on the top
+ * of this file for a description of how this are stored on disk.
+ *
+ * isencoded is set to 1 if the readed length is not actually a length but
+ * an "encoding type", check the above comments for more info */
+static uint32_t rdbLoadLen(FILE *fp, int rdbver, int *isencoded) {
     unsigned char buf[2];
     uint32_t len;
 
+    if (isencoded) *isencoded = 0;
     if (rdbver == 0) {
         if (fread(&len,4,1,fp) == 0) return REDIS_RDB_LENERR;
         return ntohl(len);
@@ -1678,7 +1733,11 @@ static uint32_t rdbLoadLen(FILE *fp, int rdbver) {
         type = (buf[0]&0xC0)>>6;
         if (type == REDIS_RDB_6BITLEN) {
             /* Read a 6 bit len */
-            return buf[0];
+            return buf[0]&0x3F;
+        } else if (type == REDIS_RDB_ENCVAL) {
+            /* Read a 6 bit len encoding type */
+            if (isencoded) *isencoded = 1;
+            return buf[0]&0x3F;
         } else if (type == REDIS_RDB_14BITLEN) {
             /* Read a 14 bit len */
             if (fread(buf+1,1,1,fp) == 0) return REDIS_RDB_LENERR;
@@ -1691,10 +1750,47 @@ static uint32_t rdbLoadLen(FILE *fp, int rdbver) {
     }
 }
 
-static robj *rdbLoadStringObject(FILE*fp,int rdbver) {
-    uint32_t len = rdbLoadLen(fp,rdbver);
+static robj *rdbLoadIntegerObject(FILE *fp, int enctype) {
+    unsigned char enc[4];
+    long long val;
+
+    if (enctype == REDIS_RDB_ENC_INT8) {
+        if (fread(enc,1,1,fp) == 0) return NULL;
+        val = (signed char)enc[0];
+    } else if (enctype == REDIS_RDB_ENC_INT16) {
+        uint16_t v;
+        if (fread(enc,2,1,fp) == 0) return NULL;
+        v = enc[0]|(enc[1]<<8);
+        val = (int16_t)v;
+    } else if (enctype == REDIS_RDB_ENC_INT32) {
+        uint32_t v;
+        if (fread(enc,4,1,fp) == 0) return NULL;
+        v = enc[0]|(enc[1]<<8)|(enc[2]<<16)|(enc[3]<<24);
+        val = (int32_t)v;
+    } else {
+        val = 0; /* anti-warning */
+        assert(0!=0);
+    }
+    return createObject(REDIS_STRING,sdscatprintf(sdsempty(),"%lld",val));
+}
+
+static robj *rdbLoadStringObject(FILE*fp, int rdbver) {
+    int isencoded;
+    uint32_t len;
     sds val;
 
+    len = rdbLoadLen(fp,rdbver,&isencoded);
+    if (isencoded) {
+        switch(len) {
+        case REDIS_RDB_ENC_INT8:
+        case REDIS_RDB_ENC_INT16:
+        case REDIS_RDB_ENC_INT32:
+            return rdbLoadIntegerObject(fp,len);
+        default:
+            assert(0!=0);
+        }
+    }
+
     if (len == REDIS_RDB_LENERR) return NULL;
     val = sdsnewlen(NULL,len);
     if (len && fread(val,len,1,fp) == 0) {
@@ -1736,7 +1832,8 @@ static int rdbLoad(char *filename) {
         if (type == REDIS_EOF) break;
         /* Handle SELECT DB opcode as a special case */
         if (type == REDIS_SELECTDB) {
-            if ((dbid = rdbLoadLen(fp,rdbver)) == REDIS_RDB_LENERR) goto eoferr;
+            if ((dbid = rdbLoadLen(fp,rdbver,NULL)) == REDIS_RDB_LENERR)
+                goto eoferr;
             if (dbid >= (unsigned)server.dbnum) {
                 redisLog(REDIS_WARNING,"FATAL: Data file was created with a Redis server configured to handle more than %d databases. Exiting\n", server.dbnum);
                 exit(1);
@@ -1754,7 +1851,7 @@ static int rdbLoad(char *filename) {
             /* Read list/set value */
             uint32_t listlen;
 
-            if ((listlen = rdbLoadLen(fp,rdbver)) == REDIS_RDB_LENERR)
+            if ((listlen = rdbLoadLen(fp,rdbver,NULL)) == REDIS_RDB_LENERR)
                 goto eoferr;
             o = (type == REDIS_LIST) ? createListObject() : createSetObject();
             /* Load every single element of the list/set */
@@ -1785,8 +1882,8 @@ static int rdbLoad(char *filename) {
     return REDIS_OK;
 
 eoferr: /* unexpected end of file is handled here with a fatal exit */
-    decrRefCount(keyobj);
-    redisLog(REDIS_WARNING,"Short read loading DB. Unrecoverable error, exiting now.");
+    if (keyobj) decrRefCount(keyobj);
+    redisLog(REDIS_WARNING,"Short read or OOM loading DB. Unrecoverable error, exiting now.");
     exit(1);
     return REDIS_ERR; /* Just to avoid warning */
 }