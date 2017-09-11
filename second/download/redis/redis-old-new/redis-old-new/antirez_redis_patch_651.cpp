@@ -33,75 +33,40 @@
  * List API
  *----------------------------------------------------------------------------*/
 
-/* Check the argument length to see if it requires us to convert the ziplist
- * to a real list. Only check raw-encoded objects because integer encoded
- * objects are never too long. */
-void listTypeTryConversion(robj *subject, robj *value) {
-    if (subject->encoding != REDIS_ENCODING_ZIPLIST) return;
-    if (sdsEncodedObject(value) &&
-        sdslen(value->ptr) > server.list_max_ziplist_value)
-            listTypeConvert(subject,REDIS_ENCODING_LINKEDLIST);
-}
-
 /* The function pushes an element to the specified list object 'subject',
  * at head or tail position as specified by 'where'.
  *
  * There is no need for the caller to increment the refcount of 'value' as
  * the function takes care of it if needed. */
 void listTypePush(robj *subject, robj *value, int where) {
-    /* Check if we need to convert the ziplist */
-    listTypeTryConversion(subject,value);
-    if (subject->encoding == REDIS_ENCODING_ZIPLIST &&
-        ziplistLen(subject->ptr) >= server.list_max_ziplist_entries)
-            listTypeConvert(subject,REDIS_ENCODING_LINKEDLIST);
-
-    if (subject->encoding == REDIS_ENCODING_ZIPLIST) {
-        int pos = (where == REDIS_HEAD) ? ZIPLIST_HEAD : ZIPLIST_TAIL;
+    if (subject->encoding == REDIS_ENCODING_QUICKLIST) {
+        int pos = (where == REDIS_HEAD) ? QUICKLIST_HEAD : QUICKLIST_TAIL;
         value = getDecodedObject(value);
-        subject->ptr = ziplistPush(subject->ptr,value->ptr,sdslen(value->ptr),pos);
+        size_t len = sdslen(value->ptr);
+        size_t zlen = server.list_max_ziplist_entries;
+        /* If this value is greater than our allowed values, create it in
+         * an isolated ziplist */
+        quicklistPush(subject->ptr, zlen, value->ptr, len, pos);
         decrRefCount(value);
-    } else if (subject->encoding == REDIS_ENCODING_LINKEDLIST) {
-        if (where == REDIS_HEAD) {
-            listAddNodeHead(subject->ptr,value);
-        } else {
-            listAddNodeTail(subject->ptr,value);
-        }
-        incrRefCount(value);
     } else {
         redisPanic("Unknown list encoding");
     }
 }
 
+void *listPopSaver(unsigned char *data, unsigned int sz) {
+    return createStringObject((char*)data,sz);
+}
+
 robj *listTypePop(robj *subject, int where) {
+    long long vlong;
     robj *value = NULL;
-    if (subject->encoding == REDIS_ENCODING_ZIPLIST) {
-        unsigned char *p;
-        unsigned char *vstr;
-        unsigned int vlen;
-        long long vlong;
-        int pos = (where == REDIS_HEAD) ? 0 : -1;
-        p = ziplistIndex(subject->ptr,pos);
-        if (ziplistGet(p,&vstr,&vlen,&vlong)) {
-            if (vstr) {
-                value = createStringObject((char*)vstr,vlen);
-            } else {
+
+    int ql_where = where == REDIS_HEAD ? QUICKLIST_HEAD : QUICKLIST_TAIL;
+    if (subject->encoding == REDIS_ENCODING_QUICKLIST) {
+        if (quicklistPopCustom(subject->ptr, ql_where, (unsigned char **)&value,
+                               NULL, &vlong, listPopSaver)) {
+            if (!value)
                 value = createStringObjectFromLongLong(vlong);
-            }
-            /* We only need to delete an element when it exists */
-            subject->ptr = ziplistDelete(subject->ptr,&p);
-        }
-    } else if (subject->encoding == REDIS_ENCODING_LINKEDLIST) {
-        list *list = subject->ptr;
-        listNode *ln;
-        if (where == REDIS_HEAD) {
-            ln = listFirst(list);
-        } else {
-            ln = listLast(list);
-        }
-        if (ln != NULL) {
-            value = listNodeValue(ln);
-            incrRefCount(value);
-            listDelNode(list,ln);
         }
     } else {
         redisPanic("Unknown list encoding");
@@ -110,25 +75,28 @@ robj *listTypePop(robj *subject, int where) {
 }
 
 unsigned long listTypeLength(robj *subject) {
-    if (subject->encoding == REDIS_ENCODING_ZIPLIST) {
-        return ziplistLen(subject->ptr);
-    } else if (subject->encoding == REDIS_ENCODING_LINKEDLIST) {
-        return listLength((list*)subject->ptr);
+    if (subject->encoding == REDIS_ENCODING_QUICKLIST) {
+        return quicklistCount(subject->ptr);
     } else {
         redisPanic("Unknown list encoding");
     }
 }
 
 /* Initialize an iterator at the specified index. */
-listTypeIterator *listTypeInitIterator(robj *subject, long index, unsigned char direction) {
+listTypeIterator *listTypeInitIterator(robj *subject, long index,
+                                       unsigned char direction) {
     listTypeIterator *li = zmalloc(sizeof(listTypeIterator));
     li->subject = subject;
     li->encoding = subject->encoding;
     li->direction = direction;
-    if (li->encoding == REDIS_ENCODING_ZIPLIST) {
-        li->zi = ziplistIndex(subject->ptr,index);
-    } else if (li->encoding == REDIS_ENCODING_LINKEDLIST) {
-        li->ln = listIndex(subject->ptr,index);
+    li->iter = NULL;
+    /* REDIS_HEAD means start at TAIL and move *towards* head.
+     * REDIS_TAIL means start at HEAD and move *towards tail. */
+    int iter_direction =
+        direction == REDIS_HEAD ? AL_START_TAIL : AL_START_HEAD;
+    if (li->encoding == REDIS_ENCODING_QUICKLIST) {
+        li->iter = quicklistGetIteratorAtIdx(li->subject->ptr,
+                                             iter_direction, index);
     } else {
         redisPanic("Unknown list encoding");
     }
@@ -137,6 +105,7 @@ listTypeIterator *listTypeInitIterator(robj *subject, long index, unsigned char
 
 /* Clean up the iterator. */
 void listTypeReleaseIterator(listTypeIterator *li) {
+    zfree(li->iter);
     zfree(li);
 }
 
@@ -148,24 +117,8 @@ int listTypeNext(listTypeIterator *li, listTypeEntry *entry) {
     redisAssert(li->subject->encoding == li->encoding);
 
     entry->li = li;
-    if (li->encoding == REDIS_ENCODING_ZIPLIST) {
-        entry->zi = li->zi;
-        if (entry->zi != NULL) {
-            if (li->direction == REDIS_TAIL)
-                li->zi = ziplistNext(li->subject->ptr,li->zi);
-            else
-                li->zi = ziplistPrev(li->subject->ptr,li->zi);
-            return 1;
-        }
-    } else if (li->encoding == REDIS_ENCODING_LINKEDLIST) {
-        entry->ln = li->ln;
-        if (entry->ln != NULL) {
-            if (li->direction == REDIS_TAIL)
-                li->ln = li->ln->next;
-            else
-                li->ln = li->ln->prev;
-            return 1;
-        }
+    if (li->encoding == REDIS_ENCODING_QUICKLIST) {
+        return quicklistNext(li->iter, &entry->entry);
     } else {
         redisPanic("Unknown list encoding");
     }
@@ -174,115 +127,68 @@ int listTypeNext(listTypeIterator *li, listTypeEntry *entry) {
 
 /* Return entry or NULL at the current position of the iterator. */
 robj *listTypeGet(listTypeEntry *entry) {
-    listTypeIterator *li = entry->li;
     robj *value = NULL;
-    if (li->encoding == REDIS_ENCODING_ZIPLIST) {
-        unsigned char *vstr;
-        unsigned int vlen;
-        long long vlong;
-        redisAssert(entry->zi != NULL);
-        if (ziplistGet(entry->zi,&vstr,&vlen,&vlong)) {
-            if (vstr) {
-                value = createStringObject((char*)vstr,vlen);
-            } else {
-                value = createStringObjectFromLongLong(vlong);
-            }
+    if (entry->li->encoding == REDIS_ENCODING_QUICKLIST) {
+        if (entry->entry.value) {
+            value = createStringObject((char *)entry->entry.value,
+                                       entry->entry.sz);
+        } else {
+            value = createStringObjectFromLongLong(entry->entry.longval);
         }
-    } else if (li->encoding == REDIS_ENCODING_LINKEDLIST) {
-        redisAssert(entry->ln != NULL);
-        value = listNodeValue(entry->ln);
-        incrRefCount(value);
     } else {
         redisPanic("Unknown list encoding");
     }
     return value;
 }
 
 void listTypeInsert(listTypeEntry *entry, robj *value, int where) {
-    robj *subject = entry->li->subject;
-    if (entry->li->encoding == REDIS_ENCODING_ZIPLIST) {
+    if (entry->li->encoding == REDIS_ENCODING_QUICKLIST) {
         value = getDecodedObject(value);
+        sds str = value->ptr;
+        size_t len = sdslen(str);
+        size_t zlen = server.list_max_ziplist_entries;
         if (where == REDIS_TAIL) {
-            unsigned char *next = ziplistNext(subject->ptr,entry->zi);
-
-            /* When we insert after the current element, but the current element
-             * is the tail of the list, we need to do a push. */
-            if (next == NULL) {
-                subject->ptr = ziplistPush(subject->ptr,value->ptr,sdslen(value->ptr),REDIS_TAIL);
-            } else {
-                subject->ptr = ziplistInsert(subject->ptr,next,value->ptr,sdslen(value->ptr));
-            }
-        } else {
-            subject->ptr = ziplistInsert(subject->ptr,entry->zi,value->ptr,sdslen(value->ptr));
+            quicklistInsertAfter((quicklist *)entry->entry.quicklist, zlen,
+                                 &entry->entry, str, len);
+        } else if (where == REDIS_HEAD) {
+            quicklistInsertBefore((quicklist *)entry->entry.quicklist, zlen,
+                                  &entry->entry, str, len);
         }
         decrRefCount(value);
-    } else if (entry->li->encoding == REDIS_ENCODING_LINKEDLIST) {
-        if (where == REDIS_TAIL) {
-            listInsertNode(subject->ptr,entry->ln,value,AL_START_TAIL);
-        } else {
-            listInsertNode(subject->ptr,entry->ln,value,AL_START_HEAD);
-        }
-        incrRefCount(value);
     } else {
         redisPanic("Unknown list encoding");
     }
 }
 
 /* Compare the given object with the entry at the current position. */
 int listTypeEqual(listTypeEntry *entry, robj *o) {
-    listTypeIterator *li = entry->li;
-    if (li->encoding == REDIS_ENCODING_ZIPLIST) {
+    if (entry->li->encoding == REDIS_ENCODING_QUICKLIST) {
         redisAssertWithInfo(NULL,o,sdsEncodedObject(o));
-        return ziplistCompare(entry->zi,o->ptr,sdslen(o->ptr));
-    } else if (li->encoding == REDIS_ENCODING_LINKEDLIST) {
-        return equalStringObjects(o,listNodeValue(entry->ln));
+        return quicklistCompare(entry->entry.zi,o->ptr,sdslen(o->ptr));
     } else {
         redisPanic("Unknown list encoding");
     }
 }
 
 /* Delete the element pointed to. */
-void listTypeDelete(listTypeEntry *entry) {
-    listTypeIterator *li = entry->li;
-    if (li->encoding == REDIS_ENCODING_ZIPLIST) {
-        unsigned char *p = entry->zi;
-        li->subject->ptr = ziplistDelete(li->subject->ptr,&p);
-
-        /* Update position of the iterator depending on the direction */
-        if (li->direction == REDIS_TAIL)
-            li->zi = p;
-        else
-            li->zi = ziplistPrev(li->subject->ptr,p);
-    } else if (entry->li->encoding == REDIS_ENCODING_LINKEDLIST) {
-        listNode *next;
-        if (li->direction == REDIS_TAIL)
-            next = entry->ln->next;
-        else
-            next = entry->ln->prev;
-        listDelNode(li->subject->ptr,entry->ln);
-        li->ln = next;
+void listTypeDelete(listTypeIterator *iter, listTypeEntry *entry) {
+    if (entry->li->encoding == REDIS_ENCODING_QUICKLIST) {
+        quicklistDelEntry(iter->iter, &entry->entry);
     } else {
         redisPanic("Unknown list encoding");
     }
 }
 
+/* Create a quicklist from a single ziplist */
 void listTypeConvert(robj *subject, int enc) {
-    listTypeIterator *li;
-    listTypeEntry entry;
-    redisAssertWithInfo(NULL,subject,subject->type == REDIS_LIST);
-
-    if (enc == REDIS_ENCODING_LINKEDLIST) {
-        list *l = listCreate();
-        listSetFreeMethod(l,decrRefCountVoid);
+    redisAssertWithInfo(NULL,subject,subject->type==REDIS_LIST);
+    redisAssertWithInfo(NULL,subject,subject->encoding==REDIS_ENCODING_ZIPLIST);
 
-        /* listTypeGet returns a robj with incremented refcount */
-        li = listTypeInitIterator(subject,0,REDIS_TAIL);
-        while (listTypeNext(li,&entry)) listAddNodeTail(l,listTypeGet(&entry));
-        listTypeReleaseIterator(li);
+    if (enc == REDIS_ENCODING_QUICKLIST) {
+        size_t zlen = server.list_max_ziplist_entries;
 
-        subject->encoding = REDIS_ENCODING_LINKEDLIST;
-        zfree(subject->ptr);
-        subject->ptr = l;
+        subject->encoding = REDIS_ENCODING_QUICKLIST;
+        subject->ptr = quicklistCreateFromZiplist(zlen, subject->ptr);
     } else {
         redisPanic("Unsupported list conversion");
     }
@@ -304,7 +210,7 @@ void pushGenericCommand(redisClient *c, int where) {
     for (j = 2; j < c->argc; j++) {
         c->argv[j] = tryObjectEncoding(c->argv[j]);
         if (!lobj) {
-            lobj = createZiplistObject();
+            lobj = createQuicklistObject();
             dbAdd(c->db,c->argv[1],lobj);
         }
         listTypePush(lobj,c->argv[j],where);
@@ -338,13 +244,6 @@ void pushxGenericCommand(redisClient *c, robj *refval, robj *val, int where) {
         checkType(c,subject,REDIS_LIST)) return;
 
     if (refval != NULL) {
-        /* We're not sure if this value can be inserted yet, but we cannot
-         * convert the list inside the iterator. We don't want to loop over
-         * the list twice (once to see if the value can be inserted and once
-         * to do the actual insert), so we assume this value can be inserted
-         * and convert the ziplist to a regular list if necessary. */
-        listTypeTryConversion(subject,val);
-
         /* Seek refval from head to tail */
         iter = listTypeInitIterator(subject,0,REDIS_TAIL);
         while (listTypeNext(iter,&entry)) {
@@ -357,10 +256,6 @@ void pushxGenericCommand(redisClient *c, robj *refval, robj *val, int where) {
         listTypeReleaseIterator(iter);
 
         if (inserted) {
-            /* Check if the length exceeds the ziplist length threshold. */
-            if (subject->encoding == REDIS_ENCODING_ZIPLIST &&
-                ziplistLen(subject->ptr) > server.list_max_ziplist_entries)
-                    listTypeConvert(subject,REDIS_ENCODING_LINKEDLIST);
             signalModifiedKey(c->db,c->argv[1]);
             notifyKeyspaceEvent(REDIS_NOTIFY_LIST,"linsert",
                                 c->argv[1],c->db->id);
@@ -418,31 +313,19 @@ void lindexCommand(redisClient *c) {
     if ((getLongFromObjectOrReply(c, c->argv[2], &index, NULL) != REDIS_OK))
         return;
 
-    if (o->encoding == REDIS_ENCODING_ZIPLIST) {
-        unsigned char *p;
-        unsigned char *vstr;
-        unsigned int vlen;
-        long long vlong;
-        p = ziplistIndex(o->ptr,index);
-        if (ziplistGet(p,&vstr,&vlen,&vlong)) {
-            if (vstr) {
-                value = createStringObject((char*)vstr,vlen);
+    if (o->encoding == REDIS_ENCODING_QUICKLIST) {
+        quicklistEntry entry;
+        if (quicklistIndex(o->ptr, index, &entry)) {
+            if (entry.value) {
+                value = createStringObject((char*)entry.value,entry.sz);
             } else {
-                value = createStringObjectFromLongLong(vlong);
+                value = createStringObjectFromLongLong(entry.longval);
             }
             addReplyBulk(c,value);
             decrRefCount(value);
         } else {
             addReply(c,shared.nullbulk);
         }
-    } else if (o->encoding == REDIS_ENCODING_LINKEDLIST) {
-        listNode *ln = listIndex(o->ptr,index);
-        if (ln != NULL) {
-            value = listNodeValue(ln);
-            addReplyBulk(c,value);
-        } else {
-            addReply(c,shared.nullbulk);
-        }
     } else {
         redisPanic("Unknown list encoding");
     }
@@ -452,35 +335,18 @@ void lsetCommand(redisClient *c) {
     robj *o = lookupKeyWriteOrReply(c,c->argv[1],shared.nokeyerr);
     if (o == NULL || checkType(c,o,REDIS_LIST)) return;
     long index;
-    robj *value = (c->argv[3] = tryObjectEncoding(c->argv[3]));
+    robj *value = c->argv[3];
 
     if ((getLongFromObjectOrReply(c, c->argv[2], &index, NULL) != REDIS_OK))
         return;
 
-    listTypeTryConversion(o,value);
-    if (o->encoding == REDIS_ENCODING_ZIPLIST) {
-        unsigned char *p, *zl = o->ptr;
-        p = ziplistIndex(zl,index);
-        if (p == NULL) {
-            addReply(c,shared.outofrangeerr);
-        } else {
-            o->ptr = ziplistDelete(o->ptr,&p);
-            value = getDecodedObject(value);
-            o->ptr = ziplistInsert(o->ptr,p,value->ptr,sdslen(value->ptr));
-            decrRefCount(value);
-            addReply(c,shared.ok);
-            signalModifiedKey(c->db,c->argv[1]);
-            notifyKeyspaceEvent(REDIS_NOTIFY_LIST,"lset",c->argv[1],c->db->id);
-            server.dirty++;
-        }
-    } else if (o->encoding == REDIS_ENCODING_LINKEDLIST) {
-        listNode *ln = listIndex(o->ptr,index);
-        if (ln == NULL) {
+    if (o->encoding == REDIS_ENCODING_QUICKLIST) {
+        quicklist *ql = o->ptr;
+        int replaced = quicklistReplaceAtIndex(ql, index,
+                                               value->ptr, sdslen(value->ptr));
+        if (!replaced) {
             addReply(c,shared.outofrangeerr);
         } else {
-            decrRefCount((robj*)listNodeValue(ln));
-            listNodeValue(ln) = value;
-            incrRefCount(value);
             addReply(c,shared.ok);
             signalModifiedKey(c->db,c->argv[1]);
             notifyKeyspaceEvent(REDIS_NOTIFY_LIST,"lset",c->argv[1],c->db->id);
@@ -549,43 +415,28 @@ void lrangeCommand(redisClient *c) {
 
     /* Return the result in form of a multi-bulk reply */
     addReplyMultiBulkLen(c,rangelen);
-    if (o->encoding == REDIS_ENCODING_ZIPLIST) {
-        unsigned char *p = ziplistIndex(o->ptr,start);
-        unsigned char *vstr;
-        unsigned int vlen;
-        long long vlong;
+    if (o->encoding == REDIS_ENCODING_QUICKLIST) {
+        listTypeIterator *iter = listTypeInitIterator(o, start, REDIS_TAIL);
 
         while(rangelen--) {
-            ziplistGet(p,&vstr,&vlen,&vlong);
-            if (vstr) {
-                addReplyBulkCBuffer(c,vstr,vlen);
+            listTypeEntry entry;
+            listTypeNext(iter, &entry);
+            quicklistEntry *qe = &entry.entry;
+            if (qe->value) {
+                addReplyBulkCBuffer(c,qe->value,qe->sz);
             } else {
-                addReplyBulkLongLong(c,vlong);
+                addReplyBulkLongLong(c,qe->longval);
             }
-            p = ziplistNext(o->ptr,p);
-        }
-    } else if (o->encoding == REDIS_ENCODING_LINKEDLIST) {
-        listNode *ln;
-
-        /* If we are nearest to the end of the list, reach the element
-         * starting from tail and going backward, as it is faster. */
-        if (start > llen/2) start -= llen;
-        ln = listIndex(o->ptr,start);
-
-        while(rangelen--) {
-            addReplyBulk(c,ln->value);
-            ln = ln->next;
         }
+        listTypeReleaseIterator(iter);
     } else {
-        redisPanic("List encoding is not LINKEDLIST nor ZIPLIST!");
+        redisPanic("List encoding is not QUICKLIST!");
     }
 }
 
 void ltrimCommand(redisClient *c) {
     robj *o;
-    long start, end, llen, j, ltrim, rtrim;
-    list *list;
-    listNode *ln;
+    long start, end, llen, ltrim, rtrim;
 
     if ((getLongFromObjectOrReply(c, c->argv[2], &start, NULL) != REDIS_OK) ||
         (getLongFromObjectOrReply(c, c->argv[3], &end, NULL) != REDIS_OK)) return;
@@ -612,19 +463,9 @@ void ltrimCommand(redisClient *c) {
     }
 
     /* Remove list elements to perform the trim */
-    if (o->encoding == REDIS_ENCODING_ZIPLIST) {
-        o->ptr = ziplistDeleteRange(o->ptr,0,ltrim);
-        o->ptr = ziplistDeleteRange(o->ptr,-rtrim,rtrim);
-    } else if (o->encoding == REDIS_ENCODING_LINKEDLIST) {
-        list = o->ptr;
-        for (j = 0; j < ltrim; j++) {
-            ln = listFirst(list);
-            listDelNode(list,ln);
-        }
-        for (j = 0; j < rtrim; j++) {
-            ln = listLast(list);
-            listDelNode(list,ln);
-        }
+    if (o->encoding == REDIS_ENCODING_QUICKLIST) {
+        quicklistDelRange(o->ptr,0,ltrim);
+        quicklistDelRange(o->ptr,-rtrim,rtrim);
     } else {
         redisPanic("Unknown list encoding");
     }
@@ -641,21 +482,16 @@ void ltrimCommand(redisClient *c) {
 
 void lremCommand(redisClient *c) {
     robj *subject, *obj;
-    obj = c->argv[3] = tryObjectEncoding(c->argv[3]);
+    obj = c->argv[3];
     long toremove;
     long removed = 0;
-    listTypeEntry entry;
 
     if ((getLongFromObjectOrReply(c, c->argv[2], &toremove, NULL) != REDIS_OK))
         return;
 
     subject = lookupKeyWriteOrReply(c,c->argv[1],shared.czero);
     if (subject == NULL || checkType(c,subject,REDIS_LIST)) return;
 
-    /* Make sure obj is raw when we're dealing with a ziplist */
-    if (subject->encoding == REDIS_ENCODING_ZIPLIST)
-        obj = getDecodedObject(obj);
-
     listTypeIterator *li;
     if (toremove < 0) {
         toremove = -toremove;
@@ -664,21 +500,21 @@ void lremCommand(redisClient *c) {
         li = listTypeInitIterator(subject,0,REDIS_TAIL);
     }
 
+    listTypeEntry entry;
     while (listTypeNext(li,&entry)) {
         if (listTypeEqual(&entry,obj)) {
-            listTypeDelete(&entry);
+            listTypeDelete(li, &entry);
             server.dirty++;
             removed++;
             if (toremove && removed == toremove) break;
         }
     }
     listTypeReleaseIterator(li);
 
-    /* Clean up raw encoded object */
-    if (subject->encoding == REDIS_ENCODING_ZIPLIST)
-        decrRefCount(obj);
+    if (listTypeLength(subject) == 0) {
+        dbDelete(c->db,c->argv[1]);
+    }
 
-    if (listTypeLength(subject) == 0) dbDelete(c->db,c->argv[1]);
     addReplyLongLong(c,removed);
     if (removed) signalModifiedKey(c->db,c->argv[1]);
 }
@@ -702,7 +538,7 @@ void lremCommand(redisClient *c) {
 void rpoplpushHandlePush(redisClient *c, robj *dstkey, robj *dstobj, robj *value) {
     /* Create the list if the key does not exist */
     if (!dstobj) {
-        dstobj = createZiplistObject();
+        dstobj = createQuicklistObject();
         dbAdd(c->db,dstkey,dstobj);
     }
     signalModifiedKey(c->db,dstkey);
@@ -1010,7 +846,9 @@ void handleClientsBlockedOnLists(void) {
                     }
                 }
 
-                if (listTypeLength(o) == 0) dbDelete(rl->db,rl->key);
+                if (listTypeLength(o) == 0) {
+                    dbDelete(rl->db,rl->key);
+                }
                 /* We don't call signalModifiedKey() as it was already called
                  * when an element was pushed on the list. */
             }