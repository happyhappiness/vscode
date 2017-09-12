@@ -4836,6 +4836,77 @@ static unsigned long lLength(robj *subject) {
     }
 }
 
+/* Structure to hold set iteration abstraction. */
+typedef struct {
+    robj *subject;
+    unsigned char encoding;
+    unsigned char *zi;
+    listNode *ln;
+} lIterator;
+
+/* Initialize an iterator at the specified index. */
+static lIterator *lInitIterator(robj *subject, int index) {
+    lIterator *li = zmalloc(sizeof(lIterator));
+    li->subject = subject;
+    li->encoding = subject->encoding;
+    if (li->encoding == REDIS_ENCODING_ZIPLIST) {
+        li->zi = ziplistIndex(subject->ptr,index);
+    } else if (li->encoding == REDIS_ENCODING_LIST) {
+        li->ln = listIndex(subject->ptr,index);
+    } else {
+        redisPanic("Unknown list encoding");
+    }
+    return li;
+}
+
+/* Clean up the iterator. */
+static void lReleaseIterator(lIterator *li) {
+    zfree(li);
+}
+
+/* Return entry or NULL at the current position of the iterator. */
+static robj *lGet(lIterator *li) {
+    robj *value = NULL;
+    if (li->encoding == REDIS_ENCODING_ZIPLIST) {
+        char *v;
+        unsigned int vlen;
+        long long vval;
+        redisAssert(li->zi != NULL);
+        if (ziplistGet(li->zi,&v,&vlen,&vval)) {
+            if (v) {
+                value = createStringObject(v,vlen);
+            } else {
+                value = createStringObjectFromLongLong(vval);
+            }
+        }
+    } else if (li->encoding == REDIS_ENCODING_LIST) {
+        redisAssert(li->ln != NULL);
+        value = listNodeValue(li->ln);
+        incrRefCount(value);
+    } else {
+        redisPanic("Unknown list encoding");
+    }
+    return value;
+}
+
+/* Move to the next or previous entry in the list. */
+static void lMove(lIterator *li, int where) {
+    if (li->encoding == REDIS_ENCODING_ZIPLIST) {
+        redisAssert(li->zi != NULL);
+        if (where == REDIS_HEAD)
+            li->zi = ziplistPrev(li->zi);
+        else
+            li->zi = ziplistNext(li->zi);
+    } else if (li->encoding == REDIS_ENCODING_LIST) {
+        redisAssert(li->ln != NULL);
+        if (where == REDIS_HEAD)
+            li->ln = li->ln->prev;
+        else
+            li->ln = li->ln->next;
+    } else {
+        redisPanic("Unknown list encoding");
+    }
+}
 
 static void pushGenericCommand(redisClient *c, int where) {
     robj *lobj = lookupKeyWrite(c->db,c->argv[1]);
@@ -4968,19 +5039,15 @@ static void rpopCommand(redisClient *c) {
 }
 
 static void lrangeCommand(redisClient *c) {
-    robj *o;
+    robj *o, *value;
     int start = atoi(c->argv[2]->ptr);
     int end = atoi(c->argv[3]->ptr);
     int llen;
     int rangelen, j;
-    list *list;
-    listNode *ln;
-    robj *ele;
 
     if ((o = lookupKeyReadOrReply(c,c->argv[1],shared.emptymultibulk)) == NULL
          || checkType(c,o,REDIS_LIST)) return;
-    list = o->ptr;
-    llen = listLength(list);
+    llen = lLength(o);
 
     /* convert negative indexes */
     if (start < 0) start = llen+start;
@@ -4998,13 +5065,15 @@ static void lrangeCommand(redisClient *c) {
     rangelen = (end-start)+1;
 
     /* Return the result in form of a multi-bulk reply */
-    ln = listIndex(list, start);
     addReplySds(c,sdscatprintf(sdsempty(),"*%d\r\n",rangelen));
+    lIterator *li = lInitIterator(o,start);
     for (j = 0; j < rangelen; j++) {
-        ele = listNodeValue(ln);
-        addReplyBulk(c,ele);
-        ln = ln->next;
+        value = lGet(li);
+        redisAssert(value != NULL);
+        addReplyBulk(c,value);
+        lMove(li,REDIS_TAIL);
     }
+    lReleaseIterator(li);
 }
 
 static void ltrimCommand(redisClient *c) {