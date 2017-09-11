@@ -138,7 +138,7 @@ robj *hashTypeGetObject(robj *o, robj *field) {
             value = aux;
         }
     } else {
-        redisPanic("Unknown hash encoding");
+        serverPanic("Unknown hash encoding");
     }
     return value;
 }
@@ -161,7 +161,7 @@ size_t hashTypeGetValueLength(robj *o, robj *field) {
         if (hashTypeGetFromHashTable(o, field, &aux) == 0)
             len = stringObjectLen(aux);
     } else {
-        redisPanic("Unknown hash encoding");
+        serverPanic("Unknown hash encoding");
     }
     return len;
 }
@@ -180,7 +180,7 @@ int hashTypeExists(robj *o, robj *field) {
 
         if (hashTypeGetFromHashTable(o, field, &aux) == 0) return 1;
     } else {
-        redisPanic("Unknown hash encoding");
+        serverPanic("Unknown hash encoding");
     }
     return 0;
 }
@@ -236,7 +236,7 @@ int hashTypeSet(robj *o, robj *field, robj *value) {
         }
         incrRefCount(value);
     } else {
-        redisPanic("Unknown hash encoding");
+        serverPanic("Unknown hash encoding");
     }
     return update;
 }
@@ -274,7 +274,7 @@ int hashTypeDelete(robj *o, robj *field) {
         }
 
     } else {
-        redisPanic("Unknown hash encoding");
+        serverPanic("Unknown hash encoding");
     }
 
     return deleted;
@@ -289,7 +289,7 @@ unsigned long hashTypeLength(robj *o) {
     } else if (o->encoding == OBJ_ENCODING_HT) {
         length = dictSize((dict*)o->ptr);
     } else {
-        redisPanic("Unknown hash encoding");
+        serverPanic("Unknown hash encoding");
     }
 
     return length;
@@ -306,7 +306,7 @@ hashTypeIterator *hashTypeInitIterator(robj *subject) {
     } else if (hi->encoding == OBJ_ENCODING_HT) {
         hi->di = dictGetIterator(subject->ptr);
     } else {
-        redisPanic("Unknown hash encoding");
+        serverPanic("Unknown hash encoding");
     }
 
     return hi;
@@ -352,7 +352,7 @@ int hashTypeNext(hashTypeIterator *hi) {
     } else if (hi->encoding == OBJ_ENCODING_HT) {
         if ((hi->de = dictNext(hi->di)) == NULL) return C_ERR;
     } else {
-        redisPanic("Unknown hash encoding");
+        serverPanic("Unknown hash encoding");
     }
     return C_OK;
 }
@@ -410,7 +410,7 @@ robj *hashTypeCurrentObject(hashTypeIterator *hi, int what) {
         hashTypeCurrentFromHashTable(hi, what, &dst);
         incrRefCount(dst);
     } else {
-        redisPanic("Unknown hash encoding");
+        serverPanic("Unknown hash encoding");
     }
     return dst;
 }
@@ -452,7 +452,7 @@ void hashTypeConvertZiplist(robj *o, int enc) {
             value = tryObjectEncoding(value);
             ret = dictAdd(dict, field, value);
             if (ret != DICT_OK) {
-                serverLogHexDump(REDIS_WARNING,"ziplist with dup elements dump",
+                serverLogHexDump(LL_WARNING,"ziplist with dup elements dump",
                     o->ptr,ziplistBlobLen(o->ptr));
                 serverAssert(ret == DICT_OK);
             }
@@ -465,17 +465,17 @@ void hashTypeConvertZiplist(robj *o, int enc) {
         o->ptr = dict;
 
     } else {
-        redisPanic("Unknown hash encoding");
+        serverPanic("Unknown hash encoding");
     }
 }
 
 void hashTypeConvert(robj *o, int enc) {
     if (o->encoding == OBJ_ENCODING_ZIPLIST) {
         hashTypeConvertZiplist(o, enc);
     } else if (o->encoding == OBJ_ENCODING_HT) {
-        redisPanic("Not implemented");
+        serverPanic("Not implemented");
     } else {
-        redisPanic("Unknown hash encoding");
+        serverPanic("Unknown hash encoding");
     }
 }
 
@@ -493,7 +493,7 @@ void hsetCommand(client *c) {
     update = hashTypeSet(o,c->argv[2],c->argv[3]);
     addReply(c, update ? shared.czero : shared.cone);
     signalModifiedKey(c->db,c->argv[1]);
-    notifyKeyspaceEvent(REDIS_NOTIFY_HASH,"hset",c->argv[1],c->db->id);
+    notifyKeyspaceEvent(NOTIFY_HASH,"hset",c->argv[1],c->db->id);
     server.dirty++;
 }
 
@@ -509,7 +509,7 @@ void hsetnxCommand(client *c) {
         hashTypeSet(o,c->argv[2],c->argv[3]);
         addReply(c, shared.cone);
         signalModifiedKey(c->db,c->argv[1]);
-        notifyKeyspaceEvent(REDIS_NOTIFY_HASH,"hset",c->argv[1],c->db->id);
+        notifyKeyspaceEvent(NOTIFY_HASH,"hset",c->argv[1],c->db->id);
         server.dirty++;
     }
 }
@@ -531,7 +531,7 @@ void hmsetCommand(client *c) {
     }
     addReply(c, shared.ok);
     signalModifiedKey(c->db,c->argv[1]);
-    notifyKeyspaceEvent(REDIS_NOTIFY_HASH,"hset",c->argv[1],c->db->id);
+    notifyKeyspaceEvent(NOTIFY_HASH,"hset",c->argv[1],c->db->id);
     server.dirty++;
 }
 
@@ -565,7 +565,7 @@ void hincrbyCommand(client *c) {
     decrRefCount(new);
     addReplyLongLong(c,value);
     signalModifiedKey(c->db,c->argv[1]);
-    notifyKeyspaceEvent(REDIS_NOTIFY_HASH,"hincrby",c->argv[1],c->db->id);
+    notifyKeyspaceEvent(NOTIFY_HASH,"hincrby",c->argv[1],c->db->id);
     server.dirty++;
 }
 
@@ -592,7 +592,7 @@ void hincrbyfloatCommand(client *c) {
     hashTypeSet(o,c->argv[2],new);
     addReplyBulk(c,new);
     signalModifiedKey(c->db,c->argv[1]);
-    notifyKeyspaceEvent(REDIS_NOTIFY_HASH,"hincrbyfloat",c->argv[1],c->db->id);
+    notifyKeyspaceEvent(NOTIFY_HASH,"hincrbyfloat",c->argv[1],c->db->id);
     server.dirty++;
 
     /* Always replicate HINCRBYFLOAT as an HSET command with the final value
@@ -640,7 +640,7 @@ static void addHashFieldToReply(client *c, robj *o, robj *field) {
         }
 
     } else {
-        redisPanic("Unknown hash encoding");
+        serverPanic("Unknown hash encoding");
     }
 }
 
@@ -690,9 +690,9 @@ void hdelCommand(client *c) {
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
@@ -736,7 +736,7 @@ static void addHashIteratorCursorToReply(client *c, hashTypeIterator *hi, int wh
         addReplyBulk(c, value);
 
     } else {
-        redisPanic("Unknown hash encoding");
+        serverPanic("Unknown hash encoding");
     }
 }
 