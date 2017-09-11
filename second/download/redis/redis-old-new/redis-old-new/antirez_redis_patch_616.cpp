@@ -29,74 +29,19 @@
  */
 
 
+#include "redis.h"
+#include "rdb.h"
 #include <stdlib.h>
 #include <stdio.h>
 #include <unistd.h>
 #include <fcntl.h>
 #include <sys/stat.h>
 #include <sys/mman.h>
-#include <string.h>
-#include <arpa/inet.h>
-#include <stdint.h>
-#include <limits.h>
 #include "lzf.h"
 #include "crc64.h"
 
-/* Object types */
-#define REDIS_STRING 0
-#define REDIS_LIST 1
-#define REDIS_SET 2
-#define REDIS_ZSET 3
-#define REDIS_HASH 4
-#define REDIS_HASH_ZIPMAP 9
-#define REDIS_LIST_ZIPLIST 10
-#define REDIS_SET_INTSET 11
-#define REDIS_ZSET_ZIPLIST 12
-#define REDIS_HASH_ZIPLIST 13
-
-/* Objects encoding. Some kind of objects like Strings and Hashes can be
- * internally represented in multiple ways. The 'encoding' field of the object
- * is set to one of this fields for this object. */
-#define REDIS_ENCODING_RAW 0    /* Raw representation */
-#define REDIS_ENCODING_INT 1    /* Encoded as integer */
-#define REDIS_ENCODING_ZIPMAP 2 /* Encoded as zipmap */
-#define REDIS_ENCODING_HT 3     /* Encoded as a hash table */
-
-/* Object types only used for dumping to disk */
-#define REDIS_EXPIRETIME_MS 252
-#define REDIS_EXPIRETIME 253
-#define REDIS_SELECTDB 254
-#define REDIS_EOF 255
-
-/* Defines related to the dump file format. To store 32 bits lengths for short
- * keys requires a lot of space, so we check the most significant 2 bits of
- * the first byte to interpreter the length:
- *
- * 00|000000 => if the two MSB are 00 the len is the 6 bits of this byte
- * 01|000000 00000000 =>  01, the len is 14 byes, 6 bits + 8 bits of next byte
- * 10|000000 [32 bit integer] => if it's 01, a full 32 bit len will follow
- * 11|000000 this means: specially encoded object will follow. The six bits
- *           number specify the kind of object that follows.
- *           See the REDIS_RDB_ENC_* defines.
- *
- * Lengths up to 63 are stored using a single byte, most DB keys, and may
- * values, will fit inside. */
-#define REDIS_RDB_6BITLEN 0
-#define REDIS_RDB_14BITLEN 1
-#define REDIS_RDB_32BITLEN 2
-#define REDIS_RDB_ENCVAL 3
-#define REDIS_RDB_LENERR UINT_MAX
-
-/* When a length of a string object stored on disk has the first two bits
- * set, the remaining two bits specify a special encoding for the object
- * accordingly to the following defines: */
-#define REDIS_RDB_ENC_INT8 0        /* 8 bit signed integer */
-#define REDIS_RDB_ENC_INT16 1       /* 16 bit signed integer */
-#define REDIS_RDB_ENC_INT32 2       /* 32 bit signed integer */
-#define REDIS_RDB_ENC_LZF 3         /* string compressed with FASTLZ */
-
 #define ERROR(...) { \
-    printf(__VA_ARGS__); \
+    redisLog(REDIS_WARNING, __VA_ARGS__); \
     exit(1); \
 }
 
@@ -139,13 +84,13 @@ typedef struct {
 static char types[MAX_TYPES_NUM][MAX_TYPE_NAME_LEN];
 
 /* Return true if 't' is a valid object type. */
-static int checkType(unsigned char t) {
+static int rdbCheckType(unsigned char t) {
     /* In case a new object type is added, update the following
      * condition as necessary. */
     return
-        (t >= REDIS_HASH_ZIPMAP && t <= REDIS_HASH_ZIPLIST) ||
-        t <= REDIS_HASH ||
-        t >= REDIS_EXPIRETIME_MS;
+        (t >= REDIS_RDB_TYPE_HASH_ZIPMAP && t <= REDIS_RDB_TYPE_HASH_ZIPLIST) ||
+        t <= REDIS_RDB_TYPE_HASH ||
+        t >= REDIS_RDB_OPCODE_EXPIRETIME_MS;
 }
 
 /* when number of bytes to read is negative, do a peek */
@@ -168,17 +113,17 @@ int processHeader(void) {
     int dump_version;
 
     if (!readBytes(buf, 9)) {
-        ERROR("Cannot read header\n");
+        ERROR("Cannot read header");
     }
 
     /* expect the first 5 bytes to equal REDIS */
     if (memcmp(buf,"REDIS",5) != 0) {
-        ERROR("Wrong signature in header\n");
+        ERROR("Wrong signature in header");
     }
 
     dump_version = (int)strtol(buf + 5, NULL, 10);
     if (dump_version < 1 || dump_version > 6) {
-        ERROR("Unknown RDB format version: %d\n", dump_version);
+        ERROR("Unknown RDB format version: %d", dump_version);
     }
     return dump_version;
 }
@@ -189,7 +134,7 @@ static int loadType(entry *e) {
     /* this byte needs to qualify as type */
     unsigned char t;
     if (readBytes(&t, 1)) {
-        if (checkType(t)) {
+        if (rdbCheckType(t)) {
             e->type = t;
             return 1;
         } else {
@@ -205,7 +150,7 @@ static int loadType(entry *e) {
 
 static int peekType() {
     unsigned char t;
-    if (readBytes(&t, -1) && (checkType(t)))
+    if (readBytes(&t, -1) && (rdbCheckType(t)))
         return t;
     return -1;
 }
@@ -214,7 +159,7 @@ static int peekType() {
 static int processTime(int type) {
     uint32_t offset = CURR_OFFSET;
     unsigned char t[8];
-    int timelen = (type == REDIS_EXPIRETIME_MS) ? 8 : 4;
+    int timelen = (type == REDIS_RDB_OPCODE_EXPIRETIME_MS) ? 8 : 4;
 
     if (readBytes(t,timelen)) {
         return 1;
@@ -279,7 +224,7 @@ static char *loadIntegerObject(int enctype) {
 
     /* convert val into string */
     char *buf;
-    buf = malloc(sizeof(char) * 128);
+    buf = zmalloc(sizeof(char) * 128);
     sprintf(buf, "%lld", val);
     return buf;
 }
@@ -291,19 +236,19 @@ static char* loadLzfStringObject() {
     if ((clen = loadLength(NULL)) == REDIS_RDB_LENERR) return NULL;
     if ((slen = loadLength(NULL)) == REDIS_RDB_LENERR) return NULL;
 
-    c = malloc(clen);
+    c = zmalloc(clen);
     if (!readBytes(c, clen)) {
-        free(c);
+        zfree(c);
         return NULL;
     }
 
-    s = malloc(slen+1);
+    s = zmalloc(slen+1);
     if (lzf_decompress(c,clen,s,slen) == 0) {
-        free(c); free(s);
+        zfree(c); zfree(s);
         return NULL;
     }
 
-    free(c);
+    zfree(c);
     return s;
 }
 
@@ -335,7 +280,7 @@ static char* loadStringObject() {
     if (buf == NULL) return NULL;
     buf[len] = '\0';
     if (!readBytes(buf, len)) {
-        free(buf);
+        zfree(buf);
         return NULL;
     }
     return buf;
@@ -346,14 +291,14 @@ static int processStringObject(char** store) {
     char *key = loadStringObject();
     if (key == NULL) {
         SHIFT_ERROR(offset, "Error reading string object");
-        free(key);
+        zfree(key);
         return 0;
     }
 
     if (store != NULL) {
         *store = key;
     } else {
-        free(key);
+        zfree(key);
     }
     return 1;
 }
@@ -365,14 +310,14 @@ static double* loadDoubleValue() {
 
     if (!readBytes(&len,1)) return NULL;
 
-    val = malloc(sizeof(double));
+    val = zmalloc(sizeof(double));
     switch(len) {
     case 255: *val = R_NegInf;  return val;
     case 254: *val = R_PosInf;  return val;
     case 253: *val = R_Nan;     return val;
     default:
         if (!readBytes(buf, len)) {
-            free(val);
+            zfree(val);
             return NULL;
         }
         buf[len] = '\0';
@@ -386,14 +331,14 @@ static int processDoubleValue(double** store) {
     double *val = loadDoubleValue();
     if (val == NULL) {
         SHIFT_ERROR(offset, "Error reading double value");
-        free(val);
+        zfree(val);
         return 0;
     }
 
     if (store != NULL) {
         *store = val;
     } else {
-        free(val);
+        zfree(val);
     }
     return 1;
 }
@@ -412,30 +357,30 @@ static int loadPair(entry *e) {
     }
 
     uint32_t length = 0;
-    if (e->type == REDIS_LIST ||
-        e->type == REDIS_SET  ||
-        e->type == REDIS_ZSET ||
-        e->type == REDIS_HASH) {
+    if (e->type == REDIS_RDB_TYPE_LIST ||
+        e->type == REDIS_RDB_TYPE_SET  ||
+        e->type == REDIS_RDB_TYPE_ZSET ||
+        e->type == REDIS_RDB_TYPE_HASH) {
         if ((length = loadLength(NULL)) == REDIS_RDB_LENERR) {
             SHIFT_ERROR(offset, "Error reading %s length", types[e->type]);
             return 0;
         }
     }
 
     switch(e->type) {
-    case REDIS_STRING:
-    case REDIS_HASH_ZIPMAP:
-    case REDIS_LIST_ZIPLIST:
-    case REDIS_SET_INTSET:
-    case REDIS_ZSET_ZIPLIST:
-    case REDIS_HASH_ZIPLIST:
+    case REDIS_RDB_TYPE_STRING:
+    case REDIS_RDB_TYPE_HASH_ZIPMAP:
+    case REDIS_RDB_TYPE_LIST_ZIPLIST:
+    case REDIS_RDB_TYPE_SET_INTSET:
+    case REDIS_RDB_TYPE_ZSET_ZIPLIST:
+    case REDIS_RDB_TYPE_HASH_ZIPLIST:
         if (!processStringObject(NULL)) {
             SHIFT_ERROR(offset, "Error reading entry value");
             return 0;
         }
     break;
-    case REDIS_LIST:
-    case REDIS_SET:
+    case REDIS_RDB_TYPE_LIST:
+    case REDIS_RDB_TYPE_SET:
         for (i = 0; i < length; i++) {
             offset = CURR_OFFSET;
             if (!processStringObject(NULL)) {
@@ -444,7 +389,7 @@ static int loadPair(entry *e) {
             }
         }
     break;
-    case REDIS_ZSET:
+    case REDIS_RDB_TYPE_ZSET:
         for (i = 0; i < length; i++) {
             offset = CURR_OFFSET;
             if (!processStringObject(NULL)) {
@@ -458,7 +403,7 @@ static int loadPair(entry *e) {
             }
         }
     break;
-    case REDIS_HASH:
+    case REDIS_RDB_TYPE_HASH:
         for (i = 0; i < length; i++) {
             offset = CURR_OFFSET;
             if (!processStringObject(NULL)) {
@@ -494,7 +439,7 @@ static entry loadEntry() {
     }
 
     offset[1] = CURR_OFFSET;
-    if (e.type == REDIS_SELECTDB) {
+    if (e.type == REDIS_RDB_OPCODE_SELECTDB) {
         if ((length = loadLength(NULL)) == REDIS_RDB_LENERR) {
             SHIFT_ERROR(offset[1], "Error reading database number");
             return e;
@@ -503,7 +448,7 @@ static entry loadEntry() {
             SHIFT_ERROR(offset[1], "Database number out of range (%d)", length);
             return e;
         }
-    } else if (e.type == REDIS_EOF) {
+    } else if (e.type == REDIS_RDB_OPCODE_EOF) {
         if (positions[level].offset < positions[level].size) {
             SHIFT_ERROR(offset[0], "Unexpected EOF");
         } else {
@@ -512,8 +457,8 @@ static entry loadEntry() {
         return e;
     } else {
         /* optionally consume expire */
-        if (e.type == REDIS_EXPIRETIME ||
-            e.type == REDIS_EXPIRETIME_MS) {
+        if (e.type == REDIS_RDB_OPCODE_EXPIRETIME ||
+            e.type == REDIS_RDB_OPCODE_EXPIRETIME_MS) {
             if (!processTime(e.type)) return e;
             if (!loadType(&e)) return e;
         }
@@ -546,7 +491,7 @@ static void printCentered(int indent, int width, char* body) {
 
     memset(head, '=', indent);
     memset(tail, '=', width - 2 - indent - strlen(body));
-    printf("%s %s %s\n", head, body, tail);
+    redisLog(REDIS_WARNING, "%s %s %s", head, body, tail);
 }
 
 static void printValid(uint64_t ops, uint64_t bytes) {
@@ -593,7 +538,7 @@ static void printErrorStack(entry *e) {
 
     /* display error stack */
     for (i = 0; i < errors.level; i++) {
-        printf("0x%08lx - %s\n",
+        redisLog(REDIS_WARNING, "0x%08lx - %s",
             (unsigned long) errors.offset[i], errors.error[i]);
     }
 }
@@ -606,7 +551,7 @@ void process(void) {
     /* Exclude the final checksum for RDB >= 5. Will be checked at the end. */
     if (dump_version >= 5) {
         if (positions[0].size < 8) {
-            printf("RDB version >= 5 but no room for checksum.\n");
+            redisLog(REDIS_WARNING, "RDB version >= 5 but no room for checksum.");
             exit(1);
         }
         positions[0].size -= 8;
@@ -655,15 +600,15 @@ void process(void) {
             /* advance position */
             positions[0] = positions[1];
         }
-        free(entry.key);
+        zfree(entry.key);
     }
 
     /* because there is another potential error,
      * print how many valid ops we have processed */
     printValid(num_valid_ops, num_valid_bytes);
 
     /* expect an eof */
-    if (entry.type != REDIS_EOF) {
+    if (entry.type != REDIS_RDB_OPCODE_EOF) {
         /* last byte should be EOF, add error */
         errors.level = 0;
         SHIFT_ERROR(positions[0].offset, "Expected EOF, got %s", types[entry.type]);
@@ -691,14 +636,13 @@ void process(void) {
         if (crc != crc2) {
             SHIFT_ERROR(positions[0].offset, "RDB CRC64 does not match.");
         } else {
-            printf("CRC64 checksum is OK\n");
+            redisLog(REDIS_WARNING, "CRC64 checksum is OK");
         }
     }
 
     /* print summary on errors */
     if (num_errors) {
-        printf("\n");
-        printf("Total unprocessable opcodes: %llu\n",
+        redisLog(REDIS_WARNING, "Total unprocessable opcodes: %llu",
             (unsigned long long) num_errors);
     }
 }
@@ -711,21 +655,21 @@ int redis_check_rdb(char *rdbfilename) {
 
     fd = open(rdbfilename, O_RDONLY);
     if (fd < 1) {
-        ERROR("Cannot open file: %s\n", rdbfilename);
+        ERROR("Cannot open file: %s", rdbfilename);
     }
     if (fstat(fd, &stat) == -1) {
-        ERROR("Cannot stat: %s\n", rdbfilename);
+        ERROR("Cannot stat: %s", rdbfilename);
     } else {
         size = stat.st_size;
     }
 
     if (sizeof(size_t) == sizeof(int32_t) && size >= INT_MAX) {
-        ERROR("Cannot check dump files >2GB on a 32-bit platform\n");
+        ERROR("Cannot check dump files >2GB on a 32-bit platform");
     }
 
     data = mmap(NULL, size, PROT_READ, MAP_SHARED, fd, 0);
     if (data == MAP_FAILED) {
-        ERROR("Cannot mmap: %s\n", rdbfilename);
+        ERROR("Cannot mmap: %s", rdbfilename);
     }
 
     /* Initialize static vars */
@@ -735,22 +679,16 @@ int redis_check_rdb(char *rdbfilename) {
     errors.level = 0;
 
     /* Object types */
-    sprintf(types[REDIS_STRING], "STRING");
-    sprintf(types[REDIS_LIST], "LIST");
-    sprintf(types[REDIS_SET], "SET");
-    sprintf(types[REDIS_ZSET], "ZSET");
-    sprintf(types[REDIS_HASH], "HASH");
+    sprintf(types[REDIS_RDB_TYPE_STRING], "STRING");
+    sprintf(types[REDIS_RDB_TYPE_LIST], "LIST");
+    sprintf(types[REDIS_RDB_TYPE_SET], "SET");
+    sprintf(types[REDIS_RDB_TYPE_ZSET], "ZSET");
+    sprintf(types[REDIS_RDB_TYPE_HASH], "HASH");
 
     /* Object types only used for dumping to disk */
-    sprintf(types[REDIS_EXPIRETIME], "EXPIRETIME");
-    sprintf(types[REDIS_SELECTDB], "SELECTDB");
-    sprintf(types[REDIS_EOF], "EOF");
-
-    /* Double constants initialization */
-    R_Zero = 0.0;
-    R_PosInf = 1.0/R_Zero;
-    R_NegInf = -1.0/R_Zero;
-    R_Nan = R_Zero/R_Zero;
+    sprintf(types[REDIS_RDB_OPCODE_EXPIRETIME], "EXPIRETIME");
+    sprintf(types[REDIS_RDB_OPCODE_SELECTDB], "SELECTDB");
+    sprintf(types[REDIS_RDB_OPCODE_EOF], "EOF");
 
     process();
 