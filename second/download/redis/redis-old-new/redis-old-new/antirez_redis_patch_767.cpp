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
@@ -707,6 +703,7 @@ void moveCommand(redisClient *c) {
     robj *o;
     redisDb *src, *dst;
     int srcid;
+    long long dbid;
 
     if (server.cluster_enabled) {
         addReplyError(c,"MOVE is not allowed in cluster mode");
@@ -716,7 +713,11 @@ void moveCommand(redisClient *c) {
     /* Obtain source and target DB pointers */
     src = c->db;
     srcid = c->db->id;
-    if (selectDb(c,atoi(c->argv[2]->ptr)) == REDIS_ERR) {
+
+    if (getLongLongFromObject(c->argv[2],&dbid) == REDIS_ERR ||
+        dbid < INT_MIN || dbid > INT_MAX ||
+        selectDb(c,dbid) == REDIS_ERR)
+    {
         addReply(c,shared.outofrangeerr);
         return;
     }
@@ -1076,7 +1077,7 @@ int *evalGetKeys(struct redisCommand *cmd, robj **argv, int argc, int *numkeys)
  * follow in SQL-alike style. Here we parse just the minimum in order to
  * correctly identify keys in the "STORE" option. */
 int *sortGetKeys(struct redisCommand *cmd, robj **argv, int argc, int *numkeys) {
-    int i, j, num, *keys;
+    int i, j, num, *keys, found_store = 0;
     REDIS_NOTUSED(cmd);
 
     num = 0;
@@ -1107,12 +1108,13 @@ int *sortGetKeys(struct redisCommand *cmd, robj **argv, int argc, int *numkeys)
                 /* Note: we don't increment "num" here and continue the loop
                  * to be sure to process the *last* "STORE" option if multiple
                  * ones are provided. This is same behavior as SORT. */
+                found_store = 1;
                 keys[num] = i+1; /* <store-key> */
                 break;
             }
         }
     }
-    *numkeys = num;
+    *numkeys = num + found_store;
     return keys;
 }
 