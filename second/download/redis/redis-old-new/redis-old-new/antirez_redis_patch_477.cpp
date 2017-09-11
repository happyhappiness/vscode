@@ -150,9 +150,9 @@ void computeDatasetDigest(unsigned char *final) {
             expiretime = getExpire(db,keyobj);
 
             /* Save the key and associated value */
-            if (o->type == REDIS_STRING) {
+            if (o->type == OBJ_STRING) {
                 mixObjectDigest(digest,o);
-            } else if (o->type == REDIS_LIST) {
+            } else if (o->type == OBJ_LIST) {
                 listTypeIterator *li = listTypeInitIterator(o,0,REDIS_TAIL);
                 listTypeEntry entry;
                 while(listTypeNext(li,&entry)) {
@@ -161,18 +161,18 @@ void computeDatasetDigest(unsigned char *final) {
                     decrRefCount(eleobj);
                 }
                 listTypeReleaseIterator(li);
-            } else if (o->type == REDIS_SET) {
+            } else if (o->type == OBJ_SET) {
                 setTypeIterator *si = setTypeInitIterator(o);
                 robj *ele;
                 while((ele = setTypeNextObject(si)) != NULL) {
                     xorObjectDigest(digest,ele);
                     decrRefCount(ele);
                 }
                 setTypeReleaseIterator(si);
-            } else if (o->type == REDIS_ZSET) {
+            } else if (o->type == OBJ_ZSET) {
                 unsigned char eledigest[20];
 
-                if (o->encoding == REDIS_ENCODING_ZIPLIST) {
+                if (o->encoding == OBJ_ENCODING_ZIPLIST) {
                     unsigned char *zl = o->ptr;
                     unsigned char *eptr, *sptr;
                     unsigned char *vstr;
@@ -202,7 +202,7 @@ void computeDatasetDigest(unsigned char *final) {
                         xorDigest(digest,eledigest,20);
                         zzlNext(zl,&eptr,&sptr);
                     }
-                } else if (o->encoding == REDIS_ENCODING_SKIPLIST) {
+                } else if (o->encoding == OBJ_ENCODING_SKIPLIST) {
                     zset *zs = o->ptr;
                     dictIterator *di = dictGetIterator(zs->dict);
                     dictEntry *de;
@@ -221,7 +221,7 @@ void computeDatasetDigest(unsigned char *final) {
                 } else {
                     redisPanic("Unknown sorted set encoding");
                 }
-            } else if (o->type == REDIS_HASH) {
+            } else if (o->type == OBJ_HASH) {
                 hashTypeIterator *hi;
                 robj *obj;
 
@@ -230,10 +230,10 @@ void computeDatasetDigest(unsigned char *final) {
                     unsigned char eledigest[20];
 
                     memset(eledigest,0,20);
-                    obj = hashTypeCurrentObject(hi,REDIS_HASH_KEY);
+                    obj = hashTypeCurrentObject(hi,OBJ_HASH_KEY);
                     mixObjectDigest(eledigest,obj);
                     decrRefCount(obj);
-                    obj = hashTypeCurrentObject(hi,REDIS_HASH_VALUE);
+                    obj = hashTypeCurrentObject(hi,OBJ_HASH_VALUE);
                     mixObjectDigest(eledigest,obj);
                     decrRefCount(obj);
                     xorDigest(digest,eledigest,20);
@@ -302,7 +302,7 @@ void debugCommand(client *c) {
         strenc = strEncoding(val->encoding);
 
         char extra[128] = {0};
-        if (val->encoding == REDIS_ENCODING_QUICKLIST) {
+        if (val->encoding == OBJ_ENCODING_QUICKLIST) {
             char *nextra = extra;
             int remaining = sizeof(extra);
             quicklist *ql = val->ptr;
@@ -353,7 +353,7 @@ void debugCommand(client *c) {
         val = dictGetVal(de);
         key = dictGetKey(de);
 
-        if (val->type != REDIS_STRING || !sdsEncodedObject(val)) {
+        if (val->type != OBJ_STRING || !sdsEncodedObject(val)) {
             addReplyError(c,"Not an sds encoded string.");
         } else {
             addReplyStatusFormat(c,
@@ -495,7 +495,7 @@ void _redisAssertPrintClientInfo(client *c) {
         char buf[128];
         char *arg;
 
-        if (c->argv[j]->type == REDIS_STRING && sdsEncodedObject(c->argv[j])) {
+        if (c->argv[j]->type == OBJ_STRING && sdsEncodedObject(c->argv[j])) {
             arg = (char*) c->argv[j]->ptr;
         } else {
             snprintf(buf,sizeof(buf),"Object type: %d, encoding: %d",
@@ -511,22 +511,22 @@ void serverLogObjectDebugInfo(robj *o) {
     serverLog(REDIS_WARNING,"Object type: %d", o->type);
     serverLog(REDIS_WARNING,"Object encoding: %d", o->encoding);
     serverLog(REDIS_WARNING,"Object refcount: %d", o->refcount);
-    if (o->type == REDIS_STRING && sdsEncodedObject(o)) {
+    if (o->type == OBJ_STRING && sdsEncodedObject(o)) {
         serverLog(REDIS_WARNING,"Object raw string len: %zu", sdslen(o->ptr));
         if (sdslen(o->ptr) < 4096) {
             sds repr = sdscatrepr(sdsempty(),o->ptr,sdslen(o->ptr));
             serverLog(REDIS_WARNING,"Object raw string content: %s", repr);
             sdsfree(repr);
         }
-    } else if (o->type == REDIS_LIST) {
+    } else if (o->type == OBJ_LIST) {
         serverLog(REDIS_WARNING,"List length: %d", (int) listTypeLength(o));
-    } else if (o->type == REDIS_SET) {
+    } else if (o->type == OBJ_SET) {
         serverLog(REDIS_WARNING,"Set size: %d", (int) setTypeSize(o));
-    } else if (o->type == REDIS_HASH) {
+    } else if (o->type == OBJ_HASH) {
         serverLog(REDIS_WARNING,"Hash size: %d", (int) hashTypeLength(o));
-    } else if (o->type == REDIS_ZSET) {
+    } else if (o->type == OBJ_ZSET) {
         serverLog(REDIS_WARNING,"Sorted set size: %d", (int) zsetLength(o));
-        if (o->encoding == REDIS_ENCODING_SKIPLIST)
+        if (o->encoding == OBJ_ENCODING_SKIPLIST)
             serverLog(REDIS_WARNING,"Skiplist level: %d", (int) ((zset*)o->ptr)->zsl->level);
     }
 }