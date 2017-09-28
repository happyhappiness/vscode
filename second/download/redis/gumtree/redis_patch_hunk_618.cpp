  * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
  * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
  * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
  * POSSIBILITY OF SUCH DAMAGE.
  */
 
-#include "redis.h"
+#include "server.h"
 
 /*-----------------------------------------------------------------------------
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
+    if (subject->encoding == OBJ_ENCODING_QUICKLIST) {
+        int pos = (where == LIST_HEAD) ? QUICKLIST_HEAD : QUICKLIST_TAIL;
         value = getDecodedObject(value);
-        subject->ptr = ziplistPush(subject->ptr,value->ptr,sdslen(value->ptr),pos);
+        size_t len = sdslen(value->ptr);
+        quicklistPush(subject->ptr, value->ptr, len, pos);
         decrRefCount(value);
-    } else if (subject->encoding == REDIS_ENCODING_LINKEDLIST) {
-        if (where == REDIS_HEAD) {
-            listAddNodeHead(subject->ptr,value);
-        } else {
-            listAddNodeTail(subject->ptr,value);
-        }
-        incrRefCount(value);
     } else {
-        redisPanic("Unknown list encoding");
+        serverPanic("Unknown list encoding");
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
+    int ql_where = where == LIST_HEAD ? QUICKLIST_HEAD : QUICKLIST_TAIL;
+    if (subject->encoding == OBJ_ENCODING_QUICKLIST) {
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
-        redisPanic("Unknown list encoding");
+        serverPanic("Unknown list encoding");
     }
     return value;
 }
 
 unsigned long listTypeLength(robj *subject) {
-    if (subject->encoding == REDIS_ENCODING_ZIPLIST) {
-        return ziplistLen(subject->ptr);
-    } else if (subject->encoding == REDIS_ENCODING_LINKEDLIST) {
-        return listLength((list*)subject->ptr);
+    if (subject->encoding == OBJ_ENCODING_QUICKLIST) {
+        return quicklistCount(subject->ptr);
     } else {
-        redisPanic("Unknown list encoding");
+        serverPanic("Unknown list encoding");
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
+    /* LIST_HEAD means start at TAIL and move *towards* head.
+     * LIST_TAIL means start at HEAD and move *towards tail. */
+    int iter_direction =
+        direction == LIST_HEAD ? AL_START_TAIL : AL_START_HEAD;
+    if (li->encoding == OBJ_ENCODING_QUICKLIST) {
+        li->iter = quicklistGetIteratorAtIdx(li->subject->ptr,
+                                             iter_direction, index);
     } else {
-        redisPanic("Unknown list encoding");
+        serverPanic("Unknown list encoding");
     }
     return li;
 }
 
 /* Clean up the iterator. */
 void listTypeReleaseIterator(listTypeIterator *li) {
+    zfree(li->iter);
     zfree(li);
 }
 
 /* Stores pointer to current the entry in the provided entry structure
  * and advances the position of the iterator. Returns 1 when the current
  * entry is in fact an entry, 0 otherwise. */
 int listTypeNext(listTypeIterator *li, listTypeEntry *entry) {
     /* Protect from converting when iterating */
-    redisAssert(li->subject->encoding == li->encoding);
+    serverAssert(li->subject->encoding == li->encoding);
 
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
+    if (li->encoding == OBJ_ENCODING_QUICKLIST) {
+        return quicklistNext(li->iter, &entry->entry);
     } else {
-        redisPanic("Unknown list encoding");
+        serverPanic("Unknown list encoding");
     }
     return 0;
 }
 
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
+    if (entry->li->encoding == OBJ_ENCODING_QUICKLIST) {
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
-        redisPanic("Unknown list encoding");
+        serverPanic("Unknown list encoding");
     }
     return value;
 }
 
 void listTypeInsert(listTypeEntry *entry, robj *value, int where) {
-    robj *subject = entry->li->subject;
-    if (entry->li->encoding == REDIS_ENCODING_ZIPLIST) {
+    if (entry->li->encoding == OBJ_ENCODING_QUICKLIST) {
         value = getDecodedObject(value);
-        if (where == REDIS_TAIL) {
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
+        sds str = value->ptr;
+        size_t len = sdslen(str);
+        if (where == LIST_TAIL) {
+            quicklistInsertAfter((quicklist *)entry->entry.quicklist,
+                                 &entry->entry, str, len);
+        } else if (where == LIST_HEAD) {
+            quicklistInsertBefore((quicklist *)entry->entry.quicklist,
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
-        redisPanic("Unknown list encoding");
+        serverPanic("Unknown list encoding");
     }
 }
 
 /* Compare the given object with the entry at the current position. */
 int listTypeEqual(listTypeEntry *entry, robj *o) {
-    listTypeIterator *li = entry->li;
-    if (li->encoding == REDIS_ENCODING_ZIPLIST) {
-        redisAssertWithInfo(NULL,o,sdsEncodedObject(o));
-        return ziplistCompare(entry->zi,o->ptr,sdslen(o->ptr));
-    } else if (li->encoding == REDIS_ENCODING_LINKEDLIST) {
-        return equalStringObjects(o,listNodeValue(entry->ln));
+    if (entry->li->encoding == OBJ_ENCODING_QUICKLIST) {
+        serverAssertWithInfo(NULL,o,sdsEncodedObject(o));
+        return quicklistCompare(entry->entry.zi,o->ptr,sdslen(o->ptr));
     } else {
-        redisPanic("Unknown list encoding");
+        serverPanic("Unknown list encoding");
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
+    if (entry->li->encoding == OBJ_ENCODING_QUICKLIST) {
+        quicklistDelEntry(iter->iter, &entry->entry);
     } else {
-        redisPanic("Unknown list encoding");
+        serverPanic("Unknown list encoding");
     }
 }
 
+/* Create a quicklist from a single ziplist */
 void listTypeConvert(robj *subject, int enc) {
-    listTypeIterator *li;
-    listTypeEntry entry;
-    redisAssertWithInfo(NULL,subject,subject->type == REDIS_LIST);
+    serverAssertWithInfo(NULL,subject,subject->type==OBJ_LIST);
+    serverAssertWithInfo(NULL,subject,subject->encoding==OBJ_ENCODING_ZIPLIST);
 
-    if (enc == REDIS_ENCODING_LINKEDLIST) {
-        list *l = listCreate();
-        listSetFreeMethod(l,decrRefCountVoid);
-
-        /* listTypeGet returns a robj with incremented refcount */
-        li = listTypeInitIterator(subject,0,REDIS_TAIL);
-        while (listTypeNext(li,&entry)) listAddNodeTail(l,listTypeGet(&entry));
-        listTypeReleaseIterator(li);
-
-        subject->encoding = REDIS_ENCODING_LINKEDLIST;
-        zfree(subject->ptr);
-        subject->ptr = l;
+    if (enc == OBJ_ENCODING_QUICKLIST) {
+        size_t zlen = server.list_max_ziplist_size;
+        int depth = server.list_compress_depth;
+        subject->ptr = quicklistCreateFromZiplist(zlen, depth, subject->ptr);
+        subject->encoding = OBJ_ENCODING_QUICKLIST;
     } else {
-        redisPanic("Unsupported list conversion");
+        serverPanic("Unsupported list conversion");
     }
 }
 
 /*-----------------------------------------------------------------------------
  * List Commands
  *----------------------------------------------------------------------------*/
 
-void pushGenericCommand(redisClient *c, int where) {
+void pushGenericCommand(client *c, int where) {
     int j, waiting = 0, pushed = 0;
     robj *lobj = lookupKeyWrite(c->db,c->argv[1]);
 
-    if (lobj && lobj->type != REDIS_LIST) {
+    if (lobj && lobj->type != OBJ_LIST) {
         addReply(c,shared.wrongtypeerr);
         return;
     }
 
     for (j = 2; j < c->argc; j++) {
         c->argv[j] = tryObjectEncoding(c->argv[j]);
         if (!lobj) {
-            lobj = createZiplistObject();
+            lobj = createQuicklistObject();
+            quicklistSetOptions(lobj->ptr, server.list_max_ziplist_size,
+                                server.list_compress_depth);
             dbAdd(c->db,c->argv[1],lobj);
         }
         listTypePush(lobj,c->argv[j],where);
         pushed++;
     }
     addReplyLongLong(c, waiting + (lobj ? listTypeLength(lobj) : 0));
     if (pushed) {
-        char *event = (where == REDIS_HEAD) ? "lpush" : "rpush";
+        char *event = (where == LIST_HEAD) ? "lpush" : "rpush";
 
         signalModifiedKey(c->db,c->argv[1]);
-        notifyKeyspaceEvent(REDIS_NOTIFY_LIST,event,c->argv[1],c->db->id);
+        notifyKeyspaceEvent(NOTIFY_LIST,event,c->argv[1],c->db->id);
     }
     server.dirty += pushed;
 }
 
-void lpushCommand(redisClient *c) {
-    pushGenericCommand(c,REDIS_HEAD);
+void lpushCommand(client *c) {
+    pushGenericCommand(c,LIST_HEAD);
 }
 
-void rpushCommand(redisClient *c) {
-    pushGenericCommand(c,REDIS_TAIL);
+void rpushCommand(client *c) {
+    pushGenericCommand(c,LIST_TAIL);
 }
 
-void pushxGenericCommand(redisClient *c, robj *refval, robj *val, int where) {
+void pushxGenericCommand(client *c, robj *refval, robj *val, int where) {
     robj *subject;
     listTypeIterator *iter;
     listTypeEntry entry;
     int inserted = 0;
 
-    if ((subject = lookupKeyReadOrReply(c,c->argv[1],shared.czero)) == NULL ||
-        checkType(c,subject,REDIS_LIST)) return;
+    if ((subject = lookupKeyWriteOrReply(c,c->argv[1],shared.czero)) == NULL ||
+        checkType(c,subject,OBJ_LIST)) return;
 
     if (refval != NULL) {
-        /* We're not sure if this value can be inserted yet, but we cannot
-         * convert the list inside the iterator. We don't want to loop over
-         * the list twice (once to see if the value can be inserted and once
-         * to do the actual insert), so we assume this value can be inserted
-         * and convert the ziplist to a regular list if necessary. */
-        listTypeTryConversion(subject,val);
-
         /* Seek refval from head to tail */
-        iter = listTypeInitIterator(subject,0,REDIS_TAIL);
+        iter = listTypeInitIterator(subject,0,LIST_TAIL);
         while (listTypeNext(iter,&entry)) {
             if (listTypeEqual(&entry,refval)) {
                 listTypeInsert(&entry,val,where);
                 inserted = 1;
                 break;
             }
         }
         listTypeReleaseIterator(iter);
 
         if (inserted) {
-            /* Check if the length exceeds the ziplist length threshold. */
-            if (subject->encoding == REDIS_ENCODING_ZIPLIST &&
-                ziplistLen(subject->ptr) > server.list_max_ziplist_entries)
-                    listTypeConvert(subject,REDIS_ENCODING_LINKEDLIST);
             signalModifiedKey(c->db,c->argv[1]);
-            notifyKeyspaceEvent(REDIS_NOTIFY_LIST,"linsert",
+            notifyKeyspaceEvent(NOTIFY_LIST,"linsert",
                                 c->argv[1],c->db->id);
             server.dirty++;
         } else {
             /* Notify client of a failed insert */
             addReply(c,shared.cnegone);
             return;
         }
     } else {
-        char *event = (where == REDIS_HEAD) ? "lpush" : "rpush";
+        char *event = (where == LIST_HEAD) ? "lpush" : "rpush";
 
         listTypePush(subject,val,where);
         signalModifiedKey(c->db,c->argv[1]);
-        notifyKeyspaceEvent(REDIS_NOTIFY_LIST,event,c->argv[1],c->db->id);
+        notifyKeyspaceEvent(NOTIFY_LIST,event,c->argv[1],c->db->id);
         server.dirty++;
     }
 
     addReplyLongLong(c,listTypeLength(subject));
 }
 
-void lpushxCommand(redisClient *c) {
+void lpushxCommand(client *c) {
     c->argv[2] = tryObjectEncoding(c->argv[2]);
-    pushxGenericCommand(c,NULL,c->argv[2],REDIS_HEAD);
+    pushxGenericCommand(c,NULL,c->argv[2],LIST_HEAD);
 }
 
-void rpushxCommand(redisClient *c) {
+void rpushxCommand(client *c) {
     c->argv[2] = tryObjectEncoding(c->argv[2]);
-    pushxGenericCommand(c,NULL,c->argv[2],REDIS_TAIL);
+    pushxGenericCommand(c,NULL,c->argv[2],LIST_TAIL);
 }
 
-void linsertCommand(redisClient *c) {
+void linsertCommand(client *c) {
     c->argv[4] = tryObjectEncoding(c->argv[4]);
     if (strcasecmp(c->argv[2]->ptr,"after") == 0) {
-        pushxGenericCommand(c,c->argv[3],c->argv[4],REDIS_TAIL);
+        pushxGenericCommand(c,c->argv[3],c->argv[4],LIST_TAIL);
     } else if (strcasecmp(c->argv[2]->ptr,"before") == 0) {
-        pushxGenericCommand(c,c->argv[3],c->argv[4],REDIS_HEAD);
+        pushxGenericCommand(c,c->argv[3],c->argv[4],LIST_HEAD);
     } else {
         addReply(c,shared.syntaxerr);
     }
 }
 
-void llenCommand(redisClient *c) {
+void llenCommand(client *c) {
     robj *o = lookupKeyReadOrReply(c,c->argv[1],shared.czero);
-    if (o == NULL || checkType(c,o,REDIS_LIST)) return;
+    if (o == NULL || checkType(c,o,OBJ_LIST)) return;
     addReplyLongLong(c,listTypeLength(o));
 }
 
-void lindexCommand(redisClient *c) {
+void lindexCommand(client *c) {
     robj *o = lookupKeyReadOrReply(c,c->argv[1],shared.nullbulk);
-    if (o == NULL || checkType(c,o,REDIS_LIST)) return;
+    if (o == NULL || checkType(c,o,OBJ_LIST)) return;
     long index;
     robj *value = NULL;
 
-    if ((getLongFromObjectOrReply(c, c->argv[2], &index, NULL) != REDIS_OK))
+    if ((getLongFromObjectOrReply(c, c->argv[2], &index, NULL) != C_OK))
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
+    if (o->encoding == OBJ_ENCODING_QUICKLIST) {
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
-        redisPanic("Unknown list encoding");
+        serverPanic("Unknown list encoding");
     }
 }
 
-void lsetCommand(redisClient *c) {
+void lsetCommand(client *c) {
     robj *o = lookupKeyWriteOrReply(c,c->argv[1],shared.nokeyerr);
-    if (o == NULL || checkType(c,o,REDIS_LIST)) return;
+    if (o == NULL || checkType(c,o,OBJ_LIST)) return;
     long index;
-    robj *value = (c->argv[3] = tryObjectEncoding(c->argv[3]));
+    robj *value = c->argv[3];
 
-    if ((getLongFromObjectOrReply(c, c->argv[2], &index, NULL) != REDIS_OK))
+    if ((getLongFromObjectOrReply(c, c->argv[2], &index, NULL) != C_OK))
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
+    if (o->encoding == OBJ_ENCODING_QUICKLIST) {
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
-            notifyKeyspaceEvent(REDIS_NOTIFY_LIST,"lset",c->argv[1],c->db->id);
+            notifyKeyspaceEvent(NOTIFY_LIST,"lset",c->argv[1],c->db->id);
             server.dirty++;
         }
     } else {
-        redisPanic("Unknown list encoding");
+        serverPanic("Unknown list encoding");
     }
 }
 
-void popGenericCommand(redisClient *c, int where) {
+void popGenericCommand(client *c, int where) {
     robj *o = lookupKeyWriteOrReply(c,c->argv[1],shared.nullbulk);
-    if (o == NULL || checkType(c,o,REDIS_LIST)) return;
+    if (o == NULL || checkType(c,o,OBJ_LIST)) return;
 
     robj *value = listTypePop(o,where);
     if (value == NULL) {
         addReply(c,shared.nullbulk);
     } else {
-        char *event = (where == REDIS_HEAD) ? "lpop" : "rpop";
+        char *event = (where == LIST_HEAD) ? "lpop" : "rpop";
 
         addReplyBulk(c,value);
         decrRefCount(value);
-        notifyKeyspaceEvent(REDIS_NOTIFY_LIST,event,c->argv[1],c->db->id);
+        notifyKeyspaceEvent(NOTIFY_LIST,event,c->argv[1],c->db->id);
         if (listTypeLength(o) == 0) {
-            notifyKeyspaceEvent(REDIS_NOTIFY_GENERIC,"del",
+            notifyKeyspaceEvent(NOTIFY_GENERIC,"del",
                                 c->argv[1],c->db->id);
             dbDelete(c->db,c->argv[1]);
         }
         signalModifiedKey(c->db,c->argv[1]);
         server.dirty++;
     }
 }
 
-void lpopCommand(redisClient *c) {
-    popGenericCommand(c,REDIS_HEAD);
+void lpopCommand(client *c) {
+    popGenericCommand(c,LIST_HEAD);
 }
 
-void rpopCommand(redisClient *c) {
-    popGenericCommand(c,REDIS_TAIL);
+void rpopCommand(client *c) {
+    popGenericCommand(c,LIST_TAIL);
 }
 
-void lrangeCommand(redisClient *c) {
+void lrangeCommand(client *c) {
     robj *o;
     long start, end, llen, rangelen;
 
-    if ((getLongFromObjectOrReply(c, c->argv[2], &start, NULL) != REDIS_OK) ||
-        (getLongFromObjectOrReply(c, c->argv[3], &end, NULL) != REDIS_OK)) return;
+    if ((getLongFromObjectOrReply(c, c->argv[2], &start, NULL) != C_OK) ||
+        (getLongFromObjectOrReply(c, c->argv[3], &end, NULL) != C_OK)) return;
 
     if ((o = lookupKeyReadOrReply(c,c->argv[1],shared.emptymultibulk)) == NULL
-         || checkType(c,o,REDIS_LIST)) return;
+         || checkType(c,o,OBJ_LIST)) return;
     llen = listTypeLength(o);
 
     /* convert negative indexes */
     if (start < 0) start = llen+start;
     if (end < 0) end = llen+end;
     if (start < 0) start = 0;
