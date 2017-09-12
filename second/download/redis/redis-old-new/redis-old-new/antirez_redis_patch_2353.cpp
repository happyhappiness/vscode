@@ -95,7 +95,9 @@
  * 00|000000 => if the two MSB are 00 the len is the 6 bits of this byte
  * 01|000000 00000000 =>  01, the len is 14 byes, 6 bits + 8 bits of next byte
  * 10|000000 [32 bit integer] => if it's 01, a full 32 bit len will follow
- * 11|000000 reserved for future uses
+ * 11|000000 this means: specially encoded object will follow. The six bits
+ *           number specify the kind of object that follows.
+ *           See the REDIS_RDB_ENC_* defines.
  *
  * Lenghts up to 63 are stored using a single byte, most DB keys, and may
  * values, will fit inside. */
@@ -105,6 +107,14 @@
 #define REDIS_RDB_64BITLEN 3
 #define REDIS_RDB_LENERR UINT_MAX
 
+/* When a length of a string object stored on disk has the first two bits
+ * set, the remaining two bits specify a special encoding for the object
+ * accordingly to the following defines: */
+#define REDIS_RDB_ENC_INT8 0        /* 8 bit signed integer */
+#define REDIS_RDB_ENC_INT16 1       /* 16 bit signed integer */
+#define REDIS_RDB_ENC_INT32 2       /* 32 bit signed integer */
+#define REDIS_RDB_ENC_FLZ 3         /* string compressed with FASTLZ */
+
 /* Client flags */
 #define REDIS_CLOSE 1       /* This client connection should be closed ASAP */
 #define REDIS_SLAVE 2       /* This client is a slave server */
@@ -620,7 +630,7 @@ int serverCron(struct aeEventLoop *eventLoop, long long id, void *clientData) {
         used = dictGetHashTableUsed(server.dict[j]);
         if (!(loops % 5) && used > 0) {
             redisLog(REDIS_DEBUG,"DB %d: %d keys in %d slots HT.",j,used,size);
-            // dictPrintStats(server.dict);
+            /* dictPrintStats(server.dict); */
         }
         if (size && used && size > REDIS_HT_MINSLOTS &&
             (used*100/size < REDIS_HT_MINFILL)) {
@@ -1027,7 +1037,7 @@ static void sendReplyToClient(aeEventLoop *el, int fd, void *privdata, int mask)
         if (c->flags & REDIS_MASTER) {
             nwritten = objlen - c->sentlen;
         } else {
-            nwritten = write(fd, o->ptr+c->sentlen, objlen - c->sentlen);
+            nwritten = write(fd, ((char*)o->ptr)+c->sentlen, objlen - c->sentlen);
             if (nwritten <= 0) break;
         }
         c->sentlen += nwritten;
@@ -1822,11 +1832,11 @@ static void setGenericCommand(redisClient *c, int nx) {
 }
 
 static void setCommand(redisClient *c) {
-    return setGenericCommand(c,0);
+    setGenericCommand(c,0);
 }
 
 static void setnxCommand(redisClient *c) {
-    return setGenericCommand(c,1);
+    setGenericCommand(c,1);
 }
 
 static void getCommand(redisClient *c) {
@@ -1907,21 +1917,21 @@ static void incrDecrCommand(redisClient *c, int incr) {
 }
 
 static void incrCommand(redisClient *c) {
-    return incrDecrCommand(c,1);
+    incrDecrCommand(c,1);
 }
 
 static void decrCommand(redisClient *c) {
-    return incrDecrCommand(c,-1);
+    incrDecrCommand(c,-1);
 }
 
 static void incrbyCommand(redisClient *c) {
     int incr = atoi(c->argv[2]->ptr);
-    return incrDecrCommand(c,incr);
+    incrDecrCommand(c,incr);
 }
 
 static void decrbyCommand(redisClient *c) {
     int incr = atoi(c->argv[2]->ptr);
-    return incrDecrCommand(c,-incr);
+    incrDecrCommand(c,-incr);
 }
 
 /* ========================= Type agnostic commands ========================= */
@@ -2439,8 +2449,9 @@ static void lremCommand(redisClient *c) {
             }
             ln = fromtail ? list->tail : list->head;
             while (ln) {
-                next = fromtail ? ln->prev : ln->next;
                 robj *ele = listNodeValue(ln);
+
+                next = fromtail ? ln->prev : ln->next;
                 if (sdscmp(ele->ptr,c->argv[3]->ptr) == 0) {
                     listDelNode(list,ln);
                     server.dirty++;
@@ -2696,7 +2707,7 @@ robj *lookupKeyByPattern(dict *dict, robj *pattern, robj *subst) {
     keyobj.ptr = ((char*)&keyname)+(sizeof(long)*2);
 
     de = dictFind(dict,&keyobj);
-    // printf("lookup '%s' => %p\n", keyname.buf,de);
+    /* printf("lookup '%s' => %p\n", keyname.buf,de); */
     if (!de) return NULL;
     return dictGetEntryVal(de);
 }
@@ -2986,7 +2997,7 @@ static int flushClientOutput(redisClient *c) {
     return REDIS_OK;
 }
 
-static int syncWrite(int fd, void *ptr, ssize_t size, int timeout) {
+static int syncWrite(int fd, char *ptr, ssize_t size, int timeout) {
     ssize_t nwritten, ret = size;
     time_t start = time(NULL);
 
@@ -3006,7 +3017,7 @@ static int syncWrite(int fd, void *ptr, ssize_t size, int timeout) {
     return ret;
 }
 
-static int syncRead(int fd, void *ptr, ssize_t size, int timeout) {
+static int syncRead(int fd, char *ptr, ssize_t size, int timeout) {
     ssize_t nread, totread = 0;
     time_t start = time(NULL);
 