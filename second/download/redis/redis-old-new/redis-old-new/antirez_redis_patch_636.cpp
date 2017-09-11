@@ -65,6 +65,13 @@ typedef long long mstime_t; /* millisecond time type. */
 #include "util.h"    /* Misc functions useful in many places */
 #include "latency.h" /* Latency monitor API */
 #include "sparkline.h" /* ASII graphs API */
+#include "quicklist.h"
+
+/* Following includes allow test functions to be called from Redis main() */
+#include "zipmap.h"
+#include "sha1.h"
+#include "endianconv.h"
+#include "crc64.h"
 
 /* Error codes */
 #define REDIS_OK                0
@@ -198,6 +205,7 @@ typedef long long mstime_t; /* millisecond time type. */
 #define REDIS_ENCODING_INTSET 6  /* Encoded as intset */
 #define REDIS_ENCODING_SKIPLIST 7  /* Encoded as skiplist */
 #define REDIS_ENCODING_EMBSTR 8  /* Embedded sds string encoding */
+#define REDIS_ENCODING_QUICKLIST 9 /* Encoded as linked list of ziplists */
 
 /* Defines related to the dump file format. To store 32 bits lengths for short
  * keys requires a lot of space, so we check the most significant 2 bits of
@@ -323,12 +331,14 @@ typedef long long mstime_t; /* millisecond time type. */
 /* Zip structure related defaults */
 #define REDIS_HASH_MAX_ZIPLIST_ENTRIES 512
 #define REDIS_HASH_MAX_ZIPLIST_VALUE 64
-#define REDIS_LIST_MAX_ZIPLIST_ENTRIES 512
-#define REDIS_LIST_MAX_ZIPLIST_VALUE 64
 #define REDIS_SET_MAX_INTSET_ENTRIES 512
 #define REDIS_ZSET_MAX_ZIPLIST_ENTRIES 128
 #define REDIS_ZSET_MAX_ZIPLIST_VALUE 64
 
+/* List defaults */
+#define REDIS_LIST_MAX_ZIPLIST_SIZE -2
+#define REDIS_LIST_COMPRESS_DEPTH 0
+
 /* HyperLogLog defines */
 #define REDIS_DEFAULT_HLL_SPARSE_MAX_BYTES 3000
 
@@ -863,12 +873,14 @@ struct redisServer {
     /* Zip structure config, see redis.conf for more information  */
     size_t hash_max_ziplist_entries;
     size_t hash_max_ziplist_value;
-    size_t list_max_ziplist_entries;
-    size_t list_max_ziplist_value;
     size_t set_max_intset_entries;
     size_t zset_max_ziplist_entries;
     size_t zset_max_ziplist_value;
     size_t hll_sparse_max_bytes;
+    /* List parameters */
+    int list_max_ziplist_size;
+    int list_compress_depth;
+    /* time cache */
     time_t unixtime;        /* Unix time sampled every cron cycle. */
     long long mstime;       /* Like 'unixtime' but with milliseconds resolution. */
     /* Pubsub */
@@ -958,15 +970,13 @@ typedef struct {
     robj *subject;
     unsigned char encoding;
     unsigned char direction; /* Iteration direction */
-    unsigned char *zi;
-    listNode *ln;
+    quicklistIter *iter;
 } listTypeIterator;
 
 /* Structure for an entry while iterating over a list. */
 typedef struct {
     listTypeIterator *li;
-    unsigned char *zi;  /* Entry in ziplist */
-    listNode *ln;       /* Entry in linked list */
+    quicklistEntry entry; /* Entry in quicklist */
 } listTypeEntry;
 
 /* Structure to hold set iteration abstraction. */
@@ -1043,6 +1053,7 @@ void addReplyBulkCBuffer(redisClient *c, void *p, size_t len);
 void addReplyBulkLongLong(redisClient *c, long long ll);
 void addReply(redisClient *c, robj *obj);
 void addReplySds(redisClient *c, sds s);
+void addReplyBulkSds(redisClient *c, sds s);
 void addReplyError(redisClient *c, char *err);
 void addReplyStatus(redisClient *c, char *status);
 void addReplyDouble(redisClient *c, double d);
@@ -1092,7 +1103,7 @@ int listTypeNext(listTypeIterator *li, listTypeEntry *entry);
 robj *listTypeGet(listTypeEntry *entry);
 void listTypeInsert(listTypeEntry *entry, robj *value, int where);
 int listTypeEqual(listTypeEntry *entry, robj *o);
-void listTypeDelete(listTypeEntry *entry);
+void listTypeDelete(listTypeIterator *iter, listTypeEntry *entry);
 void listTypeConvert(robj *subject, int enc);
 void unblockClientWaitingData(redisClient *c);
 void handleClientsBlockedOnLists(void);
@@ -1130,7 +1141,7 @@ robj *getDecodedObject(robj *o);
 size_t stringObjectLen(robj *o);
 robj *createStringObjectFromLongLong(long long value);
 robj *createStringObjectFromLongDouble(long double value, int humanfriendly);
-robj *createListObject(void);
+robj *createQuicklistObject(void);
 robj *createZiplistObject(void);
 robj *createSetObject(void);
 robj *createIntsetObject(void);