@@ -40,13 +40,13 @@
  * the function takes care of it if needed. */
 void listTypePush(robj *subject, robj *value, int where) {
     if (subject->encoding == OBJ_ENCODING_QUICKLIST) {
-        int pos = (where == REDIS_HEAD) ? QUICKLIST_HEAD : QUICKLIST_TAIL;
+        int pos = (where == LIST_HEAD) ? QUICKLIST_HEAD : QUICKLIST_TAIL;
         value = getDecodedObject(value);
         size_t len = sdslen(value->ptr);
         quicklistPush(subject->ptr, value->ptr, len, pos);
         decrRefCount(value);
     } else {
-        redisPanic("Unknown list encoding");
+        serverPanic("Unknown list encoding");
     }
 }
 
@@ -58,15 +58,15 @@ robj *listTypePop(robj *subject, int where) {
     long long vlong;
     robj *value = NULL;
 
-    int ql_where = where == REDIS_HEAD ? QUICKLIST_HEAD : QUICKLIST_TAIL;
+    int ql_where = where == LIST_HEAD ? QUICKLIST_HEAD : QUICKLIST_TAIL;
     if (subject->encoding == OBJ_ENCODING_QUICKLIST) {
         if (quicklistPopCustom(subject->ptr, ql_where, (unsigned char **)&value,
                                NULL, &vlong, listPopSaver)) {
             if (!value)
                 value = createStringObjectFromLongLong(vlong);
         }
     } else {
-        redisPanic("Unknown list encoding");
+        serverPanic("Unknown list encoding");
     }
     return value;
 }
@@ -75,7 +75,7 @@ unsigned long listTypeLength(robj *subject) {
     if (subject->encoding == OBJ_ENCODING_QUICKLIST) {
         return quicklistCount(subject->ptr);
     } else {
-        redisPanic("Unknown list encoding");
+        serverPanic("Unknown list encoding");
     }
 }
 
@@ -87,15 +87,15 @@ listTypeIterator *listTypeInitIterator(robj *subject, long index,
     li->encoding = subject->encoding;
     li->direction = direction;
     li->iter = NULL;
-    /* REDIS_HEAD means start at TAIL and move *towards* head.
-     * REDIS_TAIL means start at HEAD and move *towards tail. */
+    /* LIST_HEAD means start at TAIL and move *towards* head.
+     * LIST_TAIL means start at HEAD and move *towards tail. */
     int iter_direction =
-        direction == REDIS_HEAD ? AL_START_TAIL : AL_START_HEAD;
+        direction == LIST_HEAD ? AL_START_TAIL : AL_START_HEAD;
     if (li->encoding == OBJ_ENCODING_QUICKLIST) {
         li->iter = quicklistGetIteratorAtIdx(li->subject->ptr,
                                              iter_direction, index);
     } else {
-        redisPanic("Unknown list encoding");
+        serverPanic("Unknown list encoding");
     }
     return li;
 }
@@ -117,7 +117,7 @@ int listTypeNext(listTypeIterator *li, listTypeEntry *entry) {
     if (li->encoding == OBJ_ENCODING_QUICKLIST) {
         return quicklistNext(li->iter, &entry->entry);
     } else {
-        redisPanic("Unknown list encoding");
+        serverPanic("Unknown list encoding");
     }
     return 0;
 }
@@ -133,7 +133,7 @@ robj *listTypeGet(listTypeEntry *entry) {
             value = createStringObjectFromLongLong(entry->entry.longval);
         }
     } else {
-        redisPanic("Unknown list encoding");
+        serverPanic("Unknown list encoding");
     }
     return value;
 }
@@ -143,16 +143,16 @@ void listTypeInsert(listTypeEntry *entry, robj *value, int where) {
         value = getDecodedObject(value);
         sds str = value->ptr;
         size_t len = sdslen(str);
-        if (where == REDIS_TAIL) {
+        if (where == LIST_TAIL) {
             quicklistInsertAfter((quicklist *)entry->entry.quicklist,
                                  &entry->entry, str, len);
-        } else if (where == REDIS_HEAD) {
+        } else if (where == LIST_HEAD) {
             quicklistInsertBefore((quicklist *)entry->entry.quicklist,
                                   &entry->entry, str, len);
         }
         decrRefCount(value);
     } else {
-        redisPanic("Unknown list encoding");
+        serverPanic("Unknown list encoding");
     }
 }
 
@@ -162,7 +162,7 @@ int listTypeEqual(listTypeEntry *entry, robj *o) {
         serverAssertWithInfo(NULL,o,sdsEncodedObject(o));
         return quicklistCompare(entry->entry.zi,o->ptr,sdslen(o->ptr));
     } else {
-        redisPanic("Unknown list encoding");
+        serverPanic("Unknown list encoding");
     }
 }
 
@@ -171,7 +171,7 @@ void listTypeDelete(listTypeIterator *iter, listTypeEntry *entry) {
     if (entry->li->encoding == OBJ_ENCODING_QUICKLIST) {
         quicklistDelEntry(iter->iter, &entry->entry);
     } else {
-        redisPanic("Unknown list encoding");
+        serverPanic("Unknown list encoding");
     }
 }
 
@@ -186,7 +186,7 @@ void listTypeConvert(robj *subject, int enc) {
         subject->ptr = quicklistCreateFromZiplist(zlen, depth, subject->ptr);
         subject->encoding = OBJ_ENCODING_QUICKLIST;
     } else {
-        redisPanic("Unsupported list conversion");
+        serverPanic("Unsupported list conversion");
     }
 }
 
@@ -216,20 +216,20 @@ void pushGenericCommand(client *c, int where) {
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
 
 void lpushCommand(client *c) {
-    pushGenericCommand(c,REDIS_HEAD);
+    pushGenericCommand(c,LIST_HEAD);
 }
 
 void rpushCommand(client *c) {
-    pushGenericCommand(c,REDIS_TAIL);
+    pushGenericCommand(c,LIST_TAIL);
 }
 
 void pushxGenericCommand(client *c, robj *refval, robj *val, int where) {
@@ -243,7 +243,7 @@ void pushxGenericCommand(client *c, robj *refval, robj *val, int where) {
 
     if (refval != NULL) {
         /* Seek refval from head to tail */
-        iter = listTypeInitIterator(subject,0,REDIS_TAIL);
+        iter = listTypeInitIterator(subject,0,LIST_TAIL);
         while (listTypeNext(iter,&entry)) {
             if (listTypeEqual(&entry,refval)) {
                 listTypeInsert(&entry,val,where);
@@ -255,7 +255,7 @@ void pushxGenericCommand(client *c, robj *refval, robj *val, int where) {
 
         if (inserted) {
             signalModifiedKey(c->db,c->argv[1]);
-            notifyKeyspaceEvent(REDIS_NOTIFY_LIST,"linsert",
+            notifyKeyspaceEvent(NOTIFY_LIST,"linsert",
                                 c->argv[1],c->db->id);
             server.dirty++;
         } else {
@@ -264,11 +264,11 @@ void pushxGenericCommand(client *c, robj *refval, robj *val, int where) {
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
 
@@ -277,20 +277,20 @@ void pushxGenericCommand(client *c, robj *refval, robj *val, int where) {
 
 void lpushxCommand(client *c) {
     c->argv[2] = tryObjectEncoding(c->argv[2]);
-    pushxGenericCommand(c,NULL,c->argv[2],REDIS_HEAD);
+    pushxGenericCommand(c,NULL,c->argv[2],LIST_HEAD);
 }
 
 void rpushxCommand(client *c) {
     c->argv[2] = tryObjectEncoding(c->argv[2]);
-    pushxGenericCommand(c,NULL,c->argv[2],REDIS_TAIL);
+    pushxGenericCommand(c,NULL,c->argv[2],LIST_TAIL);
 }
 
 void linsertCommand(client *c) {
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
@@ -325,7 +325,7 @@ void lindexCommand(client *c) {
             addReply(c,shared.nullbulk);
         }
     } else {
-        redisPanic("Unknown list encoding");
+        serverPanic("Unknown list encoding");
     }
 }
 
@@ -347,11 +347,11 @@ void lsetCommand(client *c) {
         } else {
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
 
@@ -363,13 +363,13 @@ void popGenericCommand(client *c, int where) {
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
@@ -379,11 +379,11 @@ void popGenericCommand(client *c, int where) {
 }
 
 void lpopCommand(client *c) {
-    popGenericCommand(c,REDIS_HEAD);
+    popGenericCommand(c,LIST_HEAD);
 }
 
 void rpopCommand(client *c) {
-    popGenericCommand(c,REDIS_TAIL);
+    popGenericCommand(c,LIST_TAIL);
 }
 
 void lrangeCommand(client *c) {
@@ -414,7 +414,7 @@ void lrangeCommand(client *c) {
     /* Return the result in form of a multi-bulk reply */
     addReplyMultiBulkLen(c,rangelen);
     if (o->encoding == OBJ_ENCODING_QUICKLIST) {
-        listTypeIterator *iter = listTypeInitIterator(o, start, REDIS_TAIL);
+        listTypeIterator *iter = listTypeInitIterator(o, start, LIST_TAIL);
 
         while(rangelen--) {
             listTypeEntry entry;
@@ -428,7 +428,7 @@ void lrangeCommand(client *c) {
         }
         listTypeReleaseIterator(iter);
     } else {
-        redisPanic("List encoding is not QUICKLIST!");
+        serverPanic("List encoding is not QUICKLIST!");
     }
 }
 
@@ -465,13 +465,13 @@ void ltrimCommand(client *c) {
         quicklistDelRange(o->ptr,0,ltrim);
         quicklistDelRange(o->ptr,-rtrim,rtrim);
     } else {
-        redisPanic("Unknown list encoding");
+        serverPanic("Unknown list encoding");
     }
 
-    notifyKeyspaceEvent(REDIS_NOTIFY_LIST,"ltrim",c->argv[1],c->db->id);
+    notifyKeyspaceEvent(NOTIFY_LIST,"ltrim",c->argv[1],c->db->id);
     if (listTypeLength(o) == 0) {
         dbDelete(c->db,c->argv[1]);
-        notifyKeyspaceEvent(REDIS_NOTIFY_GENERIC,"del",c->argv[1],c->db->id);
+        notifyKeyspaceEvent(NOTIFY_GENERIC,"del",c->argv[1],c->db->id);
     }
     signalModifiedKey(c->db,c->argv[1]);
     server.dirty++;
@@ -493,9 +493,9 @@ void lremCommand(client *c) {
     listTypeIterator *li;
     if (toremove < 0) {
         toremove = -toremove;
-        li = listTypeInitIterator(subject,-1,REDIS_HEAD);
+        li = listTypeInitIterator(subject,-1,LIST_HEAD);
     } else {
-        li = listTypeInitIterator(subject,0,REDIS_TAIL);
+        li = listTypeInitIterator(subject,0,LIST_TAIL);
     }
 
     listTypeEntry entry;
@@ -542,8 +542,8 @@ void rpoplpushHandlePush(client *c, robj *dstkey, robj *dstobj, robj *value) {
         dbAdd(c->db,dstkey,dstobj);
     }
     signalModifiedKey(c->db,dstkey);
-    listTypePush(dstobj,value,REDIS_HEAD);
-    notifyKeyspaceEvent(REDIS_NOTIFY_LIST,"lpush",dstkey,c->db->id);
+    listTypePush(dstobj,value,LIST_HEAD);
+    notifyKeyspaceEvent(NOTIFY_LIST,"lpush",dstkey,c->db->id);
     /* Always send the pushed value to the client. */
     addReplyBulk(c,value);
 }
@@ -562,7 +562,7 @@ void rpoplpushCommand(client *c) {
         robj *touchedkey = c->argv[1];
 
         if (dobj && checkType(c,dobj,OBJ_LIST)) return;
-        value = listTypePop(sobj,REDIS_TAIL);
+        value = listTypePop(sobj,LIST_TAIL);
         /* We saved touched key, and protect it, since rpoplpushHandlePush
          * may change the client command argument vector (it does not
          * currently). */
@@ -573,10 +573,10 @@ void rpoplpushCommand(client *c) {
         decrRefCount(value);
 
         /* Delete the source list when it is empty */
-        notifyKeyspaceEvent(REDIS_NOTIFY_LIST,"rpop",touchedkey,c->db->id);
+        notifyKeyspaceEvent(NOTIFY_LIST,"rpop",touchedkey,c->db->id);
         if (listTypeLength(sobj) == 0) {
             dbDelete(c->db,touchedkey);
-            notifyKeyspaceEvent(REDIS_NOTIFY_GENERIC,"del",
+            notifyKeyspaceEvent(NOTIFY_GENERIC,"del",
                                 touchedkey,c->db->id);
         }
         signalModifiedKey(c->db,touchedkey);
@@ -638,7 +638,7 @@ void blockForKeys(client *c, robj **keys, int numkeys, mstime_t timeout, robj *t
         }
         listAddNodeTail(l,c);
     }
-    blockClient(c,REDIS_BLOCKED_LIST);
+    blockClient(c,BLOCKED_LIST);
 }
 
 /* Unblock a client that's waiting in a blocking operation such as BLPOP.
@@ -712,7 +712,7 @@ void signalListAsReady(redisDb *db, robj *key) {
  * 3) Propagate the resulting BRPOP, BLPOP and additional LPUSH if any into
  *    the AOF and replication channel.
  *
- * The argument 'where' is REDIS_TAIL or REDIS_HEAD, and indicates if the
+ * The argument 'where' is LIST_TAIL or LIST_HEAD, and indicates if the
  * 'value' element was popped fron the head (BLPOP) or tail (BRPOP) so that
  * we can propagate the command properly.
  *
@@ -727,12 +727,12 @@ int serveClientBlockedOnList(client *receiver, robj *key, robj *dstkey, redisDb
 
     if (dstkey == NULL) {
         /* Propagate the [LR]POP operation. */
-        argv[0] = (where == REDIS_HEAD) ? shared.lpop :
+        argv[0] = (where == LIST_HEAD) ? shared.lpop :
                                           shared.rpop;
         argv[1] = key;
-        propagate((where == REDIS_HEAD) ?
+        propagate((where == LIST_HEAD) ?
             server.lpopCommand : server.rpopCommand,
-            db->id,argv,2,REDIS_PROPAGATE_AOF|REDIS_PROPAGATE_REPL);
+            db->id,argv,2,PROPAGATE_AOF|PROPAGATE_REPL);
 
         /* BRPOP/BLPOP */
         addReplyMultiBulkLen(receiver,2);
@@ -750,8 +750,8 @@ int serveClientBlockedOnList(client *receiver, robj *key, robj *dstkey, redisDb
             argv[1] = key;
             propagate(server.rpopCommand,
                 db->id,argv,2,
-                REDIS_PROPAGATE_AOF|
-                REDIS_PROPAGATE_REPL);
+                PROPAGATE_AOF|
+                PROPAGATE_REPL);
             rpoplpushHandlePush(receiver,dstkey,dstobj,
                 value);
             /* Propagate the LPUSH operation. */
@@ -760,8 +760,8 @@ int serveClientBlockedOnList(client *receiver, robj *key, robj *dstkey, redisDb
             argv[2] = value;
             propagate(server.lpushCommand,
                 db->id,argv,3,
-                REDIS_PROPAGATE_AOF|
-                REDIS_PROPAGATE_REPL);
+                PROPAGATE_AOF|
+                PROPAGATE_REPL);
         } else {
             /* BRPOPLPUSH failed because of wrong
              * destination type. */
@@ -819,7 +819,7 @@ void handleClientsBlockedOnLists(void) {
                         robj *dstkey = receiver->bpop.target;
                         int where = (receiver->lastcmd &&
                                      receiver->lastcmd->proc == blpopCommand) ?
-                                    REDIS_HEAD : REDIS_TAIL;
+                                    LIST_HEAD : LIST_TAIL;
                         robj *value = listTypePop(o,where);
 
                         if (value) {
@@ -880,27 +880,27 @@ void blockingPopGenericCommand(client *c, int where) {
             } else {
                 if (listTypeLength(o) != 0) {
                     /* Non empty list, this is like a non normal [LR]POP. */
-                    char *event = (where == REDIS_HEAD) ? "lpop" : "rpop";
+                    char *event = (where == LIST_HEAD) ? "lpop" : "rpop";
                     robj *value = listTypePop(o,where);
                     serverAssert(value != NULL);
 
                     addReplyMultiBulkLen(c,2);
                     addReplyBulk(c,c->argv[j]);
                     addReplyBulk(c,value);
                     decrRefCount(value);
-                    notifyKeyspaceEvent(REDIS_NOTIFY_LIST,event,
+                    notifyKeyspaceEvent(NOTIFY_LIST,event,
                                         c->argv[j],c->db->id);
                     if (listTypeLength(o) == 0) {
                         dbDelete(c->db,c->argv[j]);
-                        notifyKeyspaceEvent(REDIS_NOTIFY_GENERIC,"del",
+                        notifyKeyspaceEvent(NOTIFY_GENERIC,"del",
                                             c->argv[j],c->db->id);
                     }
                     signalModifiedKey(c->db,c->argv[j]);
                     server.dirty++;
 
                     /* Replicate it as an [LR]POP instead of B[LR]POP. */
                     rewriteClientCommandVector(c,2,
-                        (where == REDIS_HEAD) ? shared.lpop : shared.rpop,
+                        (where == LIST_HEAD) ? shared.lpop : shared.rpop,
                         c->argv[j]);
                     return;
                 }
@@ -910,7 +910,7 @@ void blockingPopGenericCommand(client *c, int where) {
 
     /* If we are inside a MULTI/EXEC and the list is empty the only thing
      * we can do is treating it as a timeout (even with timeout 0). */
-    if (c->flags & REDIS_MULTI) {
+    if (c->flags & CLIENT_MULTI) {
         addReply(c,shared.nullmultibulk);
         return;
     }
@@ -920,11 +920,11 @@ void blockingPopGenericCommand(client *c, int where) {
 }
 
 void blpopCommand(client *c) {
-    blockingPopGenericCommand(c,REDIS_HEAD);
+    blockingPopGenericCommand(c,LIST_HEAD);
 }
 
 void brpopCommand(client *c) {
-    blockingPopGenericCommand(c,REDIS_TAIL);
+    blockingPopGenericCommand(c,LIST_TAIL);
 }
 
 void brpoplpushCommand(client *c) {
@@ -936,7 +936,7 @@ void brpoplpushCommand(client *c) {
     robj *key = lookupKeyWrite(c->db, c->argv[1]);
 
     if (key == NULL) {
-        if (c->flags & REDIS_MULTI) {
+        if (c->flags & CLIENT_MULTI) {
             /* Blocking against an empty list in a multi state
              * returns immediately. */
             addReply(c, shared.nullbulk);