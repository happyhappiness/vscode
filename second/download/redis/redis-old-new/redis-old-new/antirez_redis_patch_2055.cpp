@@ -4806,7 +4806,7 @@ static robj *lPop(robj *subject, int where) {
                 value = createStringObjectFromLongLong(vval);
             }
         }
-        subject->ptr = ziplistDelete(subject->ptr,&p,ZIPLIST_TAIL);
+        subject->ptr = ziplistDelete(subject->ptr,&p);
     } else if (subject->encoding == REDIS_ENCODING_LIST) {
         list *list = subject->ptr;
         listNode *ln;
@@ -4840,15 +4840,24 @@ static unsigned long lLength(robj *subject) {
 typedef struct {
     robj *subject;
     unsigned char encoding;
+    unsigned char direction; /* Iteration direction */
     unsigned char *zi;
     listNode *ln;
 } lIterator;
 
+/* Structure for an entry while iterating over a list. */
+typedef struct {
+    lIterator *li;
+    unsigned char *zi;  /* Entry in ziplist */
+    listNode *ln;       /* Entry in linked list */
+} lEntry;
+
 /* Initialize an iterator at the specified index. */
-static lIterator *lInitIterator(robj *subject, int index) {
+static lIterator *lInitIterator(robj *subject, int index, unsigned char direction) {
     lIterator *li = zmalloc(sizeof(lIterator));
     li->subject = subject;
     li->encoding = subject->encoding;
+    li->direction = direction;
     if (li->encoding == REDIS_ENCODING_ZIPLIST) {
         li->zi = ziplistIndex(subject->ptr,index);
     } else if (li->encoding == REDIS_ENCODING_LIST) {
@@ -4864,86 +4873,94 @@ static void lReleaseIterator(lIterator *li) {
     zfree(li);
 }
 
-/* Whether the entry pointed at is a valid entry. */
-static int lIsEntry(lIterator *li) {
+/* Stores pointer to current the entry in the provided entry structure
+ * and advances the position of the iterator. Returns 1 when the current
+ * entry is in fact an entry, 0 otherwise. */
+static int lNext(lIterator *li, lEntry *entry) {
+    entry->li = li;
     if (li->encoding == REDIS_ENCODING_ZIPLIST) {
-        return li->zi != NULL;
+        entry->zi = li->zi;
+        if (entry->zi != NULL) {
+            if (li->direction == REDIS_TAIL)
+                li->zi = ziplistNext(li->subject->ptr,li->zi);
+            else
+                li->zi = ziplistPrev(li->subject->ptr,li->zi);
+            return 1;
+        }
     } else if (li->encoding == REDIS_ENCODING_LIST) {
-        return li->ln != NULL;
+        entry->ln = li->ln;
+        if (entry->ln != NULL) {
+            if (li->direction == REDIS_TAIL)
+                li->ln = li->ln->next;
+            else
+                li->ln = li->ln->prev;
+            return 1;
+        }
     } else {
         redisPanic("Unknown list encoding");
     }
+    return 0;
 }
 
 /* Return entry or NULL at the current position of the iterator. */
-static robj *lGet(lIterator *li) {
+static robj *lGet(lEntry *entry) {
+    lIterator *li = entry->li;
     robj *value = NULL;
     if (li->encoding == REDIS_ENCODING_ZIPLIST) {
         char *v;
         unsigned int vlen;
         long long vval;
-        redisAssert(li->zi != NULL);
-        if (ziplistGet(li->zi,&v,&vlen,&vval)) {
+        redisAssert(entry->zi != NULL);
+        if (ziplistGet(entry->zi,&v,&vlen,&vval)) {
             if (v) {
                 value = createStringObject(v,vlen);
             } else {
                 value = createStringObjectFromLongLong(vval);
             }
         }
     } else if (li->encoding == REDIS_ENCODING_LIST) {
-        redisAssert(li->ln != NULL);
-        value = listNodeValue(li->ln);
+        redisAssert(entry->ln != NULL);
+        value = listNodeValue(entry->ln);
         incrRefCount(value);
     } else {
         redisPanic("Unknown list encoding");
     }
     return value;
 }
 
-/* Delete the element pointed to. */
-static void lDelete(lIterator *li, int direction) {
-    if (li->encoding == REDIS_ENCODING_ZIPLIST) {
-        direction = (direction == REDIS_HEAD) ? ZIPLIST_HEAD : ZIPLIST_TAIL;
-        li->subject->ptr = ziplistDelete(li->subject->ptr,&li->zi,direction);
-    } else if (li->encoding == REDIS_ENCODING_LIST) {
-        listNode *next;
-        if (direction == REDIS_HEAD)
-            next = li->ln->prev;
-        else
-            next = li->ln->next;
-        listDelNode(li->subject->ptr,li->ln);
-        li->ln = next;
-    } else {
-        redisPanic("Unknown list encoding");
-    }
-}
-
 /* Compare the given object with the entry at the current position. */
-static int lEqualTo(lIterator *li, robj *o) {
+static int lEqual(lEntry *entry, robj *o) {
+    lIterator *li = entry->li;
     if (li->encoding == REDIS_ENCODING_ZIPLIST) {
         redisAssert(o->encoding == REDIS_ENCODING_RAW);
-        return ziplistCompare(li->zi,o->ptr,sdslen(o->ptr));
+        return ziplistCompare(entry->zi,o->ptr,sdslen(o->ptr));
     } else if (li->encoding == REDIS_ENCODING_LIST) {
-        return equalStringObjects(o,listNodeValue(li->ln));
+        return equalStringObjects(o,listNodeValue(entry->ln));
     } else {
         redisPanic("Unknown list encoding");
     }
 }
 
-/* Move to the next or previous entry in the list. */
-static void lMove(lIterator *li, int where) {
+/* Delete the element pointed to. */
+static void lDelete(lEntry *entry) {
+    lIterator *li = entry->li;
     if (li->encoding == REDIS_ENCODING_ZIPLIST) {
-        redisAssert(li->zi != NULL);
-        if (where == REDIS_HEAD)
-            li->zi = ziplistPrev(li->zi);
+        unsigned char *p = entry->zi;
+        li->subject->ptr = ziplistDelete(li->subject->ptr,&p);
+
+        /* Update position of the iterator depending on the direction */
+        if (li->direction == REDIS_TAIL)
+            li->zi = p;
         else
-            li->zi = ziplistNext(li->zi);
-    } else if (li->encoding == REDIS_ENCODING_LIST) {
-        redisAssert(li->ln != NULL);
-        if (where == REDIS_HEAD)
-            li->ln = li->ln->prev;
+            li->zi = ziplistPrev(li->subject->ptr,p);
+    } else if (entry->li->encoding == REDIS_ENCODING_LIST) {
+        listNode *next;
+        if (li->direction == REDIS_TAIL)
+            next = entry->ln->next;
         else
-            li->ln = li->ln->next;
+            next = entry->ln->prev;
+        listDelNode(li->subject->ptr,entry->ln);
+        li->ln = next;
     } else {
         redisPanic("Unknown list encoding");
     }
@@ -5037,7 +5054,7 @@ static void lsetCommand(redisClient *c) {
         if (p == NULL) {
             addReply(c,shared.outofrangeerr);
         } else {
-            o->ptr = ziplistDelete(o->ptr,&p,ZIPLIST_TAIL);
+            o->ptr = ziplistDelete(o->ptr,&p);
             value = getDecodedObject(value);
             o->ptr = ziplistInsert(o->ptr,p,value->ptr,sdslen(value->ptr));
             decrRefCount(value);
@@ -5089,6 +5106,7 @@ static void lrangeCommand(redisClient *c) {
     int end = atoi(c->argv[3]->ptr);
     int llen;
     int rangelen, j;
+    lEntry entry;
 
     if ((o = lookupKeyReadOrReply(c,c->argv[1],shared.emptymultibulk)) == NULL
          || checkType(c,o,REDIS_LIST)) return;
@@ -5111,12 +5129,12 @@ static void lrangeCommand(redisClient *c) {
 
     /* Return the result in form of a multi-bulk reply */
     addReplySds(c,sdscatprintf(sdsempty(),"*%d\r\n",rangelen));
-    lIterator *li = lInitIterator(o,start);
+    lIterator *li = lInitIterator(o,start,REDIS_TAIL);
     for (j = 0; j < rangelen; j++) {
-        value = lGet(li);
-        redisAssert(value != NULL);
+        redisAssert(lNext(li,&entry));
+        value = lGet(&entry);
         addReplyBulk(c,value);
-        lMove(li,REDIS_TAIL);
+        decrRefCount(value);
     }
     lReleaseIterator(li);
 }
@@ -5177,7 +5195,7 @@ static void lremCommand(redisClient *c) {
     robj *subject, *obj = c->argv[3];
     int toremove = atoi(c->argv[2]->ptr);
     int removed = 0;
-    int direction;
+    lEntry entry;
 
     subject = lookupKeyWriteOrReply(c,c->argv[1],shared.czero);
     if (subject == NULL || checkType(c,subject,REDIS_LIST)) return;
@@ -5189,21 +5207,17 @@ static void lremCommand(redisClient *c) {
     lIterator *li;
     if (toremove < 0) {
         toremove = -toremove;
-        direction = REDIS_HEAD;
-        li = lInitIterator(subject,-1);
+        li = lInitIterator(subject,-1,REDIS_HEAD);
     } else {
-        direction = REDIS_TAIL;
-        li = lInitIterator(subject,0);
+        li = lInitIterator(subject,0,REDIS_TAIL);
     }
 
-    while (lIsEntry(li)) {
-        if (lEqualTo(li,obj)) {
-            lDelete(li,direction);
+    while (lNext(li,&entry)) {
+        if (lEqual(&entry,obj)) {
+            lDelete(&entry);
             server.dirty++;
             removed++;
             if (toremove && removed == toremove) break;
-        } else {
-            lMove(li,direction);
         }
     }
     lReleaseIterator(li);