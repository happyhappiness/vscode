@@ -257,6 +257,43 @@ void setrangeCommand(redisClient *c) {
     addReplyLongLong(c,sdslen(o->ptr));
 }
 
+void getrangeCommand(redisClient *c) {
+    robj *o;
+    long start, end;
+    char *str, llbuf[32];
+    size_t strlen;
+
+    if (getLongFromObjectOrReply(c,c->argv[2],&start,NULL) != REDIS_OK)
+        return;
+    if (getLongFromObjectOrReply(c,c->argv[3],&end,NULL) != REDIS_OK)
+        return;
+    if ((o = lookupKeyReadOrReply(c,c->argv[1],shared.nullbulk)) == NULL ||
+        checkType(c,o,REDIS_STRING)) return;
+
+    if (o->encoding == REDIS_ENCODING_INT) {
+        str = llbuf;
+        strlen = ll2string(llbuf,sizeof(llbuf),(long)o->ptr);
+    } else {
+        str = o->ptr;
+        strlen = sdslen(str);
+    }
+
+    /* Convert negative indexes */
+    if (start < 0) start = strlen+start;
+    if (end < 0) end = strlen+end;
+    if (start < 0) start = 0;
+    if (end < 0) end = 0;
+    if ((unsigned)end >= strlen) end = strlen-1;
+
+    /* Precondition: end >= 0 && end < strlen, so the only condition where
+     * nothing can be returned is: start > end. */
+    if (start > end) {
+        addReply(c,shared.nullbulk);
+    } else {
+        addReplyBulkCBuffer(c,(char*)str+start,end-start+1);
+    }
+}
+
 void mgetCommand(redisClient *c) {
     int j;
 
@@ -400,43 +437,6 @@ void appendCommand(redisClient *c) {
     addReplyLongLong(c,totlen);
 }
 
-void substrCommand(redisClient *c) {
-    robj *o;
-    long start = atoi(c->argv[2]->ptr);
-    long end = atoi(c->argv[3]->ptr);
-    size_t rangelen, strlen;
-    sds range;
-
-    if ((o = lookupKeyReadOrReply(c,c->argv[1],shared.nullbulk)) == NULL ||
-        checkType(c,o,REDIS_STRING)) return;
-
-    o = getDecodedObject(o);
-    strlen = sdslen(o->ptr);
-
-    /* convert negative indexes */
-    if (start < 0) start = strlen+start;
-    if (end < 0) end = strlen+end;
-    if (start < 0) start = 0;
-    if (end < 0) end = 0;
-
-    /* indexes sanity checks */
-    if (start > end || (size_t)start >= strlen) {
-        /* Out of range start or start > end result in null reply */
-        addReply(c,shared.nullbulk);
-        decrRefCount(o);
-        return;
-    }
-    if ((size_t)end >= strlen) end = strlen-1;
-    rangelen = (end-start)+1;
-
-    /* Return the result */
-    addReplySds(c,sdscatprintf(sdsempty(),"$%zu\r\n",rangelen));
-    range = sdsnewlen((char*)o->ptr+start,rangelen);
-    addReplySds(c,range);
-    addReply(c,shared.crlf);
-    decrRefCount(o);
-}
-
 void strlenCommand(redisClient *c) {
     robj *o;
 