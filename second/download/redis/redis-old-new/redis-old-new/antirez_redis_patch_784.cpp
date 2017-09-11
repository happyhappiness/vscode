@@ -421,9 +421,7 @@ int parseScanCursorOrReply(redisClient *c, robj *o, unsigned long *cursor) {
  * In the case of a Hash object the function returns both the field and value
  * of every element on the Hash. */
 void scanGenericCommand(redisClient *c, robj *o, unsigned long cursor) {
-    int rv;
     int i, j;
-    char buf[REDIS_LONGSTR_SIZE];
     list *keys = listCreate();
     listNode *node, *nextnode;
     long count = 10;
@@ -503,7 +501,7 @@ void scanGenericCommand(redisClient *c, robj *o, unsigned long cursor) {
         privdata[1] = o;
         do {
             cursor = dictScan(ht, cursor, scanCallback, privdata);
-        } while (cursor && listLength(keys) < count);
+        } while (cursor && listLength(keys) < (unsigned long)count);
     } else if (o->type == REDIS_SET) {
         int pos = 0;
         int64_t ll;
@@ -577,9 +575,7 @@ void scanGenericCommand(redisClient *c, robj *o, unsigned long cursor) {
 
     /* Step 4: Reply to the client. */
     addReplyMultiBulkLen(c, 2);
-    rv = snprintf(buf, sizeof(buf), "%lu", cursor);
-    redisAssert(rv < sizeof(buf));
-    addReplyBulkCBuffer(c, buf, rv);
+    addReplyBulkLongLong(c,cursor);
 
     addReplyMultiBulkLen(c, listLength(keys));
     while ((node = listFirst(keys)) != NULL) {