@@ -495,8 +495,8 @@ int dictEncObjKeyCompare(void *privdata, const void *key1,
     robj *o1 = (robj*) key1, *o2 = (robj*) key2;
     int cmp;
 
-    if (o1->encoding == REDIS_ENCODING_INT &&
-        o2->encoding == REDIS_ENCODING_INT)
+    if (o1->encoding == OBJ_ENCODING_INT &&
+        o2->encoding == OBJ_ENCODING_INT)
             return o1->ptr == o2->ptr;
 
     o1 = getDecodedObject(o1);
@@ -513,7 +513,7 @@ unsigned int dictEncObjHash(const void *key) {
     if (sdsEncodedObject(o)) {
         return dictGenHashFunction(o->ptr, sdslen((sds)o->ptr));
     } else {
-        if (o->encoding == REDIS_ENCODING_INT) {
+        if (o->encoding == OBJ_ENCODING_INT) {
             char buf[32];
             int len;
 
@@ -1324,61 +1324,61 @@ void beforeSleep(struct aeEventLoop *eventLoop) {
 void createSharedObjects(void) {
     int j;
 
-    shared.crlf = createObject(REDIS_STRING,sdsnew("\r\n"));
-    shared.ok = createObject(REDIS_STRING,sdsnew("+OK\r\n"));
-    shared.err = createObject(REDIS_STRING,sdsnew("-ERR\r\n"));
-    shared.emptybulk = createObject(REDIS_STRING,sdsnew("$0\r\n\r\n"));
-    shared.czero = createObject(REDIS_STRING,sdsnew(":0\r\n"));
-    shared.cone = createObject(REDIS_STRING,sdsnew(":1\r\n"));
-    shared.cnegone = createObject(REDIS_STRING,sdsnew(":-1\r\n"));
-    shared.nullbulk = createObject(REDIS_STRING,sdsnew("$-1\r\n"));
-    shared.nullmultibulk = createObject(REDIS_STRING,sdsnew("*-1\r\n"));
-    shared.emptymultibulk = createObject(REDIS_STRING,sdsnew("*0\r\n"));
-    shared.pong = createObject(REDIS_STRING,sdsnew("+PONG\r\n"));
-    shared.queued = createObject(REDIS_STRING,sdsnew("+QUEUED\r\n"));
-    shared.emptyscan = createObject(REDIS_STRING,sdsnew("*2\r\n$1\r\n0\r\n*0\r\n"));
-    shared.wrongtypeerr = createObject(REDIS_STRING,sdsnew(
+    shared.crlf = createObject(OBJ_STRING,sdsnew("\r\n"));
+    shared.ok = createObject(OBJ_STRING,sdsnew("+OK\r\n"));
+    shared.err = createObject(OBJ_STRING,sdsnew("-ERR\r\n"));
+    shared.emptybulk = createObject(OBJ_STRING,sdsnew("$0\r\n\r\n"));
+    shared.czero = createObject(OBJ_STRING,sdsnew(":0\r\n"));
+    shared.cone = createObject(OBJ_STRING,sdsnew(":1\r\n"));
+    shared.cnegone = createObject(OBJ_STRING,sdsnew(":-1\r\n"));
+    shared.nullbulk = createObject(OBJ_STRING,sdsnew("$-1\r\n"));
+    shared.nullmultibulk = createObject(OBJ_STRING,sdsnew("*-1\r\n"));
+    shared.emptymultibulk = createObject(OBJ_STRING,sdsnew("*0\r\n"));
+    shared.pong = createObject(OBJ_STRING,sdsnew("+PONG\r\n"));
+    shared.queued = createObject(OBJ_STRING,sdsnew("+QUEUED\r\n"));
+    shared.emptyscan = createObject(OBJ_STRING,sdsnew("*2\r\n$1\r\n0\r\n*0\r\n"));
+    shared.wrongtypeerr = createObject(OBJ_STRING,sdsnew(
         "-WRONGTYPE Operation against a key holding the wrong kind of value\r\n"));
-    shared.nokeyerr = createObject(REDIS_STRING,sdsnew(
+    shared.nokeyerr = createObject(OBJ_STRING,sdsnew(
         "-ERR no such key\r\n"));
-    shared.syntaxerr = createObject(REDIS_STRING,sdsnew(
+    shared.syntaxerr = createObject(OBJ_STRING,sdsnew(
         "-ERR syntax error\r\n"));
-    shared.sameobjecterr = createObject(REDIS_STRING,sdsnew(
+    shared.sameobjecterr = createObject(OBJ_STRING,sdsnew(
         "-ERR source and destination objects are the same\r\n"));
-    shared.outofrangeerr = createObject(REDIS_STRING,sdsnew(
+    shared.outofrangeerr = createObject(OBJ_STRING,sdsnew(
         "-ERR index out of range\r\n"));
-    shared.noscripterr = createObject(REDIS_STRING,sdsnew(
+    shared.noscripterr = createObject(OBJ_STRING,sdsnew(
         "-NOSCRIPT No matching script. Please use EVAL.\r\n"));
-    shared.loadingerr = createObject(REDIS_STRING,sdsnew(
+    shared.loadingerr = createObject(OBJ_STRING,sdsnew(
         "-LOADING Redis is loading the dataset in memory\r\n"));
-    shared.slowscripterr = createObject(REDIS_STRING,sdsnew(
+    shared.slowscripterr = createObject(OBJ_STRING,sdsnew(
         "-BUSY Redis is busy running a script. You can only call SCRIPT KILL or SHUTDOWN NOSAVE.\r\n"));
-    shared.masterdownerr = createObject(REDIS_STRING,sdsnew(
+    shared.masterdownerr = createObject(OBJ_STRING,sdsnew(
         "-MASTERDOWN Link with MASTER is down and slave-serve-stale-data is set to 'no'.\r\n"));
-    shared.bgsaveerr = createObject(REDIS_STRING,sdsnew(
+    shared.bgsaveerr = createObject(OBJ_STRING,sdsnew(
         "-MISCONF Redis is configured to save RDB snapshots, but is currently not able to persist on disk. Commands that may modify the data set are disabled. Please check Redis logs for details about the error.\r\n"));
-    shared.roslaveerr = createObject(REDIS_STRING,sdsnew(
+    shared.roslaveerr = createObject(OBJ_STRING,sdsnew(
         "-READONLY You can't write against a read only slave.\r\n"));
-    shared.noautherr = createObject(REDIS_STRING,sdsnew(
+    shared.noautherr = createObject(OBJ_STRING,sdsnew(
         "-NOAUTH Authentication required.\r\n"));
-    shared.oomerr = createObject(REDIS_STRING,sdsnew(
+    shared.oomerr = createObject(OBJ_STRING,sdsnew(
         "-OOM command not allowed when used memory > 'maxmemory'.\r\n"));
-    shared.execaborterr = createObject(REDIS_STRING,sdsnew(
+    shared.execaborterr = createObject(OBJ_STRING,sdsnew(
         "-EXECABORT Transaction discarded because of previous errors.\r\n"));
-    shared.noreplicaserr = createObject(REDIS_STRING,sdsnew(
+    shared.noreplicaserr = createObject(OBJ_STRING,sdsnew(
         "-NOREPLICAS Not enough good slaves to write.\r\n"));
-    shared.busykeyerr = createObject(REDIS_STRING,sdsnew(
+    shared.busykeyerr = createObject(OBJ_STRING,sdsnew(
         "-BUSYKEY Target key name already exists.\r\n"));
-    shared.space = createObject(REDIS_STRING,sdsnew(" "));
-    shared.colon = createObject(REDIS_STRING,sdsnew(":"));
-    shared.plus = createObject(REDIS_STRING,sdsnew("+"));
+    shared.space = createObject(OBJ_STRING,sdsnew(" "));
+    shared.colon = createObject(OBJ_STRING,sdsnew(":"));
+    shared.plus = createObject(OBJ_STRING,sdsnew("+"));
 
     for (j = 0; j < REDIS_SHARED_SELECT_CMDS; j++) {
         char dictid_str[64];
         int dictid_len;
 
         dictid_len = ll2string(dictid_str,sizeof(dictid_str),j);
-        shared.select[j] = createObject(REDIS_STRING,
+        shared.select[j] = createObject(OBJ_STRING,
             sdscatprintf(sdsempty(),
                 "*2\r\n$6\r\nSELECT\r\n$%d\r\n%s\r\n",
                 dictid_len, dictid_str));
@@ -1394,13 +1394,13 @@ void createSharedObjects(void) {
     shared.lpop = createStringObject("LPOP",4);
     shared.lpush = createStringObject("LPUSH",5);
     for (j = 0; j < REDIS_SHARED_INTEGERS; j++) {
-        shared.integers[j] = createObject(REDIS_STRING,(void*)(long)j);
-        shared.integers[j]->encoding = REDIS_ENCODING_INT;
+        shared.integers[j] = createObject(OBJ_STRING,(void*)(long)j);
+        shared.integers[j]->encoding = OBJ_ENCODING_INT;
     }
     for (j = 0; j < REDIS_SHARED_BULKHDR_LEN; j++) {
-        shared.mbulkhdr[j] = createObject(REDIS_STRING,
+        shared.mbulkhdr[j] = createObject(OBJ_STRING,
             sdscatprintf(sdsempty(),"*%d\r\n",j));
-        shared.bulkhdr[j] = createObject(REDIS_STRING,
+        shared.bulkhdr[j] = createObject(OBJ_STRING,
             sdscatprintf(sdsempty(),"$%d\r\n",j));
     }
     /* The following two shared objects, minstring and maxstrings, are not
@@ -1472,13 +1472,13 @@ void initServerConfig(void) {
     server.maxmemory = CONFIG_DEFAULT_MAXMEMORY;
     server.maxmemory_policy = CONFIG_DEFAULT_MAXMEMORY_POLICY;
     server.maxmemory_samples = CONFIG_DEFAULT_MAXMEMORY_SAMPLES;
-    server.hash_max_ziplist_entries = REDIS_HASH_MAX_ZIPLIST_ENTRIES;
-    server.hash_max_ziplist_value = REDIS_HASH_MAX_ZIPLIST_VALUE;
-    server.list_max_ziplist_size = REDIS_LIST_MAX_ZIPLIST_SIZE;
-    server.list_compress_depth = REDIS_LIST_COMPRESS_DEPTH;
-    server.set_max_intset_entries = REDIS_SET_MAX_INTSET_ENTRIES;
-    server.zset_max_ziplist_entries = REDIS_ZSET_MAX_ZIPLIST_ENTRIES;
-    server.zset_max_ziplist_value = REDIS_ZSET_MAX_ZIPLIST_VALUE;
+    server.hash_max_ziplist_entries = OBJ_HASH_MAX_ZIPLIST_ENTRIES;
+    server.hash_max_ziplist_value = OBJ_HASH_MAX_ZIPLIST_VALUE;
+    server.list_max_ziplist_size = OBJ_LIST_MAX_ZIPLIST_SIZE;
+    server.list_compress_depth = OBJ_LIST_COMPRESS_DEPTH;
+    server.set_max_intset_entries = OBJ_SET_MAX_INTSET_ENTRIES;
+    server.zset_max_ziplist_entries = OBJ_ZSET_MAX_ZIPLIST_ENTRIES;
+    server.zset_max_ziplist_value = OBJ_ZSET_MAX_ZIPLIST_VALUE;
     server.hll_sparse_max_bytes = CONFIG_DEFAULT_HLL_SPARSE_MAX_BYTES;
     server.shutdown_asap = 0;
     server.repl_ping_slave_period = REDIS_REPL_PING_SLAVE_PERIOD;