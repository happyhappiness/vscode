@@ -650,7 +650,7 @@ static struct redisCommand *lookupCommand(char *name);
 static void call(redisClient *c, struct redisCommand *cmd);
 static void resetClient(redisClient *c);
 static void convertToRealHash(robj *o);
-static void convertList(robj *o, int enc);
+static void listTypeConvert(robj *o, int enc);
 static int pubsubUnsubscribeAllChannels(redisClient *c, int notify);
 static int pubsubUnsubscribeAllPatterns(redisClient *c, int notify);
 static void freePubsubPattern(void *p);
@@ -4181,7 +4181,7 @@ static robj *rdbLoadObject(int type, FILE *fp) {
             if (o->encoding == REDIS_ENCODING_ZIPLIST &&
                 ele->encoding == REDIS_ENCODING_RAW &&
                 sdslen(ele->ptr) > server.list_max_ziplist_value)
-                    convertList(o,REDIS_ENCODING_LIST);
+                    listTypeConvert(o,REDIS_ENCODING_LIST);
 
             if (o->encoding == REDIS_ENCODING_ZIPLIST) {
                 dec = getDecodedObject(ele);
@@ -4910,19 +4910,19 @@ static void moveCommand(redisClient *c) {
 /* Check the argument length to see if it requires us to convert the ziplist
  * to a real list. Only check raw-encoded objects because integer encoded
  * objects are never too long. */
-static void listTryConversion(robj *subject, robj *value) {
+static void listTypeTryConversion(robj *subject, robj *value) {
     if (subject->encoding != REDIS_ENCODING_ZIPLIST) return;
     if (value->encoding == REDIS_ENCODING_RAW &&
         sdslen(value->ptr) > server.list_max_ziplist_value)
-            convertList(subject,REDIS_ENCODING_LIST);
+            listTypeConvert(subject,REDIS_ENCODING_LIST);
 }
 
-static void lPush(robj *subject, robj *value, int where) {
+static void listTypePush(robj *subject, robj *value, int where) {
     /* Check if we need to convert the ziplist */
-    listTryConversion(subject,value);
+    listTypeTryConversion(subject,value);
     if (subject->encoding == REDIS_ENCODING_ZIPLIST &&
         ziplistLen(subject->ptr) > server.list_max_ziplist_entries)
-            convertList(subject,REDIS_ENCODING_LIST);
+            listTypeConvert(subject,REDIS_ENCODING_LIST);
 
     if (subject->encoding == REDIS_ENCODING_ZIPLIST) {
         int pos = (where == REDIS_HEAD) ? ZIPLIST_HEAD : ZIPLIST_TAIL;
@@ -4941,7 +4941,7 @@ static void lPush(robj *subject, robj *value, int where) {
     }
 }
 
-static robj *lPop(robj *subject, int where) {
+static robj *listTypePop(robj *subject, int where) {
     robj *value = NULL;
     if (subject->encoding == REDIS_ENCODING_ZIPLIST) {
         unsigned char *p;
@@ -4978,7 +4978,7 @@ static robj *lPop(robj *subject, int where) {
     return value;
 }
 
-static unsigned long lLength(robj *subject) {
+static unsigned long listTypeLength(robj *subject) {
     if (subject->encoding == REDIS_ENCODING_ZIPLIST) {
         return ziplistLen(subject->ptr);
     } else if (subject->encoding == REDIS_ENCODING_LIST) {
@@ -4995,18 +4995,18 @@ typedef struct {
     unsigned char direction; /* Iteration direction */
     unsigned char *zi;
     listNode *ln;
-} lIterator;
+} listTypeIterator;
 
 /* Structure for an entry while iterating over a list. */
 typedef struct {
-    lIterator *li;
+    listTypeIterator *li;
     unsigned char *zi;  /* Entry in ziplist */
     listNode *ln;       /* Entry in linked list */
-} lEntry;
+} listTypeEntry;
 
 /* Initialize an iterator at the specified index. */
-static lIterator *lInitIterator(robj *subject, int index, unsigned char direction) {
-    lIterator *li = zmalloc(sizeof(lIterator));
+static listTypeIterator *listTypeInitIterator(robj *subject, int index, unsigned char direction) {
+    listTypeIterator *li = zmalloc(sizeof(listTypeIterator));
     li->subject = subject;
     li->encoding = subject->encoding;
     li->direction = direction;
@@ -5021,14 +5021,14 @@ static lIterator *lInitIterator(robj *subject, int index, unsigned char directio
 }
 
 /* Clean up the iterator. */
-static void lReleaseIterator(lIterator *li) {
+static void listTypeReleaseIterator(listTypeIterator *li) {
     zfree(li);
 }
 
 /* Stores pointer to current the entry in the provided entry structure
  * and advances the position of the iterator. Returns 1 when the current
  * entry is in fact an entry, 0 otherwise. */
-static int lNext(lIterator *li, lEntry *entry) {
+static int listTypeNext(listTypeIterator *li, listTypeEntry *entry) {
     entry->li = li;
     if (li->encoding == REDIS_ENCODING_ZIPLIST) {
         entry->zi = li->zi;
@@ -5055,8 +5055,8 @@ static int lNext(lIterator *li, lEntry *entry) {
 }
 
 /* Return entry or NULL at the current position of the iterator. */
-static robj *lGet(lEntry *entry) {
-    lIterator *li = entry->li;
+static robj *listTypeGet(listTypeEntry *entry) {
+    listTypeIterator *li = entry->li;
     robj *value = NULL;
     if (li->encoding == REDIS_ENCODING_ZIPLIST) {
         unsigned char *vstr;
@@ -5081,8 +5081,8 @@ static robj *lGet(lEntry *entry) {
 }
 
 /* Compare the given object with the entry at the current position. */
-static int lEqual(lEntry *entry, robj *o) {
-    lIterator *li = entry->li;
+static int listTypeEqual(listTypeEntry *entry, robj *o) {
+    listTypeIterator *li = entry->li;
     if (li->encoding == REDIS_ENCODING_ZIPLIST) {
         redisAssert(o->encoding == REDIS_ENCODING_RAW);
         return ziplistCompare(entry->zi,o->ptr,sdslen(o->ptr));
@@ -5094,8 +5094,8 @@ static int lEqual(lEntry *entry, robj *o) {
 }
 
 /* Delete the element pointed to. */
-static void lDelete(lEntry *entry) {
-    lIterator *li = entry->li;
+static void listTypeDelete(listTypeEntry *entry) {
+    listTypeIterator *li = entry->li;
     if (li->encoding == REDIS_ENCODING_ZIPLIST) {
         unsigned char *p = entry->zi;
         li->subject->ptr = ziplistDelete(li->subject->ptr,&p);
@@ -5118,18 +5118,18 @@ static void lDelete(lEntry *entry) {
     }
 }
 
-static void convertList(robj *subject, int enc) {
-    lIterator *li;
-    lEntry entry;
+static void listTypeConvert(robj *subject, int enc) {
+    listTypeIterator *li;
+    listTypeEntry entry;
     redisAssert(subject->type == REDIS_LIST);
 
     if (enc == REDIS_ENCODING_LIST) {
         list *l = listCreate();
 
-        /* lGet returns a robj with incremented refcount */
-        li = lInitIterator(subject,0,REDIS_TAIL);
-        while (lNext(li,&entry)) listAddNodeTail(l,lGet(&entry));
-        lReleaseIterator(li);
+        /* listTypeGet returns a robj with incremented refcount */
+        li = listTypeInitIterator(subject,0,REDIS_TAIL);
+        while (listTypeNext(li,&entry)) listAddNodeTail(l,listTypeGet(&entry));
+        listTypeReleaseIterator(li);
 
         subject->encoding = REDIS_ENCODING_LIST;
         zfree(subject->ptr);
@@ -5158,8 +5158,8 @@ static void pushGenericCommand(redisClient *c, int where) {
             return;
         }
     }
-    lPush(lobj,c->argv[2],where);
-    addReplyLongLong(c,lLength(lobj));
+    listTypePush(lobj,c->argv[2],where);
+    addReplyLongLong(c,listTypeLength(lobj));
     server.dirty++;
 }
 
@@ -5174,7 +5174,7 @@ static void rpushCommand(redisClient *c) {
 static void llenCommand(redisClient *c) {
     robj *o = lookupKeyReadOrReply(c,c->argv[1],shared.czero);
     if (o == NULL || checkType(c,o,REDIS_LIST)) return;
-    addReplyUlong(c,lLength(o));
+    addReplyUlong(c,listTypeLength(o));
 }
 
 static void lindexCommand(redisClient *c) {
@@ -5219,7 +5219,7 @@ static void lsetCommand(redisClient *c) {
     int index = atoi(c->argv[2]->ptr);
     robj *value = c->argv[3];
 
-    listTryConversion(o,value);
+    listTypeTryConversion(o,value);
     if (o->encoding == REDIS_ENCODING_ZIPLIST) {
         unsigned char *p, *zl = o->ptr;
         p = ziplistIndex(zl,index);
@@ -5253,13 +5253,13 @@ static void popGenericCommand(redisClient *c, int where) {
     robj *o = lookupKeyWriteOrReply(c,c->argv[1],shared.nullbulk);
     if (o == NULL || checkType(c,o,REDIS_LIST)) return;
 
-    robj *value = lPop(o,where);
+    robj *value = listTypePop(o,where);
     if (value == NULL) {
         addReply(c,shared.nullbulk);
     } else {
         addReplyBulk(c,value);
         decrRefCount(value);
-        if (lLength(o) == 0) dbDelete(c->db,c->argv[1]);
+        if (listTypeLength(o) == 0) dbDelete(c->db,c->argv[1]);
         server.dirty++;
     }
 }
@@ -5278,11 +5278,11 @@ static void lrangeCommand(redisClient *c) {
     int end = atoi(c->argv[3]->ptr);
     int llen;
     int rangelen, j;
-    lEntry entry;
+    listTypeEntry entry;
 
     if ((o = lookupKeyReadOrReply(c,c->argv[1],shared.emptymultibulk)) == NULL
          || checkType(c,o,REDIS_LIST)) return;
-    llen = lLength(o);
+    llen = listTypeLength(o);
 
     /* convert negative indexes */
     if (start < 0) start = llen+start;
@@ -5301,14 +5301,14 @@ static void lrangeCommand(redisClient *c) {
 
     /* Return the result in form of a multi-bulk reply */
     addReplySds(c,sdscatprintf(sdsempty(),"*%d\r\n",rangelen));
-    lIterator *li = lInitIterator(o,start,REDIS_TAIL);
+    listTypeIterator *li = listTypeInitIterator(o,start,REDIS_TAIL);
     for (j = 0; j < rangelen; j++) {
-        redisAssert(lNext(li,&entry));
-        value = lGet(&entry);
+        redisAssert(listTypeNext(li,&entry));
+        value = listTypeGet(&entry);
         addReplyBulk(c,value);
         decrRefCount(value);
     }
-    lReleaseIterator(li);
+    listTypeReleaseIterator(li);
 }
 
 static void ltrimCommand(redisClient *c) {
@@ -5322,7 +5322,7 @@ static void ltrimCommand(redisClient *c) {
 
     if ((o = lookupKeyWriteOrReply(c,c->argv[1],shared.ok)) == NULL ||
         checkType(c,o,REDIS_LIST)) return;
-    llen = lLength(o);
+    llen = listTypeLength(o);
 
     /* convert negative indexes */
     if (start < 0) start = llen+start;
@@ -5358,7 +5358,7 @@ static void ltrimCommand(redisClient *c) {
     } else {
         redisPanic("Unknown list encoding");
     }
-    if (lLength(o) == 0) dbDelete(c->db,c->argv[1]);
+    if (listTypeLength(o) == 0) dbDelete(c->db,c->argv[1]);
     server.dirty++;
     addReply(c,shared.ok);
 }
@@ -5367,7 +5367,7 @@ static void lremCommand(redisClient *c) {
     robj *subject, *obj = c->argv[3];
     int toremove = atoi(c->argv[2]->ptr);
     int removed = 0;
-    lEntry entry;
+    listTypeEntry entry;
 
     subject = lookupKeyWriteOrReply(c,c->argv[1],shared.czero);
     if (subject == NULL || checkType(c,subject,REDIS_LIST)) return;
@@ -5376,29 +5376,29 @@ static void lremCommand(redisClient *c) {
     if (subject->encoding == REDIS_ENCODING_ZIPLIST)
         obj = getDecodedObject(obj);
 
-    lIterator *li;
+    listTypeIterator *li;
     if (toremove < 0) {
         toremove = -toremove;
-        li = lInitIterator(subject,-1,REDIS_HEAD);
+        li = listTypeInitIterator(subject,-1,REDIS_HEAD);
     } else {
-        li = lInitIterator(subject,0,REDIS_TAIL);
+        li = listTypeInitIterator(subject,0,REDIS_TAIL);
     }
 
-    while (lNext(li,&entry)) {
-        if (lEqual(&entry,obj)) {
-            lDelete(&entry);
+    while (listTypeNext(li,&entry)) {
+        if (listTypeEqual(&entry,obj)) {
+            listTypeDelete(&entry);
             server.dirty++;
             removed++;
             if (toremove && removed == toremove) break;
         }
     }
-    lReleaseIterator(li);
+    listTypeReleaseIterator(li);
 
     /* Clean up raw encoded object */
     if (subject->encoding == REDIS_ENCODING_ZIPLIST)
         decrRefCount(obj);
 
-    if (lLength(subject) == 0) dbDelete(c->db,c->argv[1]);
+    if (listTypeLength(subject) == 0) dbDelete(c->db,c->argv[1]);
     addReplySds(c,sdscatprintf(sdsempty(),":%d\r\n",removed));
 }
 
@@ -5422,12 +5422,12 @@ static void rpoplpushcommand(redisClient *c) {
     if ((sobj = lookupKeyWriteOrReply(c,c->argv[1],shared.nullbulk)) == NULL ||
         checkType(c,sobj,REDIS_LIST)) return;
 
-    if (lLength(sobj) == 0) {
+    if (listTypeLength(sobj) == 0) {
         addReply(c,shared.nullbulk);
     } else {
         robj *dobj = lookupKeyWrite(c->db,c->argv[2]);
         if (dobj && checkType(c,dobj,REDIS_LIST)) return;
-        value = lPop(sobj,REDIS_TAIL);
+        value = listTypePop(sobj,REDIS_TAIL);
 
         /* Add the element to the target list (unless it's directly
          * passed to some BLPOP-ing client */
@@ -5437,17 +5437,17 @@ static void rpoplpushcommand(redisClient *c) {
                 dobj = createZiplistObject();
                 dbAdd(c->db,c->argv[2],dobj);
             }
-            lPush(dobj,value,REDIS_HEAD);
+            listTypePush(dobj,value,REDIS_HEAD);
         }
 
         /* Send the element to the client as reply as well */
         addReplyBulk(c,value);
 
-        /* lPop returns an object with its refcount incremented */
+        /* listTypePop returns an object with its refcount incremented */
         decrRefCount(value);
 
         /* Delete the source list when it is empty */
-        if (lLength(sobj) == 0) dbDelete(c->db,c->argv[1]);
+        if (listTypeLength(sobj) == 0) dbDelete(c->db,c->argv[1]);
         server.dirty++;
     }
 }
@@ -6070,7 +6070,7 @@ static zskiplistNode *zslFirstWithScore(zskiplist *zsl, double score) {
  * Returns 0 when the element cannot be found, rank otherwise.
  * Note that the rank is 1-based due to the span of zsl->header to the
  * first element. */
-static unsigned long zslGetRank(zskiplist *zsl, double score, robj *o) {
+static unsigned long zslistTypeGetRank(zskiplist *zsl, double score, robj *o) {
     zskiplistNode *x;
     unsigned long rank = 0;
     int i;
@@ -6094,7 +6094,7 @@ static unsigned long zslGetRank(zskiplist *zsl, double score, robj *o) {
 }
 
 /* Finds an element by its rank. The rank argument needs to be 1-based. */
-zskiplistNode* zslGetElementByRank(zskiplist *zsl, unsigned long rank) {
+zskiplistNode* zslistTypeGetElementByRank(zskiplist *zsl, unsigned long rank) {
     zskiplistNode *x;
     unsigned long traversed = 0;
     int i;
@@ -6560,10 +6560,10 @@ static void zrangeGenericCommand(redisClient *c, int reverse) {
     /* check if starting point is trivial, before searching
      * the element in log(N) time */
     if (reverse) {
-        ln = start == 0 ? zsl->tail : zslGetElementByRank(zsl, llen-start);
+        ln = start == 0 ? zsl->tail : zslistTypeGetElementByRank(zsl, llen-start);
     } else {
         ln = start == 0 ?
-            zsl->header->forward[0] : zslGetElementByRank(zsl, start+1);
+            zsl->header->forward[0] : zslistTypeGetElementByRank(zsl, start+1);
     }
 
     /* Return the result in form of a multi-bulk reply */
@@ -6760,7 +6760,7 @@ static void zrankGenericCommand(redisClient *c, int reverse) {
     }
 
     score = dictGetEntryVal(de);
-    rank = zslGetRank(zsl, *score, c->argv[2]);
+    rank = zslistTypeGetRank(zsl, *score, c->argv[2]);
     if (rank) {
         if (reverse) {
             addReplyLongLong(c, zsl->length - rank);
@@ -7407,7 +7407,7 @@ static void sortCommand(redisClient *c) {
 
     /* Load the sorting vector with all the objects to sort */
     switch(sortval->type) {
-    case REDIS_LIST: vectorlen = lLength(sortval); break;
+    case REDIS_LIST: vectorlen = listTypeLength(sortval); break;
     case REDIS_SET: vectorlen =  dictSize((dict*)sortval->ptr); break;
     case REDIS_ZSET: vectorlen = dictSize(((zset*)sortval->ptr)->dict); break;
     default: vectorlen = 0; redisPanic("Bad SORT type"); /* Avoid GCC warning */
@@ -7416,15 +7416,15 @@ static void sortCommand(redisClient *c) {
     j = 0;
 
     if (sortval->type == REDIS_LIST) {
-        lIterator *li = lInitIterator(sortval,0,REDIS_TAIL);
-        lEntry entry;
-        while(lNext(li,&entry)) {
-            vector[j].obj = lGet(&entry);
+        listTypeIterator *li = listTypeInitIterator(sortval,0,REDIS_TAIL);
+        listTypeEntry entry;
+        while(listTypeNext(li,&entry)) {
+            vector[j].obj = listTypeGet(&entry);
             vector[j].u.score = 0;
             vector[j].u.cmpobj = NULL;
             j++;
         }
-        lReleaseIterator(li);
+        listTypeReleaseIterator(li);
     } else {
         dict *set;
         dictIterator *di;
@@ -7542,7 +7542,7 @@ static void sortCommand(redisClient *c) {
             listIter li;
 
             if (!getop) {
-                lPush(sobj,vector[j].obj,REDIS_TAIL);
+                listTypePush(sobj,vector[j].obj,REDIS_TAIL);
             } else {
                 listRewind(operations,&li);
                 while((ln = listNext(&li))) {
@@ -7553,10 +7553,10 @@ static void sortCommand(redisClient *c) {
                     if (sop->type == REDIS_SORT_GET) {
                         if (!val) val = createStringObject("",0);
 
-                        /* lPush does an incrRefCount, so we should take care
+                        /* listTypePush does an incrRefCount, so we should take care
                          * care of the incremented refcount caused by either
                          * lookupKeyByPattern or createStringObject("",0) */
-                        lPush(sobj,val,REDIS_TAIL);
+                        listTypePush(sobj,val,REDIS_TAIL);
                         decrRefCount(val);
                     } else {
                         /* always fails */
@@ -11075,14 +11075,14 @@ static void computeDatasetDigest(unsigned char *final) {
             if (o->type == REDIS_STRING) {
                 mixObjectDigest(digest,o);
             } else if (o->type == REDIS_LIST) {
-                lIterator *li = lInitIterator(o,0,REDIS_TAIL);
-                lEntry entry;
-                while(lNext(li,&entry)) {
-                    robj *eleobj = lGet(&entry);
+                listTypeIterator *li = listTypeInitIterator(o,0,REDIS_TAIL);
+                listTypeEntry entry;
+                while(listTypeNext(li,&entry)) {
+                    robj *eleobj = listTypeGet(&entry);
                     mixObjectDigest(digest,eleobj);
                     decrRefCount(eleobj);
                 }
-                lReleaseIterator(li);
+                listTypeReleaseIterator(li);
             } else if (o->type == REDIS_SET) {
                 dict *set = o->ptr;
                 dictIterator *di = dictGetIterator(set);