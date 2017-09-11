@@ -33,6 +33,7 @@
 #include "fmacros.h"
 #include "config.h"
 #include "solarisfixes.h"
+#include "rio.h"
 
 #include <stdio.h>
 #include <stdlib.h>
@@ -164,7 +165,7 @@ typedef long long mstime_t; /* millisecond time type. */
 #define PROTO_REPLY_CHUNK_BYTES (16*1024) /* 16k output buffer */
 #define PROTO_INLINE_MAX_SIZE   (1024*64) /* Max size of inline reads */
 #define PROTO_MBULK_BIG_ARG     (1024*32)
-#define LONG_STR_SIZE      21          /* Bytes needed for long -> str */
+#define LONG_STR_SIZE      21          /* Bytes needed for long -> str + '\0' */
 #define AOF_AUTOSYNC_BYTES (1024*1024*32) /* fdatasync every 32MB */
 
 /* When configuring the server eventloop, we setup it so that the total number
@@ -195,33 +196,6 @@ typedef long long mstime_t; /* millisecond time type. */
 #define CMD_MODULE_GETKEYS (1<<14)  /* Use the modules getkeys interface. */
 #define CMD_MODULE_NO_CLUSTER (1<<15) /* Deny on Redis Cluster. */
 
-/* Defines related to the dump file format. To store 32 bits lengths for short
- * keys requires a lot of space, so we check the most significant 2 bits of
- * the first byte to interpreter the length:
- *
- * 00|000000 => if the two MSB are 00 the len is the 6 bits of this byte
- * 01|000000 00000000 =>  01, the len is 14 byes, 6 bits + 8 bits of next byte
- * 10|000000 [32 bit integer] => if it's 10, a full 32 bit len will follow
- * 11|000000 this means: specially encoded object will follow. The six bits
- *           number specify the kind of object that follows.
- *           See the RDB_ENC_* defines.
- *
- * Lengths up to 63 are stored using a single byte, most DB keys, and may
- * values, will fit inside. */
-#define RDB_6BITLEN 0
-#define RDB_14BITLEN 1
-#define RDB_32BITLEN 2
-#define RDB_ENCVAL 3
-#define RDB_LENERR UINT_MAX
-
-/* When a length of a string object stored on disk has the first two bits
- * set, the remaining two bits specify a special encoding for the object
- * accordingly to the following defines: */
-#define RDB_ENC_INT8 0        /* 8 bit signed integer */
-#define RDB_ENC_INT16 1       /* 16 bit signed integer */
-#define RDB_ENC_INT32 2       /* 32 bit signed integer */
-#define RDB_ENC_LZF 3         /* string compressed with FASTLZ */
-
 /* AOF states */
 #define AOF_OFF 0             /* AOF is off */
 #define AOF_ON 1              /* AOF is on */
@@ -448,6 +422,90 @@ typedef long long mstime_t; /* millisecond time type. */
 #define OBJ_ZSET 3
 #define OBJ_HASH 4
 
+/* The "module" object type is a special one that signals that the object
+ * is one directly managed by a Redis module. In this case the value points
+ * to a moduleValue struct, which contains the object value (which is only
+ * handled by the module itself) and the RedisModuleType struct which lists
+ * function pointers in order to serialize, deserialize, AOF-rewrite and
+ * free the object.
+ *
+ * Inside the RDB file, module types are encoded as OBJ_MODULE followed
+ * by a 64 bit module type ID, which has a 54 bits module-specific signature
+ * in order to dispatch the loading to the right module, plus a 10 bits
+ * encoding version. */
+#define OBJ_MODULE 5
+
+/* Extract encver / signature from a module type ID. */
+#define REDISMODULE_TYPE_ENCVER_BITS 10
+#define REDISMODULE_TYPE_ENCVER_MASK ((1<<REDISMODULE_TYPE_ENCVER_BITS)-1)
+#define REDISMODULE_TYPE_ENCVER(id) (id & REDISMODULE_TYPE_ENCVER_MASK)
+#define REDISMODULE_TYPE_SIGN(id) ((id & ~((uint64_t)REDISMODULE_TYPE_ENCVER_MASK)) >>REDISMODULE_TYPE_ENCVER_BITS)
+
+struct RedisModule;
+struct RedisModuleIO;
+struct RedisModuleDigest;
+struct redisObject;
+
+/* Each module type implementation should export a set of methods in order
+ * to serialize and deserialize the value in the RDB file, rewrite the AOF
+ * log, create the digest for "DEBUG DIGEST", and free the value when a key
+ * is deleted. */
+typedef void *(*moduleTypeLoadFunc)(struct RedisModuleIO *io, int encver);
+typedef void (*moduleTypeSaveFunc)(struct RedisModuleIO *io, void *value);
+typedef void (*moduleTypeRewriteFunc)(struct RedisModuleIO *io, struct redisObject *key, void *value);
+typedef void (*moduleTypeDigestFunc)(struct RedisModuleDigest *digest, void *value);
+typedef void (*moduleTypeFreeFunc)(void *value);
+
+/* The module type, which is referenced in each value of a given type, defines
+ * the methods and links to the module exporting the type. */
+typedef struct RedisModuleType {
+    uint64_t id; /* Higher 54 bits of type ID + 10 lower bits of encoding ver. */
+    struct RedisModule *module;
+    moduleTypeLoadFunc rdb_load;
+    moduleTypeSaveFunc rdb_save;
+    moduleTypeRewriteFunc aof_rewrite;
+    moduleTypeDigestFunc digest;
+    moduleTypeFreeFunc free;
+    char name[10]; /* 9 bytes name + null term. Charset: A-Z a-z 0-9 _- */
+} moduleType;
+
+/* In Redis objects 'robj' structures of type OBJ_MODULE, the value pointer
+ * is set to the following structure, referencing the moduleType structure
+ * in order to work with the value, and at the same time providing a raw
+ * pointer to the value, as created by the module commands operating with
+ * the module type.
+ *
+ * So for example in order to free such a value, it is possible to use
+ * the following code:
+ *
+ *  if (robj->type == OBJ_MODULE) {
+ *      moduleValue *mt = robj->ptr;
+ *      mt->type->free(mt->value);
+ *      zfree(mt); // We need to release this in-the-middle struct as well.
+ *  }
+ */
+typedef struct moduleValue {
+    moduleType *type;
+    void *value;
+} moduleValue;
+
+/* This is a wrapper for the 'rio' streams used inside rdb.c in Redis, so that
+ * the user does not have to take the total count of the written bytes nor
+ * to care about error conditions. */
+typedef struct RedisModuleIO {
+    size_t bytes;       /* Bytes read / written so far. */
+    rio *rio;           /* Rio stream. */
+    moduleType *type;   /* Module type doing the operation. */
+    int error;          /* True if error condition happened. */
+} RedisModuleIO;
+
+#define moduleInitIOContext(iovar,mtype,rioptr) do { \
+    iovar.rio = rioptr; \
+    iovar.type = mtype; \
+    iovar.bytes = 0; \
+    iovar.error = 0; \
+} while(0);
+
 /* Objects encoding. Some kind of objects like Strings and Hashes can be
  * internally represented in multiple ways. The 'encoding' field of the object
  * is set to one of this fields for this object. */
@@ -478,7 +536,7 @@ typedef struct redisObject {
 /* Macro used to obtain the current LRU clock.
  * If the current resolution is lower than the frequency we refresh the
  * LRU clock (as it should be in production servers) we return the
- * precomputed value, otherwise we need to resort to a function call. */
+ * precomputed value, otherwise we need to resort to a system call. */
 #define LRU_CLOCK() ((1000/server.hz <= LRU_CLOCK_RESOLUTION) ? server.lruclock : getLRUClock())
 
 /* Macro used to initialize a Redis object allocated on the stack.
@@ -625,6 +683,12 @@ struct saveparam {
     int changes;
 };
 
+struct moduleLoadQueueEntry {
+    sds path;
+    int argc;
+    robj **argv;
+};
+
 struct sharedObjectsStruct {
     robj *crlf, *ok, *err, *emptybulk, *czero, *cone, *cnegone, *pong, *space,
     *colon, *nullbulk, *nullmultibulk, *queued,
@@ -984,8 +1048,8 @@ struct redisServer {
     long long latency_monitor_threshold;
     dict *latency_events;
     /* Assert & bug reporting */
-    char *assert_failed;
-    char *assert_file;
+    const char *assert_failed;
+    const char *assert_file;
     int assert_line;
     int bug_report_start; /* True if bug report header was already logged. */
     int watchdog_period;  /* Software watchdog period in ms. 0 = off */
@@ -1098,9 +1162,11 @@ extern dictType modulesDictType;
 
 /* Modules */
 void moduleInitModulesSystem(void);
-int moduleLoad(const char *path);
+int moduleLoad(const char *path, void **argv, int argc);
 void moduleLoadFromQueue(void);
 int *moduleGetCommandKeysViaAPI(struct redisCommand *cmd, robj **argv, int argc, int *numkeys);
+moduleType *moduleTypeLookupModuleByID(uint64_t id);
+void moduleTypeNameByID(char *name, uint64_t moduleid);
 
 /* Utils */
 long long ustime(void);
@@ -1179,7 +1245,7 @@ void addReplyStatusFormat(client *c, const char *fmt, ...);
 void listTypeTryConversion(robj *subject, robj *value);
 void listTypePush(robj *subject, robj *value, int where);
 robj *listTypePop(robj *subject, int where);
-unsigned long listTypeLength(robj *subject);
+unsigned long listTypeLength(const robj *subject);
 listTypeIterator *listTypeInitIterator(robj *subject, long index, unsigned char direction);
 void listTypeReleaseIterator(listTypeIterator *li);
 int listTypeNext(listTypeIterator *li, listTypeEntry *entry);
@@ -1219,7 +1285,7 @@ robj *createObject(int type, void *ptr);
 robj *createStringObject(const char *ptr, size_t len);
 robj *createRawStringObject(const char *ptr, size_t len);
 robj *createEmbeddedStringObject(const char *ptr, size_t len);
-robj *dupStringObject(robj *o);
+robj *dupStringObject(const robj *o);
 int isSdsRepresentableAsLongLong(sds s, long long *llval);
 int isObjectRepresentableAsLongLong(robj *o, long long *llongval);
 robj *tryObjectEncoding(robj *o);
@@ -1234,11 +1300,12 @@ robj *createIntsetObject(void);
 robj *createHashObject(void);
 robj *createZsetObject(void);
 robj *createZsetZiplistObject(void);
+robj *createModuleObject(moduleType *mt, void *value);
 int getLongFromObjectOrReply(client *c, robj *o, long *target, const char *msg);
 int checkType(client *c, robj *o, int type);
 int getLongLongFromObjectOrReply(client *c, robj *o, long long *target, const char *msg);
 int getDoubleFromObjectOrReply(client *c, robj *o, double *target, const char *msg);
-int getDoubleFromObject(robj *o, double *target);
+int getDoubleFromObject(const robj *o, double *target);
 int getLongLongFromObject(robj *o, long long *target);
 int getLongDoubleFromObject(robj *o, long double *target);
 int getLongDoubleFromObjectOrReply(client *c, robj *o, long double *target, const char *msg);
@@ -1339,7 +1406,7 @@ void zzlNext(unsigned char *zl, unsigned char **eptr, unsigned char **sptr);
 void zzlPrev(unsigned char *zl, unsigned char **eptr, unsigned char **sptr);
 unsigned char *zzlFirstInRange(unsigned char *zl, zrangespec *range);
 unsigned char *zzlLastInRange(unsigned char *zl, zrangespec *range);
-unsigned int zsetLength(robj *zobj);
+unsigned int zsetLength(const robj *zobj);
 void zsetConvert(robj *zobj, int encoding);
 void zsetConvertToZiplistIfNeeded(robj *zobj, size_t maxelelen);
 int zsetScore(robj *zobj, sds member, double *score);
@@ -1387,7 +1454,6 @@ void serverLogFromHandler(int level, const char *msg);
 void usage(void);
 void updateDictResizePolicy(void);
 int htNeedsResize(dict *dict);
-void oom(const char *msg);
 void populateCommandTable(void);
 void resetCommandTableStats(void);
 void adjustOpenFilesLimit(void);
@@ -1413,7 +1479,7 @@ int setTypeNext(setTypeIterator *si, sds *sdsele, int64_t *llele);
 sds setTypeNextObject(setTypeIterator *si);
 int setTypeRandomElement(robj *setobj, sds *sdsele, int64_t *llele);
 unsigned long setTypeRandomElements(robj *set, unsigned long count, robj *aux_set);
-unsigned long setTypeSize(robj *subject);
+unsigned long setTypeSize(const robj *subject);
 void setTypeConvert(robj *subject, int enc);
 
 /* Hash data type */
@@ -1426,7 +1492,7 @@ void hashTypeTryConversion(robj *subject, robj **argv, int start, int end);
 void hashTypeTryObjectEncoding(robj *subject, robj **o1, robj **o2);
 int hashTypeExists(robj *o, sds key);
 int hashTypeDelete(robj *o, sds key);
-unsigned long hashTypeLength(robj *o);
+unsigned long hashTypeLength(const robj *o);
 hashTypeIterator *hashTypeInitIterator(robj *subject);
 void hashTypeReleaseIterator(hashTypeIterator *hi);
 int hashTypeNext(hashTypeIterator *hi);
@@ -1467,11 +1533,14 @@ void propagateExpire(redisDb *db, robj *key, int lazy);
 int expireIfNeeded(redisDb *db, robj *key);
 long long getExpire(redisDb *db, robj *key);
 void setExpire(redisDb *db, robj *key, long long when);
-robj *lookupKey(redisDb *db, robj *key);
+robj *lookupKey(redisDb *db, robj *key, int flags);
 robj *lookupKeyRead(redisDb *db, robj *key);
 robj *lookupKeyWrite(redisDb *db, robj *key);
 robj *lookupKeyReadOrReply(client *c, robj *key, robj *reply);
 robj *lookupKeyWriteOrReply(client *c, robj *key, robj *reply);
+robj *lookupKeyReadWithFlags(redisDb *db, robj *key, int flags);
+#define LOOKUP_NONE 0
+#define LOOKUP_NOTOUCH (1<<0)
 void dbAdd(redisDb *db, robj *key, robj *val);
 void dbOverwrite(redisDb *db, robj *key, robj *val);
 void setKey(redisDb *db, robj *key, robj *val);
@@ -1627,6 +1696,7 @@ void pexpireCommand(client *c);
 void pexpireatCommand(client *c);
 void getsetCommand(client *c);
 void ttlCommand(client *c);
+void touchCommand(client *c);
 void pttlCommand(client *c);
 void persistCommand(client *c);
 void slaveofCommand(client *c);
@@ -1729,11 +1799,11 @@ void *realloc(void *ptr, size_t size) __attribute__ ((deprecated));
 #endif
 
 /* Debugging stuff */
-void _serverAssertWithInfo(client *c, robj *o, char *estr, char *file, int line);
-void _serverAssert(char *estr, char *file, int line);
-void _serverPanic(char *msg, char *file, int line);
+void _serverAssertWithInfo(const client *c, const robj *o, const char *estr, const char *file, int line);
+void _serverAssert(const char *estr, const char *file, int line);
+void _serverPanic(const char *msg, const char *file, int line);
 void bugReportStart(void);
-void serverLogObjectDebugInfo(robj *o);
+void serverLogObjectDebugInfo(const robj *o);
 void sigsegvHandler(int sig, siginfo_t *info, void *secret);
 sds genRedisInfoString(char *section);
 void enableWatchdog(int period);