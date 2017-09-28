                 break;
             }
         }
     }
     if (deleted) {
         signalModifiedKey(c->db,c->argv[1]);
-        notifyKeyspaceEvent(REDIS_NOTIFY_HASH,"hdel",c->argv[1],c->db->id);
+        notifyKeyspaceEvent(NOTIFY_HASH,"hdel",c->argv[1],c->db->id);
         if (keyremoved)
-            notifyKeyspaceEvent(REDIS_NOTIFY_GENERIC,"del",c->argv[1],
+            notifyKeyspaceEvent(NOTIFY_GENERIC,"del",c->argv[1],
                                 c->db->id);
         server.dirty += deleted;
     }
     addReplyLongLong(c,deleted);
 }
 
-void hlenCommand(redisClient *c) {
+void hlenCommand(client *c) {
     robj *o;
+
     if ((o = lookupKeyReadOrReply(c,c->argv[1],shared.czero)) == NULL ||
-        checkType(c,o,REDIS_HASH)) return;
+        checkType(c,o,OBJ_HASH)) return;
 
     addReplyLongLong(c,hashTypeLength(o));
 }
 
-static void addHashIteratorCursorToReply(redisClient *c, hashTypeIterator *hi, int what) {
-    if (hi->encoding == REDIS_ENCODING_ZIPLIST) {
+void hstrlenCommand(client *c) {
+    robj *o;
+
+    if ((o = lookupKeyReadOrReply(c,c->argv[1],shared.czero)) == NULL ||
+        checkType(c,o,OBJ_HASH)) return;
+    addReplyLongLong(c,hashTypeGetValueLength(o,c->argv[2]));
+}
+
+static void addHashIteratorCursorToReply(client *c, hashTypeIterator *hi, int what) {
+    if (hi->encoding == OBJ_ENCODING_ZIPLIST) {
         unsigned char *vstr = NULL;
         unsigned int vlen = UINT_MAX;
         long long vll = LLONG_MAX;
 
         hashTypeCurrentFromZiplist(hi, what, &vstr, &vlen, &vll);
         if (vstr) {
             addReplyBulkCBuffer(c, vstr, vlen);
         } else {
             addReplyBulkLongLong(c, vll);
         }
 
-    } else if (hi->encoding == REDIS_ENCODING_HT) {
+    } else if (hi->encoding == OBJ_ENCODING_HT) {
         robj *value;
 
         hashTypeCurrentFromHashTable(hi, what, &value);
         addReplyBulk(c, value);
 
     } else {
-        redisPanic("Unknown hash encoding");
+        serverPanic("Unknown hash encoding");
     }
 }
 
-void genericHgetallCommand(redisClient *c, int flags) {
+void genericHgetallCommand(client *c, int flags) {
     robj *o;
     hashTypeIterator *hi;
     int multiplier = 0;
     int length, count = 0;
 
     if ((o = lookupKeyReadOrReply(c,c->argv[1],shared.emptymultibulk)) == NULL
-        || checkType(c,o,REDIS_HASH)) return;
+        || checkType(c,o,OBJ_HASH)) return;
 
-    if (flags & REDIS_HASH_KEY) multiplier++;
-    if (flags & REDIS_HASH_VALUE) multiplier++;
+    if (flags & OBJ_HASH_KEY) multiplier++;
+    if (flags & OBJ_HASH_VALUE) multiplier++;
 
     length = hashTypeLength(o) * multiplier;
     addReplyMultiBulkLen(c, length);
 
     hi = hashTypeInitIterator(o);
-    while (hashTypeNext(hi) != REDIS_ERR) {
-        if (flags & REDIS_HASH_KEY) {
-            addHashIteratorCursorToReply(c, hi, REDIS_HASH_KEY);
+    while (hashTypeNext(hi) != C_ERR) {
+        if (flags & OBJ_HASH_KEY) {
+            addHashIteratorCursorToReply(c, hi, OBJ_HASH_KEY);
             count++;
         }
-        if (flags & REDIS_HASH_VALUE) {
-            addHashIteratorCursorToReply(c, hi, REDIS_HASH_VALUE);
+        if (flags & OBJ_HASH_VALUE) {
+            addHashIteratorCursorToReply(c, hi, OBJ_HASH_VALUE);
             count++;
         }
     }
 
     hashTypeReleaseIterator(hi);
-    redisAssert(count == length);
+    serverAssert(count == length);
 }
 
-void hkeysCommand(redisClient *c) {
-    genericHgetallCommand(c,REDIS_HASH_KEY);
+void hkeysCommand(client *c) {
+    genericHgetallCommand(c,OBJ_HASH_KEY);
 }
 
-void hvalsCommand(redisClient *c) {
-    genericHgetallCommand(c,REDIS_HASH_VALUE);
+void hvalsCommand(client *c) {
+    genericHgetallCommand(c,OBJ_HASH_VALUE);
 }
 
-void hgetallCommand(redisClient *c) {
-    genericHgetallCommand(c,REDIS_HASH_KEY|REDIS_HASH_VALUE);
+void hgetallCommand(client *c) {
+    genericHgetallCommand(c,OBJ_HASH_KEY|OBJ_HASH_VALUE);
 }
 
-void hexistsCommand(redisClient *c) {
+void hexistsCommand(client *c) {
     robj *o;
     if ((o = lookupKeyReadOrReply(c,c->argv[1],shared.czero)) == NULL ||
-        checkType(c,o,REDIS_HASH)) return;
+        checkType(c,o,OBJ_HASH)) return;
 
     addReply(c, hashTypeExists(o,c->argv[2]) ? shared.cone : shared.czero);
 }
 
-void hscanCommand(redisClient *c) {
+void hscanCommand(client *c) {
     robj *o;
     unsigned long cursor;
 
-    if (parseScanCursorOrReply(c,c->argv[2],&cursor) == REDIS_ERR) return;
+    if (parseScanCursorOrReply(c,c->argv[2],&cursor) == C_ERR) return;
     if ((o = lookupKeyReadOrReply(c,c->argv[1],shared.emptyscan)) == NULL ||
-        checkType(c,o,REDIS_HASH)) return;
+        checkType(c,o,OBJ_HASH)) return;
     scanGenericCommand(c,o,cursor);
 }
