@@ -26,6 +26,7 @@
 #include "anet.h"   /* Networking the easy way */
 #include "zipmap.h" /* Compact string -> string data structure */
 #include "ziplist.h" /* Compact list data structure */
+#include "intset.h" /* Compact integer set structure */
 #include "version.h"
 
 /* Error codes */
@@ -46,6 +47,7 @@
 #define REDIS_MAX_WRITE_PER_EVENT (1024*64)
 #define REDIS_REQUEST_MAX_SIZE (1024*1024*256) /* max bytes in inline command */
 #define REDIS_SHARED_INTEGERS 10000
+#define REDIS_REPLY_CHUNK_BYTES (5*1500) /* 5 TCP packets with default MTU */
 
 /* If more then REDIS_WRITEV_THRESHOLD write packets are pending use writev */
 #define REDIS_WRITEV_THRESHOLD      3
@@ -82,6 +84,7 @@
 #define REDIS_ENCODING_ZIPMAP 3  /* Encoded as zipmap */
 #define REDIS_ENCODING_LINKEDLIST 4 /* Encoded as regular linked list */
 #define REDIS_ENCODING_ZIPLIST 5 /* Encoded as ziplist */
+#define REDIS_ENCODING_INTSET 6  /* Encoded as intset */
 
 /* Object types only used for dumping to disk */
 #define REDIS_EXPIRETIME 253
@@ -188,6 +191,7 @@
 #define REDIS_HASH_MAX_ZIPMAP_VALUE 512
 #define REDIS_LIST_MAX_ZIPLIST_ENTRIES 1024
 #define REDIS_LIST_MAX_ZIPLIST_VALUE 32
+#define REDIS_SET_MAX_INTSET_ENTRIES 4096
 
 /* Sets operations codes */
 #define REDIS_OP_UNION 0
@@ -282,8 +286,9 @@ typedef struct redisClient {
     int dictid;
     sds querybuf;
     robj **argv, **mbargv;
+    char *newline;          /* pointing to the detected newline in querybuf */
     int argc, mbargc;
-    int bulklen;            /* bulk read len. -1 if not in bulk read mode */
+    long bulklen;            /* bulk read len. -1 if not in bulk read mode */
     int multibulk;          /* multi bulk command format active */
     list *reply;
     int sentlen;
@@ -306,6 +311,10 @@ typedef struct redisClient {
     list *watched_keys;     /* Keys WATCHED for MULTI/EXEC CAS */
     dict *pubsub_channels;  /* channels a client is interested in (SUBSCRIBE) */
     list *pubsub_patterns;  /* patterns a client is interested in (SUBSCRIBE) */
+
+    /* Response buffer */
+    int bufpos;
+    char buf[REDIS_REPLY_CHUNK_BYTES];
 } redisClient;
 
 struct saveparam {
@@ -335,6 +344,7 @@ struct redisServer {
     int sofd;
     redisDb *db;
     long long dirty;            /* changes to DB from the last save */
+    long long dirty_before_bgsave; /* used to restore dirty on failed BGSAVE */
     list *clients;
     list *slaves, *monitors;
     char neterr[ANET_ERR_LEN];
@@ -400,6 +410,7 @@ struct redisServer {
     size_t hash_max_zipmap_value;
     size_t list_max_ziplist_entries;
     size_t list_max_ziplist_value;
+    size_t set_max_intset_entries;
     /* Virtual memory state */
     FILE *vm_fp;
     int vm_fd;
@@ -482,13 +493,14 @@ typedef struct _redisSortOperation {
 } redisSortOperation;
 
 /* ZSETs use a specialized version of Skiplists */
-
 typedef struct zskiplistNode {
-    struct zskiplistNode **forward;
-    struct zskiplistNode *backward;
-    unsigned int *span;
-    double score;
     robj *obj;
+    double score;
+    struct zskiplistNode *backward;
+    struct zskiplistLevel {
+        struct zskiplistNode *forward;
+        unsigned int span;
+    } level[];
 } zskiplistNode;
 
 typedef struct zskiplist {
@@ -537,6 +549,14 @@ typedef struct {
     listNode *ln;       /* Entry in linked list */
 } listTypeEntry;
 
+/* Structure to hold set iteration abstraction. */
+typedef struct {
+    robj *subject;
+    int encoding;
+    int ii; /* intset iterator */
+    dictIterator *di;
+} setTypeIterator;
+
 /* Structure to hold hash iteration abstration. Note that iteration over
  * hashes involves both fields and values. Because it is possible that
  * not both are required, store pointers in the iterator to avoid
@@ -577,6 +597,8 @@ void resetClient(redisClient *c);
 void sendReplyToClient(aeEventLoop *el, int fd, void *privdata, int mask);
 void sendReplyToClientWritev(aeEventLoop *el, int fd, void *privdata, int mask);
 void addReply(redisClient *c, robj *obj);
+void *addDeferredMultiBulkLength(redisClient *c);
+void setDeferredMultiBulkLength(redisClient *c, void *node, long length);
 void addReplySds(redisClient *c, sds s);
 void processInputBuffer(redisClient *c);
 void acceptTcpHandler(aeEventLoop *el, int fd, void *privdata, int mask);
@@ -587,11 +609,23 @@ void addReplyBulkCString(redisClient *c, char *s);
 void acceptHandler(aeEventLoop *el, int fd, void *privdata, int mask);
 void addReply(redisClient *c, robj *obj);
 void addReplySds(redisClient *c, sds s);
+void addReplyError(redisClient *c, char *err);
+void addReplyStatus(redisClient *c, char *status);
 void addReplyDouble(redisClient *c, double d);
 void addReplyLongLong(redisClient *c, long long ll);
-void addReplyUlong(redisClient *c, unsigned long ul);
+void addReplyMultiBulkLen(redisClient *c, long length);
 void *dupClientReplyValue(void *o);
 
+#ifdef __GNUC__
+void addReplyErrorFormat(redisClient *c, const char *fmt, ...)
+    __attribute__((format(printf, 2, 3)));
+void addReplyStatusFormat(redisClient *c, const char *fmt, ...)
+    __attribute__((format(printf, 2, 3)));
+#else
+void addReplyErrorFormat(redisClient *c, const char *fmt, ...);
+void addReplyStatusFormat(redisClient *c, const char *fmt, ...);
+#endif
+
 /* List data type */
 void listTypeTryConversion(robj *subject, robj *value);
 void listTypePush(robj *subject, robj *value, int where);
@@ -636,6 +670,7 @@ robj *createStringObjectFromLongLong(long long value);
 robj *createListObject(void);
 robj *createZiplistObject(void);
 robj *createSetObject(void);
+robj *createIntsetObject(void);
 robj *createHashObject(void);
 robj *createZsetObject(void);
 int getLongFromObjectOrReply(redisClient *c, robj *o, long *target, const char *msg);
@@ -677,7 +712,7 @@ void backgroundRewriteDoneHandler(int statloc);
 /* Sorted sets data type */
 zskiplist *zslCreate(void);
 void zslFree(zskiplist *zsl);
-void zslInsert(zskiplist *zsl, double score, robj *obj);
+zskiplistNode *zslInsert(zskiplist *zsl, double score, robj *obj);
 
 /* Core functions */
 void freeMemoryIfNeeded(void);
@@ -719,6 +754,18 @@ int dontWaitForSwappedKey(redisClient *c, robj *key);
 void handleClientsBlockedOnSwappedKey(redisDb *db, robj *key);
 vmpointer *vmSwapObjectBlocking(robj *val);
 
+/* Set data type */
+robj *setTypeCreate(robj *value);
+int setTypeAdd(robj *subject, robj *value);
+int setTypeRemove(robj *subject, robj *value);
+int setTypeIsMember(robj *subject, robj *value);
+setTypeIterator *setTypeInitIterator(robj *subject);
+void setTypeReleaseIterator(setTypeIterator *si);
+robj *setTypeNext(setTypeIterator *si);
+robj *setTypeRandomElement(robj *subject);
+unsigned long setTypeSize(robj *subject);
+void setTypeConvert(robj *subject, int enc);
+
 /* Hash data type */
 void convertToRealHash(robj *o);
 void hashTypeTryConversion(robj *subject, robj **argv, int start, int end);
@@ -747,6 +794,8 @@ int stringmatch(const char *pattern, const char *string, int nocase);
 long long memtoll(const char *p, int *err);
 int ll2string(char *s, size_t len, long long value);
 int isStringRepresentableAsLong(sds s, long *longval);
+int isStringRepresentableAsLongLong(sds s, long long *longval);
+int isObjectRepresentableAsLongLong(robj *o, long long *llongval);
 
 /* Configuration */
 void loadServerConfig(char *filename);
@@ -755,10 +804,10 @@ void resetServerSaveParams();
 
 /* db.c -- Keyspace access API */
 int removeExpire(redisDb *db, robj *key);
+void propagateExpire(redisDb *db, robj *key);
 int expireIfNeeded(redisDb *db, robj *key);
-int deleteIfVolatile(redisDb *db, robj *key);
 time_t getExpire(redisDb *db, robj *key);
-int setExpire(redisDb *db, robj *key, time_t when);
+void setExpire(redisDb *db, robj *key, time_t when);
 robj *lookupKey(redisDb *db, robj *key);
 robj *lookupKeyRead(redisDb *db, robj *key);
 robj *lookupKeyWrite(redisDb *db, robj *key);
@@ -841,6 +890,7 @@ void expireCommand(redisClient *c);
 void expireatCommand(redisClient *c);
 void getsetCommand(redisClient *c);
 void ttlCommand(redisClient *c);
+void persistCommand(redisClient *c);
 void slaveofCommand(redisClient *c);
 void debugCommand(redisClient *c);
 void msetCommand(redisClient *c);