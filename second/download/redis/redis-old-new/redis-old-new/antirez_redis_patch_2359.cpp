@@ -214,10 +214,10 @@ typedef struct _redisSortOperation {
 } redisSortOperation;
 
 struct sharedObjectsStruct {
-    robj *crlf, *ok, *err, *zerobulk, *nil, *zero, *one, *pong, *space,
-    *minus1, *minus2, *minus3, *minus4,
-    *wrongtypeerr, *nokeyerr, *wrongtypeerrbulk, *nokeyerrbulk,
-    *syntaxerr, *syntaxerrbulk,
+    robj *crlf, *ok, *err, *emptybulk, *czero, *cone, *pong, *space,
+    *colon, *minus1, *nullbulk, *nullmultibulk,
+    *emptymultibulk, *wrongtypeerr, *nokeyerr, *syntaxerr, *sameobjecterr,
+    *outofrangeerr, *plus,
     *select0, *select1, *select2, *select3, *select4,
     *select5, *select6, *select7, *select8, *select9;
 } shared;
@@ -660,29 +660,28 @@ static void createSharedObjects(void) {
     shared.crlf = createObject(REDIS_STRING,sdsnew("\r\n"));
     shared.ok = createObject(REDIS_STRING,sdsnew("+OK\r\n"));
     shared.err = createObject(REDIS_STRING,sdsnew("-ERR\r\n"));
-    shared.zerobulk = createObject(REDIS_STRING,sdsnew("0\r\n\r\n"));
-    shared.nil = createObject(REDIS_STRING,sdsnew("nil\r\n"));
-    shared.zero = createObject(REDIS_STRING,sdsnew("0\r\n"));
-    shared.one = createObject(REDIS_STRING,sdsnew("1\r\n"));
+    shared.emptybulk = createObject(REDIS_STRING,sdsnew("$0\r\n\r\n"));
+    shared.czero = createObject(REDIS_STRING,sdsnew(":0\r\n"));
+    shared.cone = createObject(REDIS_STRING,sdsnew(":1\r\n"));
+    shared.nullbulk = createObject(REDIS_STRING,sdsnew("$-1\r\n"));
+    shared.nullmultibulk = createObject(REDIS_STRING,sdsnew("*-1\r\n"));
+    shared.emptymultibulk = createObject(REDIS_STRING,sdsnew("*0\r\n"));
     /* no such key */
     shared.minus1 = createObject(REDIS_STRING,sdsnew("-1\r\n"));
-    /* operation against key holding a value of the wrong type */
-    shared.minus2 = createObject(REDIS_STRING,sdsnew("-2\r\n"));
-    /* src and dest objects are the same */
-    shared.minus3 = createObject(REDIS_STRING,sdsnew("-3\r\n"));
-    /* out of range argument */
-    shared.minus4 = createObject(REDIS_STRING,sdsnew("-4\r\n"));
     shared.pong = createObject(REDIS_STRING,sdsnew("+PONG\r\n"));
     shared.wrongtypeerr = createObject(REDIS_STRING,sdsnew(
         "-ERR Operation against a key holding the wrong kind of value\r\n"));
-    shared.wrongtypeerrbulk = createObject(REDIS_STRING,sdscatprintf(sdsempty(),"%d\r\n%s",-sdslen(shared.wrongtypeerr->ptr)+2,shared.wrongtypeerr->ptr));
     shared.nokeyerr = createObject(REDIS_STRING,sdsnew(
         "-ERR no such key\r\n"));
-    shared.nokeyerrbulk = createObject(REDIS_STRING,sdscatprintf(sdsempty(),"%d\r\n%s",-sdslen(shared.nokeyerr->ptr)+2,shared.nokeyerr->ptr));
     shared.syntaxerr = createObject(REDIS_STRING,sdsnew(
         "-ERR syntax error\r\n"));
-    shared.syntaxerrbulk = createObject(REDIS_STRING,sdscatprintf(sdsempty(),"%d\r\n%s",-sdslen(shared.syntaxerr->ptr)+2,shared.syntaxerr->ptr));
+    shared.sameobjecterr = createObject(REDIS_STRING,sdsnew(
+        "-ERR source and destination objects are the same\r\n"));
+    shared.outofrangeerr = createObject(REDIS_STRING,sdsnew(
+        "-ERR index out of range\r\n"));
     shared.space = createObject(REDIS_STRING,sdsnew(" "));
+    shared.colon = createObject(REDIS_STRING,sdsnew(":"));
+    shared.plus = createObject(REDIS_STRING,sdsnew("+"));
     shared.select0 = createStringObject("select 0\r\n",10);
     shared.select1 = createStringObject("select 1\r\n",10);
     shared.select2 = createStringObject("select 2\r\n",10);
@@ -1654,7 +1653,7 @@ static void pingCommand(redisClient *c) {
 }
 
 static void echoCommand(redisClient *c) {
-    addReplySds(c,sdscatprintf(sdsempty(),"%d\r\n",
+    addReplySds(c,sdscatprintf(sdsempty(),"$%d\r\n",
         (int)sdslen(c->argv[1]->ptr)));
     addReply(c,c->argv[1]);
     addReply(c,shared.crlf);
@@ -1671,15 +1670,15 @@ static void setGenericCommand(redisClient *c, int nx) {
             dictReplace(c->dict,c->argv[1],c->argv[2]);
             incrRefCount(c->argv[2]);
         } else {
-            addReply(c,shared.zero);
+            addReply(c,shared.czero);
             return;
         }
     } else {
         incrRefCount(c->argv[1]);
         incrRefCount(c->argv[2]);
     }
     server.dirty++;
-    addReply(c, nx ? shared.one : shared.ok);
+    addReply(c, nx ? shared.cone : shared.ok);
 }
 
 static void setCommand(redisClient *c) {
@@ -1695,14 +1694,14 @@ static void getCommand(redisClient *c) {
     
     de = dictFind(c->dict,c->argv[1]);
     if (de == NULL) {
-        addReply(c,shared.nil);
+        addReply(c,shared.nullbulk);
     } else {
         robj *o = dictGetEntryVal(de);
         
         if (o->type != REDIS_STRING) {
-            addReply(c,shared.wrongtypeerrbulk);
+            addReply(c,shared.wrongtypeerr);
         } else {
-            addReplySds(c,sdscatprintf(sdsempty(),"%d\r\n",(int)sdslen(o->ptr)));
+            addReplySds(c,sdscatprintf(sdsempty(),"$%d\r\n",(int)sdslen(o->ptr)));
             addReply(c,o);
             addReply(c,shared.crlf);
         }
@@ -1713,18 +1712,18 @@ static void mgetCommand(redisClient *c) {
     dictEntry *de;
     int j;
   
-    addReplySds(c,sdscatprintf(sdsempty(),"%d\r\n",c->argc-1));
+    addReplySds(c,sdscatprintf(sdsempty(),"*%d\r\n",c->argc-1));
     for (j = 1; j < c->argc; j++) {
         de = dictFind(c->dict,c->argv[j]);
         if (de == NULL) {
-            addReply(c,shared.minus1);
+            addReply(c,shared.nullbulk);
         } else {
             robj *o = dictGetEntryVal(de);
             
             if (o->type != REDIS_STRING) {
-                addReply(c,shared.minus1);
+                addReply(c,shared.nullbulk);
             } else {
-                addReplySds(c,sdscatprintf(sdsempty(),"%d\r\n",(int)sdslen(o->ptr)));
+                addReplySds(c,sdscatprintf(sdsempty(),"$%d\r\n",(int)sdslen(o->ptr)));
                 addReply(c,o);
                 addReply(c,shared.crlf);
             }
@@ -1762,6 +1761,7 @@ static void incrDecrCommand(redisClient *c, int incr) {
         incrRefCount(c->argv[1]);
     }
     server.dirty++;
+    addReply(c,shared.colon);
     addReply(c,o);
     addReply(c,shared.crlf);
 }
@@ -1789,9 +1789,9 @@ static void decrbyCommand(redisClient *c) {
 static void delCommand(redisClient *c) {
     if (dictDelete(c->dict,c->argv[1]) == DICT_OK) {
         server.dirty++;
-        addReply(c,shared.one);
+        addReply(c,shared.cone);
     } else {
-        addReply(c,shared.zero);
+        addReply(c,shared.czero);
     }
 }
 
@@ -1800,9 +1800,9 @@ static void existsCommand(redisClient *c) {
     
     de = dictFind(c->dict,c->argv[1]);
     if (de == NULL)
-        addReply(c,shared.zero);
+        addReply(c,shared.czero);
     else
-        addReply(c,shared.one);
+        addReply(c,shared.cone);
 }
 
 static void selectCommand(redisClient *c) {
@@ -1822,6 +1822,7 @@ static void randomkeyCommand(redisClient *c) {
     if (de == NULL) {
         addReply(c,shared.crlf);
     } else {
+        addReply(c,shared.plus);
         addReply(c,dictGetEntryKey(de));
         addReply(c,shared.crlf);
     }
@@ -1852,18 +1853,18 @@ static void keysCommand(redisClient *c) {
         }
     }
     dictReleaseIterator(di);
-    lenobj->ptr = sdscatprintf(sdsempty(),"%lu\r\n",keyslen+(numkeys ? (numkeys-1) : 0));
+    lenobj->ptr = sdscatprintf(sdsempty(),"$%lu\r\n",keyslen+(numkeys ? (numkeys-1) : 0));
     addReply(c,shared.crlf);
 }
 
 static void dbsizeCommand(redisClient *c) {
     addReplySds(c,
-        sdscatprintf(sdsempty(),"%lu\r\n",dictGetHashTableUsed(c->dict)));
+        sdscatprintf(sdsempty(),":%lu\r\n",dictGetHashTableUsed(c->dict)));
 }
 
 static void lastsaveCommand(redisClient *c) {
     addReplySds(c,
-        sdscatprintf(sdsempty(),"%lu\r\n",server.lastsave));
+        sdscatprintf(sdsempty(),":%lu\r\n",server.lastsave));
 }
 
 static void typeCommand(redisClient *c) {
@@ -1872,14 +1873,14 @@ static void typeCommand(redisClient *c) {
     
     de = dictFind(c->dict,c->argv[1]);
     if (de == NULL) {
-        type = "none";
+        type = "+none";
     } else {
         robj *o = dictGetEntryVal(de);
         
         switch(o->type) {
-        case REDIS_STRING: type = "string"; break;
-        case REDIS_LIST: type = "list"; break;
-        case REDIS_SET: type = "set"; break;
+        case REDIS_STRING: type = "+string"; break;
+        case REDIS_LIST: type = "+list"; break;
+        case REDIS_SET: type = "+set"; break;
         default: type = "unknown"; break;
         }
     }
@@ -1927,27 +1928,21 @@ static void renameGenericCommand(redisClient *c, int nx) {
 
     /* To use the same key as src and dst is probably an error */
     if (sdscmp(c->argv[1]->ptr,c->argv[2]->ptr) == 0) {
-        if (nx)
-            addReply(c,shared.minus3);
-        else
-            addReplySds(c,sdsnew("-ERR src and dest key are the same\r\n"));
+        addReply(c,shared.sameobjecterr);
         return;
     }
 
     de = dictFind(c->dict,c->argv[1]);
     if (de == NULL) {
-        if (nx)
-            addReply(c,shared.minus1);
-        else
-            addReply(c,shared.nokeyerr);
+        addReply(c,shared.nokeyerr);
         return;
     }
     o = dictGetEntryVal(de);
     incrRefCount(o);
     if (dictAdd(c->dict,c->argv[2],o) == DICT_ERR) {
         if (nx) {
             decrRefCount(o);
-            addReply(c,shared.zero);
+            addReply(c,shared.czero);
             return;
         }
         dictReplace(c->dict,c->argv[2],o);
@@ -1956,7 +1951,7 @@ static void renameGenericCommand(redisClient *c, int nx) {
     }
     dictDelete(c->dict,c->argv[1]);
     server.dirty++;
-    addReply(c,nx ? shared.one : shared.ok);
+    addReply(c,nx ? shared.cone : shared.ok);
 }
 
 static void renameCommand(redisClient *c) {
@@ -1977,7 +1972,7 @@ static void moveCommand(redisClient *c) {
     src = c->dict;
     srcid = c->dictid;
     if (selectDb(c,atoi(c->argv[2]->ptr)) == REDIS_ERR) {
-        addReply(c,shared.minus4);
+        addReply(c,shared.outofrangeerr);
         return;
     }
     dst = c->dict;
@@ -1987,22 +1982,22 @@ static void moveCommand(redisClient *c) {
     /* If the user is moving using as target the same
      * DB as the source DB it is probably an error. */
     if (src == dst) {
-        addReply(c,shared.minus3);
+        addReply(c,shared.sameobjecterr);
         return;
     }
 
     /* Check if the element exists and get a reference */
     de = dictFind(c->dict,c->argv[1]);
     if (!de) {
-        addReply(c,shared.zero);
+        addReply(c,shared.czero);
         return;
     }
 
     /* Try to add the element to the target DB */
     key = dictGetEntryKey(de);
     o = dictGetEntryVal(de);
     if (dictAdd(dst,key,o) == DICT_ERR) {
-        addReply(c,shared.zero);
+        addReply(c,shared.czero);
         return;
     }
     incrRefCount(key);
@@ -2011,7 +2006,7 @@ static void moveCommand(redisClient *c) {
     /* OK! key moved, free the entry in the source DB */
     dictDelete(src,c->argv[1]);
     server.dirty++;
-    addReply(c,shared.one);
+    addReply(c,shared.cone);
 }
 
 /* =================================== Lists ================================ */
@@ -2064,15 +2059,15 @@ static void llenCommand(redisClient *c) {
     
     de = dictFind(c->dict,c->argv[1]);
     if (de == NULL) {
-        addReply(c,shared.zero);
+        addReply(c,shared.czero);
         return;
     } else {
         robj *o = dictGetEntryVal(de);
         if (o->type != REDIS_LIST) {
-            addReply(c,shared.minus2);
+            addReply(c,shared.wrongtypeerr);
         } else {
             l = o->ptr;
-            addReplySds(c,sdscatprintf(sdsempty(),"%d\r\n",listLength(l)));
+            addReplySds(c,sdscatprintf(sdsempty(),":%d\r\n",listLength(l)));
         }
     }
 }
@@ -2083,22 +2078,22 @@ static void lindexCommand(redisClient *c) {
     
     de = dictFind(c->dict,c->argv[1]);
     if (de == NULL) {
-        addReply(c,shared.nil);
+        addReply(c,shared.nullbulk);
     } else {
         robj *o = dictGetEntryVal(de);
         
         if (o->type != REDIS_LIST) {
-            addReply(c,shared.wrongtypeerrbulk);
+            addReply(c,shared.wrongtypeerr);
         } else {
             list *list = o->ptr;
             listNode *ln;
             
             ln = listIndex(list, index);
             if (ln == NULL) {
-                addReply(c,shared.nil);
+                addReply(c,shared.nullbulk);
             } else {
                 robj *ele = listNodeValue(ln);
-                addReplySds(c,sdscatprintf(sdsempty(),"%d\r\n",(int)sdslen(ele->ptr)));
+                addReplySds(c,sdscatprintf(sdsempty(),"$%d\r\n",(int)sdslen(ele->ptr)));
                 addReply(c,ele);
                 addReply(c,shared.crlf);
             }
@@ -2124,7 +2119,7 @@ static void lsetCommand(redisClient *c) {
             
             ln = listIndex(list, index);
             if (ln == NULL) {
-                addReplySds(c,sdsnew("-ERR index out of range\r\n"));
+                addReply(c,shared.outofrangeerr);
             } else {
                 robj *ele = listNodeValue(ln);
 
@@ -2143,12 +2138,12 @@ static void popGenericCommand(redisClient *c, int where) {
     
     de = dictFind(c->dict,c->argv[1]);
     if (de == NULL) {
-        addReply(c,shared.nil);
+        addReply(c,shared.nullbulk);
     } else {
         robj *o = dictGetEntryVal(de);
         
         if (o->type != REDIS_LIST) {
-            addReply(c,shared.wrongtypeerrbulk);
+            addReply(c,shared.wrongtypeerr);
         } else {
             list *list = o->ptr;
             listNode *ln;
@@ -2159,10 +2154,10 @@ static void popGenericCommand(redisClient *c, int where) {
                 ln = listLast(list);
 
             if (ln == NULL) {
-                addReply(c,shared.nil);
+                addReply(c,shared.nullbulk);
             } else {
                 robj *ele = listNodeValue(ln);
-                addReplySds(c,sdscatprintf(sdsempty(),"%d\r\n",(int)sdslen(ele->ptr)));
+                addReplySds(c,sdscatprintf(sdsempty(),"$%d\r\n",(int)sdslen(ele->ptr)));
                 addReply(c,ele);
                 addReply(c,shared.crlf);
                 listDelNode(list,ln);
@@ -2187,12 +2182,12 @@ static void lrangeCommand(redisClient *c) {
     
     de = dictFind(c->dict,c->argv[1]);
     if (de == NULL) {
-        addReply(c,shared.nil);
+        addReply(c,shared.nullmultibulk);
     } else {
         robj *o = dictGetEntryVal(de);
         
         if (o->type != REDIS_LIST) {
-            addReply(c,shared.wrongtypeerrbulk);
+            addReply(c,shared.wrongtypeerr);
         } else {
             list *list = o->ptr;
             listNode *ln;
@@ -2209,18 +2204,18 @@ static void lrangeCommand(redisClient *c) {
             /* indexes sanity checks */
             if (start > end || start >= llen) {
                 /* Out of range start or start > end result in empty list */
-                addReply(c,shared.zero);
+                addReply(c,shared.emptymultibulk);
                 return;
             }
             if (end >= llen) end = llen-1;
             rangelen = (end-start)+1;
 
             /* Return the result in form of a multi-bulk reply */
             ln = listIndex(list, start);
-            addReplySds(c,sdscatprintf(sdsempty(),"%d\r\n",rangelen));
+            addReplySds(c,sdscatprintf(sdsempty(),"*%d\r\n",rangelen));
             for (j = 0; j < rangelen; j++) {
                 ele = listNodeValue(ln);
-                addReplySds(c,sdscatprintf(sdsempty(),"%d\r\n",(int)sdslen(ele->ptr)));
+                addReplySds(c,sdscatprintf(sdsempty(),"$%d\r\n",(int)sdslen(ele->ptr)));
                 addReply(c,ele);
                 addReply(c,shared.crlf);
                 ln = ln->next;
@@ -2290,7 +2285,7 @@ static void lremCommand(redisClient *c) {
         robj *o = dictGetEntryVal(de);
         
         if (o->type != REDIS_LIST) {
-            addReply(c,shared.minus2);
+            addReply(c,shared.wrongtypeerr);
         } else {
             list *list = o->ptr;
             listNode *ln, *next;
@@ -2314,7 +2309,7 @@ static void lremCommand(redisClient *c) {
                 }
                 ln = next;
             }
-            addReplySds(c,sdscatprintf(sdsempty(),"%d\r\n",removed));
+            addReplySds(c,sdscatprintf(sdsempty(),":%d\r\n",removed));
         }
     }
 }
@@ -2333,16 +2328,16 @@ static void saddCommand(redisClient *c) {
     } else {
         set = dictGetEntryVal(de);
         if (set->type != REDIS_SET) {
-            addReply(c,shared.minus2);
+            addReply(c,shared.wrongtypeerr);
             return;
         }
     }
     if (dictAdd(set->ptr,c->argv[2],NULL) == DICT_OK) {
         incrRefCount(c->argv[2]);
         server.dirty++;
-        addReply(c,shared.one);
+        addReply(c,shared.cone);
     } else {
-        addReply(c,shared.zero);
+        addReply(c,shared.czero);
     }
 }
 
@@ -2351,20 +2346,20 @@ static void sremCommand(redisClient *c) {
 
     de = dictFind(c->dict,c->argv[1]);
     if (de == NULL) {
-        addReply(c,shared.zero);
+        addReply(c,shared.czero);
     } else {
         robj *set;
 
         set = dictGetEntryVal(de);
         if (set->type != REDIS_SET) {
-            addReply(c,shared.minus2);
+            addReply(c,shared.wrongtypeerr);
             return;
         }
         if (dictDelete(set->ptr,c->argv[2]) == DICT_OK) {
             server.dirty++;
-            addReply(c,shared.one);
+            addReply(c,shared.cone);
         } else {
-            addReply(c,shared.zero);
+            addReply(c,shared.czero);
         }
     }
 }
@@ -2374,19 +2369,19 @@ static void sismemberCommand(redisClient *c) {
 
     de = dictFind(c->dict,c->argv[1]);
     if (de == NULL) {
-        addReply(c,shared.zero);
+        addReply(c,shared.czero);
     } else {
         robj *set;
 
         set = dictGetEntryVal(de);
         if (set->type != REDIS_SET) {
-            addReply(c,shared.minus2);
+            addReply(c,shared.wrongtypeerr);
             return;
         }
         if (dictFind(set->ptr,c->argv[2]))
-            addReply(c,shared.one);
+            addReply(c,shared.cone);
         else
-            addReply(c,shared.zero);
+            addReply(c,shared.czero);
     }
 }
 
@@ -2396,15 +2391,15 @@ static void scardCommand(redisClient *c) {
     
     de = dictFind(c->dict,c->argv[1]);
     if (de == NULL) {
-        addReply(c,shared.zero);
+        addReply(c,shared.czero);
         return;
     } else {
         robj *o = dictGetEntryVal(de);
         if (o->type != REDIS_SET) {
-            addReply(c,shared.minus2);
+            addReply(c,shared.wrongtypeerr);
         } else {
             s = o->ptr;
-            addReplySds(c,sdscatprintf(sdsempty(),"%d\r\n",
+            addReplySds(c,sdscatprintf(sdsempty(),":%d\r\n",
                 dictGetHashTableUsed(s)));
         }
     }
@@ -2431,13 +2426,13 @@ static void sinterGenericCommand(redisClient *c, robj **setskeys, int setsnum, r
         de = dictFind(c->dict,setskeys[j]);
         if (!de) {
             zfree(dv);
-            addReply(c,dstkey ? shared.nokeyerr : shared.nil);
+            addReply(c,shared.nokeyerr);
             return;
         }
         setobj = dictGetEntryVal(de);
         if (setobj->type != REDIS_SET) {
             zfree(dv);
-            addReply(c,dstkey ? shared.wrongtypeerr : shared.wrongtypeerrbulk);
+            addReply(c,shared.wrongtypeerr);
             return;
         }
         dv[j] = setobj->ptr;
@@ -2479,7 +2474,7 @@ static void sinterGenericCommand(redisClient *c, robj **setskeys, int setsnum, r
             continue; /* at least one set does not contain the member */
         ele = dictGetEntryKey(de);
         if (!dstkey) {
-            addReplySds(c,sdscatprintf(sdsempty(),"%d\r\n",sdslen(ele->ptr)));
+            addReplySds(c,sdscatprintf(sdsempty(),"$%d\r\n",sdslen(ele->ptr)));
             addReply(c,ele);
             addReply(c,shared.crlf);
             cardinality++;
@@ -2491,7 +2486,7 @@ static void sinterGenericCommand(redisClient *c, robj **setskeys, int setsnum, r
     dictReleaseIterator(di);
 
     if (!dstkey)
-        lenobj->ptr = sdscatprintf(sdsempty(),"%d\r\n",cardinality);
+        lenobj->ptr = sdscatprintf(sdsempty(),"*%d\r\n",cardinality);
     else
         addReply(c,shared.ok);
     zfree(dv);
@@ -2621,12 +2616,12 @@ static void sortCommand(redisClient *c) {
     /* Lookup the key to sort. It must be of the right types */
     de = dictFind(c->dict,c->argv[1]);
     if (de == NULL) {
-        addReply(c,shared.nokeyerrbulk);
+        addReply(c,shared.nokeyerr);
         return;
     }
     sortval = dictGetEntryVal(de);
     if (sortval->type != REDIS_SET && sortval->type != REDIS_LIST) {
-        addReply(c,shared.wrongtypeerrbulk);
+        addReply(c,shared.wrongtypeerr);
         return;
     }
 
@@ -2680,7 +2675,7 @@ static void sortCommand(redisClient *c) {
         } else {
             decrRefCount(sortval);
             listRelease(operations);
-            addReply(c,shared.syntaxerrbulk);
+            addReply(c,shared.syntaxerr);
             return;
         }
         j++;
@@ -2761,11 +2756,11 @@ static void sortCommand(redisClient *c) {
     /* Send command output to the output buffer, performing the specified
      * GET/DEL/INCR/DECR operations if any. */
     outputlen = getop ? getop*(end-start+1) : end-start+1;
-    addReplySds(c,sdscatprintf(sdsempty(),"%d\r\n",outputlen));
+    addReplySds(c,sdscatprintf(sdsempty(),"*%d\r\n",outputlen));
     for (j = start; j <= end; j++) {
         listNode *ln = operations->head;
         if (!getop) {
-            addReplySds(c,sdscatprintf(sdsempty(),"%d\r\n",
+            addReplySds(c,sdscatprintf(sdsempty(),"$%d\r\n",
                 sdslen(vector[j].obj->ptr)));
             addReply(c,vector[j].obj);
             addReply(c,shared.crlf);
@@ -2779,7 +2774,7 @@ static void sortCommand(redisClient *c) {
                 if (!val || val->type != REDIS_STRING) {
                     addReply(c,shared.minus1);
                 } else {
-                    addReplySds(c,sdscatprintf(sdsempty(),"%d\r\n",
+                    addReplySds(c,sdscatprintf(sdsempty(),"$%d\r\n",
                         sdslen(val->ptr)));
                     addReply(c,val);
                     addReply(c,shared.crlf);
@@ -2827,7 +2822,7 @@ static void infoCommand(redisClient *c) {
         uptime,
         uptime/(3600*24)
     );
-    addReplySds(c,sdscatprintf(sdsempty(),"%d\r\n",sdslen(info)));
+    addReplySds(c,sdscatprintf(sdsempty(),"$%d\r\n",sdslen(info)));
     addReplySds(c,info);
     addReply(c,shared.crlf);
 }
@@ -2930,7 +2925,7 @@ static void syncCommand(redisClient *c) {
     if (fd == -1 || fstat(fd,&sb) == -1) goto closeconn;
     len = sb.st_size;
 
-    snprintf(sizebuf,32,"%d\r\n",len);
+    snprintf(sizebuf,32,"$%d\r\n",len);
     if (syncWrite(c->fd,sizebuf,strlen(sizebuf),5) == -1) goto closeconn;
     while(len) {
         char buf[1024];
@@ -2982,7 +2977,7 @@ static int syncWithMaster(void) {
             strerror(errno));
         return REDIS_ERR;
     }
-    dumpsize = atoi(buf);
+    dumpsize = atoi(buf+1);
     redisLog(REDIS_NOTICE,"Receiving %d bytes data dump from MASTER",dumpsize);
     /* Read the bulk write data on a temp file */
     snprintf(tmpfile,256,"temp-%d.%ld.rdb",(int)time(NULL),(long int)random());