@@ -99,13 +99,13 @@ robj *lookupKeyWrite(redisDb *db, robj *key) {
     return lookupKey(db,key);
 }
 
-robj *lookupKeyReadOrReply(redisClient *c, robj *key, robj *reply) {
+robj *lookupKeyReadOrReply(client *c, robj *key, robj *reply) {
     robj *o = lookupKeyRead(c->db, key);
     if (!o) addReply(c,reply);
     return o;
 }
 
-robj *lookupKeyWriteOrReply(redisClient *c, robj *key, robj *reply) {
+robj *lookupKeyWriteOrReply(client *c, robj *key, robj *reply) {
     robj *o = lookupKeyWrite(c->db, key);
     if (!o) addReply(c,reply);
     return o;
@@ -247,7 +247,7 @@ long long emptyDb(void(callback)(void*)) {
     return removed;
 }
 
-int selectDb(redisClient *c, int id) {
+int selectDb(client *c, int id) {
     if (id < 0 || id >= server.dbnum)
         return REDIS_ERR;
     c->db = &server.db[id];
@@ -275,7 +275,7 @@ void signalFlushedDb(int dbid) {
  * Type agnostic commands operating on the key space
  *----------------------------------------------------------------------------*/
 
-void flushdbCommand(redisClient *c) {
+void flushdbCommand(client *c) {
     server.dirty += dictSize(c->db->dict);
     signalFlushedDb(c->db->id);
     dictEmpty(c->db->dict,NULL);
@@ -284,7 +284,7 @@ void flushdbCommand(redisClient *c) {
     addReply(c,shared.ok);
 }
 
-void flushallCommand(redisClient *c) {
+void flushallCommand(client *c) {
     signalFlushedDb(-1);
     server.dirty += emptyDb(NULL);
     addReply(c,shared.ok);
@@ -302,7 +302,7 @@ void flushallCommand(redisClient *c) {
     server.dirty++;
 }
 
-void delCommand(redisClient *c) {
+void delCommand(client *c) {
     int deleted = 0, j;
 
     for (j = 1; j < c->argc; j++) {
@@ -320,7 +320,7 @@ void delCommand(redisClient *c) {
 
 /* EXISTS key1 key2 ... key_N.
  * Return value is the number of keys existing. */
-void existsCommand(redisClient *c) {
+void existsCommand(client *c) {
     long long count = 0;
     int j;
 
@@ -331,7 +331,7 @@ void existsCommand(redisClient *c) {
     addReplyLongLong(c,count);
 }
 
-void selectCommand(redisClient *c) {
+void selectCommand(client *c) {
     long id;
 
     if (getLongFromObjectOrReply(c, c->argv[1], &id,
@@ -349,7 +349,7 @@ void selectCommand(redisClient *c) {
     }
 }
 
-void randomkeyCommand(redisClient *c) {
+void randomkeyCommand(client *c) {
     robj *key;
 
     if ((key = dbRandomKey(c->db)) == NULL) {
@@ -361,7 +361,7 @@ void randomkeyCommand(redisClient *c) {
     decrRefCount(key);
 }
 
-void keysCommand(redisClient *c) {
+void keysCommand(client *c) {
     dictIterator *di;
     dictEntry *de;
     sds pattern = c->argv[1]->ptr;
@@ -423,7 +423,7 @@ void scanCallback(void *privdata, const dictEntry *de) {
  * if the cursor is valid, store it as unsigned integer into *cursor and
  * returns REDIS_OK. Otherwise return REDIS_ERR and send an error to the
  * client. */
-int parseScanCursorOrReply(redisClient *c, robj *o, unsigned long *cursor) {
+int parseScanCursorOrReply(client *c, robj *o, unsigned long *cursor) {
     char *eptr;
 
     /* Use strtoul() because we need an *unsigned* long, so
@@ -449,7 +449,7 @@ int parseScanCursorOrReply(redisClient *c, robj *o, unsigned long *cursor) {
  *
  * In the case of a Hash object the function returns both the field and value
  * of every element on the Hash. */
-void scanGenericCommand(redisClient *c, robj *o, unsigned long cursor) {
+void scanGenericCommand(client *c, robj *o, unsigned long cursor) {
     int i, j;
     list *keys = listCreate();
     listNode *node, *nextnode;
@@ -627,21 +627,21 @@ void scanGenericCommand(redisClient *c, robj *o, unsigned long cursor) {
 }
 
 /* The SCAN command completely relies on scanGenericCommand. */
-void scanCommand(redisClient *c) {
+void scanCommand(client *c) {
     unsigned long cursor;
     if (parseScanCursorOrReply(c,c->argv[1],&cursor) == REDIS_ERR) return;
     scanGenericCommand(c,NULL,cursor);
 }
 
-void dbsizeCommand(redisClient *c) {
+void dbsizeCommand(client *c) {
     addReplyLongLong(c,dictSize(c->db->dict));
 }
 
-void lastsaveCommand(redisClient *c) {
+void lastsaveCommand(client *c) {
     addReplyLongLong(c,server.lastsave);
 }
 
-void typeCommand(redisClient *c) {
+void typeCommand(client *c) {
     robj *o;
     char *type;
 
@@ -661,7 +661,7 @@ void typeCommand(redisClient *c) {
     addReplyStatus(c,type);
 }
 
-void shutdownCommand(redisClient *c) {
+void shutdownCommand(client *c) {
     int flags = 0;
 
     if (c->argc > 2) {
@@ -689,7 +689,7 @@ void shutdownCommand(redisClient *c) {
     addReplyError(c,"Errors trying to SHUTDOWN. Check logs.");
 }
 
-void renameGenericCommand(redisClient *c, int nx) {
+void renameGenericCommand(client *c, int nx) {
     robj *o;
     long long expire;
     int samekey = 0;
@@ -731,15 +731,15 @@ void renameGenericCommand(redisClient *c, int nx) {
     addReply(c,nx ? shared.cone : shared.ok);
 }
 
-void renameCommand(redisClient *c) {
+void renameCommand(client *c) {
     renameGenericCommand(c,0);
 }
 
-void renamenxCommand(redisClient *c) {
+void renamenxCommand(client *c) {
     renameGenericCommand(c,1);
 }
 
-void moveCommand(redisClient *c) {
+void moveCommand(client *c) {
     robj *o;
     redisDb *src, *dst;
     int srcid;
@@ -899,7 +899,7 @@ int expireIfNeeded(redisDb *db, robj *key) {
  *
  * unit is either UNIT_SECONDS or UNIT_MILLISECONDS, and is only used for
  * the argv[2] parameter. The basetime is always specified in milliseconds. */
-void expireGenericCommand(redisClient *c, long long basetime, int unit) {
+void expireGenericCommand(client *c, long long basetime, int unit) {
     robj *key = c->argv[1], *param = c->argv[2];
     long long when; /* unix time in milliseconds when the key will expire. */
 
@@ -945,23 +945,23 @@ void expireGenericCommand(redisClient *c, long long basetime, int unit) {
     }
 }
 
-void expireCommand(redisClient *c) {
+void expireCommand(client *c) {
     expireGenericCommand(c,mstime(),UNIT_SECONDS);
 }
 
-void expireatCommand(redisClient *c) {
+void expireatCommand(client *c) {
     expireGenericCommand(c,0,UNIT_SECONDS);
 }
 
-void pexpireCommand(redisClient *c) {
+void pexpireCommand(client *c) {
     expireGenericCommand(c,mstime(),UNIT_MILLISECONDS);
 }
 
-void pexpireatCommand(redisClient *c) {
+void pexpireatCommand(client *c) {
     expireGenericCommand(c,0,UNIT_MILLISECONDS);
 }
 
-void ttlGenericCommand(redisClient *c, int output_ms) {
+void ttlGenericCommand(client *c, int output_ms) {
     long long expire, ttl = -1;
 
     /* If the key does not exist at all, return -2 */
@@ -983,15 +983,15 @@ void ttlGenericCommand(redisClient *c, int output_ms) {
     }
 }
 
-void ttlCommand(redisClient *c) {
+void ttlCommand(client *c) {
     ttlGenericCommand(c, 0);
 }
 
-void pttlCommand(redisClient *c) {
+void pttlCommand(client *c) {
     ttlGenericCommand(c, 1);
 }
 
-void persistCommand(redisClient *c) {
+void persistCommand(client *c) {
     dictEntry *de;
 
     de = dictFind(c->db->dict,c->argv[1]->ptr);