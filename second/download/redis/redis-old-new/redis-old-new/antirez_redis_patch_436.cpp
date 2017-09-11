@@ -47,7 +47,7 @@
 #define rdbExitReportCorruptRDB(reason) rdbCheckThenExit(reason, __LINE__);
 
 void rdbCheckThenExit(char *reason, int where) {
-    serverLog(REDIS_WARNING, "Corrupt RDB detected at rdb.c:%d (%s). "
+    serverLog(LL_WARNING, "Corrupt RDB detected at rdb.c:%d (%s). "
         "Running 'redis-check-rdb %s'",
         where, reason, server.rdb_filename);
     redis_check_rdb(server.rdb_filename);
@@ -91,26 +91,26 @@ long long rdbLoadMillisecondTime(rio *rdb) {
 }
 
 /* Saves an encoded length. The first two bits in the first byte are used to
- * hold the encoding type. See the REDIS_RDB_* definitions for more information
+ * hold the encoding type. See the RDB_* definitions for more information
  * on the types of encoding. */
 int rdbSaveLen(rio *rdb, uint32_t len) {
     unsigned char buf[2];
     size_t nwritten;
 
     if (len < (1<<6)) {
         /* Save a 6 bit len */
-        buf[0] = (len&0xFF)|(REDIS_RDB_6BITLEN<<6);
+        buf[0] = (len&0xFF)|(RDB_6BITLEN<<6);
         if (rdbWriteRaw(rdb,buf,1) == -1) return -1;
         nwritten = 1;
     } else if (len < (1<<14)) {
         /* Save a 14 bit len */
-        buf[0] = ((len>>8)&0xFF)|(REDIS_RDB_14BITLEN<<6);
+        buf[0] = ((len>>8)&0xFF)|(RDB_14BITLEN<<6);
         buf[1] = len&0xFF;
         if (rdbWriteRaw(rdb,buf,2) == -1) return -1;
         nwritten = 2;
     } else {
         /* Save a 32 bit len */
-        buf[0] = (REDIS_RDB_32BITLEN<<6);
+        buf[0] = (RDB_32BITLEN<<6);
         if (rdbWriteRaw(rdb,buf,1) == -1) return -1;
         len = htonl(len);
         if (rdbWriteRaw(rdb,&len,4) == -1) return -1;
@@ -120,30 +120,30 @@ int rdbSaveLen(rio *rdb, uint32_t len) {
 }
 
 /* Load an encoded length. The "isencoded" argument is set to 1 if the length
- * is not actually a length but an "encoding type". See the REDIS_RDB_ENC_*
+ * is not actually a length but an "encoding type". See the RDB_ENC_*
  * definitions in rdb.h for more information. */
 uint32_t rdbLoadLen(rio *rdb, int *isencoded) {
     unsigned char buf[2];
     uint32_t len;
     int type;
 
     if (isencoded) *isencoded = 0;
-    if (rioRead(rdb,buf,1) == 0) return REDIS_RDB_LENERR;
+    if (rioRead(rdb,buf,1) == 0) return RDB_LENERR;
     type = (buf[0]&0xC0)>>6;
-    if (type == REDIS_RDB_ENCVAL) {
+    if (type == RDB_ENCVAL) {
         /* Read a 6 bit encoding type. */
         if (isencoded) *isencoded = 1;
         return buf[0]&0x3F;
-    } else if (type == REDIS_RDB_6BITLEN) {
+    } else if (type == RDB_6BITLEN) {
         /* Read a 6 bit len. */
         return buf[0]&0x3F;
-    } else if (type == REDIS_RDB_14BITLEN) {
+    } else if (type == RDB_14BITLEN) {
         /* Read a 14 bit len. */
-        if (rioRead(rdb,buf+1,1) == 0) return REDIS_RDB_LENERR;
+        if (rioRead(rdb,buf+1,1) == 0) return RDB_LENERR;
         return ((buf[0]&0x3F)<<8)|buf[1];
     } else {
         /* Read a 32 bit len. */
-        if (rioRead(rdb,&len,4) == 0) return REDIS_RDB_LENERR;
+        if (rioRead(rdb,&len,4) == 0) return RDB_LENERR;
         return ntohl(len);
     }
 }
@@ -154,16 +154,16 @@ uint32_t rdbLoadLen(rio *rdb, int *isencoded) {
  * length is returned. Otherwise 0 is returned. */
 int rdbEncodeInteger(long long value, unsigned char *enc) {
     if (value >= -(1<<7) && value <= (1<<7)-1) {
-        enc[0] = (REDIS_RDB_ENCVAL<<6)|REDIS_RDB_ENC_INT8;
+        enc[0] = (RDB_ENCVAL<<6)|RDB_ENC_INT8;
         enc[1] = value&0xFF;
         return 2;
     } else if (value >= -(1<<15) && value <= (1<<15)-1) {
-        enc[0] = (REDIS_RDB_ENCVAL<<6)|REDIS_RDB_ENC_INT16;
+        enc[0] = (RDB_ENCVAL<<6)|RDB_ENC_INT16;
         enc[1] = value&0xFF;
         enc[2] = (value>>8)&0xFF;
         return 3;
     } else if (value >= -((long long)1<<31) && value <= ((long long)1<<31)-1) {
-        enc[0] = (REDIS_RDB_ENCVAL<<6)|REDIS_RDB_ENC_INT32;
+        enc[0] = (RDB_ENCVAL<<6)|RDB_ENC_INT32;
         enc[1] = value&0xFF;
         enc[2] = (value>>8)&0xFF;
         enc[3] = (value>>16)&0xFF;
@@ -183,15 +183,15 @@ void *rdbLoadIntegerObject(rio *rdb, int enctype, int flags) {
     unsigned char enc[4];
     long long val;
 
-    if (enctype == REDIS_RDB_ENC_INT8) {
+    if (enctype == RDB_ENC_INT8) {
         if (rioRead(rdb,enc,1) == 0) return NULL;
         val = (signed char)enc[0];
-    } else if (enctype == REDIS_RDB_ENC_INT16) {
+    } else if (enctype == RDB_ENC_INT16) {
         uint16_t v;
         if (rioRead(rdb,enc,2) == 0) return NULL;
         v = enc[0]|(enc[1]<<8);
         val = (int16_t)v;
-    } else if (enctype == REDIS_RDB_ENC_INT32) {
+    } else if (enctype == RDB_ENC_INT32) {
         uint32_t v;
         if (rioRead(rdb,enc,4) == 0) return NULL;
         v = enc[0]|(enc[1]<<8)|(enc[2]<<16)|(enc[3]<<24);
@@ -201,7 +201,7 @@ void *rdbLoadIntegerObject(rio *rdb, int enctype, int flags) {
         rdbExitReportCorruptRDB("Unknown RDB integer encoding type");
     }
     if (plain) {
-        char buf[REDIS_LONGSTR_SIZE], *p;
+        char buf[LONG_STR_SIZE], *p;
         int len = ll2string(buf,sizeof(buf),val);
         p = zmalloc(len);
         memcpy(p,buf,len);
@@ -238,7 +238,7 @@ ssize_t rdbSaveLzfBlob(rio *rdb, void *data, size_t compress_len,
     ssize_t n, nwritten = 0;
 
     /* Data compressed! Let's save it on disk */
-    byte = (REDIS_RDB_ENCVAL<<6)|REDIS_RDB_ENC_LZF;
+    byte = (RDB_ENCVAL<<6)|RDB_ENC_LZF;
     if ((n = rdbWriteRaw(rdb,&byte,1)) == -1) goto writeerr;
     nwritten += n;
 
@@ -284,8 +284,8 @@ void *rdbLoadLzfStringObject(rio *rdb, int flags) {
     unsigned char *c = NULL;
     sds val = NULL;
 
-    if ((clen = rdbLoadLen(rdb,NULL)) == REDIS_RDB_LENERR) return NULL;
-    if ((len = rdbLoadLen(rdb,NULL)) == REDIS_RDB_LENERR) return NULL;
+    if ((clen = rdbLoadLen(rdb,NULL)) == RDB_LENERR) return NULL;
+    if ((len = rdbLoadLen(rdb,NULL)) == RDB_LENERR) return NULL;
     if ((c = zmalloc(clen)) == NULL) goto err;
 
     /* Allocate our target according to the uncompressed size. */
@@ -397,18 +397,18 @@ void *rdbGenericLoadStringObject(rio *rdb, int flags) {
     len = rdbLoadLen(rdb,&isencoded);
     if (isencoded) {
         switch(len) {
-        case REDIS_RDB_ENC_INT8:
-        case REDIS_RDB_ENC_INT16:
-        case REDIS_RDB_ENC_INT32:
+        case RDB_ENC_INT8:
+        case RDB_ENC_INT16:
+        case RDB_ENC_INT32:
             return rdbLoadIntegerObject(rdb,len,flags);
-        case REDIS_RDB_ENC_LZF:
+        case RDB_ENC_LZF:
             return rdbLoadLzfStringObject(rdb,flags);
         default:
             rdbExitReportCorruptRDB("Unknown RDB encoding type");
         }
     }
 
-    if (len == REDIS_RDB_LENERR) return NULL;
+    if (len == RDB_LENERR) return NULL;
     if (!plain) {
         robj *o = encode ? createStringObject(NULL,len) :
                            createRawStringObject(NULL,len);
@@ -499,35 +499,35 @@ int rdbLoadDoubleValue(rio *rdb, double *val) {
 int rdbSaveObjectType(rio *rdb, robj *o) {
     switch (o->type) {
     case OBJ_STRING:
-        return rdbSaveType(rdb,REDIS_RDB_TYPE_STRING);
+        return rdbSaveType(rdb,RDB_TYPE_STRING);
     case OBJ_LIST:
         if (o->encoding == OBJ_ENCODING_QUICKLIST)
-            return rdbSaveType(rdb,REDIS_RDB_TYPE_LIST_QUICKLIST);
+            return rdbSaveType(rdb,RDB_TYPE_LIST_QUICKLIST);
         else
-            redisPanic("Unknown list encoding");
+            serverPanic("Unknown list encoding");
     case OBJ_SET:
         if (o->encoding == OBJ_ENCODING_INTSET)
-            return rdbSaveType(rdb,REDIS_RDB_TYPE_SET_INTSET);
+            return rdbSaveType(rdb,RDB_TYPE_SET_INTSET);
         else if (o->encoding == OBJ_ENCODING_HT)
-            return rdbSaveType(rdb,REDIS_RDB_TYPE_SET);
+            return rdbSaveType(rdb,RDB_TYPE_SET);
         else
-            redisPanic("Unknown set encoding");
+            serverPanic("Unknown set encoding");
     case OBJ_ZSET:
         if (o->encoding == OBJ_ENCODING_ZIPLIST)
-            return rdbSaveType(rdb,REDIS_RDB_TYPE_ZSET_ZIPLIST);
+            return rdbSaveType(rdb,RDB_TYPE_ZSET_ZIPLIST);
         else if (o->encoding == OBJ_ENCODING_SKIPLIST)
-            return rdbSaveType(rdb,REDIS_RDB_TYPE_ZSET);
+            return rdbSaveType(rdb,RDB_TYPE_ZSET);
         else
-            redisPanic("Unknown sorted set encoding");
+            serverPanic("Unknown sorted set encoding");
     case OBJ_HASH:
         if (o->encoding == OBJ_ENCODING_ZIPLIST)
-            return rdbSaveType(rdb,REDIS_RDB_TYPE_HASH_ZIPLIST);
+            return rdbSaveType(rdb,RDB_TYPE_HASH_ZIPLIST);
         else if (o->encoding == OBJ_ENCODING_HT)
-            return rdbSaveType(rdb,REDIS_RDB_TYPE_HASH);
+            return rdbSaveType(rdb,RDB_TYPE_HASH);
         else
-            redisPanic("Unknown hash encoding");
+            serverPanic("Unknown hash encoding");
     default:
-        redisPanic("Unknown object type");
+        serverPanic("Unknown object type");
     }
     return -1; /* avoid warning */
 }
@@ -570,7 +570,7 @@ ssize_t rdbSaveObject(rio *rdb, robj *o) {
                 }
             } while ((node = node->next));
         } else {
-            redisPanic("Unknown list encoding");
+            serverPanic("Unknown list encoding");
         }
     } else if (o->type == OBJ_SET) {
         /* Save a set value */
@@ -594,7 +594,7 @@ ssize_t rdbSaveObject(rio *rdb, robj *o) {
             if ((n = rdbSaveRawString(rdb,o->ptr,l)) == -1) return -1;
             nwritten += n;
         } else {
-            redisPanic("Unknown set encoding");
+            serverPanic("Unknown set encoding");
         }
     } else if (o->type == OBJ_ZSET) {
         /* Save a sorted set value */
@@ -622,7 +622,7 @@ ssize_t rdbSaveObject(rio *rdb, robj *o) {
             }
             dictReleaseIterator(di);
         } else {
-            redisPanic("Unknown sorted set encoding");
+            serverPanic("Unknown sorted set encoding");
         }
     } else if (o->type == OBJ_HASH) {
         /* Save a hash value */
@@ -651,11 +651,11 @@ ssize_t rdbSaveObject(rio *rdb, robj *o) {
             dictReleaseIterator(di);
 
         } else {
-            redisPanic("Unknown hash encoding");
+            serverPanic("Unknown hash encoding");
         }
 
     } else {
-        redisPanic("Unknown object type");
+        serverPanic("Unknown object type");
     }
     return nwritten;
 }
@@ -681,7 +681,7 @@ int rdbSaveKeyValuePair(rio *rdb, robj *key, robj *val,
     if (expiretime != -1) {
         /* If this key is already expired skip it */
         if (expiretime < now) return 0;
-        if (rdbSaveType(rdb,REDIS_RDB_OPCODE_EXPIRETIME_MS) == -1) return -1;
+        if (rdbSaveType(rdb,RDB_OPCODE_EXPIRETIME_MS) == -1) return -1;
         if (rdbSaveMillisecondTime(rdb,expiretime) == -1) return -1;
     }
 
@@ -694,7 +694,7 @@ int rdbSaveKeyValuePair(rio *rdb, robj *key, robj *val,
 
 /* Save an AUX field. */
 int rdbSaveAuxField(rio *rdb, void *key, size_t keylen, void *val, size_t vallen) {
-    if (rdbSaveType(rdb,REDIS_RDB_OPCODE_AUX) == -1) return -1;
+    if (rdbSaveType(rdb,RDB_OPCODE_AUX) == -1) return -1;
     if (rdbSaveRawString(rdb,key,keylen) == -1) return -1;
     if (rdbSaveRawString(rdb,val,vallen) == -1) return -1;
     return 1;
@@ -708,7 +708,7 @@ int rdbSaveAuxFieldStrStr(rio *rdb, char *key, char *val) {
 
 /* Wrapper for strlen(key) + integer type (up to long long range). */
 int rdbSaveAuxFieldStrInt(rio *rdb, char *key, long long val) {
-    char buf[REDIS_LONGSTR_SIZE];
+    char buf[LONG_STR_SIZE];
     int vlen = ll2string(buf,sizeof(buf),val);
     return rdbSaveAuxField(rdb,key,strlen(key),buf,vlen);
 }
@@ -743,7 +743,7 @@ int rdbSaveRio(rio *rdb, int *error) {
 
     if (server.rdb_checksum)
         rdb->update_cksum = rioGenericUpdateChecksum;
-    snprintf(magic,sizeof(magic),"REDIS%04d",REDIS_RDB_VERSION);
+    snprintf(magic,sizeof(magic),"REDIS%04d",RDB_VERSION);
     if (rdbWriteRaw(rdb,magic,9) == -1) goto werr;
     if (rdbSaveInfoAuxFields(rdb) == -1) goto werr;
 
@@ -755,7 +755,7 @@ int rdbSaveRio(rio *rdb, int *error) {
         if (!di) return C_ERR;
 
         /* Write the SELECT DB opcode */
-        if (rdbSaveType(rdb,REDIS_RDB_OPCODE_SELECTDB) == -1) goto werr;
+        if (rdbSaveType(rdb,RDB_OPCODE_SELECTDB) == -1) goto werr;
         if (rdbSaveLen(rdb,j) == -1) goto werr;
 
         /* Write the RESIZE DB opcode. We trim the size to UINT32_MAX, which
@@ -769,7 +769,7 @@ int rdbSaveRio(rio *rdb, int *error) {
         expires_size = (dictSize(db->dict) <= UINT32_MAX) ?
                                 dictSize(db->expires) :
                                 UINT32_MAX;
-        if (rdbSaveType(rdb,REDIS_RDB_OPCODE_RESIZEDB) == -1) goto werr;
+        if (rdbSaveType(rdb,RDB_OPCODE_RESIZEDB) == -1) goto werr;
         if (rdbSaveLen(rdb,db_size) == -1) goto werr;
         if (rdbSaveLen(rdb,expires_size) == -1) goto werr;
 
@@ -788,7 +788,7 @@ int rdbSaveRio(rio *rdb, int *error) {
     di = NULL; /* So that we don't release it again on error. */
 
     /* EOF opcode */
-    if (rdbSaveType(rdb,REDIS_RDB_OPCODE_EOF) == -1) goto werr;
+    if (rdbSaveType(rdb,RDB_OPCODE_EOF) == -1) goto werr;
 
     /* CRC64 checksum. It will be zero if checksum computation is disabled, the
      * loading code skips the check in this case. */
@@ -812,15 +812,15 @@ int rdbSaveRio(rio *rdb, int *error) {
  * This way processes receiving the payload can understand when it ends
  * without doing any processing of the content. */
 int rdbSaveRioWithEOFMark(rio *rdb, int *error) {
-    char eofmark[REDIS_EOF_MARK_SIZE];
+    char eofmark[RDB_EOF_MARK_SIZE];
 
-    getRandomHexChars(eofmark,REDIS_EOF_MARK_SIZE);
+    getRandomHexChars(eofmark,RDB_EOF_MARK_SIZE);
     if (error) *error = 0;
     if (rioWrite(rdb,"$EOF:",5) == 0) goto werr;
-    if (rioWrite(rdb,eofmark,REDIS_EOF_MARK_SIZE) == 0) goto werr;
+    if (rioWrite(rdb,eofmark,RDB_EOF_MARK_SIZE) == 0) goto werr;
     if (rioWrite(rdb,"\r\n",2) == 0) goto werr;
     if (rdbSaveRio(rdb,error) == C_ERR) goto werr;
-    if (rioWrite(rdb,eofmark,REDIS_EOF_MARK_SIZE) == 0) goto werr;
+    if (rioWrite(rdb,eofmark,RDB_EOF_MARK_SIZE) == 0) goto werr;
     return C_OK;
 
 werr: /* Write error. */
@@ -839,7 +839,7 @@ int rdbSave(char *filename) {
     snprintf(tmpfile,256,"temp-%d.rdb", (int) getpid());
     fp = fopen(tmpfile,"w");
     if (!fp) {
-        serverLog(REDIS_WARNING, "Failed opening .rdb for saving: %s",
+        serverLog(LL_WARNING, "Failed opening .rdb for saving: %s",
             strerror(errno));
         return C_ERR;
     }
@@ -858,18 +858,18 @@ int rdbSave(char *filename) {
     /* Use RENAME to make sure the DB file is changed atomically only
      * if the generate DB file is ok. */
     if (rename(tmpfile,filename) == -1) {
-        serverLog(REDIS_WARNING,"Error moving temp DB file on the final destination: %s", strerror(errno));
+        serverLog(LL_WARNING,"Error moving temp DB file on the final destination: %s", strerror(errno));
         unlink(tmpfile);
         return C_ERR;
     }
-    serverLog(REDIS_NOTICE,"DB saved on disk");
+    serverLog(LL_NOTICE,"DB saved on disk");
     server.dirty = 0;
     server.lastsave = time(NULL);
     server.lastbgsave_status = C_OK;
     return C_OK;
 
 werr:
-    serverLog(REDIS_WARNING,"Write error saving DB on disk: %s", strerror(errno));
+    serverLog(LL_WARNING,"Write error saving DB on disk: %s", strerror(errno));
     fclose(fp);
     unlink(tmpfile);
     return C_ERR;
@@ -896,7 +896,7 @@ int rdbSaveBackground(char *filename) {
             size_t private_dirty = zmalloc_get_private_dirty();
 
             if (private_dirty) {
-                serverLog(REDIS_NOTICE,
+                serverLog(LL_NOTICE,
                     "RDB: %zu MB of memory used by copy-on-write",
                     private_dirty/(1024*1024));
             }
@@ -909,14 +909,14 @@ int rdbSaveBackground(char *filename) {
         latencyAddSampleIfNeeded("fork",server.stat_fork_time/1000);
         if (childpid == -1) {
             server.lastbgsave_status = C_ERR;
-            serverLog(REDIS_WARNING,"Can't save in background: fork: %s",
+            serverLog(LL_WARNING,"Can't save in background: fork: %s",
                 strerror(errno));
             return C_ERR;
         }
-        serverLog(REDIS_NOTICE,"Background saving started by pid %d",childpid);
+        serverLog(LL_NOTICE,"Background saving started by pid %d",childpid);
         server.rdb_save_time_start = time(NULL);
         server.rdb_child_pid = childpid;
-        server.rdb_child_type = REDIS_RDB_CHILD_TYPE_DISK;
+        server.rdb_child_type = RDB_CHILD_TYPE_DISK;
         updateDictResizePolicy();
         return C_OK;
     }
@@ -937,13 +937,13 @@ robj *rdbLoadObject(int rdbtype, rio *rdb) {
     size_t len;
     unsigned int i;
 
-    if (rdbtype == REDIS_RDB_TYPE_STRING) {
+    if (rdbtype == RDB_TYPE_STRING) {
         /* Read string value */
         if ((o = rdbLoadEncodedStringObject(rdb)) == NULL) return NULL;
         o = tryObjectEncoding(o);
-    } else if (rdbtype == REDIS_RDB_TYPE_LIST) {
+    } else if (rdbtype == RDB_TYPE_LIST) {
         /* Read list value */
-        if ((len = rdbLoadLen(rdb,NULL)) == REDIS_RDB_LENERR) return NULL;
+        if ((len = rdbLoadLen(rdb,NULL)) == RDB_LENERR) return NULL;
 
         o = createQuicklistObject();
         quicklistSetOptions(o->ptr, server.list_max_ziplist_size,
@@ -958,9 +958,9 @@ robj *rdbLoadObject(int rdbtype, rio *rdb) {
             decrRefCount(dec);
             decrRefCount(ele);
         }
-    } else if (rdbtype == REDIS_RDB_TYPE_SET) {
+    } else if (rdbtype == RDB_TYPE_SET) {
         /* Read list/set value */
-        if ((len = rdbLoadLen(rdb,NULL)) == REDIS_RDB_LENERR) return NULL;
+        if ((len = rdbLoadLen(rdb,NULL)) == RDB_LENERR) return NULL;
 
         /* Use a regular set when there are too many entries. */
         if (len > server.set_max_intset_entries) {
@@ -997,13 +997,13 @@ robj *rdbLoadObject(int rdbtype, rio *rdb) {
                 decrRefCount(ele);
             }
         }
-    } else if (rdbtype == REDIS_RDB_TYPE_ZSET) {
+    } else if (rdbtype == RDB_TYPE_ZSET) {
         /* Read list/set value */
         size_t zsetlen;
         size_t maxelelen = 0;
         zset *zs;
 
-        if ((zsetlen = rdbLoadLen(rdb,NULL)) == REDIS_RDB_LENERR) return NULL;
+        if ((zsetlen = rdbLoadLen(rdb,NULL)) == RDB_LENERR) return NULL;
         o = createZsetObject();
         zs = o->ptr;
 
@@ -1030,12 +1030,12 @@ robj *rdbLoadObject(int rdbtype, rio *rdb) {
         if (zsetLength(o) <= server.zset_max_ziplist_entries &&
             maxelelen <= server.zset_max_ziplist_value)
                 zsetConvert(o,OBJ_ENCODING_ZIPLIST);
-    } else if (rdbtype == REDIS_RDB_TYPE_HASH) {
+    } else if (rdbtype == RDB_TYPE_HASH) {
         size_t len;
         int ret;
 
         len = rdbLoadLen(rdb, NULL);
-        if (len == REDIS_RDB_LENERR) return NULL;
+        if (len == RDB_LENERR) return NULL;
 
         o = createHashObject();
 
@@ -1095,8 +1095,8 @@ robj *rdbLoadObject(int rdbtype, rio *rdb) {
 
         /* All pairs should be read by now */
         serverAssert(len == 0);
-    } else if (rdbtype == REDIS_RDB_TYPE_LIST_QUICKLIST) {
-        if ((len = rdbLoadLen(rdb,NULL)) == REDIS_RDB_LENERR) return NULL;
+    } else if (rdbtype == RDB_TYPE_LIST_QUICKLIST) {
+        if ((len = rdbLoadLen(rdb,NULL)) == RDB_LENERR) return NULL;
         o = createQuicklistObject();
         quicklistSetOptions(o->ptr, server.list_max_ziplist_size,
                             server.list_compress_depth);
@@ -1106,11 +1106,11 @@ robj *rdbLoadObject(int rdbtype, rio *rdb) {
             if (zl == NULL) return NULL;
             quicklistAppendZiplist(o->ptr, zl);
         }
-    } else if (rdbtype == REDIS_RDB_TYPE_HASH_ZIPMAP  ||
-               rdbtype == REDIS_RDB_TYPE_LIST_ZIPLIST ||
-               rdbtype == REDIS_RDB_TYPE_SET_INTSET   ||
-               rdbtype == REDIS_RDB_TYPE_ZSET_ZIPLIST ||
-               rdbtype == REDIS_RDB_TYPE_HASH_ZIPLIST)
+    } else if (rdbtype == RDB_TYPE_HASH_ZIPMAP  ||
+               rdbtype == RDB_TYPE_LIST_ZIPLIST ||
+               rdbtype == RDB_TYPE_SET_INTSET   ||
+               rdbtype == RDB_TYPE_ZSET_ZIPLIST ||
+               rdbtype == RDB_TYPE_HASH_ZIPLIST)
     {
         unsigned char *encoded = rdbGenericLoadStringObject(rdb,RDB_LOAD_PLAIN);
         if (encoded == NULL) return NULL;
@@ -1123,7 +1123,7 @@ robj *rdbLoadObject(int rdbtype, rio *rdb) {
          * size as this is an O(N) scan. Eventually everything will get
          * converted. */
         switch(rdbtype) {
-            case REDIS_RDB_TYPE_HASH_ZIPMAP:
+            case RDB_TYPE_HASH_ZIPMAP:
                 /* Convert to ziplist encoded hash. This must be deprecated
                  * when loading dumps created by Redis 2.4 gets deprecated. */
                 {
@@ -1152,24 +1152,24 @@ robj *rdbLoadObject(int rdbtype, rio *rdb) {
                     }
                 }
                 break;
-            case REDIS_RDB_TYPE_LIST_ZIPLIST:
+            case RDB_TYPE_LIST_ZIPLIST:
                 o->type = OBJ_LIST;
                 o->encoding = OBJ_ENCODING_ZIPLIST;
                 listTypeConvert(o,OBJ_ENCODING_QUICKLIST);
                 break;
-            case REDIS_RDB_TYPE_SET_INTSET:
+            case RDB_TYPE_SET_INTSET:
                 o->type = OBJ_SET;
                 o->encoding = OBJ_ENCODING_INTSET;
                 if (intsetLen(o->ptr) > server.set_max_intset_entries)
                     setTypeConvert(o,OBJ_ENCODING_HT);
                 break;
-            case REDIS_RDB_TYPE_ZSET_ZIPLIST:
+            case RDB_TYPE_ZSET_ZIPLIST:
                 o->type = OBJ_ZSET;
                 o->encoding = OBJ_ENCODING_ZIPLIST;
                 if (zsetLength(o) > server.zset_max_ziplist_entries)
                     zsetConvert(o,OBJ_ENCODING_SKIPLIST);
                 break;
-            case REDIS_RDB_TYPE_HASH_ZIPLIST:
+            case RDB_TYPE_HASH_ZIPLIST:
                 o->type = OBJ_HASH;
                 o->encoding = OBJ_ENCODING_ZIPLIST;
                 if (hashTypeLength(o) > server.hash_max_ziplist_entries)
@@ -1225,7 +1225,7 @@ void rdbLoadProgressCallback(rio *r, const void *buf, size_t len) {
          * our cached time since it is used to create and update the last
          * interaction time with clients and for other important things. */
         updateCachedTime();
-        if (server.masterhost && server.repl_state == REDIS_REPL_TRANSFER)
+        if (server.masterhost && server.repl_state == REPL_STATE_TRANSFER)
             replicationSendNewlineToMaster();
         loadingProgress(r->processed_bytes);
         processEventsWhileBlocked();
@@ -1250,14 +1250,14 @@ int rdbLoad(char *filename) {
     buf[9] = '\0';
     if (memcmp(buf,"REDIS",5) != 0) {
         fclose(fp);
-        serverLog(REDIS_WARNING,"Wrong signature trying to load DB from file");
+        serverLog(LL_WARNING,"Wrong signature trying to load DB from file");
         errno = EINVAL;
         return C_ERR;
     }
     rdbver = atoi(buf+5);
-    if (rdbver < 1 || rdbver > REDIS_RDB_VERSION) {
+    if (rdbver < 1 || rdbver > RDB_VERSION) {
         fclose(fp);
-        serverLog(REDIS_WARNING,"Can't handle RDB format version %d",rdbver);
+        serverLog(LL_WARNING,"Can't handle RDB format version %d",rdbver);
         errno = EINVAL;
         return C_ERR;
     }
@@ -1271,7 +1271,7 @@ int rdbLoad(char *filename) {
         if ((type = rdbLoadType(&rdb)) == -1) goto eoferr;
 
         /* Handle special types. */
-        if (type == REDIS_RDB_OPCODE_EXPIRETIME) {
+        if (type == RDB_OPCODE_EXPIRETIME) {
             /* EXPIRETIME: load an expire associated with the next key
              * to load. Note that after loading an expire we need to
              * load the actual type, and continue. */
@@ -1281,40 +1281,40 @@ int rdbLoad(char *filename) {
             /* the EXPIRETIME opcode specifies time in seconds, so convert
              * into milliseconds. */
             expiretime *= 1000;
-        } else if (type == REDIS_RDB_OPCODE_EXPIRETIME_MS) {
+        } else if (type == RDB_OPCODE_EXPIRETIME_MS) {
             /* EXPIRETIME_MS: milliseconds precision expire times introduced
              * with RDB v3. Like EXPIRETIME but no with more precision. */
             if ((expiretime = rdbLoadMillisecondTime(&rdb)) == -1) goto eoferr;
             /* We read the time so we need to read the object type again. */
             if ((type = rdbLoadType(&rdb)) == -1) goto eoferr;
-        } else if (type == REDIS_RDB_OPCODE_EOF) {
+        } else if (type == RDB_OPCODE_EOF) {
             /* EOF: End of file, exit the main loop. */
             break;
-        } else if (type == REDIS_RDB_OPCODE_SELECTDB) {
+        } else if (type == RDB_OPCODE_SELECTDB) {
             /* SELECTDB: Select the specified database. */
-            if ((dbid = rdbLoadLen(&rdb,NULL)) == REDIS_RDB_LENERR)
+            if ((dbid = rdbLoadLen(&rdb,NULL)) == RDB_LENERR)
                 goto eoferr;
             if (dbid >= (unsigned)server.dbnum) {
-                serverLog(REDIS_WARNING,
+                serverLog(LL_WARNING,
                     "FATAL: Data file was created with a Redis "
                     "server configured to handle more than %d "
                     "databases. Exiting\n", server.dbnum);
                 exit(1);
             }
             db = server.db+dbid;
             continue; /* Read type again. */
-        } else if (type == REDIS_RDB_OPCODE_RESIZEDB) {
+        } else if (type == RDB_OPCODE_RESIZEDB) {
             /* RESIZEDB: Hint about the size of the keys in the currently
              * selected data base, in order to avoid useless rehashing. */
             uint32_t db_size, expires_size;
-            if ((db_size = rdbLoadLen(&rdb,NULL)) == REDIS_RDB_LENERR)
+            if ((db_size = rdbLoadLen(&rdb,NULL)) == RDB_LENERR)
                 goto eoferr;
-            if ((expires_size = rdbLoadLen(&rdb,NULL)) == REDIS_RDB_LENERR)
+            if ((expires_size = rdbLoadLen(&rdb,NULL)) == RDB_LENERR)
                 goto eoferr;
             dictExpand(db->dict,db_size);
             dictExpand(db->expires,expires_size);
             continue; /* Read type again. */
-        } else if (type == REDIS_RDB_OPCODE_AUX) {
+        } else if (type == RDB_OPCODE_AUX) {
             /* AUX: generic string-string fields. Use to add state to RDB
              * which is backward compatible. Implementations of RDB loading
              * are requierd to skip AUX fields they don't understand.
@@ -1328,13 +1328,13 @@ int rdbLoad(char *filename) {
                 /* All the fields with a name staring with '%' are considered
                  * information fields and are logged at startup with a log
                  * level of NOTICE. */
-                serverLog(REDIS_NOTICE,"RDB '%s': %s",
+                serverLog(LL_NOTICE,"RDB '%s': %s",
                     (char*)auxkey->ptr,
                     (char*)auxval->ptr);
             } else {
                 /* We ignore fields we don't understand, as by AUX field
                  * contract. */
-                serverLog(REDIS_DEBUG,"Unrecognized RDB AUX field: '%s'",
+                serverLog(LL_DEBUG,"Unrecognized RDB AUX field: '%s'",
                     (char*)auxkey->ptr);
             }
 
@@ -1372,9 +1372,9 @@ int rdbLoad(char *filename) {
         if (rioRead(&rdb,&cksum,8) == 0) goto eoferr;
         memrev64ifbe(&cksum);
         if (cksum == 0) {
-            serverLog(REDIS_WARNING,"RDB file was saved with checksum disabled: no check performed.");
+            serverLog(LL_WARNING,"RDB file was saved with checksum disabled: no check performed.");
         } else if (cksum != expected) {
-            serverLog(REDIS_WARNING,"Wrong RDB checksum. Aborting now.");
+            serverLog(LL_WARNING,"Wrong RDB checksum. Aborting now.");
             rdbExitReportCorruptRDB("RDB CRC error");
         }
     }
@@ -1384,7 +1384,7 @@ int rdbLoad(char *filename) {
     return C_OK;
 
 eoferr: /* unexpected end of file is handled here with a fatal exit */
-    serverLog(REDIS_WARNING,"Short read or OOM loading DB. Unrecoverable error, aborting now.");
+    serverLog(LL_WARNING,"Short read or OOM loading DB. Unrecoverable error, aborting now.");
     rdbExitReportCorruptRDB("Unexpected EOF reading RDB file");
     return C_ERR; /* Just to avoid warning */
 }
@@ -1393,18 +1393,18 @@ int rdbLoad(char *filename) {
  * This function covers the case of actual BGSAVEs. */
 void backgroundSaveDoneHandlerDisk(int exitcode, int bysignal) {
     if (!bysignal && exitcode == 0) {
-        serverLog(REDIS_NOTICE,
+        serverLog(LL_NOTICE,
             "Background saving terminated with success");
         server.dirty = server.dirty - server.dirty_before_bgsave;
         server.lastsave = time(NULL);
         server.lastbgsave_status = C_OK;
     } else if (!bysignal && exitcode != 0) {
-        serverLog(REDIS_WARNING, "Background saving error");
+        serverLog(LL_WARNING, "Background saving error");
         server.lastbgsave_status = C_ERR;
     } else {
         mstime_t latency;
 
-        serverLog(REDIS_WARNING,
+        serverLog(LL_WARNING,
             "Background saving terminated by signal %d", bysignal);
         latencyStartMonitor(latency);
         rdbRemoveTempFile(server.rdb_child_pid);
@@ -1416,12 +1416,12 @@ void backgroundSaveDoneHandlerDisk(int exitcode, int bysignal) {
             server.lastbgsave_status = C_ERR;
     }
     server.rdb_child_pid = -1;
-    server.rdb_child_type = REDIS_RDB_CHILD_TYPE_NONE;
+    server.rdb_child_type = RDB_CHILD_TYPE_NONE;
     server.rdb_save_time_last = time(NULL)-server.rdb_save_time_start;
     server.rdb_save_time_start = -1;
     /* Possibly there are slaves waiting for a BGSAVE in order to be served
      * (the first stage of SYNC is a bulk transfer of dump.rdb) */
-    updateSlavesWaitingBgsave((!bysignal && exitcode == 0) ? C_OK : C_ERR, REDIS_RDB_CHILD_TYPE_DISK);
+    updateSlavesWaitingBgsave((!bysignal && exitcode == 0) ? C_OK : C_ERR, RDB_CHILD_TYPE_DISK);
 }
 
 /* A background saving child (BGSAVE) terminated its work. Handle this.
@@ -1431,16 +1431,16 @@ void backgroundSaveDoneHandlerSocket(int exitcode, int bysignal) {
     uint64_t *ok_slaves;
 
     if (!bysignal && exitcode == 0) {
-        serverLog(REDIS_NOTICE,
+        serverLog(LL_NOTICE,
             "Background RDB transfer terminated with success");
     } else if (!bysignal && exitcode != 0) {
-        serverLog(REDIS_WARNING, "Background transfer error");
+        serverLog(LL_WARNING, "Background transfer error");
     } else {
-        serverLog(REDIS_WARNING,
+        serverLog(LL_WARNING,
             "Background transfer terminated by signal %d", bysignal);
     }
     server.rdb_child_pid = -1;
-    server.rdb_child_type = REDIS_RDB_CHILD_TYPE_NONE;
+    server.rdb_child_type = RDB_CHILD_TYPE_NONE;
     server.rdb_save_time_start = -1;
 
     /* If the child returns an OK exit code, read the set of slave client
@@ -1484,7 +1484,7 @@ void backgroundSaveDoneHandlerSocket(int exitcode, int bysignal) {
     while((ln = listNext(&li))) {
         client *slave = ln->value;
 
-        if (slave->replstate == REDIS_REPL_WAIT_BGSAVE_END) {
+        if (slave->replstate == SLAVE_STATE_WAIT_BGSAVE_END) {
             uint64_t j;
             int errorcode = 0;
 
@@ -1498,14 +1498,14 @@ void backgroundSaveDoneHandlerSocket(int exitcode, int bysignal) {
                 }
             }
             if (j == ok_slaves[0] || errorcode != 0) {
-                serverLog(REDIS_WARNING,
+                serverLog(LL_WARNING,
                 "Closing slave %s: child->slave RDB transfer failed: %s",
                     replicationGetSlaveName(slave),
                     (errorcode == 0) ? "RDB transfer child aborted"
                                      : strerror(errorcode));
                 freeClient(slave);
             } else {
-                serverLog(REDIS_WARNING,
+                serverLog(LL_WARNING,
                 "Slave %s correctly received the streamed RDB file.",
                     replicationGetSlaveName(slave));
                 /* Restore the socket as non-blocking. */
@@ -1516,26 +1516,26 @@ void backgroundSaveDoneHandlerSocket(int exitcode, int bysignal) {
     }
     zfree(ok_slaves);
 
-    updateSlavesWaitingBgsave((!bysignal && exitcode == 0) ? C_OK : C_ERR, REDIS_RDB_CHILD_TYPE_SOCKET);
+    updateSlavesWaitingBgsave((!bysignal && exitcode == 0) ? C_OK : C_ERR, RDB_CHILD_TYPE_SOCKET);
 }
 
 /* When a background RDB saving/transfer terminates, call the right handler. */
 void backgroundSaveDoneHandler(int exitcode, int bysignal) {
     switch(server.rdb_child_type) {
-    case REDIS_RDB_CHILD_TYPE_DISK:
+    case RDB_CHILD_TYPE_DISK:
         backgroundSaveDoneHandlerDisk(exitcode,bysignal);
         break;
-    case REDIS_RDB_CHILD_TYPE_SOCKET:
+    case RDB_CHILD_TYPE_SOCKET:
         backgroundSaveDoneHandlerSocket(exitcode,bysignal);
         break;
     default:
-        redisPanic("Unknown RDB child type.");
+        serverPanic("Unknown RDB child type.");
         break;
     }
 }
 
 /* Spawn an RDB child that writes the RDB to the sockets of the slaves
- * that are currently in REDIS_REPL_WAIT_BGSAVE_START state. */
+ * that are currently in SLAVE_STATE_WAIT_BGSAVE_START state. */
 int rdbSaveToSlavesSockets(void) {
     int *fds;
     uint64_t *clientids;
@@ -1568,10 +1568,10 @@ int rdbSaveToSlavesSockets(void) {
     while((ln = listNext(&li))) {
         client *slave = ln->value;
 
-        if (slave->replstate == REDIS_REPL_WAIT_BGSAVE_START) {
+        if (slave->replstate == SLAVE_STATE_WAIT_BGSAVE_START) {
             clientids[numfds] = slave->id;
             fds[numfds++] = slave->fd;
-            slave->replstate = REDIS_REPL_WAIT_BGSAVE_END;
+            slave->replstate = SLAVE_STATE_WAIT_BGSAVE_END;
             /* Put the socket in non-blocking mode to simplify RDB transfer.
              * We'll restore it when the children returns (since duped socket
              * will share the O_NONBLOCK attribute with the parent). */
@@ -1601,7 +1601,7 @@ int rdbSaveToSlavesSockets(void) {
             size_t private_dirty = zmalloc_get_private_dirty();
 
             if (private_dirty) {
-                serverLog(REDIS_NOTICE,
+                serverLog(LL_NOTICE,
                     "RDB: %zu MB of memory used by copy-on-write",
                     private_dirty/(1024*1024));
             }
@@ -1654,17 +1654,17 @@ int rdbSaveToSlavesSockets(void) {
         server.stat_fork_rate = (double) zmalloc_used_memory() * 1000000 / server.stat_fork_time / (1024*1024*1024); /* GB per second. */
         latencyAddSampleIfNeeded("fork",server.stat_fork_time/1000);
         if (childpid == -1) {
-            serverLog(REDIS_WARNING,"Can't save in background: fork: %s",
+            serverLog(LL_WARNING,"Can't save in background: fork: %s",
                 strerror(errno));
             zfree(fds);
             close(pipefds[0]);
             close(pipefds[1]);
             return C_ERR;
         }
-        serverLog(REDIS_NOTICE,"Background RDB transfer started by pid %d",childpid);
+        serverLog(LL_NOTICE,"Background RDB transfer started by pid %d",childpid);
         server.rdb_save_time_start = time(NULL);
         server.rdb_child_pid = childpid;
-        server.rdb_child_type = REDIS_RDB_CHILD_TYPE_SOCKET;
+        server.rdb_child_type = RDB_CHILD_TYPE_SOCKET;
         updateDictResizePolicy();
         zfree(fds);
         return C_OK;