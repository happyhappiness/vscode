@@ -41,7 +41,7 @@
 #include "crc64.h"
 
 #define ERROR(...) { \
-    serverLog(REDIS_WARNING, __VA_ARGS__); \
+    serverLog(LL_WARNING, __VA_ARGS__); \
     exit(1); \
 }
 
@@ -88,9 +88,9 @@ static int rdbCheckType(unsigned char t) {
     /* In case a new object type is added, update the following
      * condition as necessary. */
     return
-        (t >= REDIS_RDB_TYPE_HASH_ZIPMAP && t <= REDIS_RDB_TYPE_HASH_ZIPLIST) ||
-        t <= REDIS_RDB_TYPE_HASH ||
-        t >= REDIS_RDB_OPCODE_EXPIRETIME_MS;
+        (t >= RDB_TYPE_HASH_ZIPMAP && t <= RDB_TYPE_HASH_ZIPLIST) ||
+        t <= RDB_TYPE_HASH ||
+        t >= RDB_OPCODE_EXPIRETIME_MS;
 }
 
 /* when number of bytes to read is negative, do a peek */
@@ -159,7 +159,7 @@ static int peekType() {
 static int processTime(int type) {
     uint32_t offset = CURR_OFFSET;
     unsigned char t[8];
-    int timelen = (type == REDIS_RDB_OPCODE_EXPIRETIME_MS) ? 8 : 4;
+    int timelen = (type == RDB_OPCODE_EXPIRETIME_MS) ? 8 : 4;
 
     if (readBytes(t,timelen)) {
         return 1;
@@ -177,22 +177,22 @@ static uint32_t loadLength(int *isencoded) {
     int type;
 
     if (isencoded) *isencoded = 0;
-    if (!readBytes(buf, 1)) return REDIS_RDB_LENERR;
+    if (!readBytes(buf, 1)) return RDB_LENERR;
     type = (buf[0] & 0xC0) >> 6;
-    if (type == REDIS_RDB_6BITLEN) {
+    if (type == RDB_6BITLEN) {
         /* Read a 6 bit len */
         return buf[0] & 0x3F;
-    } else if (type == REDIS_RDB_ENCVAL) {
+    } else if (type == RDB_ENCVAL) {
         /* Read a 6 bit len encoding type */
         if (isencoded) *isencoded = 1;
         return buf[0] & 0x3F;
-    } else if (type == REDIS_RDB_14BITLEN) {
+    } else if (type == RDB_14BITLEN) {
         /* Read a 14 bit len */
-        if (!readBytes(buf+1,1)) return REDIS_RDB_LENERR;
+        if (!readBytes(buf+1,1)) return RDB_LENERR;
         return ((buf[0] & 0x3F) << 8) | buf[1];
     } else {
         /* Read a 32 bit len */
-        if (!readBytes(&len, 4)) return REDIS_RDB_LENERR;
+        if (!readBytes(&len, 4)) return RDB_LENERR;
         return (unsigned int)ntohl(len);
     }
 }
@@ -202,17 +202,17 @@ static char *loadIntegerObject(int enctype) {
     unsigned char enc[4];
     long long val;
 
-    if (enctype == REDIS_RDB_ENC_INT8) {
+    if (enctype == RDB_ENC_INT8) {
         uint8_t v;
         if (!readBytes(enc, 1)) return NULL;
         v = enc[0];
         val = (int8_t)v;
-    } else if (enctype == REDIS_RDB_ENC_INT16) {
+    } else if (enctype == RDB_ENC_INT16) {
         uint16_t v;
         if (!readBytes(enc, 2)) return NULL;
         v = enc[0]|(enc[1]<<8);
         val = (int16_t)v;
-    } else if (enctype == REDIS_RDB_ENC_INT32) {
+    } else if (enctype == RDB_ENC_INT32) {
         uint32_t v;
         if (!readBytes(enc, 4)) return NULL;
         v = enc[0]|(enc[1]<<8)|(enc[2]<<16)|(enc[3]<<24);
@@ -233,8 +233,8 @@ static char* loadLzfStringObject() {
     unsigned int slen, clen;
     char *c, *s;
 
-    if ((clen = loadLength(NULL)) == REDIS_RDB_LENERR) return NULL;
-    if ((slen = loadLength(NULL)) == REDIS_RDB_LENERR) return NULL;
+    if ((clen = loadLength(NULL)) == RDB_LENERR) return NULL;
+    if ((slen = loadLength(NULL)) == RDB_LENERR) return NULL;
 
     c = zmalloc(clen);
     if (!readBytes(c, clen)) {
@@ -261,11 +261,11 @@ static char* loadStringObject() {
     len = loadLength(&isencoded);
     if (isencoded) {
         switch(len) {
-        case REDIS_RDB_ENC_INT8:
-        case REDIS_RDB_ENC_INT16:
-        case REDIS_RDB_ENC_INT32:
+        case RDB_ENC_INT8:
+        case RDB_ENC_INT16:
+        case RDB_ENC_INT32:
             return loadIntegerObject(len);
-        case REDIS_RDB_ENC_LZF:
+        case RDB_ENC_LZF:
             return loadLzfStringObject();
         default:
             /* unknown encoding */
@@ -274,7 +274,7 @@ static char* loadStringObject() {
         }
     }
 
-    if (len == REDIS_RDB_LENERR) return NULL;
+    if (len == RDB_LENERR) return NULL;
 
     char *buf = zmalloc(sizeof(char) * (len+1));
     if (buf == NULL) return NULL;
@@ -357,30 +357,30 @@ static int loadPair(entry *e) {
     }
 
     uint32_t length = 0;
-    if (e->type == REDIS_RDB_TYPE_LIST ||
-        e->type == REDIS_RDB_TYPE_SET  ||
-        e->type == REDIS_RDB_TYPE_ZSET ||
-        e->type == REDIS_RDB_TYPE_HASH) {
-        if ((length = loadLength(NULL)) == REDIS_RDB_LENERR) {
+    if (e->type == RDB_TYPE_LIST ||
+        e->type == RDB_TYPE_SET  ||
+        e->type == RDB_TYPE_ZSET ||
+        e->type == RDB_TYPE_HASH) {
+        if ((length = loadLength(NULL)) == RDB_LENERR) {
             SHIFT_ERROR(offset, "Error reading %s length", types[e->type]);
             return 0;
         }
     }
 
     switch(e->type) {
-    case REDIS_RDB_TYPE_STRING:
-    case REDIS_RDB_TYPE_HASH_ZIPMAP:
-    case REDIS_RDB_TYPE_LIST_ZIPLIST:
-    case REDIS_RDB_TYPE_SET_INTSET:
-    case REDIS_RDB_TYPE_ZSET_ZIPLIST:
-    case REDIS_RDB_TYPE_HASH_ZIPLIST:
+    case RDB_TYPE_STRING:
+    case RDB_TYPE_HASH_ZIPMAP:
+    case RDB_TYPE_LIST_ZIPLIST:
+    case RDB_TYPE_SET_INTSET:
+    case RDB_TYPE_ZSET_ZIPLIST:
+    case RDB_TYPE_HASH_ZIPLIST:
         if (!processStringObject(NULL)) {
             SHIFT_ERROR(offset, "Error reading entry value");
             return 0;
         }
     break;
-    case REDIS_RDB_TYPE_LIST:
-    case REDIS_RDB_TYPE_SET:
+    case RDB_TYPE_LIST:
+    case RDB_TYPE_SET:
         for (i = 0; i < length; i++) {
             offset = CURR_OFFSET;
             if (!processStringObject(NULL)) {
@@ -389,7 +389,7 @@ static int loadPair(entry *e) {
             }
         }
     break;
-    case REDIS_RDB_TYPE_ZSET:
+    case RDB_TYPE_ZSET:
         for (i = 0; i < length; i++) {
             offset = CURR_OFFSET;
             if (!processStringObject(NULL)) {
@@ -403,7 +403,7 @@ static int loadPair(entry *e) {
             }
         }
     break;
-    case REDIS_RDB_TYPE_HASH:
+    case RDB_TYPE_HASH:
         for (i = 0; i < length; i++) {
             offset = CURR_OFFSET;
             if (!processStringObject(NULL)) {
@@ -439,16 +439,16 @@ static entry loadEntry() {
     }
 
     offset[1] = CURR_OFFSET;
-    if (e.type == REDIS_RDB_OPCODE_SELECTDB) {
-        if ((length = loadLength(NULL)) == REDIS_RDB_LENERR) {
+    if (e.type == RDB_OPCODE_SELECTDB) {
+        if ((length = loadLength(NULL)) == RDB_LENERR) {
             SHIFT_ERROR(offset[1], "Error reading database number");
             return e;
         }
         if (length > 63) {
             SHIFT_ERROR(offset[1], "Database number out of range (%d)", length);
             return e;
         }
-    } else if (e.type == REDIS_RDB_OPCODE_EOF) {
+    } else if (e.type == RDB_OPCODE_EOF) {
         if (positions[level].offset < positions[level].size) {
             SHIFT_ERROR(offset[0], "Unexpected EOF");
         } else {
@@ -457,8 +457,8 @@ static entry loadEntry() {
         return e;
     } else {
         /* optionally consume expire */
-        if (e.type == REDIS_RDB_OPCODE_EXPIRETIME ||
-            e.type == REDIS_RDB_OPCODE_EXPIRETIME_MS) {
+        if (e.type == RDB_OPCODE_EXPIRETIME ||
+            e.type == RDB_OPCODE_EXPIRETIME_MS) {
             if (!processTime(e.type)) return e;
             if (!loadType(&e)) return e;
         }
@@ -491,7 +491,7 @@ static void printCentered(int indent, int width, char* body) {
 
     memset(head, '=', indent);
     memset(tail, '=', width - 2 - indent - strlen(body));
-    serverLog(REDIS_WARNING, "%s %s %s", head, body, tail);
+    serverLog(LL_WARNING, "%s %s %s", head, body, tail);
 }
 
 static void printValid(uint64_t ops, uint64_t bytes) {
@@ -538,7 +538,7 @@ static void printErrorStack(entry *e) {
 
     /* display error stack */
     for (i = 0; i < errors.level; i++) {
-        serverLog(REDIS_WARNING, "0x%08lx - %s",
+        serverLog(LL_WARNING, "0x%08lx - %s",
             (unsigned long) errors.offset[i], errors.error[i]);
     }
 }
@@ -551,7 +551,7 @@ void process(void) {
     /* Exclude the final checksum for RDB >= 5. Will be checked at the end. */
     if (dump_version >= 5) {
         if (positions[0].size < 8) {
-            serverLog(REDIS_WARNING, "RDB version >= 5 but no room for checksum.");
+            serverLog(LL_WARNING, "RDB version >= 5 but no room for checksum.");
             exit(1);
         }
         positions[0].size -= 8;
@@ -608,7 +608,7 @@ void process(void) {
     printValid(num_valid_ops, num_valid_bytes);
 
     /* expect an eof */
-    if (entry.type != REDIS_RDB_OPCODE_EOF) {
+    if (entry.type != RDB_OPCODE_EOF) {
         /* last byte should be EOF, add error */
         errors.level = 0;
         SHIFT_ERROR(positions[0].offset, "Expected EOF, got %s", types[entry.type]);
@@ -636,13 +636,13 @@ void process(void) {
         if (crc != crc2) {
             SHIFT_ERROR(positions[0].offset, "RDB CRC64 does not match.");
         } else {
-            serverLog(REDIS_WARNING, "CRC64 checksum is OK");
+            serverLog(LL_WARNING, "CRC64 checksum is OK");
         }
     }
 
     /* print summary on errors */
     if (num_errors) {
-        serverLog(REDIS_WARNING, "Total unprocessable opcodes: %llu",
+        serverLog(LL_WARNING, "Total unprocessable opcodes: %llu",
             (unsigned long long) num_errors);
     }
 }
@@ -679,16 +679,16 @@ int redis_check_rdb(char *rdbfilename) {
     errors.level = 0;
 
     /* Object types */
-    sprintf(types[REDIS_RDB_TYPE_STRING], "STRING");
-    sprintf(types[REDIS_RDB_TYPE_LIST], "LIST");
-    sprintf(types[REDIS_RDB_TYPE_SET], "SET");
-    sprintf(types[REDIS_RDB_TYPE_ZSET], "ZSET");
-    sprintf(types[REDIS_RDB_TYPE_HASH], "HASH");
+    sprintf(types[RDB_TYPE_STRING], "STRING");
+    sprintf(types[RDB_TYPE_LIST], "LIST");
+    sprintf(types[RDB_TYPE_SET], "SET");
+    sprintf(types[RDB_TYPE_ZSET], "ZSET");
+    sprintf(types[RDB_TYPE_HASH], "HASH");
 
     /* Object types only used for dumping to disk */
-    sprintf(types[REDIS_RDB_OPCODE_EXPIRETIME], "EXPIRETIME");
-    sprintf(types[REDIS_RDB_OPCODE_SELECTDB], "SELECTDB");
-    sprintf(types[REDIS_RDB_OPCODE_EOF], "EOF");
+    sprintf(types[RDB_OPCODE_EXPIRETIME], "EXPIRETIME");
+    sprintf(types[RDB_OPCODE_SELECTDB], "SELECTDB");
+    sprintf(types[RDB_OPCODE_EOF], "EOF");
 
     process();
 
@@ -704,7 +704,7 @@ int redis_check_rdb_main(char **argv, int argc) {
         fprintf(stderr, "Usage: %s <rdb-file-name>\n", argv[0]);
         exit(1);
     }
-    serverLog(REDIS_WARNING, "Checking RDB file %s", argv[1]);
+    serverLog(LL_WARNING, "Checking RDB file %s", argv[1]);
     exit(redis_check_rdb(argv[1]));
     return 0;
 }