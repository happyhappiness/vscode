@@ -44,10 +44,10 @@ size_t sdsZmallocSize(sds s) {
 /* Return the amount of memory used by the sds string at object->ptr
  * for a string object. */
 size_t getStringObjectSdsUsedMemory(robj *o) {
-    redisAssertWithInfo(NULL,o,o->type == REDIS_STRING);
+    redisAssertWithInfo(NULL,o,o->type == OBJ_STRING);
     switch(o->encoding) {
-    case REDIS_ENCODING_RAW: return sdsZmallocSize(o->ptr);
-    case REDIS_ENCODING_EMBSTR: return zmalloc_size(o)-sizeof(robj);
+    case OBJ_ENCODING_RAW: return sdsZmallocSize(o->ptr);
+    case OBJ_ENCODING_EMBSTR: return zmalloc_size(o)-sizeof(robj);
     default: return 0; /* Just integer encoding for now. */
     }
 }
@@ -232,7 +232,7 @@ void _addReplyObjectToList(client *c, robj *o) {
 
         /* Append to this object when possible. */
         if (tail->ptr != NULL &&
-            tail->encoding == REDIS_ENCODING_RAW &&
+            tail->encoding == OBJ_ENCODING_RAW &&
             sdslen(tail->ptr)+sdslen(o->ptr) <= REDIS_REPLY_CHUNK_BYTES)
         {
             c->reply_bytes -= sdsZmallocSize(tail->ptr);
@@ -259,13 +259,13 @@ void _addReplySdsToList(client *c, sds s) {
     }
 
     if (listLength(c->reply) == 0) {
-        listAddNodeTail(c->reply,createObject(REDIS_STRING,s));
+        listAddNodeTail(c->reply,createObject(OBJ_STRING,s));
         c->reply_bytes += sdsZmallocSize(s);
     } else {
         tail = listNodeValue(listLast(c->reply));
 
         /* Append to this object when possible. */
-        if (tail->ptr != NULL && tail->encoding == REDIS_ENCODING_RAW &&
+        if (tail->ptr != NULL && tail->encoding == OBJ_ENCODING_RAW &&
             sdslen(tail->ptr)+sdslen(s) <= REDIS_REPLY_CHUNK_BYTES)
         {
             c->reply_bytes -= sdsZmallocSize(tail->ptr);
@@ -274,7 +274,7 @@ void _addReplySdsToList(client *c, sds s) {
             c->reply_bytes += sdsZmallocSize(tail->ptr);
             sdsfree(s);
         } else {
-            listAddNodeTail(c->reply,createObject(REDIS_STRING,s));
+            listAddNodeTail(c->reply,createObject(OBJ_STRING,s));
             c->reply_bytes += sdsZmallocSize(s);
         }
     }
@@ -295,7 +295,7 @@ void _addReplyStringToList(client *c, const char *s, size_t len) {
         tail = listNodeValue(listLast(c->reply));
 
         /* Append to this object when possible. */
-        if (tail->ptr != NULL && tail->encoding == REDIS_ENCODING_RAW &&
+        if (tail->ptr != NULL && tail->encoding == OBJ_ENCODING_RAW &&
             sdslen(tail->ptr)+len <= REDIS_REPLY_CHUNK_BYTES)
         {
             c->reply_bytes -= sdsZmallocSize(tail->ptr);
@@ -330,7 +330,7 @@ void addReply(client *c, robj *obj) {
     if (sdsEncodedObject(obj)) {
         if (_addReplyToBuffer(c,obj->ptr,sdslen(obj->ptr)) != REDIS_OK)
             _addReplyObjectToList(c,obj);
-    } else if (obj->encoding == REDIS_ENCODING_INT) {
+    } else if (obj->encoding == OBJ_ENCODING_INT) {
         /* Optimization: if there is room in the static buffer for 32 bytes
          * (more than the max chars a 64 bit integer can take as string) we
          * avoid decoding the object and go for the lower level approach. */
@@ -425,7 +425,7 @@ void *addDeferredMultiBulkLength(client *c) {
      * ready to be sent, since we are sure that before returning to the
      * event loop setDeferredMultiBulkLength() will be called. */
     if (prepareClientToWrite(c) != REDIS_OK) return NULL;
-    listAddNodeTail(c->reply,createObject(REDIS_STRING,NULL));
+    listAddNodeTail(c->reply,createObject(OBJ_STRING,NULL));
     return listLast(c->reply);
 }
 
@@ -439,7 +439,7 @@ void setDeferredMultiBulkLength(client *c, void *node, long length) {
 
     len = listNodeValue(ln);
     len->ptr = sdscatprintf(sdsempty(),"*%ld\r\n",length);
-    len->encoding = REDIS_ENCODING_RAW; /* in case it was an EMBSTR. */
+    len->encoding = OBJ_ENCODING_RAW; /* in case it was an EMBSTR. */
     c->reply_bytes += sdsZmallocSize(len->ptr);
     if (ln->next != NULL) {
         next = listNodeValue(ln->next);
@@ -970,7 +970,7 @@ int processInlineBuffer(client *c) {
     /* Create redis objects for all arguments. */
     for (c->argc = 0, j = 0; j < argc; j++) {
         if (sdslen(argv[j])) {
-            c->argv[c->argc] = createObject(REDIS_STRING,argv[j]);
+            c->argv[c->argc] = createObject(OBJ_STRING,argv[j]);
             c->argc++;
         } else {
             sdsfree(argv[j]);
@@ -1104,7 +1104,7 @@ int processMultibulkBuffer(client *c) {
                 c->bulklen >= REDIS_MBULK_BIG_ARG &&
                 (signed) sdslen(c->querybuf) == c->bulklen+2)
             {
-                c->argv[c->argc++] = createObject(REDIS_STRING,c->querybuf);
+                c->argv[c->argc++] = createObject(OBJ_STRING,c->querybuf);
                 sdsIncrLen(c->querybuf,-2); /* remove CRLF */
                 c->querybuf = sdsempty();
                 /* Assume that if we saw a fat argument we'll see another one