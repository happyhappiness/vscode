@@ -4864,6 +4864,17 @@ static void lReleaseIterator(lIterator *li) {
     zfree(li);
 }
 
+/* Whether the entry pointed at is a valid entry. */
+static int lIsEntry(lIterator *li) {
+    if (li->encoding == REDIS_ENCODING_ZIPLIST) {
+        return li->zi != NULL;
+    } else if (li->encoding == REDIS_ENCODING_LIST) {
+        return li->ln != NULL;
+    } else {
+        redisPanic("Unknown list encoding");
+    }
+}
+
 /* Return entry or NULL at the current position of the iterator. */
 static robj *lGet(lIterator *li) {
     robj *value = NULL;
@@ -4889,6 +4900,36 @@ static robj *lGet(lIterator *li) {
     return value;
 }
 
+/* Delete the element pointed to. */
+static void lDelete(lIterator *li, int direction) {
+    if (li->encoding == REDIS_ENCODING_ZIPLIST) {
+        direction = (direction == REDIS_HEAD) ? ZIPLIST_HEAD : ZIPLIST_TAIL;
+        li->subject->ptr = ziplistDelete(li->subject->ptr,&li->zi,direction);
+    } else if (li->encoding == REDIS_ENCODING_LIST) {
+        listNode *next;
+        if (direction == REDIS_HEAD)
+            next = li->ln->prev;
+        else
+            next = li->ln->next;
+        listDelNode(li->subject->ptr,li->ln);
+        li->ln = next;
+    } else {
+        redisPanic("Unknown list encoding");
+    }
+}
+
+/* Compare the given object with the entry at the current position. */
+static int lEqualTo(lIterator *li, robj *o) {
+    if (li->encoding == REDIS_ENCODING_ZIPLIST) {
+        redisAssert(o->encoding == REDIS_ENCODING_RAW);
+        return ziplistCompare(li->zi,o->ptr,sdslen(o->ptr));
+    } else if (li->encoding == REDIS_ENCODING_LIST) {
+        return equalStringObjects(o,listNodeValue(li->ln));
+    } else {
+        redisPanic("Unknown list encoding");
+    }
+}
+
 /* Move to the next or previous entry in the list. */
 static void lMove(lIterator *li, int where) {
     if (li->encoding == REDIS_ENCODING_ZIPLIST) {
@@ -5129,35 +5170,45 @@ static void ltrimCommand(redisClient *c) {
 }
 
 static void lremCommand(redisClient *c) {
-    robj *o;
-    list *list;
-    listNode *ln, *next;
+    robj *subject, *obj = c->argv[3];
     int toremove = atoi(c->argv[2]->ptr);
     int removed = 0;
-    int fromtail = 0;
+    int direction;
 
-    if ((o = lookupKeyWriteOrReply(c,c->argv[1],shared.czero)) == NULL ||
-        checkType(c,o,REDIS_LIST)) return;
-    list = o->ptr;
+    subject = lookupKeyWriteOrReply(c,c->argv[1],shared.czero);
+    if (subject == NULL || checkType(c,subject,REDIS_LIST)) return;
+
+    /* Make sure obj is raw when we're dealing with a ziplist */
+    if (subject->encoding == REDIS_ENCODING_ZIPLIST)
+        obj = getDecodedObject(obj);
 
+    lIterator *li;
     if (toremove < 0) {
         toremove = -toremove;
-        fromtail = 1;
+        direction = REDIS_HEAD;
+        li = lInitIterator(subject,-1);
+    } else {
+        direction = REDIS_TAIL;
+        li = lInitIterator(subject,0);
     }
-    ln = fromtail ? list->tail : list->head;
-    while (ln) {
-        robj *ele = listNodeValue(ln);
 
-        next = fromtail ? ln->prev : ln->next;
-        if (equalStringObjects(ele,c->argv[3])) {
-            listDelNode(list,ln);
+    while (toremove && lIsEntry(li)) {
+        if (lEqualTo(li,obj)) {
+            lDelete(li,direction);
             server.dirty++;
+            toremove--;
             removed++;
-            if (toremove && removed == toremove) break;
+        } else {
+            lMove(li,direction);
         }
-        ln = next;
     }
-    if (listLength(list) == 0) deleteKey(c->db,c->argv[1]);
+    lReleaseIterator(li);
+
+    /* Clean up raw encoded object */
+    if (subject->encoding == REDIS_ENCODING_ZIPLIST)
+        decrRefCount(obj);
+
+    if (lLength(subject) == 0) deleteKey(c->db,c->argv[1]);
     addReplySds(c,sdscatprintf(sdsempty(),":%d\r\n",removed));
 }
 