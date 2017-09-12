@@ -2478,6 +2478,13 @@ static void addReplyLong(redisClient *c, long l) {
     char buf[128];
     size_t len;
 
+    if (l == 0) {
+        addReply(c,shared.czero);
+        return;
+    } else if (l == 1) {
+        addReply(c,shared.cone);
+        return;
+    }
     len = snprintf(buf,sizeof(buf),":%ld\r\n",l);
     addReplySds(c,sdsnewlen(buf,len));
 }
@@ -2486,6 +2493,13 @@ static void addReplyUlong(redisClient *c, unsigned long ul) {
     char buf[128];
     size_t len;
 
+    if (ul == 0) {
+        addReply(c,shared.czero);
+        return;
+    } else if (ul == 1) {
+        addReply(c,shared.cone);
+        return;
+    }
     len = snprintf(buf,sizeof(buf),":%lu\r\n",ul);
     addReplySds(c,sdsnewlen(buf,len));
 }
@@ -2511,6 +2525,12 @@ static void addReplyBulkLen(redisClient *c, robj *obj) {
     addReplySds(c,sdscatprintf(sdsempty(),"$%lu\r\n",(unsigned long)len));
 }
 
+static void addReplyBulk(redisClient *c, robj *obj) {
+    addReplyBulkLen(c,obj);
+    addReply(c,obj);
+    addReply(c,shared.crlf);
+}
+
 static void acceptHandler(aeEventLoop *el, int fd, void *privdata, int mask) {
     int cport, cfd;
     char cip[128];
@@ -3682,9 +3702,7 @@ static void pingCommand(redisClient *c) {
 }
 
 static void echoCommand(redisClient *c) {
-    addReplyBulkLen(c,c->argv[1]);
-    addReply(c,c->argv[1]);
-    addReply(c,shared.crlf);
+    addReplyBulk(c,c->argv[1]);
 }
 
 /*=================================== Strings =============================== */
@@ -3726,21 +3744,17 @@ static void setnxCommand(redisClient *c) {
 }
 
 static int getGenericCommand(redisClient *c) {
-    robj *o = lookupKeyRead(c->db,c->argv[1]);
-
-    if (o == NULL) {
-        addReply(c,shared.nullbulk);
+    robj *o;
+    
+    if ((o = lookupKeyReadOrReply(c,c->argv[1],shared.nullbulk)) == NULL)
         return REDIS_OK;
+
+    if (o->type != REDIS_STRING) {
+        addReply(c,shared.wrongtypeerr);
+        return REDIS_ERR;
     } else {
-        if (o->type != REDIS_STRING) {
-            addReply(c,shared.wrongtypeerr);
-            return REDIS_ERR;
-        } else {
-            addReplyBulkLen(c,o);
-            addReply(c,o);
-            addReply(c,shared.crlf);
-            return REDIS_OK;
-        }
+        addReplyBulk(c,o);
+        return REDIS_OK;
     }
 }
 
@@ -3772,9 +3786,7 @@ static void mgetCommand(redisClient *c) {
             if (o->type != REDIS_STRING) {
                 addReply(c,shared.nullbulk);
             } else {
-                addReplyBulkLen(c,o);
-                addReply(c,o);
-                addReply(c,shared.crlf);
+                addReplyBulk(c,o);
             }
         }
     }
@@ -3934,44 +3946,37 @@ static void substrCommand(redisClient *c) {
     robj *o;
     long start = atoi(c->argv[2]->ptr);
     long end = atoi(c->argv[3]->ptr);
+    size_t rangelen, strlen;
+    sds range;
 
-    o = lookupKeyRead(c->db,c->argv[1]);
-    if (o == NULL) {
-        addReply(c,shared.nullbulk);
-    } else {
-        if (o->type != REDIS_STRING) {
-            addReply(c,shared.wrongtypeerr);
-        } else {
-            size_t rangelen, strlen;
-            sds range;
-
-            o = getDecodedObject(o);
-            strlen = sdslen(o->ptr);
+    if ((o = lookupKeyReadOrReply(c,c->argv[1],shared.nullbulk)) == NULL ||
+        checkType(c,o,REDIS_STRING)) return;
 
-            /* convert negative indexes */
-            if (start < 0) start = strlen+start;
-            if (end < 0) end = strlen+end;
-            if (start < 0) start = 0;
-            if (end < 0) end = 0;
+    o = getDecodedObject(o);
+    strlen = sdslen(o->ptr);
 
-            /* indexes sanity checks */
-            if (start > end || (size_t)start >= strlen) {
-                /* Out of range start or start > end result in null reply */
-                addReply(c,shared.nullbulk);
-                decrRefCount(o);
-                return;
-            }
-            if ((size_t)end >= strlen) end = strlen-1;
-            rangelen = (end-start)+1;
+    /* convert negative indexes */
+    if (start < 0) start = strlen+start;
+    if (end < 0) end = strlen+end;
+    if (start < 0) start = 0;
+    if (end < 0) end = 0;
 
-            /* Return the result */
-            addReplySds(c,sdscatprintf(sdsempty(),"$%zu\r\n",rangelen));
-            range = sdsnewlen((char*)o->ptr+start,rangelen);
-            addReplySds(c,range);
-            addReply(c,shared.crlf);
-            decrRefCount(o);
-        }
+    /* indexes sanity checks */
+    if (start > end || (size_t)start >= strlen) {
+        /* Out of range start or start > end result in null reply */
+        addReply(c,shared.nullbulk);
+        decrRefCount(o);
+        return;
     }
+    if ((size_t)end >= strlen) end = strlen-1;
+    rangelen = (end-start)+1;
+
+    /* Return the result */
+    addReplySds(c,sdscatprintf(sdsempty(),"$%zu\r\n",rangelen));
+    range = sdsnewlen((char*)o->ptr+start,rangelen);
+    addReplySds(c,range);
+    addReply(c,shared.crlf);
+    decrRefCount(o);
 }
 
 /* ========================= Type agnostic commands ========================= */
@@ -3985,17 +3990,7 @@ static void delCommand(redisClient *c) {
             deleted++;
         }
     }
-    switch(deleted) {
-    case 0:
-        addReply(c,shared.czero);
-        break;
-    case 1:
-        addReply(c,shared.cone);
-        break;
-    default:
-        addReplySds(c,sdscatprintf(sdsempty(),":%d\r\n",deleted));
-        break;
-    }
+    addReplyLong(c,deleted);
 }
 
 static void existsCommand(redisClient *c) {
@@ -4047,9 +4042,7 @@ static void keysCommand(redisClient *c) {
         if ((pattern[0] == '*' && pattern[1] == '\0') ||
             stringmatchlen(pattern,plen,key,sdslen(key),0)) {
             if (expireIfNeeded(c->db,keyobj) == 0) {
-                addReplyBulkLen(c,keyobj);
-                addReply(c,keyobj);
-                addReply(c,shared.crlf);
+                addReplyBulk(c,keyobj);
                 numkeys++;
             }
         }
@@ -4139,12 +4132,14 @@ static void shutdownCommand(redisClient *c) {
             if (server.vm_enabled) unlink(server.vm_swap_file);
             exit(0);
         } else {
-            /* Ooops.. error saving! The best we can do is to continue operating.
-             * Note that if there was a background saving process, in the next
-             * cron() Redis will be notified that the background saving aborted,
-             * handling special stuff like slaves pending for synchronization... */
+            /* Ooops.. error saving! The best we can do is to continue
+             * operating. Note that if there was a background saving process,
+             * in the next cron() Redis will be notified that the background
+             * saving aborted, handling special stuff like slaves pending for
+             * synchronization... */
             redisLog(REDIS_WARNING,"Error trying to save the DB, can't exit"); 
-            addReplySds(c,sdsnew("-ERR can't quit, problems saving the DB\r\n"));
+            addReplySds(c,
+                sdsnew("-ERR can't quit, problems saving the DB\r\n"));
         }
     }
 }
@@ -4158,11 +4153,9 @@ static void renameGenericCommand(redisClient *c, int nx) {
         return;
     }
 
-    o = lookupKeyWrite(c->db,c->argv[1]);
-    if (o == NULL) {
-        addReply(c,shared.nokeyerr);
+    if ((o = lookupKeyWriteOrReply(c,c->argv[1],shared.nokeyerr)) == NULL)
         return;
-    }
+
     incrRefCount(o);
     deleteIfVolatile(c->db,c->argv[2]);
     if (dictAdd(c->db->dict,c->argv[2],o) == DICT_ERR) {
@@ -4285,107 +4278,78 @@ static void rpushCommand(redisClient *c) {
 static void llenCommand(redisClient *c) {
     robj *o;
     list *l;
+
+    if ((o = lookupKeyReadOrReply(c,c->argv[1],shared.czero)) == NULL ||
+        checkType(c,o,REDIS_LIST)) return;
     
-    o = lookupKeyRead(c->db,c->argv[1]);
-    if (o == NULL) {
-        addReply(c,shared.czero);
-        return;
-    } else {
-        if (o->type != REDIS_LIST) {
-            addReply(c,shared.wrongtypeerr);
-        } else {
-            l = o->ptr;
-            addReplySds(c,sdscatprintf(sdsempty(),":%d\r\n",listLength(l)));
-        }
-    }
+    l = o->ptr;
+    addReplyUlong(c,listLength(l));
 }
 
 static void lindexCommand(redisClient *c) {
     robj *o;
     int index = atoi(c->argv[2]->ptr);
-    
-    o = lookupKeyRead(c->db,c->argv[1]);
-    if (o == NULL) {
+    list *list;
+    listNode *ln;
+
+    if ((o = lookupKeyReadOrReply(c,c->argv[1],shared.nullbulk)) == NULL ||
+        checkType(c,o,REDIS_LIST)) return;
+    list = o->ptr;
+
+    ln = listIndex(list, index);
+    if (ln == NULL) {
         addReply(c,shared.nullbulk);
     } else {
-        if (o->type != REDIS_LIST) {
-            addReply(c,shared.wrongtypeerr);
-        } else {
-            list *list = o->ptr;
-            listNode *ln;
-            
-            ln = listIndex(list, index);
-            if (ln == NULL) {
-                addReply(c,shared.nullbulk);
-            } else {
-                robj *ele = listNodeValue(ln);
-                addReplyBulkLen(c,ele);
-                addReply(c,ele);
-                addReply(c,shared.crlf);
-            }
-        }
+        robj *ele = listNodeValue(ln);
+        addReplyBulk(c,ele);
     }
 }
 
 static void lsetCommand(redisClient *c) {
     robj *o;
     int index = atoi(c->argv[2]->ptr);
-    
-    o = lookupKeyWrite(c->db,c->argv[1]);
-    if (o == NULL) {
-        addReply(c,shared.nokeyerr);
+    list *list;
+    listNode *ln;
+
+    if ((o = lookupKeyWriteOrReply(c,c->argv[1],shared.nokeyerr)) == NULL ||
+        checkType(c,o,REDIS_LIST)) return;
+    list = o->ptr;
+
+    ln = listIndex(list, index);
+    if (ln == NULL) {
+        addReply(c,shared.outofrangeerr);
     } else {
-        if (o->type != REDIS_LIST) {
-            addReply(c,shared.wrongtypeerr);
-        } else {
-            list *list = o->ptr;
-            listNode *ln;
-            
-            ln = listIndex(list, index);
-            if (ln == NULL) {
-                addReply(c,shared.outofrangeerr);
-            } else {
-                robj *ele = listNodeValue(ln);
+        robj *ele = listNodeValue(ln);
 
-                decrRefCount(ele);
-                listNodeValue(ln) = c->argv[3];
-                incrRefCount(c->argv[3]);
-                addReply(c,shared.ok);
-                server.dirty++;
-            }
-        }
+        decrRefCount(ele);
+        listNodeValue(ln) = c->argv[3];
+        incrRefCount(c->argv[3]);
+        addReply(c,shared.ok);
+        server.dirty++;
     }
 }
 
 static void popGenericCommand(redisClient *c, int where) {
     robj *o;
+    list *list;
+    listNode *ln;
 
-    o = lookupKeyWrite(c->db,c->argv[1]);
-    if (o == NULL) {
-        addReply(c,shared.nullbulk);
-    } else {
-        if (o->type != REDIS_LIST) {
-            addReply(c,shared.wrongtypeerr);
-        } else {
-            list *list = o->ptr;
-            listNode *ln;
+    if ((o = lookupKeyWriteOrReply(c,c->argv[1],shared.nullbulk)) == NULL ||
+        checkType(c,o,REDIS_LIST)) return;
+    list = o->ptr;
 
-            if (where == REDIS_HEAD)
-                ln = listFirst(list);
-            else
-                ln = listLast(list);
+    if (where == REDIS_HEAD)
+        ln = listFirst(list);
+    else
+        ln = listLast(list);
 
-            if (ln == NULL) {
-                addReply(c,shared.nullbulk);
-            } else {
-                robj *ele = listNodeValue(ln);
-                addReplyBulkLen(c,ele);
-                addReply(c,ele);
-                addReply(c,shared.crlf);
-                listDelNode(list,ln);
-                server.dirty++;
-            }
-        }
+    if (ln == NULL) {
+        addReply(c,shared.nullbulk);
+    } else {
+        robj *ele = listNodeValue(ln);
+        addReplyBulk(c,ele);
+        listDelNode(list,ln);
+        server.dirty++;
     }
 }
 
@@ -4401,134 +4365,116 @@ static void lrangeCommand(redisClient *c) {
     robj *o;
     int start = atoi(c->argv[2]->ptr);
     int end = atoi(c->argv[3]->ptr);
+    int llen;
+    int rangelen, j;
+    list *list;
+    listNode *ln;
+    robj *ele;
+
+    if ((o = lookupKeyReadOrReply(c,c->argv[1],shared.nullmultibulk)) == NULL ||
+        checkType(c,o,REDIS_LIST)) return;
+    list = o->ptr;
+    llen = listLength(list);
+
+    /* convert negative indexes */
+    if (start < 0) start = llen+start;
+    if (end < 0) end = llen+end;
+    if (start < 0) start = 0;
+    if (end < 0) end = 0;
+
+    /* indexes sanity checks */
+    if (start > end || start >= llen) {
+        /* Out of range start or start > end result in empty list */
+        addReply(c,shared.emptymultibulk);
+        return;
+    }
+    if (end >= llen) end = llen-1;
+    rangelen = (end-start)+1;
 
-    o = lookupKeyRead(c->db,c->argv[1]);
-    if (o == NULL) {
-        addReply(c,shared.nullmultibulk);
-    } else {
-        if (o->type != REDIS_LIST) {
-            addReply(c,shared.wrongtypeerr);
-        } else {
-            list *list = o->ptr;
-            listNode *ln;
-            int llen = listLength(list);
-            int rangelen, j;
-            robj *ele;
-
-            /* convert negative indexes */
-            if (start < 0) start = llen+start;
-            if (end < 0) end = llen+end;
-            if (start < 0) start = 0;
-            if (end < 0) end = 0;
-
-            /* indexes sanity checks */
-            if (start > end || start >= llen) {
-                /* Out of range start or start > end result in empty list */
-                addReply(c,shared.emptymultibulk);
-                return;
-            }
-            if (end >= llen) end = llen-1;
-            rangelen = (end-start)+1;
-
-            /* Return the result in form of a multi-bulk reply */
-            ln = listIndex(list, start);
-            addReplySds(c,sdscatprintf(sdsempty(),"*%d\r\n",rangelen));
-            for (j = 0; j < rangelen; j++) {
-                ele = listNodeValue(ln);
-                addReplyBulkLen(c,ele);
-                addReply(c,ele);
-                addReply(c,shared.crlf);
-                ln = ln->next;
-            }
-        }
+    /* Return the result in form of a multi-bulk reply */
+    ln = listIndex(list, start);
+    addReplySds(c,sdscatprintf(sdsempty(),"*%d\r\n",rangelen));
+    for (j = 0; j < rangelen; j++) {
+        ele = listNodeValue(ln);
+        addReplyBulk(c,ele);
+        ln = ln->next;
     }
 }
 
 static void ltrimCommand(redisClient *c) {
     robj *o;
     int start = atoi(c->argv[2]->ptr);
     int end = atoi(c->argv[3]->ptr);
-    
-    o = lookupKeyWrite(c->db,c->argv[1]);
-    if (o == NULL) {
-        addReply(c,shared.ok);
+    int llen;
+    int j, ltrim, rtrim;
+    list *list;
+    listNode *ln;
+
+    if ((o = lookupKeyWriteOrReply(c,c->argv[1],shared.ok)) == NULL ||
+        checkType(c,o,REDIS_LIST)) return;
+    list = o->ptr;
+    llen = listLength(list);
+
+    /* convert negative indexes */
+    if (start < 0) start = llen+start;
+    if (end < 0) end = llen+end;
+    if (start < 0) start = 0;
+    if (end < 0) end = 0;
+
+    /* indexes sanity checks */
+    if (start > end || start >= llen) {
+        /* Out of range start or start > end result in empty list */
+        ltrim = llen;
+        rtrim = 0;
     } else {
-        if (o->type != REDIS_LIST) {
-            addReply(c,shared.wrongtypeerr);
-        } else {
-            list *list = o->ptr;
-            listNode *ln;
-            int llen = listLength(list);
-            int j, ltrim, rtrim;
-
-            /* convert negative indexes */
-            if (start < 0) start = llen+start;
-            if (end < 0) end = llen+end;
-            if (start < 0) start = 0;
-            if (end < 0) end = 0;
-
-            /* indexes sanity checks */
-            if (start > end || start >= llen) {
-                /* Out of range start or start > end result in empty list */
-                ltrim = llen;
-                rtrim = 0;
-            } else {
-                if (end >= llen) end = llen-1;
-                ltrim = start;
-                rtrim = llen-end-1;
-            }
+        if (end >= llen) end = llen-1;
+        ltrim = start;
+        rtrim = llen-end-1;
+    }
 
-            /* Remove list elements to perform the trim */
-            for (j = 0; j < ltrim; j++) {
-                ln = listFirst(list);
-                listDelNode(list,ln);
-            }
-            for (j = 0; j < rtrim; j++) {
-                ln = listLast(list);
-                listDelNode(list,ln);
-            }
-            server.dirty++;
-            addReply(c,shared.ok);
-        }
+    /* Remove list elements to perform the trim */
+    for (j = 0; j < ltrim; j++) {
+        ln = listFirst(list);
+        listDelNode(list,ln);
+    }
+    for (j = 0; j < rtrim; j++) {
+        ln = listLast(list);
+        listDelNode(list,ln);
     }
+    server.dirty++;
+    addReply(c,shared.ok);
 }
 
 static void lremCommand(redisClient *c) {
     robj *o;
-    
-    o = lookupKeyWrite(c->db,c->argv[1]);
-    if (o == NULL) {
-        addReply(c,shared.czero);
-    } else {
-        if (o->type != REDIS_LIST) {
-            addReply(c,shared.wrongtypeerr);
-        } else {
-            list *list = o->ptr;
-            listNode *ln, *next;
-            int toremove = atoi(c->argv[2]->ptr);
-            int removed = 0;
-            int fromtail = 0;
-
-            if (toremove < 0) {
-                toremove = -toremove;
-                fromtail = 1;
-            }
-            ln = fromtail ? list->tail : list->head;
-            while (ln) {
-                robj *ele = listNodeValue(ln);
+    list *list;
+    listNode *ln, *next;
+    int toremove = atoi(c->argv[2]->ptr);
+    int removed = 0;
+    int fromtail = 0;
 
-                next = fromtail ? ln->prev : ln->next;
-                if (compareStringObjects(ele,c->argv[3]) == 0) {
-                    listDelNode(list,ln);
-                    server.dirty++;
-                    removed++;
-                    if (toremove && removed == toremove) break;
-                }
-                ln = next;
-            }
-            addReplySds(c,sdscatprintf(sdsempty(),":%d\r\n",removed));
+    if ((o = lookupKeyWriteOrReply(c,c->argv[1],shared.czero)) == NULL ||
+        checkType(c,o,REDIS_LIST)) return;
+    list = o->ptr;
+
+    if (toremove < 0) {
+        toremove = -toremove;
+        fromtail = 1;
+    }
+    ln = fromtail ? list->tail : list->head;
+    while (ln) {
+        robj *ele = listNodeValue(ln);
+
+        next = fromtail ? ln->prev : ln->next;
+        if (compareStringObjects(ele,c->argv[3]) == 0) {
+            listDelNode(list,ln);
+            server.dirty++;
+            removed++;
+            if (toremove && removed == toremove) break;
         }
+        ln = next;
     }
+    addReplySds(c,sdscatprintf(sdsempty(),":%d\r\n",removed));
 }
 
 /* This is the semantic of this command:
@@ -4548,57 +4494,49 @@ static void lremCommand(redisClient *c) {
  */
 static void rpoplpushcommand(redisClient *c) {
     robj *sobj;
+    list *srclist;
+    listNode *ln;
+
+    if ((sobj = lookupKeyWriteOrReply(c,c->argv[1],shared.nullbulk)) == NULL ||
+        checkType(c,sobj,REDIS_LIST)) return;
+    srclist = sobj->ptr;
+    ln = listLast(srclist);
 
-    sobj = lookupKeyWrite(c->db,c->argv[1]);
-    if (sobj == NULL) {
+    if (ln == NULL) {
         addReply(c,shared.nullbulk);
     } else {
-        if (sobj->type != REDIS_LIST) {
-            addReply(c,shared.wrongtypeerr);
-        } else {
-            list *srclist = sobj->ptr;
-            listNode *ln = listLast(srclist);
-
-            if (ln == NULL) {
-                addReply(c,shared.nullbulk);
-            } else {
-                robj *dobj = lookupKeyWrite(c->db,c->argv[2]);
-                robj *ele = listNodeValue(ln);
-                list *dstlist;
-
-                if (dobj && dobj->type != REDIS_LIST) {
-                    addReply(c,shared.wrongtypeerr);
-                    return;
-                }
+        robj *dobj = lookupKeyWrite(c->db,c->argv[2]);
+        robj *ele = listNodeValue(ln);
+        list *dstlist;
 
-                /* Add the element to the target list (unless it's directly
-                 * passed to some BLPOP-ing client */
-                if (!handleClientsWaitingListPush(c,c->argv[2],ele)) {
-                    if (dobj == NULL) {
-                        /* Create the list if the key does not exist */
-                        dobj = createListObject();
-                        dictAdd(c->db->dict,c->argv[2],dobj);
-                        incrRefCount(c->argv[2]);
-                    }
-                    dstlist = dobj->ptr;
-                    listAddNodeHead(dstlist,ele);
-                    incrRefCount(ele);
-                }
-
-                /* Send the element to the client as reply as well */
-                addReplyBulkLen(c,ele);
-                addReply(c,ele);
-                addReply(c,shared.crlf);
+        if (dobj && dobj->type != REDIS_LIST) {
+            addReply(c,shared.wrongtypeerr);
+            return;
+        }
 
-                /* Finally remove the element from the source list */
-                listDelNode(srclist,ln);
-                server.dirty++;
+        /* Add the element to the target list (unless it's directly
+         * passed to some BLPOP-ing client */
+        if (!handleClientsWaitingListPush(c,c->argv[2],ele)) {
+            if (dobj == NULL) {
+                /* Create the list if the key does not exist */
+                dobj = createListObject();
+                dictAdd(c->db->dict,c->argv[2],dobj);
+                incrRefCount(c->argv[2]);
             }
+            dstlist = dobj->ptr;
+            listAddNodeHead(dstlist,ele);
+            incrRefCount(ele);
         }
+
+        /* Send the element to the client as reply as well */
+        addReplyBulk(c,ele);
+
+        /* Finally remove the element from the source list */
+        listDelNode(srclist,ln);
+        server.dirty++;
     }
 }
 
-
 /* ==================================== Sets ================================ */
 
 static void saddCommand(redisClient *c) {
@@ -4627,21 +4565,15 @@ static void saddCommand(redisClient *c) {
 static void sremCommand(redisClient *c) {
     robj *set;
 
-    set = lookupKeyWrite(c->db,c->argv[1]);
-    if (set == NULL) {
-        addReply(c,shared.czero);
+    if ((set = lookupKeyWriteOrReply(c,c->argv[1],shared.czero)) == NULL ||
+        checkType(c,set,REDIS_SET)) return;
+
+    if (dictDelete(set->ptr,c->argv[2]) == DICT_OK) {
+        server.dirty++;
+        if (htNeedsResize(set->ptr)) dictResize(set->ptr);
+        addReply(c,shared.cone);
     } else {
-        if (set->type != REDIS_SET) {
-            addReply(c,shared.wrongtypeerr);
-            return;
-        }
-        if (dictDelete(set->ptr,c->argv[2]) == DICT_OK) {
-            server.dirty++;
-            if (htNeedsResize(set->ptr)) dictResize(set->ptr);
-            addReply(c,shared.cone);
-        } else {
-            addReply(c,shared.czero);
-        }
+        addReply(c,shared.czero);
     }
 }
 
@@ -4683,90 +4615,60 @@ static void smoveCommand(redisClient *c) {
 static void sismemberCommand(redisClient *c) {
     robj *set;
 
-    set = lookupKeyRead(c->db,c->argv[1]);
-    if (set == NULL) {
+    if ((set = lookupKeyReadOrReply(c,c->argv[1],shared.czero)) == NULL ||
+        checkType(c,set,REDIS_SET)) return;
+
+    if (dictFind(set->ptr,c->argv[2]))
+        addReply(c,shared.cone);
+    else
         addReply(c,shared.czero);
-    } else {
-        if (set->type != REDIS_SET) {
-            addReply(c,shared.wrongtypeerr);
-            return;
-        }
-        if (dictFind(set->ptr,c->argv[2]))
-            addReply(c,shared.cone);
-        else
-            addReply(c,shared.czero);
-    }
 }
 
 static void scardCommand(redisClient *c) {
     robj *o;
     dict *s;
+
+    if ((o = lookupKeyReadOrReply(c,c->argv[1],shared.czero)) == NULL ||
+        checkType(c,o,REDIS_SET)) return;
     
-    o = lookupKeyRead(c->db,c->argv[1]);
-    if (o == NULL) {
-        addReply(c,shared.czero);
-        return;
-    } else {
-        if (o->type != REDIS_SET) {
-            addReply(c,shared.wrongtypeerr);
-        } else {
-            s = o->ptr;
-            addReplySds(c,sdscatprintf(sdsempty(),":%lu\r\n",
-                dictSize(s)));
-        }
-    }
+    s = o->ptr;
+    addReplyUlong(c,dictSize(s));
 }
 
 static void spopCommand(redisClient *c) {
     robj *set;
     dictEntry *de;
 
-    set = lookupKeyWrite(c->db,c->argv[1]);
-    if (set == NULL) {
+    if ((set = lookupKeyWriteOrReply(c,c->argv[1],shared.nullbulk)) == NULL ||
+        checkType(c,set,REDIS_SET)) return;
+
+    de = dictGetRandomKey(set->ptr);
+    if (de == NULL) {
         addReply(c,shared.nullbulk);
     } else {
-        if (set->type != REDIS_SET) {
-            addReply(c,shared.wrongtypeerr);
-            return;
-        }
-        de = dictGetRandomKey(set->ptr);
-        if (de == NULL) {
-            addReply(c,shared.nullbulk);
-        } else {
-            robj *ele = dictGetEntryKey(de);
+        robj *ele = dictGetEntryKey(de);
 
-            addReplyBulkLen(c,ele);
-            addReply(c,ele);
-            addReply(c,shared.crlf);
-            dictDelete(set->ptr,ele);
-            if (htNeedsResize(set->ptr)) dictResize(set->ptr);
-            server.dirty++;
-        }
+        addReplyBulk(c,ele);
+        dictDelete(set->ptr,ele);
+        if (htNeedsResize(set->ptr)) dictResize(set->ptr);
+        server.dirty++;
     }
 }
 
 static void srandmemberCommand(redisClient *c) {
     robj *set;
     dictEntry *de;
 
-    set = lookupKeyRead(c->db,c->argv[1]);
-    if (set == NULL) {
+    if ((set = lookupKeyReadOrReply(c,c->argv[1],shared.nullbulk)) == NULL ||
+        checkType(c,set,REDIS_SET)) return;
+
+    de = dictGetRandomKey(set->ptr);
+    if (de == NULL) {
         addReply(c,shared.nullbulk);
     } else {
-        if (set->type != REDIS_SET) {
-            addReply(c,shared.wrongtypeerr);
-            return;
-        }
-        de = dictGetRandomKey(set->ptr);
-        if (de == NULL) {
-            addReply(c,shared.nullbulk);
-        } else {
-            robj *ele = dictGetEntryKey(de);
+        robj *ele = dictGetEntryKey(de);
 
-            addReplyBulkLen(c,ele);
-            addReply(c,ele);
-            addReply(c,shared.crlf);
-        }
+        addReplyBulk(c,ele);
     }
 }
 
@@ -4840,9 +4742,7 @@ static void sinterGenericCommand(redisClient *c, robj **setskeys, unsigned long
             continue; /* at least one set does not contain the member */
         ele = dictGetEntryKey(de);
         if (!dstkey) {
-            addReplyBulkLen(c,ele);
-            addReply(c,ele);
-            addReply(c,shared.crlf);
+            addReplyBulk(c,ele);
             cardinality++;
         } else {
             dictAdd(dstset->ptr,ele,NULL);
@@ -4947,9 +4847,7 @@ static void sunionDiffGenericCommand(redisClient *c, robj **setskeys, int setsnu
             robj *ele;
 
             ele = dictGetEntryKey(de);
-            addReplyBulkLen(c,ele);
-            addReply(c,ele);
-            addReply(c,shared.crlf);
+            addReplyBulk(c,ele);
         }
         dictReleaseIterator(di);
     } else {
@@ -5284,11 +5182,11 @@ zskiplistNode* zslGetElementByRank(zskiplist *zsl, unsigned long rank) {
 
     x = zsl->header;
     for (i = zsl->level-1; i >= 0; i--) {
-        while (x->forward[i] && (traversed + (i > 0 ? x->span[i-1] : 1)) <= rank) {
+        while (x->forward[i] && (traversed + (i>0 ? x->span[i-1] : 1)) <= rank)
+        {
             traversed += i > 0 ? x->span[i-1] : 1;
             x = x->forward[i];
         }
-
         if (traversed == rank) {
             return x;
         }
@@ -5396,101 +5294,80 @@ static void zincrbyCommand(redisClient *c) {
 static void zremCommand(redisClient *c) {
     robj *zsetobj;
     zset *zs;
+    dictEntry *de;
+    double *oldscore;
+    int deleted;
 
-    zsetobj = lookupKeyWrite(c->db,c->argv[1]);
-    if (zsetobj == NULL) {
-        addReply(c,shared.czero);
-    } else {
-        dictEntry *de;
-        double *oldscore;
-        int deleted;
-
-        if (zsetobj->type != REDIS_ZSET) {
-            addReply(c,shared.wrongtypeerr);
-            return;
-        }
-        zs = zsetobj->ptr;
-        de = dictFind(zs->dict,c->argv[2]);
-        if (de == NULL) {
-            addReply(c,shared.czero);
-            return;
-        }
-        /* Delete from the skiplist */
-        oldscore = dictGetEntryVal(de);
-        deleted = zslDelete(zs->zsl,*oldscore,c->argv[2]);
-        redisAssert(deleted != 0);
+    if ((zsetobj = lookupKeyWriteOrReply(c,c->argv[1],shared.czero)) == NULL ||
+        checkType(c,zsetobj,REDIS_ZSET)) return;
 
-        /* Delete from the hash table */
-        dictDelete(zs->dict,c->argv[2]);
-        if (htNeedsResize(zs->dict)) dictResize(zs->dict);
-        server.dirty++;
-        addReply(c,shared.cone);
+    zs = zsetobj->ptr;
+    de = dictFind(zs->dict,c->argv[2]);
+    if (de == NULL) {
+        addReply(c,shared.czero);
+        return;
     }
+    /* Delete from the skiplist */
+    oldscore = dictGetEntryVal(de);
+    deleted = zslDelete(zs->zsl,*oldscore,c->argv[2]);
+    redisAssert(deleted != 0);
+
+    /* Delete from the hash table */
+    dictDelete(zs->dict,c->argv[2]);
+    if (htNeedsResize(zs->dict)) dictResize(zs->dict);
+    server.dirty++;
+    addReply(c,shared.cone);
 }
 
 static void zremrangebyscoreCommand(redisClient *c) {
     double min = strtod(c->argv[2]->ptr,NULL);
     double max = strtod(c->argv[3]->ptr,NULL);
+    long deleted;
     robj *zsetobj;
     zset *zs;
 
-    zsetobj = lookupKeyWrite(c->db,c->argv[1]);
-    if (zsetobj == NULL) {
-        addReply(c,shared.czero);
-    } else {
-        long deleted;
+    if ((zsetobj = lookupKeyWriteOrReply(c,c->argv[1],shared.czero)) == NULL ||
+        checkType(c,zsetobj,REDIS_ZSET)) return;
 
-        if (zsetobj->type != REDIS_ZSET) {
-            addReply(c,shared.wrongtypeerr);
-            return;
-        }
-        zs = zsetobj->ptr;
-        deleted = zslDeleteRangeByScore(zs->zsl,min,max,zs->dict);
-        if (htNeedsResize(zs->dict)) dictResize(zs->dict);
-        server.dirty += deleted;
-        addReplySds(c,sdscatprintf(sdsempty(),":%lu\r\n",deleted));
-    }
+    zs = zsetobj->ptr;
+    deleted = zslDeleteRangeByScore(zs->zsl,min,max,zs->dict);
+    if (htNeedsResize(zs->dict)) dictResize(zs->dict);
+    server.dirty += deleted;
+    addReplyLong(c,deleted);
 }
 
 static void zremrangebyrankCommand(redisClient *c) {
     int start = atoi(c->argv[2]->ptr);
     int end = atoi(c->argv[3]->ptr);
+    int llen;
+    long deleted;
     robj *zsetobj;
     zset *zs;
 
-    zsetobj = lookupKeyWrite(c->db,c->argv[1]);
-    if (zsetobj == NULL) {
-        addReply(c,shared.czero);
-    } else {
-        if (zsetobj->type != REDIS_ZSET) {
-            addReply(c,shared.wrongtypeerr);
-            return;
-        }
-
-        zs = zsetobj->ptr;
-        int llen = zs->zsl->length;
-        long deleted;
-
-        /* convert negative indexes */
-        if (start < 0) start = llen+start;
-        if (end < 0) end = llen+end;
-        if (start < 0) start = 0;
-        if (end < 0) end = 0;
+    if ((zsetobj = lookupKeyWriteOrReply(c,c->argv[1],shared.czero)) == NULL ||
+        checkType(c,zsetobj,REDIS_ZSET)) return;
+    zs = zsetobj->ptr;
+    llen = zs->zsl->length;
 
-        /* indexes sanity checks */
-        if (start > end || start >= llen) {
-            addReply(c,shared.czero);
-            return;
-        }
-        if (end >= llen) end = llen-1;
+    /* convert negative indexes */
+    if (start < 0) start = llen+start;
+    if (end < 0) end = llen+end;
+    if (start < 0) start = 0;
+    if (end < 0) end = 0;
 
-        /* increment start and end because zsl*Rank functions
-         * use 1-based rank */
-        deleted = zslDeleteRangeByRank(zs->zsl,start+1,end+1,zs->dict);
-        if (htNeedsResize(zs->dict)) dictResize(zs->dict);
-        server.dirty += deleted;
-        addReplyLong(c, deleted);
+    /* indexes sanity checks */
+    if (start > end || start >= llen) {
+        addReply(c,shared.czero);
+        return;
     }
+    if (end >= llen) end = llen-1;
+
+    /* increment start and end because zsl*Rank functions
+     * use 1-based rank */
+    deleted = zslDeleteRangeByRank(zs->zsl,start+1,end+1,zs->dict);
+    if (htNeedsResize(zs->dict)) dictResize(zs->dict);
+    server.dirty += deleted;
+    addReplyLong(c, deleted);
 }
 
 typedef struct {
@@ -5663,6 +5540,12 @@ static void zrangeGenericCommand(redisClient *c, int reverse) {
     int start = atoi(c->argv[2]->ptr);
     int end = atoi(c->argv[3]->ptr);
     int withscores = 0;
+    int llen;
+    int rangelen, j;
+    zset *zsetobj;
+    zskiplist *zsl;
+    zskiplistNode *ln;
+    robj *ele;
 
     if (c->argc == 5 && !strcasecmp(c->argv[4]->ptr,"withscores")) {
         withscores = 1;
@@ -5671,57 +5554,45 @@ static void zrangeGenericCommand(redisClient *c, int reverse) {
         return;
     }
 
-    o = lookupKeyRead(c->db,c->argv[1]);
-    if (o == NULL) {
-        addReply(c,shared.nullmultibulk);
-    } else {
-        if (o->type != REDIS_ZSET) {
-            addReply(c,shared.wrongtypeerr);
-        } else {
-            zset *zsetobj = o->ptr;
-            zskiplist *zsl = zsetobj->zsl;
-            zskiplistNode *ln;
+    if ((o = lookupKeyReadOrReply(c,c->argv[1],shared.nullmultibulk)) == NULL ||
+        checkType(c,o,REDIS_ZSET)) return;
+    zsetobj = o->ptr;
+    zsl = zsetobj->zsl;
+    llen = zsl->length;
 
-            int llen = zsl->length;
-            int rangelen, j;
-            robj *ele;
+    /* convert negative indexes */
+    if (start < 0) start = llen+start;
+    if (end < 0) end = llen+end;
+    if (start < 0) start = 0;
+    if (end < 0) end = 0;
 
-            /* convert negative indexes */
-            if (start < 0) start = llen+start;
-            if (end < 0) end = llen+end;
-            if (start < 0) start = 0;
-            if (end < 0) end = 0;
-
-            /* indexes sanity checks */
-            if (start > end || start >= llen) {
-                /* Out of range start or start > end result in empty list */
-                addReply(c,shared.emptymultibulk);
-                return;
-            }
-            if (end >= llen) end = llen-1;
-            rangelen = (end-start)+1;
+    /* indexes sanity checks */
+    if (start > end || start >= llen) {
+        /* Out of range start or start > end result in empty list */
+        addReply(c,shared.emptymultibulk);
+        return;
+    }
+    if (end >= llen) end = llen-1;
+    rangelen = (end-start)+1;
 
-            /* check if starting point is trivial, before searching
-             * the element in log(N) time */
-            if (reverse) {
-                ln = start == 0 ? zsl->tail : zslGetElementByRank(zsl, llen-start);
-            } else {
-                ln = start == 0 ? zsl->header->forward[0] : zslGetElementByRank(zsl, start+1);
-            }
+    /* check if starting point is trivial, before searching
+     * the element in log(N) time */
+    if (reverse) {
+        ln = start == 0 ? zsl->tail : zslGetElementByRank(zsl, llen-start);
+    } else {
+        ln = start == 0 ?
+            zsl->header->forward[0] : zslGetElementByRank(zsl, start+1);
+    }
 
-            /* Return the result in form of a multi-bulk reply */
-            addReplySds(c,sdscatprintf(sdsempty(),"*%d\r\n",
-                withscores ? (rangelen*2) : rangelen));
-            for (j = 0; j < rangelen; j++) {
-                ele = ln->obj;
-                addReplyBulkLen(c,ele);
-                addReply(c,ele);
-                addReply(c,shared.crlf);
-                if (withscores)
-                    addReplyDouble(c,ln->score);
-                ln = reverse ? ln->backward : ln->forward[0];
-            }
-        }
+    /* Return the result in form of a multi-bulk reply */
+    addReplySds(c,sdscatprintf(sdsempty(),"*%d\r\n",
+        withscores ? (rangelen*2) : rangelen));
+    for (j = 0; j < rangelen; j++) {
+        ele = ln->obj;
+        addReplyBulk(c,ele);
+        if (withscores)
+            addReplyDouble(c,ln->score);
+        ln = reverse ? ln->backward : ln->forward[0];
     }
 }
 
@@ -5831,9 +5702,7 @@ static void genericZrangebyscoreCommand(redisClient *c, int justcount) {
                 if (limit == 0) break;
                 if (!justcount) {
                     ele = ln->obj;
-                    addReplyBulkLen(c,ele);
-                    addReply(c,ele);
-                    addReply(c,shared.crlf);
+                    addReplyBulk(c,ele);
                     if (withscores)
                         addReplyDouble(c,ln->score);
                 }
@@ -5862,80 +5731,62 @@ static void zcountCommand(redisClient *c) {
 static void zcardCommand(redisClient *c) {
     robj *o;
     zset *zs;
-    
-    o = lookupKeyRead(c->db,c->argv[1]);
-    if (o == NULL) {
-        addReply(c,shared.czero);
-        return;
-    } else {
-        if (o->type != REDIS_ZSET) {
-            addReply(c,shared.wrongtypeerr);
-        } else {
-            zs = o->ptr;
-            addReplySds(c,sdscatprintf(sdsempty(),":%lu\r\n",zs->zsl->length));
-        }
-    }
+
+    if ((o = lookupKeyReadOrReply(c,c->argv[1],shared.czero)) == NULL ||
+        checkType(c,o,REDIS_ZSET)) return;
+
+    zs = o->ptr;
+    addReplyUlong(c,zs->zsl->length);
 }
 
 static void zscoreCommand(redisClient *c) {
     robj *o;
     zset *zs;
-    
-    o = lookupKeyRead(c->db,c->argv[1]);
-    if (o == NULL) {
+    dictEntry *de;
+
+    if ((o = lookupKeyReadOrReply(c,c->argv[1],shared.nullbulk)) == NULL ||
+        checkType(c,o,REDIS_ZSET)) return;
+
+    zs = o->ptr;
+    de = dictFind(zs->dict,c->argv[2]);
+    if (!de) {
         addReply(c,shared.nullbulk);
-        return;
     } else {
-        if (o->type != REDIS_ZSET) {
-            addReply(c,shared.wrongtypeerr);
-        } else {
-            dictEntry *de;
-
-            zs = o->ptr;
-            de = dictFind(zs->dict,c->argv[2]);
-            if (!de) {
-                addReply(c,shared.nullbulk);
-            } else {
-                double *score = dictGetEntryVal(de);
+        double *score = dictGetEntryVal(de);
 
-                addReplyDouble(c,*score);
-            }
-        }
+        addReplyDouble(c,*score);
     }
 }
 
 static void zrankGenericCommand(redisClient *c, int reverse) {
     robj *o;
-    o = lookupKeyRead(c->db,c->argv[1]);
-    if (o == NULL) {
+    zset *zs;
+    zskiplist *zsl;
+    dictEntry *de;
+    unsigned long rank;
+    double *score;
+
+    if ((o = lookupKeyReadOrReply(c,c->argv[1],shared.nullbulk)) == NULL ||
+        checkType(c,o,REDIS_ZSET)) return;
+
+    zs = o->ptr;
+    zsl = zs->zsl;
+    de = dictFind(zs->dict,c->argv[2]);
+    if (!de) {
         addReply(c,shared.nullbulk);
         return;
     }
-    if (o->type != REDIS_ZSET) {
-        addReply(c,shared.wrongtypeerr);
-    } else {
-        zset *zs = o->ptr;
-        zskiplist *zsl = zs->zsl;
-        dictEntry *de;
-        unsigned long rank;
 
-        de = dictFind(zs->dict,c->argv[2]);
-        if (!de) {
-            addReply(c,shared.nullbulk);
-            return;
-        }
-
-        double *score = dictGetEntryVal(de);
-        rank = zslGetRank(zsl, *score, c->argv[2]);
-        if (rank) {
-            if (reverse) {
-                addReplyLong(c, zsl->length - rank);
-            } else {
-                addReplyLong(c, rank-1);
-            }
+    score = dictGetEntryVal(de);
+    rank = zslGetRank(zsl, *score, c->argv[2]);
+    if (rank) {
+        if (reverse) {
+            addReplyLong(c, zsl->length - rank);
         } else {
-            addReply(c,shared.nullbulk);
+            addReplyLong(c, rank-1);
         }
+    } else {
+        addReply(c,shared.nullbulk);
     }
 }
 
@@ -6006,78 +5857,61 @@ static void hsetCommand(redisClient *c) {
 }
 
 static void hgetCommand(redisClient *c) {
-    robj *o = lookupKeyRead(c->db,c->argv[1]);
+    robj *o;
 
-    if (o == NULL) {
-        addReply(c,shared.nullbulk);
-        return;
-    } else {
-        if (o->type != REDIS_HASH) {
-            addReply(c,shared.wrongtypeerr);
+    if ((o = lookupKeyReadOrReply(c,c->argv[1],shared.nullbulk)) == NULL ||
+        checkType(c,o,REDIS_HASH)) return;
+
+    if (o->encoding == REDIS_ENCODING_ZIPMAP) {
+        unsigned char *zm = o->ptr;
+        unsigned char *val;
+        unsigned int vlen;
+
+        if (zipmapGet(zm,c->argv[2]->ptr,sdslen(c->argv[2]->ptr), &val,&vlen)) {
+            addReplySds(c,sdscatprintf(sdsempty(),"$%u\r\n", vlen));
+            addReplySds(c,sdsnewlen(val,vlen));
+            addReply(c,shared.crlf);
+            return;
+        } else {
+            addReply(c,shared.nullbulk);
             return;
         }
+    } else {
+        struct dictEntry *de;
 
-        if (o->encoding == REDIS_ENCODING_ZIPMAP) {
-            unsigned char *zm = o->ptr;
-            unsigned char *val;
-            unsigned int vlen;
-
-            if (zipmapGet(zm,c->argv[2]->ptr,sdslen(c->argv[2]->ptr), &val,&vlen)) {
-                addReplySds(c,sdscatprintf(sdsempty(),"$%u\r\n", vlen));
-                addReplySds(c,sdsnewlen(val,vlen));
-                addReply(c,shared.crlf);
-                return;
-            } else {
-                addReply(c,shared.nullbulk);
-                return;
-            }
+        de = dictFind(o->ptr,c->argv[2]);
+        if (de == NULL) {
+            addReply(c,shared.nullbulk);
         } else {
-            struct dictEntry *de;
+            robj *e = dictGetEntryVal(de);
 
-            de = dictFind(o->ptr,c->argv[2]);
-            if (de == NULL) {
-                addReply(c,shared.nullbulk);
-            } else {
-                robj *e = dictGetEntryVal(de);
-
-                addReplyBulkLen(c,e);
-                addReply(c,e);
-                addReply(c,shared.crlf);
-            }
+            addReplyBulk(c,e);
         }
     }
 }
 
 static void hdelCommand(redisClient *c) {
-    robj *o = lookupKeyWrite(c->db,c->argv[1]);
-
-    if (o == NULL) {
-        addReply(c,shared.czero);
-        return;
-    } else {
-        int deleted = 0;
+    robj *o;
+    int deleted = 0;
 
-        if (o->type != REDIS_HASH) {
-            addReply(c,shared.wrongtypeerr);
-            return;
-        }
+    if ((o = lookupKeyWriteOrReply(c,c->argv[1],shared.czero)) == NULL ||
+        checkType(c,o,REDIS_HASH)) return;
 
-        if (o->encoding == REDIS_ENCODING_ZIPMAP) {
-            o->ptr = zipmapDel((unsigned char*) o->ptr,
-                (unsigned char*) c->argv[2]->ptr,
-                sdslen(c->argv[2]->ptr), &deleted);
-        } else {
-            deleted = dictDelete((dict*)o->ptr,c->argv[2]) == DICT_OK;
-        }
-        addReply(c,deleted ? shared.cone : shared.czero);
+    if (o->encoding == REDIS_ENCODING_ZIPMAP) {
+        o->ptr = zipmapDel((unsigned char*) o->ptr,
+            (unsigned char*) c->argv[2]->ptr,
+            sdslen(c->argv[2]->ptr), &deleted);
+    } else {
+        deleted = dictDelete((dict*)o->ptr,c->argv[2]) == DICT_OK;
     }
+    addReply(c,deleted ? shared.cone : shared.czero);
 }
 
 static void hlenCommand(redisClient *c) {
     robj *o;
     unsigned long len;
 
-    if ((o = lookupKeyWriteOrReply(c,c->argv[1],shared.czero)) == NULL ||
+    if ((o = lookupKeyReadOrReply(c,c->argv[1],shared.czero)) == NULL ||
         checkType(c,o,REDIS_HASH)) return;
 
     len = (o->encoding == REDIS_ENCODING_ZIPMAP) ?
@@ -6410,11 +6244,7 @@ static void sortCommand(redisClient *c) {
             listNode *ln;
             listIter li;
 
-            if (!getop) {
-                addReplyBulkLen(c,vector[j].obj);
-                addReply(c,vector[j].obj);
-                addReply(c,shared.crlf);
-            }
+            if (!getop) addReplyBulk(c,vector[j].obj);
             listRewind(operations,&li);
             while((ln = listNext(&li))) {
                 redisSortOperation *sop = ln->value;
@@ -6425,9 +6255,7 @@ static void sortCommand(redisClient *c) {
                     if (!val || val->type != REDIS_STRING) {
                         addReply(c,shared.nullbulk);
                     } else {
-                        addReplyBulkLen(c,val);
-                        addReply(c,val);
-                        addReply(c,shared.crlf);
+                        addReplyBulk(c,val);
                     }
                 } else {
                     redisAssert(sop->type == REDIS_SORT_GET); /* always fails */
@@ -6945,12 +6773,8 @@ static int handleClientsWaitingListPush(redisClient *c, robj *key, robj *ele) {
     receiver = ln->value;
 
     addReplySds(receiver,sdsnew("*2\r\n"));
-    addReplyBulkLen(receiver,key);
-    addReply(receiver,key);
-    addReply(receiver,shared.crlf);
-    addReplyBulkLen(receiver,ele);
-    addReply(receiver,ele);
-    addReply(receiver,shared.crlf);
+    addReplyBulk(receiver,key);
+    addReplyBulk(receiver,ele);
     unblockClientWaitingData(receiver);
     return 1;
 }
@@ -6989,9 +6813,7 @@ static void blockingPopGenericCommand(redisClient *c, int where) {
                      * for us. If this souds like an hack to you it's just
                      * because it is... */
                     addReplySds(c,sdsnew("*2\r\n"));
-                    addReplyBulkLen(c,argv[1]);
-                    addReply(c,argv[1]);
-                    addReply(c,shared.crlf);
+                    addReplyBulk(c,argv[1]);
                     popGenericCommand(c,where);
 
                     /* Fix the client structure with the original stuff */