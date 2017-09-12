@@ -403,97 +403,271 @@ static int zslParseRange(robj *min, robj *max, zrangespec *spec) {
     return REDIS_OK;
 }
 
+/*-----------------------------------------------------------------------------
+ * Ziplist-backed sorted set API
+ *----------------------------------------------------------------------------*/
+
+double zzlGetScore(unsigned char *sptr) {
+    unsigned char *vstr;
+    unsigned int vlen;
+    long long vlong;
+    char buf[128];
+    double score;
+
+    redisAssert(sptr != NULL);
+    redisAssert(ziplistGet(sptr,&vstr,&vlen,&vlong));
+
+    if (vstr) {
+        memcpy(buf,vstr,vlen);
+        buf[vlen] = '\0';
+        score = strtod(buf,NULL);
+    } else {
+        score = vlong;
+    }
+
+    return score;
+}
+
+/* Compare element in sorted set with given element. */
+int zzlCompareElements(unsigned char *eptr, unsigned char *cstr, unsigned int clen) {
+    unsigned char *vstr;
+    unsigned int vlen;
+    long long vlong;
+    unsigned char vbuf[32];
+    int minlen, cmp;
+
+    redisAssert(ziplistGet(eptr,&vstr,&vlen,&vlong));
+    if (vstr == NULL) {
+        /* Store string representation of long long in buf. */
+        vlen = ll2string((char*)vbuf,sizeof(vbuf),vlong);
+        vstr = vbuf;
+    }
+
+    minlen = (vlen < clen) ? vlen : clen;
+    cmp = memcmp(vstr,cstr,minlen);
+    if (cmp == 0) return vlen-clen;
+    return cmp;
+}
+
+unsigned char *zzlFind(robj *zobj, robj *ele, double *score) {
+    unsigned char *zl = zobj->ptr;
+    unsigned char *eptr = ziplistIndex(zl,0), *sptr;
+
+    ele = getDecodedObject(ele);
+    while (eptr != NULL) {
+        sptr = ziplistNext(zl,eptr);
+        redisAssert(sptr != NULL);
+
+        if (ziplistCompare(eptr,ele->ptr,sdslen(ele->ptr))) {
+            /* Matching element, pull out score. */
+            *score = zzlGetScore(sptr);
+            decrRefCount(ele);
+            return eptr;
+        }
+
+        /* Move to next element. */
+        eptr = ziplistNext(zl,sptr);
+    }
+
+    decrRefCount(ele);
+    return NULL;
+}
+
+/* Delete (element,score) pair from ziplist. Use local copy of eptr because we
+ * don't want to modify the one given as argument. */
+int zzlDelete(robj *zobj, unsigned char *eptr) {
+    unsigned char *zl = zobj->ptr;
+    unsigned char *p = eptr;
+
+    /* TODO: add function to ziplist API to delete N elements from offset. */
+    zl = ziplistDelete(zl,&p);
+    zl = ziplistDelete(zl,&p);
+    zobj->ptr = zl;
+    return REDIS_OK;
+}
+
+int zzlInsertAt(robj *zobj, robj *ele, double score, unsigned char *eptr) {
+    unsigned char *zl = zobj->ptr;
+    unsigned char *sptr;
+    char scorebuf[128];
+    int scorelen;
+    int offset;
+
+    redisAssert(ele->encoding == REDIS_ENCODING_RAW);
+    scorelen = d2string(scorebuf,sizeof(scorebuf),score);
+    if (eptr == NULL) {
+        zl = ziplistPush(zl,ele->ptr,sdslen(ele->ptr),ZIPLIST_TAIL);
+        zl = ziplistPush(zl,(unsigned char*)scorebuf,scorelen,ZIPLIST_TAIL);
+    } else {
+        /* Keep offset relative to zl, as it might be re-allocated. */
+        offset = eptr-zl;
+        zl = ziplistInsert(zl,eptr,ele->ptr,sdslen(ele->ptr));
+        eptr = zl+offset;
+
+        /* Insert score after the element. */
+        redisAssert((sptr = ziplistNext(zl,eptr)) != NULL);
+        zl = ziplistInsert(zl,sptr,(unsigned char*)scorebuf,scorelen);
+    }
+
+    zobj->ptr = zl;
+    return REDIS_OK;
+}
+
+/* Insert (element,score) pair in ziplist. This function assumes the element is
+ * not yet present in the list. */
+int zzlInsert(robj *zobj, robj *ele, double score) {
+    unsigned char *zl = zobj->ptr;
+    unsigned char *eptr = ziplistIndex(zl,0), *sptr;
+    double s;
+    int insert = 0;
+
+    ele = getDecodedObject(ele);
+    while (eptr != NULL) {
+        sptr = ziplistNext(zl,eptr);
+        redisAssert(sptr != NULL);
+        s = zzlGetScore(sptr);
+
+        if (s > score) {
+            /* First element with score larger than score for element to be
+             * inserted. This means we should take its spot in the list to
+             * maintain ordering. */
+            insert = 1;
+        } else if (s == score) {
+            /* Ensure lexicographical ordering for elements. */
+            if (zzlCompareElements(eptr,ele->ptr,sdslen(ele->ptr)) < 0)
+                insert = 1;
+        }
+
+        if (insert) {
+            zzlInsertAt(zobj,ele,score,eptr);
+            break;
+        }
+
+        /* Move to next element. */
+        eptr = ziplistNext(zl,sptr);
+    }
+
+    /* Push on tail of list when it was not yet inserted. */
+    if (!insert)
+        zzlInsertAt(zobj,ele,score,eptr);
+
+    decrRefCount(ele);
+    return REDIS_OK;
+}
 
 /*-----------------------------------------------------------------------------
  * Sorted set commands 
  *----------------------------------------------------------------------------*/
 
 /* This generic command implements both ZADD and ZINCRBY. */
 void zaddGenericCommand(redisClient *c, robj *key, robj *ele, double score, int incr) {
-    robj *zsetobj;
-    zset *zs;
-    zskiplistNode *znode;
-
-    zsetobj = lookupKeyWrite(c->db,key);
-    if (zsetobj == NULL) {
-        zsetobj = createZsetObject();
-        dbAdd(c->db,key,zsetobj);
+    static char *nanerr = "resulting score is not a number (NaN)";
+    robj *zobj;
+    robj *curobj;
+    double curscore = 0.0;
+
+    zobj = lookupKeyWrite(c->db,key);
+    if (zobj == NULL) {
+        zobj = createZsetZiplistObject();
+        dbAdd(c->db,key,zobj);
     } else {
-        if (zsetobj->type != REDIS_ZSET) {
+        if (zobj->type != REDIS_ZSET) {
             addReply(c,shared.wrongtypeerr);
             return;
         }
     }
-    zs = zsetobj->ptr;
 
-    /* Since both ZADD and ZINCRBY are implemented here, we need to increment
-     * the score first by the current score if ZINCRBY is called. */
-    if (incr) {
-        /* Read the old score. If the element was not present starts from 0 */
-        dictEntry *de = dictFind(zs->dict,ele);
-        if (de != NULL)
-            score += *(double*)dictGetEntryVal(de);
-
-        if (isnan(score)) {
-            addReplyError(c,"resulting score is not a number (NaN)");
-            /* Note that we don't need to check if the zset may be empty and
-             * should be removed here, as we can only obtain Nan as score if
-             * there was already an element in the sorted set. */
-            return;
-        }
-    }
+    if (zobj->encoding == REDIS_ENCODING_ZIPLIST) {
+        unsigned char *eptr;
 
-    /* We need to remove and re-insert the element when it was already present
-     * in the dictionary, to update the skiplist. Note that we delay adding a
-     * pointer to the score because we want to reference the score in the
-     * skiplist node. */
-    if (dictAdd(zs->dict,ele,NULL) == DICT_OK) {
-        dictEntry *de;
+        if ((eptr = zzlFind(zobj,ele,&curscore)) != NULL) {
+            if (incr) {
+                score += curscore;
+                if (isnan(score)) {
+                    addReplyError(c,nanerr);
+                    /* Don't need to check if the sorted set is empty, because
+                     * we know it has at least one element. */
+                    return;
+                }
+            }
 
-        /* New element */
-        incrRefCount(ele); /* added to hash */
-        znode = zslInsert(zs->zsl,score,ele);
-        incrRefCount(ele); /* added to skiplist */
+            /* Remove and re-insert when score changed. */
+            if (score != curscore) {
+                redisAssert(zzlDelete(zobj,eptr) == REDIS_OK);
+                redisAssert(zzlInsert(zobj,ele,score) == REDIS_OK);
 
-        /* Update the score in the dict entry */
-        de = dictFind(zs->dict,ele);
-        redisAssert(de != NULL);
-        dictGetEntryVal(de) = &znode->score;
-        signalModifiedKey(c->db,c->argv[1]);
-        server.dirty++;
-        if (incr)
-            addReplyDouble(c,score);
-        else
-            addReply(c,shared.cone);
-    } else {
+                signalModifiedKey(c->db,key);
+                server.dirty++;
+            }
+
+            if (incr) /* ZINCRBY */
+                addReplyDouble(c,score);
+            else /* ZADD */
+                addReply(c,shared.czero);
+        } else {
+            redisAssert(zzlInsert(zobj,ele,score) == REDIS_OK);
+
+            signalModifiedKey(c->db,key);
+            server.dirty++;
+
+            if (incr) /* ZINCRBY */
+                addReplyDouble(c,score);
+            else /* ZADD */
+                addReply(c,shared.cone);
+        }
+    } else if (zobj->encoding == REDIS_ENCODING_RAW) {
+        zset *zs = zobj->ptr;
+        zskiplistNode *znode;
         dictEntry *de;
-        robj *curobj;
-        double *curscore;
-        int deleted;
 
-        /* Update score */
         de = dictFind(zs->dict,ele);
-        redisAssert(de != NULL);
-        curobj = dictGetEntryKey(de);
-        curscore = dictGetEntryVal(de);
-
-        /* When the score is updated, reuse the existing string object to
-         * prevent extra alloc/dealloc of strings on ZINCRBY. */
-        if (score != *curscore) {
-            deleted = zslDelete(zs->zsl,*curscore,curobj);
-            redisAssert(deleted != 0);
-            znode = zslInsert(zs->zsl,score,curobj);
-            incrRefCount(curobj);
-
-            /* Update the score in the current dict entry */
-            dictGetEntryVal(de) = &znode->score;
-            signalModifiedKey(c->db,c->argv[1]);
+        if (de != NULL) {
+            curobj = dictGetEntryKey(de);
+            curscore = *(double*)dictGetEntryVal(de);
+
+            if (incr) {
+                score += curscore;
+                if (isnan(score)) {
+                    addReplyError(c,nanerr);
+                    /* Don't need to check if the sorted set is empty, because
+                     * we know it has at least one element. */
+                    return;
+                }
+            }
+
+            /* Remove and re-insert when score changed. We can safely delete
+             * the key object from the skiplist, since the dictionary still has
+             * a reference to it. */
+            if (score != curscore) {
+                redisAssert(zslDelete(zs->zsl,curscore,curobj));
+                znode = zslInsert(zs->zsl,score,curobj);
+                incrRefCount(curobj); /* Re-inserted in skiplist. */
+                dictGetEntryVal(de) = &znode->score; /* Update score ptr. */
+
+                signalModifiedKey(c->db,key);
+                server.dirty++;
+            }
+
+            if (incr) /* ZINCRBY */
+                addReplyDouble(c,score);
+            else /* ZADD */
+                addReply(c,shared.czero);
+        } else {
+            znode = zslInsert(zs->zsl,score,ele);
+            incrRefCount(ele); /* Inserted in skiplist. */
+            redisAssert(dictAdd(zs->dict,ele,&znode->score) == DICT_OK);
+            incrRefCount(ele); /* Added to dictionary. */
+
+            signalModifiedKey(c->db,key);
             server.dirty++;
+
+            if (incr) /* ZINCRBY */
+                addReplyDouble(c,score);
+            else /* ZADD */
+                addReply(c,shared.cone);
         }
-        if (incr)
-            addReplyDouble(c,score);
-        else
-            addReply(c,shared.czero);
+    } else {
+        redisPanic("Unknown sorted set encoding");
     }
 }
 