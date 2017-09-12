@@ -180,6 +180,82 @@ typedef struct {
     int minex, maxex; /* are min or max exclusive? */
 } zrangespec;
 
+static int zslValueGteMin(double value, zrangespec *spec) {
+    return spec->minex ? (value > spec->min) : (value >= spec->min);
+}
+
+static int zslValueLteMax(double value, zrangespec *spec) {
+    return spec->maxex ? (value < spec->max) : (value <= spec->max);
+}
+
+/* Returns if there is a part of the zset is in range. */
+int zslIsInRange(zskiplist *zsl, zrangespec *range) {
+    zskiplistNode *x;
+
+    /* Test for ranges that will always be empty. */
+    if (range->min > range->max ||
+            (range->min == range->max && (range->minex || range->maxex)))
+        return 0;
+    x = zsl->tail;
+    if (x == NULL || !zslValueGteMin(x->score,range))
+        return 0;
+    x = zsl->header->level[0].forward;
+    if (x == NULL || !zslValueLteMax(x->score,range))
+        return 0;
+    return 1;
+}
+
+/* Find the first node that is contained in the specified range.
+ * Returns NULL when no element is contained in the range. */
+zskiplistNode *zslFirstInRange(zskiplist *zsl, zrangespec range) {
+    zskiplistNode *x;
+    int i;
+
+    /* If everything is out of range, return early. */
+    if (!zslIsInRange(zsl,&range)) return NULL;
+
+    x = zsl->header;
+    for (i = zsl->level-1; i >= 0; i--) {
+        /* Go forward while *OUT* of range. */
+        while (x->level[i].forward &&
+            !zslValueGteMin(x->level[i].forward->score,&range))
+                x = x->level[i].forward;
+    }
+
+    /* This is an inner range, so the next node cannot be NULL. */
+    x = x->level[0].forward;
+    redisAssert(x != NULL);
+
+    /* Check if score <= max. */
+    if (!zslValueLteMax(x->score,&range)) return NULL;
+    return x;
+}
+
+/* Find the last node that is contained in the specified range.
+ * Returns NULL when no element is contained in the range. */
+zskiplistNode *zslLastInRange(zskiplist *zsl, zrangespec range) {
+    zskiplistNode *x;
+    int i;
+
+    /* If everything is out of range, return early. */
+    if (!zslIsInRange(zsl,&range)) return NULL;
+
+    x = zsl->header;
+    for (i = zsl->level-1; i >= 0; i--) {
+        /* Go forward while *IN* range. */
+        while (x->level[i].forward &&
+            zslValueLteMax(x->level[i].forward->score,&range))
+                x = x->level[i].forward;
+    }
+
+    /* This is an inner range, so this node cannot be NULL. */
+    redisAssert(x != NULL);
+
+    /* Check if score >= min. */
+    if (!zslValueGteMin(x->score,&range)) return NULL;
+    return x;
+}
+
 /* Delete all the elements with score between min and max from the skiplist.
  * Min and mx are inclusive, so a score >= min || score <= max is deleted.
  * Note that this function takes the reference to the hash table view of the
@@ -243,27 +319,11 @@ unsigned long zslDeleteRangeByRank(zskiplist *zsl, unsigned int start, unsigned
     return removed;
 }
 
-/* Find the first node having a score equal or greater than the specified one.
- * Returns NULL if there is no match. */
-zskiplistNode *zslFirstWithScore(zskiplist *zsl, double score) {
-    zskiplistNode *x;
-    int i;
-
-    x = zsl->header;
-    for (i = zsl->level-1; i >= 0; i--) {
-        while (x->level[i].forward && x->level[i].forward->score < score)
-            x = x->level[i].forward;
-    }
-    /* We may have multiple elements with the same score, what we need
-     * is to find the element with both the right score and object. */
-    return x->level[0].forward;
-}
-
 /* Find the rank for an element by both score and key.
  * Returns 0 when the element cannot be found, rank otherwise.
  * Note that the rank is 1-based due to the span of zsl->header to the
  * first element. */
-unsigned long zslistTypeGetRank(zskiplist *zsl, double score, robj *o) {
+unsigned long zslGetRank(zskiplist *zsl, double score, robj *o) {
     zskiplistNode *x;
     unsigned long rank = 0;
     int i;
@@ -287,7 +347,7 @@ unsigned long zslistTypeGetRank(zskiplist *zsl, double score, robj *o) {
 }
 
 /* Finds an element by its rank. The rank argument needs to be 1-based. */
-zskiplistNode* zslistTypeGetElementByRank(zskiplist *zsl, unsigned long rank) {
+zskiplistNode* zslGetElementByRank(zskiplist *zsl, unsigned long rank) {
     zskiplistNode *x;
     unsigned long traversed = 0;
     int i;
@@ -343,186 +403,646 @@ static int zslParseRange(robj *min, robj *max, zrangespec *spec) {
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
+unsigned int zzlLength(unsigned char *zl) {
+    return ziplistLen(zl)/2;
+}
+
+/* Move to next entry based on the values in eptr and sptr. Both are set to
+ * NULL when there is no next entry. */
+void zzlNext(unsigned char *zl, unsigned char **eptr, unsigned char **sptr) {
+    unsigned char *_eptr, *_sptr;
+    redisAssert(*eptr != NULL && *sptr != NULL);
+
+    _eptr = ziplistNext(zl,*sptr);
+    if (_eptr != NULL) {
+        _sptr = ziplistNext(zl,_eptr);
+        redisAssert(_sptr != NULL);
+    } else {
+        /* No next entry. */
+        _sptr = NULL;
+    }
+
+    *eptr = _eptr;
+    *sptr = _sptr;
+}
+
+/* Move to the previous entry based on the values in eptr and sptr. Both are
+ * set to NULL when there is no next entry. */
+void zzlPrev(unsigned char *zl, unsigned char **eptr, unsigned char **sptr) {
+    unsigned char *_eptr, *_sptr;
+    redisAssert(*eptr != NULL && *sptr != NULL);
+
+    _sptr = ziplistPrev(zl,*eptr);
+    if (_sptr != NULL) {
+        _eptr = ziplistPrev(zl,_sptr);
+        redisAssert(_eptr != NULL);
+    } else {
+        /* No previous entry. */
+        _eptr = NULL;
+    }
+
+    *eptr = _eptr;
+    *sptr = _sptr;
+}
+
+/* Returns if there is a part of the zset is in range. Should only be used
+ * internally by zzlFirstInRange and zzlLastInRange. */
+int zzlIsInRange(unsigned char *zl, zrangespec *range) {
+    unsigned char *p;
+    double score;
+
+    /* Test for ranges that will always be empty. */
+    if (range->min > range->max ||
+            (range->min == range->max && (range->minex || range->maxex)))
+        return 0;
+
+    p = ziplistIndex(zl,-1); /* Last score. */
+    redisAssert(p != NULL);
+    score = zzlGetScore(p);
+    if (!zslValueGteMin(score,range))
+        return 0;
+
+    p = ziplistIndex(zl,1); /* First score. */
+    redisAssert(p != NULL);
+    score = zzlGetScore(p);
+    if (!zslValueLteMax(score,range))
+        return 0;
+
+    return 1;
+}
+
+/* Find pointer to the first element contained in the specified range.
+ * Returns NULL when no element is contained in the range. */
+unsigned char *zzlFirstInRange(unsigned char *zl, zrangespec range) {
+    unsigned char *eptr = ziplistIndex(zl,0), *sptr;
+    double score;
+
+    /* If everything is out of range, return early. */
+    if (!zzlIsInRange(zl,&range)) return NULL;
+
+    while (eptr != NULL) {
+        sptr = ziplistNext(zl,eptr);
+        redisAssert(sptr != NULL);
+
+        score = zzlGetScore(sptr);
+        if (zslValueGteMin(score,&range)) {
+            /* Check if score <= max. */
+            if (zslValueLteMax(score,&range))
+                return eptr;
+            return NULL;
+        }
+
+        /* Move to next element. */
+        eptr = ziplistNext(zl,sptr);
+    }
+
+    return NULL;
+}
+
+/* Find pointer to the last element contained in the specified range.
+ * Returns NULL when no element is contained in the range. */
+unsigned char *zzlLastInRange(unsigned char *zl, zrangespec range) {
+    unsigned char *eptr = ziplistIndex(zl,-2), *sptr;
+    double score;
+
+    /* If everything is out of range, return early. */
+    if (!zzlIsInRange(zl,&range)) return NULL;
+
+    while (eptr != NULL) {
+        sptr = ziplistNext(zl,eptr);
+        redisAssert(sptr != NULL);
+
+        score = zzlGetScore(sptr);
+        if (zslValueLteMax(score,&range)) {
+            /* Check if score >= min. */
+            if (zslValueGteMin(score,&range))
+                return eptr;
+            return NULL;
+        }
+
+        /* Move to previous element by moving to the score of previous element.
+         * When this returns NULL, we know there also is no element. */
+        sptr = ziplistPrev(zl,eptr);
+        if (sptr != NULL)
+            redisAssert((eptr = ziplistPrev(zl,sptr)) != NULL);
+        else
+            eptr = NULL;
+    }
+
+    return NULL;
+}
+
+unsigned char *zzlFind(unsigned char *zl, robj *ele, double *score) {
+    unsigned char *eptr = ziplistIndex(zl,0), *sptr;
+
+    ele = getDecodedObject(ele);
+    while (eptr != NULL) {
+        sptr = ziplistNext(zl,eptr);
+        redisAssert(sptr != NULL);
+
+        if (ziplistCompare(eptr,ele->ptr,sdslen(ele->ptr))) {
+            /* Matching element, pull out score. */
+            if (score != NULL) *score = zzlGetScore(sptr);
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
+unsigned char *zzlDelete(unsigned char *zl, unsigned char *eptr) {
+    unsigned char *p = eptr;
+
+    /* TODO: add function to ziplist API to delete N elements from offset. */
+    zl = ziplistDelete(zl,&p);
+    zl = ziplistDelete(zl,&p);
+    return zl;
+}
+
+unsigned char *zzlInsertAt(unsigned char *zl, unsigned char *eptr, robj *ele, double score) {
+    unsigned char *sptr;
+    char scorebuf[128];
+    int scorelen;
+    size_t offset;
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
+    return zl;
+}
+
+/* Insert (element,score) pair in ziplist. This function assumes the element is
+ * not yet present in the list. */
+unsigned char *zzlInsert(unsigned char *zl, robj *ele, double score) {
+    unsigned char *eptr = ziplistIndex(zl,0), *sptr;
+    double s;
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
+            zl = zzlInsertAt(zl,eptr,ele,score);
+            break;
+        } else if (s == score) {
+            /* Ensure lexicographical ordering for elements. */
+            if (zzlCompareElements(eptr,ele->ptr,sdslen(ele->ptr)) > 0) {
+                zl = zzlInsertAt(zl,eptr,ele,score);
+                break;
+            }
+        }
+
+        /* Move to next element. */
+        eptr = ziplistNext(zl,sptr);
+    }
+
+    /* Push on tail of list when it was not yet inserted. */
+    if (eptr == NULL)
+        zl = zzlInsertAt(zl,NULL,ele,score);
+
+    decrRefCount(ele);
+    return zl;
+}
+
+unsigned char *zzlDeleteRangeByScore(unsigned char *zl, zrangespec range, unsigned long *deleted) {
+    unsigned char *eptr, *sptr;
+    double score;
+    unsigned long num = 0;
+
+    if (deleted != NULL) *deleted = 0;
+
+    eptr = zzlFirstInRange(zl,range);
+    if (eptr == NULL) return zl;
+
+    /* When the tail of the ziplist is deleted, eptr will point to the sentinel
+     * byte and ziplistNext will return NULL. */
+    while ((sptr = ziplistNext(zl,eptr)) != NULL) {
+        score = zzlGetScore(sptr);
+        if (zslValueLteMax(score,&range)) {
+            /* Delete both the element and the score. */
+            zl = ziplistDelete(zl,&eptr);
+            zl = ziplistDelete(zl,&eptr);
+            num++;
+        } else {
+            /* No longer in range. */
+            break;
+        }
+    }
+
+    if (deleted != NULL) *deleted = num;
+    return zl;
+}
+
+/* Delete all the elements with rank between start and end from the skiplist.
+ * Start and end are inclusive. Note that start and end need to be 1-based */
+unsigned char *zzlDeleteRangeByRank(unsigned char *zl, unsigned int start, unsigned int end, unsigned long *deleted) {
+    unsigned int num = (end-start)+1;
+    if (deleted) *deleted = num;
+    zl = ziplistDeleteRange(zl,2*(start-1),2*num);
+    return zl;
+}
+
+/*-----------------------------------------------------------------------------
+ * Common sorted set API
+ *----------------------------------------------------------------------------*/
+
+unsigned int zsetLength(robj *zobj) {
+    int length = -1;
+    if (zobj->encoding == REDIS_ENCODING_ZIPLIST) {
+        length = zzlLength(zobj->ptr);
+    } else if (zobj->encoding == REDIS_ENCODING_SKIPLIST) {
+        length = ((zset*)zobj->ptr)->zsl->length;
+    } else {
+        redisPanic("Unknown sorted set encoding");
+    }
+    return length;
+}
+
+void zsetConvert(robj *zobj, int encoding) {
+    zset *zs;
+    zskiplistNode *node, *next;
+    robj *ele;
+    double score;
+
+    if (zobj->encoding == encoding) return;
+    if (zobj->encoding == REDIS_ENCODING_ZIPLIST) {
+        unsigned char *zl = zobj->ptr;
+        unsigned char *eptr, *sptr;
+        unsigned char *vstr;
+        unsigned int vlen;
+        long long vlong;
+
+        if (encoding != REDIS_ENCODING_SKIPLIST)
+            redisPanic("Unknown target encoding");
+
+        zs = zmalloc(sizeof(*zs));
+        zs->dict = dictCreate(&zsetDictType,NULL);
+        zs->zsl = zslCreate();
+
+        eptr = ziplistIndex(zl,0);
+        redisAssert(eptr != NULL);
+        sptr = ziplistNext(zl,eptr);
+        redisAssert(sptr != NULL);
+
+        while (eptr != NULL) {
+            score = zzlGetScore(sptr);
+            redisAssert(ziplistGet(eptr,&vstr,&vlen,&vlong));
+            if (vstr == NULL)
+                ele = createStringObjectFromLongLong(vlong);
+            else
+                ele = createStringObject((char*)vstr,vlen);
+
+            /* Has incremented refcount since it was just created. */
+            node = zslInsert(zs->zsl,score,ele);
+            redisAssert(dictAdd(zs->dict,ele,&node->score) == DICT_OK);
+            incrRefCount(ele); /* Added to dictionary. */
+            zzlNext(zl,&eptr,&sptr);
+        }
+
+        zfree(zobj->ptr);
+        zobj->ptr = zs;
+        zobj->encoding = REDIS_ENCODING_SKIPLIST;
+    } else if (zobj->encoding == REDIS_ENCODING_SKIPLIST) {
+        unsigned char *zl = ziplistNew();
+
+        if (encoding != REDIS_ENCODING_ZIPLIST)
+            redisPanic("Unknown target encoding");
+
+        /* Approach similar to zslFree(), since we want to free the skiplist at
+         * the same time as creating the ziplist. */
+        zs = zobj->ptr;
+        dictRelease(zs->dict);
+        node = zs->zsl->header->level[0].forward;
+        zfree(zs->zsl->header);
+        zfree(zs->zsl);
+
+        while (node) {
+            ele = getDecodedObject(node->obj);
+            zl = zzlInsertAt(zl,NULL,ele,node->score);
+            decrRefCount(ele);
+
+            next = node->level[0].forward;
+            zslFreeNode(node);
+            node = next;
+        }
+
+        zfree(zs);
+        zobj->ptr = zl;
+        zobj->encoding = REDIS_ENCODING_ZIPLIST;
+    } else {
+        redisPanic("Unknown sorted set encoding");
+    }
+}
 
 /*-----------------------------------------------------------------------------
  * Sorted set commands 
  *----------------------------------------------------------------------------*/
 
 /* This generic command implements both ZADD and ZINCRBY. */
-void zaddGenericCommand(redisClient *c, robj *key, robj *ele, double score, int incr) {
-    robj *zsetobj;
-    zset *zs;
-    zskiplistNode *znode;
+void zaddGenericCommand(redisClient *c, int incr) {
+    static char *nanerr = "resulting score is not a number (NaN)";
+    robj *key = c->argv[1];
+    robj *ele;
+    robj *zobj;
+    robj *curobj;
+    double score, curscore = 0.0;
 
-    zsetobj = lookupKeyWrite(c->db,key);
-    if (zsetobj == NULL) {
-        zsetobj = createZsetObject();
-        dbAdd(c->db,key,zsetobj);
+    if (getDoubleFromObjectOrReply(c,c->argv[2],&score,NULL) != REDIS_OK)
+        return;
+
+    zobj = lookupKeyWrite(c->db,key);
+    if (zobj == NULL) {
+        if (server.zset_max_ziplist_entries == 0 ||
+            server.zset_max_ziplist_value < sdslen(c->argv[3]->ptr))
+        {
+            zobj = createZsetObject();
+        } else {
+            zobj = createZsetZiplistObject();
+        }
+        dbAdd(c->db,key,zobj);
     } else {
-        if (zsetobj->type != REDIS_ZSET) {
+        if (zobj->type != REDIS_ZSET) {
             addReply(c,shared.wrongtypeerr);
             return;
         }
     }
-    zs = zsetobj->ptr;
-
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
 
-    /* We need to remove and re-insert the element when it was already present
-     * in the dictionary, to update the skiplist. Note that we delay adding a
-     * pointer to the score because we want to reference the score in the
-     * skiplist node. */
-    if (dictAdd(zs->dict,ele,NULL) == DICT_OK) {
-        dictEntry *de;
+    if (zobj->encoding == REDIS_ENCODING_ZIPLIST) {
+        unsigned char *eptr;
+
+        /* Prefer non-encoded element when dealing with ziplists. */
+        ele = c->argv[3];
+        if ((eptr = zzlFind(zobj->ptr,ele,&curscore)) != NULL) {
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
+                zobj->ptr = zzlDelete(zobj->ptr,eptr);
+                zobj->ptr = zzlInsert(zobj->ptr,ele,score);
 
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
+            /* Optimize: check if the element is too large or the list becomes
+             * too long *before* executing zzlInsert. */
+            zobj->ptr = zzlInsert(zobj->ptr,ele,score);
+            if (zzlLength(zobj->ptr) > server.zset_max_ziplist_entries)
+                zsetConvert(zobj,REDIS_ENCODING_SKIPLIST);
+            if (sdslen(ele->ptr) > server.zset_max_ziplist_value)
+                zsetConvert(zobj,REDIS_ENCODING_SKIPLIST);
+
+            signalModifiedKey(c->db,key);
+            server.dirty++;
+
+            if (incr) /* ZINCRBY */
+                addReplyDouble(c,score);
+            else /* ZADD */
+                addReply(c,shared.cone);
+        }
+    } else if (zobj->encoding == REDIS_ENCODING_SKIPLIST) {
+        zset *zs = zobj->ptr;
+        zskiplistNode *znode;
         dictEntry *de;
-        robj *curobj;
-        double *curscore;
-        int deleted;
 
-        /* Update score */
+        ele = c->argv[3] = tryObjectEncoding(c->argv[3]);
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
 
 void zaddCommand(redisClient *c) {
-    double scoreval;
-    if (getDoubleFromObjectOrReply(c,c->argv[2],&scoreval,NULL) != REDIS_OK) return;
-    c->argv[3] = tryObjectEncoding(c->argv[3]);
-    zaddGenericCommand(c,c->argv[1],c->argv[3],scoreval,0);
+    zaddGenericCommand(c,0);
 }
 
 void zincrbyCommand(redisClient *c) {
-    double scoreval;
-    if (getDoubleFromObjectOrReply(c,c->argv[2],&scoreval,NULL) != REDIS_OK) return;
-    c->argv[3] = tryObjectEncoding(c->argv[3]);
-    zaddGenericCommand(c,c->argv[1],c->argv[3],scoreval,1);
+    zaddGenericCommand(c,1);
 }
 
 void zremCommand(redisClient *c) {
-    robj *zsetobj;
-    zset *zs;
-    dictEntry *de;
-    double curscore;
-    int deleted;
+    robj *key = c->argv[1];
+    robj *ele = c->argv[2];
+    robj *zobj;
 
-    if ((zsetobj = lookupKeyWriteOrReply(c,c->argv[1],shared.czero)) == NULL ||
-        checkType(c,zsetobj,REDIS_ZSET)) return;
+    if ((zobj = lookupKeyWriteOrReply(c,key,shared.czero)) == NULL ||
+        checkType(c,zobj,REDIS_ZSET)) return;
 
-    zs = zsetobj->ptr;
-    c->argv[2] = tryObjectEncoding(c->argv[2]);
-    de = dictFind(zs->dict,c->argv[2]);
-    if (de == NULL) {
-        addReply(c,shared.czero);
-        return;
+    if (zobj->encoding == REDIS_ENCODING_ZIPLIST) {
+        unsigned char *eptr;
+
+        if ((eptr = zzlFind(zobj->ptr,ele,NULL)) != NULL) {
+            zobj->ptr = zzlDelete(zobj->ptr,eptr);
+            if (zzlLength(zobj->ptr) == 0) dbDelete(c->db,key);
+        } else {
+            addReply(c,shared.czero);
+            return;
+        }
+    } else if (zobj->encoding == REDIS_ENCODING_SKIPLIST) {
+        zset *zs = zobj->ptr;
+        dictEntry *de;
+        double score;
+
+        de = dictFind(zs->dict,ele);
+        if (de != NULL) {
+            /* Delete from the skiplist */
+            score = *(double*)dictGetEntryVal(de);
+            redisAssert(zslDelete(zs->zsl,score,ele));
+
+            /* Delete from the hash table */
+            dictDelete(zs->dict,ele);
+            if (htNeedsResize(zs->dict)) dictResize(zs->dict);
+            if (dictSize(zs->dict) == 0) dbDelete(c->db,key);
+        } else {
+            addReply(c,shared.czero);
+            return;
+        }
+    } else {
+        redisPanic("Unknown sorted set encoding");
     }
-    /* Delete from the skiplist */
-    curscore = *(double*)dictGetEntryVal(de);
-    deleted = zslDelete(zs->zsl,curscore,c->argv[2]);
-    redisAssert(deleted != 0);
 
-    /* Delete from the hash table */
-    dictDelete(zs->dict,c->argv[2]);
-    if (htNeedsResize(zs->dict)) dictResize(zs->dict);
-    if (dictSize(zs->dict) == 0) dbDelete(c->db,c->argv[1]);
-    signalModifiedKey(c->db,c->argv[1]);
+    signalModifiedKey(c->db,key);
     server.dirty++;
     addReply(c,shared.cone);
 }
 
 void zremrangebyscoreCommand(redisClient *c) {
+    robj *key = c->argv[1];
+    robj *zobj;
     zrangespec range;
-    long deleted;
-    robj *o;
-    zset *zs;
+    unsigned long deleted;
 
     /* Parse the range arguments. */
     if (zslParseRange(c->argv[2],c->argv[3],&range) != REDIS_OK) {
         addReplyError(c,"min or max is not a double");
         return;
     }
 
-    if ((o = lookupKeyWriteOrReply(c,c->argv[1],shared.czero)) == NULL ||
-        checkType(c,o,REDIS_ZSET)) return;
+    if ((zobj = lookupKeyWriteOrReply(c,key,shared.czero)) == NULL ||
+        checkType(c,zobj,REDIS_ZSET)) return;
+
+    if (zobj->encoding == REDIS_ENCODING_ZIPLIST) {
+        zobj->ptr = zzlDeleteRangeByScore(zobj->ptr,range,&deleted);
+        if (zzlLength(zobj->ptr) == 0) dbDelete(c->db,key);
+    } else if (zobj->encoding == REDIS_ENCODING_SKIPLIST) {
+        zset *zs = zobj->ptr;
+        deleted = zslDeleteRangeByScore(zs->zsl,range,zs->dict);
+        if (htNeedsResize(zs->dict)) dictResize(zs->dict);
+        if (dictSize(zs->dict) == 0) dbDelete(c->db,key);
+    } else {
+        redisPanic("Unknown sorted set encoding");
+    }
 
-    zs = o->ptr;
-    deleted = zslDeleteRangeByScore(zs->zsl,range,zs->dict);
-    if (htNeedsResize(zs->dict)) dictResize(zs->dict);
-    if (dictSize(zs->dict) == 0) dbDelete(c->db,c->argv[1]);
-    if (deleted) signalModifiedKey(c->db,c->argv[1]);
+    if (deleted) signalModifiedKey(c->db,key);
     server.dirty += deleted;
     addReplyLongLong(c,deleted);
 }
 
 void zremrangebyrankCommand(redisClient *c) {
+    robj *key = c->argv[1];
+    robj *zobj;
     long start;
     long end;
     int llen;
-    long deleted;
-    robj *zsetobj;
-    zset *zs;
+    unsigned long deleted;
 
     if ((getLongFromObjectOrReply(c, c->argv[2], &start, NULL) != REDIS_OK) ||
         (getLongFromObjectOrReply(c, c->argv[3], &end, NULL) != REDIS_OK)) return;
 
-    if ((zsetobj = lookupKeyWriteOrReply(c,c->argv[1],shared.czero)) == NULL ||
-        checkType(c,zsetobj,REDIS_ZSET)) return;
-    zs = zsetobj->ptr;
-    llen = zs->zsl->length;
+    if ((zobj = lookupKeyWriteOrReply(c,key,shared.czero)) == NULL ||
+        checkType(c,zobj,REDIS_ZSET)) return;
 
-    /* convert negative indexes */
+    /* Sanitize indexes. */
+    llen = zsetLength(zobj);
     if (start < 0) start = llen+start;
     if (end < 0) end = llen+end;
     if (start < 0) start = 0;
@@ -535,27 +1055,348 @@ void zremrangebyrankCommand(redisClient *c) {
     }
     if (end >= llen) end = llen-1;
 
-    /* increment start and end because zsl*Rank functions
-     * use 1-based rank */
-    deleted = zslDeleteRangeByRank(zs->zsl,start+1,end+1,zs->dict);
-    if (htNeedsResize(zs->dict)) dictResize(zs->dict);
-    if (dictSize(zs->dict) == 0) dbDelete(c->db,c->argv[1]);
-    if (deleted) signalModifiedKey(c->db,c->argv[1]);
+    if (zobj->encoding == REDIS_ENCODING_ZIPLIST) {
+        /* Correct for 1-based rank. */
+        zobj->ptr = zzlDeleteRangeByRank(zobj->ptr,start+1,end+1,&deleted);
+        if (zzlLength(zobj->ptr) == 0) dbDelete(c->db,key);
+    } else if (zobj->encoding == REDIS_ENCODING_SKIPLIST) {
+        zset *zs = zobj->ptr;
+
+        /* Correct for 1-based rank. */
+        deleted = zslDeleteRangeByRank(zs->zsl,start+1,end+1,zs->dict);
+        if (htNeedsResize(zs->dict)) dictResize(zs->dict);
+        if (dictSize(zs->dict) == 0) dbDelete(c->db,key);
+    } else {
+        redisPanic("Unknown sorted set encoding");
+    }
+
+    if (deleted) signalModifiedKey(c->db,key);
     server.dirty += deleted;
-    addReplyLongLong(c, deleted);
+    addReplyLongLong(c,deleted);
 }
 
 typedef struct {
-    dict *dict;
+    robj *subject;
+    int type; /* Set, sorted set */
+    int encoding;
     double weight;
+
+    union {
+        /* Set iterators. */
+        union _iterset {
+            struct {
+                intset *is;
+                int ii;
+            } is;
+            struct {
+                dict *dict;
+                dictIterator *di;
+                dictEntry *de;
+            } ht;
+        } set;
+
+        /* Sorted set iterators. */
+        union _iterzset {
+            struct {
+                unsigned char *zl;
+                unsigned char *eptr, *sptr;
+            } zl;
+            struct {
+                zset *zs;
+                zskiplistNode *node;
+            } sl;
+        } zset;
+    } iter;
 } zsetopsrc;
 
-int qsortCompareZsetopsrcByCardinality(const void *s1, const void *s2) {
-    zsetopsrc *d1 = (void*) s1, *d2 = (void*) s2;
-    unsigned long size1, size2;
-    size1 = d1->dict ? dictSize(d1->dict) : 0;
-    size2 = d2->dict ? dictSize(d2->dict) : 0;
-    return size1 - size2;
+
+/* Use dirty flags for pointers that need to be cleaned up in the next
+ * iteration over the zsetopval. The dirty flag for the long long value is
+ * special, since long long values don't need cleanup. Instead, it means that
+ * we already checked that "ell" holds a long long, or tried to convert another
+ * representation into a long long value. When this was successful,
+ * OPVAL_VALID_LL is set as well. */
+#define OPVAL_DIRTY_ROBJ 1
+#define OPVAL_DIRTY_LL 2
+#define OPVAL_VALID_LL 4
+
+/* Store value retrieved from the iterator. */
+typedef struct {
+    int flags;
+    unsigned char _buf[32]; /* Private buffer. */
+    robj *ele;
+    unsigned char *estr;
+    unsigned int elen;
+    long long ell;
+    double score;
+} zsetopval;
+
+typedef union _iterset iterset;
+typedef union _iterzset iterzset;
+
+void zuiInitIterator(zsetopsrc *op) {
+    if (op->subject == NULL)
+        return;
+
+    if (op->type == REDIS_SET) {
+        iterset *it = &op->iter.set;
+        if (op->encoding == REDIS_ENCODING_INTSET) {
+            it->is.is = op->subject->ptr;
+            it->is.ii = 0;
+        } else if (op->encoding == REDIS_ENCODING_HT) {
+            it->ht.dict = op->subject->ptr;
+            it->ht.di = dictGetIterator(op->subject->ptr);
+            it->ht.de = dictNext(it->ht.di);
+        } else {
+            redisPanic("Unknown set encoding");
+        }
+    } else if (op->type == REDIS_ZSET) {
+        iterzset *it = &op->iter.zset;
+        if (op->encoding == REDIS_ENCODING_ZIPLIST) {
+            it->zl.zl = op->subject->ptr;
+            it->zl.eptr = ziplistIndex(it->zl.zl,0);
+            if (it->zl.eptr != NULL) {
+                it->zl.sptr = ziplistNext(it->zl.zl,it->zl.eptr);
+                redisAssert(it->zl.sptr != NULL);
+            }
+        } else if (op->encoding == REDIS_ENCODING_SKIPLIST) {
+            it->sl.zs = op->subject->ptr;
+            it->sl.node = it->sl.zs->zsl->header->level[0].forward;
+        } else {
+            redisPanic("Unknown sorted set encoding");
+        }
+    } else {
+        redisPanic("Unsupported type");
+    }
+}
+
+void zuiClearIterator(zsetopsrc *op) {
+    if (op->subject == NULL)
+        return;
+
+    if (op->type == REDIS_SET) {
+        iterset *it = &op->iter.set;
+        if (op->encoding == REDIS_ENCODING_INTSET) {
+            REDIS_NOTUSED(it); /* skip */
+        } else if (op->encoding == REDIS_ENCODING_HT) {
+            dictReleaseIterator(it->ht.di);
+        } else {
+            redisPanic("Unknown set encoding");
+        }
+    } else if (op->type == REDIS_ZSET) {
+        iterzset *it = &op->iter.zset;
+        if (op->encoding == REDIS_ENCODING_ZIPLIST) {
+            REDIS_NOTUSED(it); /* skip */
+        } else if (op->encoding == REDIS_ENCODING_SKIPLIST) {
+            REDIS_NOTUSED(it); /* skip */
+        } else {
+            redisPanic("Unknown sorted set encoding");
+        }
+    } else {
+        redisPanic("Unsupported type");
+    }
+}
+
+int zuiLength(zsetopsrc *op) {
+    if (op->subject == NULL)
+        return 0;
+
+    if (op->type == REDIS_SET) {
+        iterset *it = &op->iter.set;
+        if (op->encoding == REDIS_ENCODING_INTSET) {
+            return intsetLen(it->is.is);
+        } else if (op->encoding == REDIS_ENCODING_HT) {
+            return dictSize(it->ht.dict);
+        } else {
+            redisPanic("Unknown set encoding");
+        }
+    } else if (op->type == REDIS_ZSET) {
+        iterzset *it = &op->iter.zset;
+        if (op->encoding == REDIS_ENCODING_ZIPLIST) {
+            return zzlLength(it->zl.zl);
+        } else if (op->encoding == REDIS_ENCODING_SKIPLIST) {
+            return it->sl.zs->zsl->length;
+        } else {
+            redisPanic("Unknown sorted set encoding");
+        }
+    } else {
+        redisPanic("Unsupported type");
+    }
+}
+
+/* Check if the current value is valid. If so, store it in the passed structure
+ * and move to the next element. If not valid, this means we have reached the
+ * end of the structure and can abort. */
+int zuiNext(zsetopsrc *op, zsetopval *val) {
+    if (op->subject == NULL)
+        return 0;
+
+    if (val->flags & OPVAL_DIRTY_ROBJ)
+        decrRefCount(val->ele);
+
+    bzero(val,sizeof(zsetopval));
+
+    if (op->type == REDIS_SET) {
+        iterset *it = &op->iter.set;
+        if (op->encoding == REDIS_ENCODING_INTSET) {
+            if (!intsetGet(it->is.is,it->is.ii,&val->ell))
+                return 0;
+            val->score = 1.0;
+
+            /* Move to next element. */
+            it->is.ii++;
+        } else if (op->encoding == REDIS_ENCODING_HT) {
+            if (it->ht.de == NULL)
+                return 0;
+            val->ele = dictGetEntryKey(it->ht.de);
+            val->score = 1.0;
+
+            /* Move to next element. */
+            it->ht.de = dictNext(it->ht.di);
+        } else {
+            redisPanic("Unknown set encoding");
+        }
+    } else if (op->type == REDIS_ZSET) {
+        iterzset *it = &op->iter.zset;
+        if (op->encoding == REDIS_ENCODING_ZIPLIST) {
+            /* No need to check both, but better be explicit. */
+            if (it->zl.eptr == NULL || it->zl.sptr == NULL)
+                return 0;
+            redisAssert(ziplistGet(it->zl.eptr,&val->estr,&val->elen,&val->ell));
+            val->score = zzlGetScore(it->zl.sptr);
+
+            /* Move to next element. */
+            zzlNext(it->zl.zl,&it->zl.eptr,&it->zl.sptr);
+        } else if (op->encoding == REDIS_ENCODING_SKIPLIST) {
+            if (it->sl.node == NULL)
+                return 0;
+            val->ele = it->sl.node->obj;
+            val->score = it->sl.node->score;
+
+            /* Move to next element. */
+            it->sl.node = it->sl.node->level[0].forward;
+        } else {
+            redisPanic("Unknown sorted set encoding");
+        }
+    } else {
+        redisPanic("Unsupported type");
+    }
+    return 1;
+}
+
+int zuiLongLongFromValue(zsetopval *val) {
+    if (!(val->flags & OPVAL_DIRTY_LL)) {
+        val->flags |= OPVAL_DIRTY_LL;
+
+        if (val->ele != NULL) {
+            if (val->ele->encoding == REDIS_ENCODING_INT) {
+                val->ell = (long)val->ele->ptr;
+                val->flags |= OPVAL_VALID_LL;
+            } else if (val->ele->encoding == REDIS_ENCODING_RAW) {
+                if (string2ll(val->ele->ptr,sdslen(val->ele->ptr),&val->ell))
+                    val->flags |= OPVAL_VALID_LL;
+            } else {
+                redisPanic("Unsupported element encoding");
+            }
+        } else if (val->estr != NULL) {
+            if (string2ll((char*)val->estr,val->elen,&val->ell))
+                val->flags |= OPVAL_VALID_LL;
+        } else {
+            /* The long long was already set, flag as valid. */
+            val->flags |= OPVAL_VALID_LL;
+        }
+    }
+    return val->flags & OPVAL_VALID_LL;
+}
+
+robj *zuiObjectFromValue(zsetopval *val) {
+    if (val->ele == NULL) {
+        if (val->estr != NULL) {
+            val->ele = createStringObject((char*)val->estr,val->elen);
+        } else {
+            val->ele = createStringObjectFromLongLong(val->ell);
+        }
+        val->flags |= OPVAL_DIRTY_ROBJ;
+    }
+    return val->ele;
+}
+
+int zuiBufferFromValue(zsetopval *val) {
+    if (val->estr == NULL) {
+        if (val->ele != NULL) {
+            if (val->ele->encoding == REDIS_ENCODING_INT) {
+                val->elen = ll2string((char*)val->_buf,sizeof(val->_buf),(long)val->ele->ptr);
+                val->estr = val->_buf;
+            } else if (val->ele->encoding == REDIS_ENCODING_RAW) {
+                val->elen = sdslen(val->ele->ptr);
+                val->estr = val->ele->ptr;
+            } else {
+                redisPanic("Unsupported element encoding");
+            }
+        } else {
+            val->elen = ll2string((char*)val->_buf,sizeof(val->_buf),val->ell);
+            val->estr = val->_buf;
+        }
+    }
+    return 1;
+}
+
+/* Find value pointed to by val in the source pointer to by op. When found,
+ * return 1 and store its score in target. Return 0 otherwise. */
+int zuiFind(zsetopsrc *op, zsetopval *val, double *score) {
+    if (op->subject == NULL)
+        return 0;
+
+    if (op->type == REDIS_SET) {
+        iterset *it = &op->iter.set;
+
+        if (op->encoding == REDIS_ENCODING_INTSET) {
+            if (zuiLongLongFromValue(val) && intsetFind(it->is.is,val->ell)) {
+                *score = 1.0;
+                return 1;
+            } else {
+                return 0;
+            }
+        } else if (op->encoding == REDIS_ENCODING_HT) {
+            zuiObjectFromValue(val);
+            if (dictFind(it->ht.dict,val->ele) != NULL) {
+                *score = 1.0;
+                return 1;
+            } else {
+                return 0;
+            }
+        } else {
+            redisPanic("Unknown set encoding");
+        }
+    } else if (op->type == REDIS_ZSET) {
+        iterzset *it = &op->iter.zset;
+        zuiObjectFromValue(val);
+
+        if (op->encoding == REDIS_ENCODING_ZIPLIST) {
+            if (zzlFind(it->zl.zl,val->ele,score) != NULL) {
+                /* Score is already set by zzlFind. */
+                return 1;
+            } else {
+                return 0;
+            }
+        } else if (op->encoding == REDIS_ENCODING_SKIPLIST) {
+            dictEntry *de;
+            if ((de = dictFind(it->sl.zs->dict,val->ele)) != NULL) {
+                *score = *(double*)dictGetEntryVal(de);
+                return 1;
+            } else {
+                return 0;
+            }
+        } else {
+            redisPanic("Unknown sorted set encoding");
+        }
+    } else {
+        redisPanic("Unsupported type");
+    }
+}
+
+int zuiCompareByCardinality(const void *s1, const void *s2) {
+    return zuiLength((zsetopsrc*)s1) - zuiLength((zsetopsrc*)s2);
 }
 
 #define REDIS_AGGR_SUM 1
@@ -584,11 +1425,12 @@ void zunionInterGenericCommand(redisClient *c, robj *dstkey, int op) {
     int i, j, setnum;
     int aggregate = REDIS_AGGR_SUM;
     zsetopsrc *src;
+    zsetopval zval;
+    robj *tmp;
+    unsigned int maxelelen = 0;
     robj *dstobj;
     zset *dstzset;
     zskiplistNode *znode;
-    dictIterator *di;
-    dictEntry *de;
     int touched = 0;
 
     /* expect setnum input keys to be given */
@@ -606,24 +1448,24 @@ void zunionInterGenericCommand(redisClient *c, robj *dstkey, int op) {
     }
 
     /* read keys to be used for input */
-    src = zmalloc(sizeof(zsetopsrc) * setnum);
+    src = zcalloc(sizeof(zsetopsrc) * setnum);
     for (i = 0, j = 3; i < setnum; i++, j++) {
         robj *obj = lookupKeyWrite(c->db,c->argv[j]);
-        if (!obj) {
-            src[i].dict = NULL;
-        } else {
-            if (obj->type == REDIS_ZSET) {
-                src[i].dict = ((zset*)obj->ptr)->dict;
-            } else if (obj->type == REDIS_SET) {
-                src[i].dict = (obj->ptr);
-            } else {
+        if (obj != NULL) {
+            if (obj->type != REDIS_ZSET && obj->type != REDIS_SET) {
                 zfree(src);
                 addReply(c,shared.wrongtypeerr);
                 return;
             }
+
+            src[i].subject = obj;
+            src[i].type = obj->type;
+            src[i].encoding = obj->encoding;
+        } else {
+            src[i].subject = NULL;
         }
 
-        /* default all weights to 1 */
+        /* Default all weights to 1. */
         src[i].weight = 1.0;
     }
 
@@ -664,95 +1506,109 @@ void zunionInterGenericCommand(redisClient *c, robj *dstkey, int op) {
         }
     }
 
+    for (i = 0; i < setnum; i++)
+        zuiInitIterator(&src[i]);
+
     /* sort sets from the smallest to largest, this will improve our
      * algorithm's performance */
-    qsort(src,setnum,sizeof(zsetopsrc),qsortCompareZsetopsrcByCardinality);
+    qsort(src,setnum,sizeof(zsetopsrc),zuiCompareByCardinality);
 
     dstobj = createZsetObject();
     dstzset = dstobj->ptr;
+    memset(&zval, 0, sizeof(zval));
 
     if (op == REDIS_OP_INTER) {
-        /* skip going over all entries if the smallest zset is NULL or empty */
-        if (src[0].dict && dictSize(src[0].dict) > 0) {
-            /* precondition: as src[0].dict is non-empty and the zsets are ordered
-             * from small to large, all src[i > 0].dict are non-empty too */
-            di = dictGetIterator(src[0].dict);
-            while((de = dictNext(di)) != NULL) {
+        /* Skip everything if the smallest input is empty. */
+        if (zuiLength(&src[0]) > 0) {
+            /* Precondition: as src[0] is non-empty and the inputs are ordered
+             * by size, all src[i > 0] are non-empty too. */
+            while (zuiNext(&src[0],&zval)) {
                 double score, value;
 
-                score = src[0].weight * zunionInterDictValue(de);
+                score = src[0].weight * zval.score;
                 for (j = 1; j < setnum; j++) {
-                    dictEntry *other = dictFind(src[j].dict,dictGetEntryKey(de));
-                    if (other) {
-                        value = src[j].weight * zunionInterDictValue(other);
+                    if (zuiFind(&src[j],&zval,&value)) {
+                        value *= src[j].weight;
                         zunionInterAggregate(&score,value,aggregate);
                     } else {
                         break;
                     }
                 }
 
-                /* Only continue when present in every source dict. */
+                /* Only continue when present in every input. */
                 if (j == setnum) {
-                    robj *o = dictGetEntryKey(de);
-                    znode = zslInsert(dstzset->zsl,score,o);
-                    incrRefCount(o); /* added to skiplist */
-                    dictAdd(dstzset->dict,o,&znode->score);
-                    incrRefCount(o); /* added to dictionary */
+                    tmp = zuiObjectFromValue(&zval);
+                    znode = zslInsert(dstzset->zsl,score,tmp);
+                    incrRefCount(tmp); /* added to skiplist */
+                    dictAdd(dstzset->dict,tmp,&znode->score);
+                    incrRefCount(tmp); /* added to dictionary */
+
+                    if (tmp->encoding == REDIS_ENCODING_RAW)
+                        if (sdslen(tmp->ptr) > maxelelen)
+                            maxelelen = sdslen(tmp->ptr);
                 }
             }
-            dictReleaseIterator(di);
         }
     } else if (op == REDIS_OP_UNION) {
         for (i = 0; i < setnum; i++) {
-            if (!src[i].dict) continue;
+            if (zuiLength(&src[0]) == 0)
+                continue;
 
-            di = dictGetIterator(src[i].dict);
-            while((de = dictNext(di)) != NULL) {
+            while (zuiNext(&src[i],&zval)) {
                 double score, value;
 
-                /* skip key when already processed */
-                if (dictFind(dstzset->dict,dictGetEntryKey(de)) != NULL)
+                /* Skip key when already processed */
+                if (dictFind(dstzset->dict,zuiObjectFromValue(&zval)) != NULL)
                     continue;
 
-                /* initialize score */
-                score = src[i].weight * zunionInterDictValue(de);
+                /* Initialize score */
+                score = src[i].weight * zval.score;
 
-                /* because the zsets are sorted by size, its only possible
-                 * for sets at larger indices to hold this entry */
+                /* Because the inputs are sorted by size, it's only possible
+                 * for sets at larger indices to hold this element. */
                 for (j = (i+1); j < setnum; j++) {
-                    dictEntry *other = dictFind(src[j].dict,dictGetEntryKey(de));
-                    if (other) {
-                        value = src[j].weight * zunionInterDictValue(other);
+                    if (zuiFind(&src[j],&zval,&value)) {
+                        value *= src[j].weight;
                         zunionInterAggregate(&score,value,aggregate);
                     }
                 }
 
-                robj *o = dictGetEntryKey(de);
-                znode = zslInsert(dstzset->zsl,score,o);
-                incrRefCount(o); /* added to skiplist */
-                dictAdd(dstzset->dict,o,&znode->score);
-                incrRefCount(o); /* added to dictionary */
+                tmp = zuiObjectFromValue(&zval);
+                znode = zslInsert(dstzset->zsl,score,tmp);
+                incrRefCount(zval.ele); /* added to skiplist */
+                dictAdd(dstzset->dict,tmp,&znode->score);
+                incrRefCount(zval.ele); /* added to dictionary */
+
+                if (tmp->encoding == REDIS_ENCODING_RAW)
+                    if (sdslen(tmp->ptr) > maxelelen)
+                        maxelelen = sdslen(tmp->ptr);
             }
-            dictReleaseIterator(di);
         }
     } else {
-        /* unknown operator */
-        redisAssert(op == REDIS_OP_INTER || op == REDIS_OP_UNION);
+        redisPanic("Unknown operator");
     }
 
+    for (i = 0; i < setnum; i++)
+        zuiClearIterator(&src[i]);
+
     if (dbDelete(c->db,dstkey)) {
         signalModifiedKey(c->db,dstkey);
         touched = 1;
         server.dirty++;
     }
     if (dstzset->zsl->length) {
+        /* Convert to ziplist when in limits. */
+        if (dstzset->zsl->length <= server.zset_max_ziplist_entries &&
+            maxelelen <= server.zset_max_ziplist_value)
+                zsetConvert(dstobj,REDIS_ENCODING_ZIPLIST);
+
         dbAdd(c->db,dstkey,dstobj);
-        addReplyLongLong(c, dstzset->zsl->length);
+        addReplyLongLong(c,zsetLength(dstobj));
         if (!touched) signalModifiedKey(c->db,dstkey);
         server.dirty++;
     } else {
         decrRefCount(dstobj);
-        addReply(c, shared.czero);
+        addReply(c,shared.czero);
     }
     zfree(src);
 }
@@ -766,16 +1622,13 @@ void zinterstoreCommand(redisClient *c) {
 }
 
 void zrangeGenericCommand(redisClient *c, int reverse) {
-    robj *o;
+    robj *key = c->argv[1];
+    robj *zobj;
+    int withscores = 0;
     long start;
     long end;
-    int withscores = 0;
     int llen;
-    int rangelen, j;
-    zset *zsetobj;
-    zskiplist *zsl;
-    zskiplistNode *ln;
-    robj *ele;
+    int rangelen;
 
     if ((getLongFromObjectOrReply(c, c->argv[2], &start, NULL) != REDIS_OK) ||
         (getLongFromObjectOrReply(c, c->argv[3], &end, NULL) != REDIS_OK)) return;
@@ -787,13 +1640,11 @@ void zrangeGenericCommand(redisClient *c, int reverse) {
         return;
     }
 
-    if ((o = lookupKeyReadOrReply(c,c->argv[1],shared.emptymultibulk)) == NULL
-         || checkType(c,o,REDIS_ZSET)) return;
-    zsetobj = o->ptr;
-    zsl = zsetobj->zsl;
-    llen = zsl->length;
+    if ((zobj = lookupKeyReadOrReply(c,key,shared.emptymultibulk)) == NULL
+         || checkType(c,zobj,REDIS_ZSET)) return;
 
-    /* convert negative indexes */
+    /* Sanitize indexes. */
+    llen = zsetLength(zobj);
     if (start < 0) start = llen+start;
     if (end < 0) end = llen+end;
     if (start < 0) start = 0;
@@ -807,23 +1658,68 @@ void zrangeGenericCommand(redisClient *c, int reverse) {
     if (end >= llen) end = llen-1;
     rangelen = (end-start)+1;
 
-    /* check if starting point is trivial, before searching
-     * the element in log(N) time */
-    if (reverse) {
-        ln = start == 0 ? zsl->tail : zslistTypeGetElementByRank(zsl, llen-start);
-    } else {
-        ln = start == 0 ?
-            zsl->header->level[0].forward : zslistTypeGetElementByRank(zsl, start+1);
-    }
-
     /* Return the result in form of a multi-bulk reply */
-    addReplyMultiBulkLen(c,withscores ? (rangelen*2) : rangelen);
-    for (j = 0; j < rangelen; j++) {
-        ele = ln->obj;
-        addReplyBulk(c,ele);
-        if (withscores)
-            addReplyDouble(c,ln->score);
-        ln = reverse ? ln->backward : ln->level[0].forward;
+    addReplyMultiBulkLen(c, withscores ? (rangelen*2) : rangelen);
+
+    if (zobj->encoding == REDIS_ENCODING_ZIPLIST) {
+        unsigned char *zl = zobj->ptr;
+        unsigned char *eptr, *sptr;
+        unsigned char *vstr;
+        unsigned int vlen;
+        long long vlong;
+
+        if (reverse)
+            eptr = ziplistIndex(zl,-2-(2*start));
+        else
+            eptr = ziplistIndex(zl,2*start);
+
+        redisAssert(eptr != NULL);
+        sptr = ziplistNext(zl,eptr);
+
+        while (rangelen--) {
+            redisAssert(eptr != NULL && sptr != NULL);
+            redisAssert(ziplistGet(eptr,&vstr,&vlen,&vlong));
+            if (vstr == NULL)
+                addReplyBulkLongLong(c,vlong);
+            else
+                addReplyBulkCBuffer(c,vstr,vlen);
+
+            if (withscores)
+                addReplyDouble(c,zzlGetScore(sptr));
+
+            if (reverse)
+                zzlPrev(zl,&eptr,&sptr);
+            else
+                zzlNext(zl,&eptr,&sptr);
+        }
+
+    } else if (zobj->encoding == REDIS_ENCODING_SKIPLIST) {
+        zset *zs = zobj->ptr;
+        zskiplist *zsl = zs->zsl;
+        zskiplistNode *ln;
+        robj *ele;
+
+        /* Check if starting point is trivial, before doing log(N) lookup. */
+        if (reverse) {
+            ln = zsl->tail;
+            if (start > 0)
+                ln = zslGetElementByRank(zsl,llen-start);
+        } else {
+            ln = zsl->header->level[0].forward;
+            if (start > 0)
+                ln = zslGetElementByRank(zsl,start+1);
+        }
+
+        while(rangelen--) {
+            redisAssert(ln != NULL);
+            ele = ln->obj;
+            addReplyBulk(c,ele);
+            if (withscores)
+                addReplyDouble(c,ln->score);
+            ln = reverse ? ln->backward : ln->level[0].forward;
+        }
+    } else {
+        redisPanic("Unknown sorted set encoding");
     }
 }
 
@@ -839,17 +1735,24 @@ void zrevrangeCommand(redisClient *c) {
  * If "justcount", only the number of elements in the range is returned. */
 void genericZrangebyscoreCommand(redisClient *c, int reverse, int justcount) {
     zrangespec range;
-    robj *o, *emptyreply;
-    zset *zsetobj;
-    zskiplist *zsl;
-    zskiplistNode *ln;
+    robj *key = c->argv[1];
+    robj *emptyreply, *zobj;
     int offset = 0, limit = -1;
     int withscores = 0;
     unsigned long rangelen = 0;
     void *replylen = NULL;
+    int minidx, maxidx;
 
     /* Parse the range arguments. */
-    if (zslParseRange(c->argv[2],c->argv[3],&range) != REDIS_OK) {
+    if (reverse) {
+        /* Range is given as [max,min] */
+        maxidx = 2; minidx = 3;
+    } else {
+        /* Range is given as [min,max] */
+        minidx = 2; maxidx = 3;
+    }
+
+    if (zslParseRange(c->argv[minidx],c->argv[maxidx],&range) != REDIS_OK) {
         addReplyError(c,"min or max is not a double");
         return;
     }
@@ -877,101 +1780,132 @@ void genericZrangebyscoreCommand(redisClient *c, int reverse, int justcount) {
 
     /* Ok, lookup the key and get the range */
     emptyreply = justcount ? shared.czero : shared.emptymultibulk;
-    if ((o = lookupKeyReadOrReply(c,c->argv[1],emptyreply)) == NULL ||
-        checkType(c,o,REDIS_ZSET)) return;
-    zsetobj = o->ptr;
-    zsl = zsetobj->zsl;
+    if ((zobj = lookupKeyReadOrReply(c,key,emptyreply)) == NULL ||
+        checkType(c,zobj,REDIS_ZSET)) return;
+
+    if (zobj->encoding == REDIS_ENCODING_ZIPLIST) {
+        unsigned char *zl = zobj->ptr;
+        unsigned char *eptr, *sptr;
+        unsigned char *vstr;
+        unsigned int vlen;
+        long long vlong;
+        double score;
+
+        /* If reversed, get the last node in range as starting point. */
+        if (reverse)
+            eptr = zzlLastInRange(zl,range);
+        else
+            eptr = zzlFirstInRange(zl,range);
 
-    /* If reversed, assume the elements are sorted from high to low score. */
-    ln = zslFirstWithScore(zsl,range.min);
-    if (reverse) {
-        /* If range.min is out of range, ln will be NULL and we need to use
-         * the tail of the skiplist as first node of the range. */
-        if (ln == NULL) ln = zsl->tail;
-
-        /* zslFirstWithScore returns the first element with where with
-         * score >= range.min, so backtrack to make sure the element we use
-         * here has score <= range.min. */
-        while (ln && ln->score > range.min) ln = ln->backward;
-
-        /* Move to the right element according to the range spec. */
-        if (range.minex) {
-            /* Find last element with score < range.min */
-            while (ln && ln->score == range.min) ln = ln->backward;
-        } else {
-            /* Find last element with score <= range.min */
-            while (ln && ln->level[0].forward &&
-                         ln->level[0].forward->score == range.min)
-                ln = ln->level[0].forward;
-        }
-    } else {
-        if (range.minex) {
-            /* Find first element with score > range.min */
-            while (ln && ln->score == range.min) ln = ln->level[0].forward;
+        /* No "first" element in the specified interval. */
+        if (eptr == NULL) {
+            addReply(c,emptyreply);
+            return;
         }
-    }
 
-    /* No "first" element in the specified interval. */
-    if (ln == NULL) {
-        addReply(c,emptyreply);
-        return;
-    }
+        /* Get score pointer for the first element. */
+        redisAssert(eptr != NULL);
+        sptr = ziplistNext(zl,eptr);
+
+        /* We don't know in advance how many matching elements there are in the
+         * list, so we push this object that will represent the multi-bulk
+         * length in the output buffer, and will "fix" it later */
+        if (!justcount)
+            replylen = addDeferredMultiBulkLength(c);
+
+        /* If there is an offset, just traverse the number of elements without
+         * checking the score because that is done in the next loop. */
+        while (eptr && offset--)
+            if (reverse)
+                zzlPrev(zl,&eptr,&sptr);
+            else
+                zzlNext(zl,&eptr,&sptr);
+
+        while (eptr && limit--) {
+            score = zzlGetScore(sptr);
+
+            /* Abort when the node is no longer in range. */
+            if (reverse) {
+                if (!zslValueGteMin(score,&range)) break;
+            } else {
+                if (!zslValueLteMax(score,&range)) break;
+            }
 
-    /* We don't know in advance how many matching elements there
-     * are in the list, so we push this object that will represent
-     * the multi-bulk length in the output buffer, and will "fix"
-     * it later */
-    if (!justcount)
-        replylen = addDeferredMultiBulkLength(c);
+            /* Do our magic */
+            rangelen++;
+            if (!justcount) {
+                redisAssert(ziplistGet(eptr,&vstr,&vlen,&vlong));
+                if (vstr == NULL)
+                    addReplyBulkLongLong(c,vlong);
+                else
+                    addReplyBulkCBuffer(c,vstr,vlen);
+
+                if (withscores)
+                    addReplyDouble(c,score);
+            }
+
+            /* Move to next node */
+            if (reverse)
+                zzlPrev(zl,&eptr,&sptr);
+            else
+                zzlNext(zl,&eptr,&sptr);
+        }
+    } else if (zobj->encoding == REDIS_ENCODING_SKIPLIST) {
+        zset *zs = zobj->ptr;
+        zskiplist *zsl = zs->zsl;
+        zskiplistNode *ln;
 
-    /* If there is an offset, just traverse the number of elements without
-     * checking the score because that is done in the next loop. */
-    while(ln && offset--) {
+        /* If reversed, get the last node in range as starting point. */
         if (reverse)
-            ln = ln->backward;
+            ln = zslLastInRange(zsl,range);
         else
-            ln = ln->level[0].forward;
-    }
+            ln = zslFirstInRange(zsl,range);
 
-    while (ln && limit--) {
-        /* Check if this this element is in range. */
-        if (reverse) {
-            if (range.maxex) {
-                /* Element should have score > range.max */
-                if (ln->score <= range.max) break;
+        /* No "first" element in the specified interval. */
+        if (ln == NULL) {
+            addReply(c,emptyreply);
+            return;
+        }
+
+        /* We don't know in advance how many matching elements there are in the
+         * list, so we push this object that will represent the multi-bulk
+         * length in the output buffer, and will "fix" it later */
+        if (!justcount)
+            replylen = addDeferredMultiBulkLength(c);
+
+        /* If there is an offset, just traverse the number of elements without
+         * checking the score because that is done in the next loop. */
+        while (ln && offset--)
+            ln = reverse ? ln->backward : ln->level[0].forward;
+
+        while (ln && limit--) {
+            /* Abort when the node is no longer in range. */
+            if (reverse) {
+                if (!zslValueGteMin(ln->score,&range)) break;
             } else {
-                /* Element should have score >= range.max */
-                if (ln->score < range.max) break;
+                if (!zslValueLteMax(ln->score,&range)) break;
             }
-        } else {
-            if (range.maxex) {
-                /* Element should have score < range.max */
-                if (ln->score >= range.max) break;
-            } else {
-                /* Element should have score <= range.max */
-                if (ln->score > range.max) break;
+
+            /* Do our magic */
+            rangelen++;
+            if (!justcount) {
+                addReplyBulk(c,ln->obj);
+                if (withscores)
+                    addReplyDouble(c,ln->score);
             }
-        }
 
-        /* Do our magic */
-        rangelen++;
-        if (!justcount) {
-            addReplyBulk(c,ln->obj);
-            if (withscores)
-                addReplyDouble(c,ln->score);
+            /* Move to next node */
+            ln = reverse ? ln->backward : ln->level[0].forward;
         }
-
-        if (reverse)
-            ln = ln->backward;
-        else
-            ln = ln->level[0].forward;
+    } else {
+        redisPanic("Unknown sorted set encoding");
     }
 
     if (justcount) {
         addReplyLongLong(c,(long)rangelen);
     } else {
-        setDeferredMultiBulkLength(c,replylen,
-             withscores ? (rangelen*2) : rangelen);
+        if (withscores) rangelen *= 2;
+        setDeferredMultiBulkLength(c,replylen,rangelen);
     }
 }
 
@@ -988,66 +1922,103 @@ void zcountCommand(redisClient *c) {
 }
 
 void zcardCommand(redisClient *c) {
-    robj *o;
-    zset *zs;
+    robj *key = c->argv[1];
+    robj *zobj;
 
-    if ((o = lookupKeyReadOrReply(c,c->argv[1],shared.czero)) == NULL ||
-        checkType(c,o,REDIS_ZSET)) return;
+    if ((zobj = lookupKeyReadOrReply(c,key,shared.czero)) == NULL ||
+        checkType(c,zobj,REDIS_ZSET)) return;
 
-    zs = o->ptr;
-    addReplyLongLong(c,zs->zsl->length);
+    addReplyLongLong(c,zsetLength(zobj));
 }
 
 void zscoreCommand(redisClient *c) {
-    robj *o;
-    zset *zs;
-    dictEntry *de;
+    robj *key = c->argv[1];
+    robj *zobj;
+    double score;
 
-    if ((o = lookupKeyReadOrReply(c,c->argv[1],shared.nullbulk)) == NULL ||
-        checkType(c,o,REDIS_ZSET)) return;
+    if ((zobj = lookupKeyReadOrReply(c,key,shared.nullbulk)) == NULL ||
+        checkType(c,zobj,REDIS_ZSET)) return;
 
-    zs = o->ptr;
-    c->argv[2] = tryObjectEncoding(c->argv[2]);
-    de = dictFind(zs->dict,c->argv[2]);
-    if (!de) {
-        addReply(c,shared.nullbulk);
-    } else {
-        double *score = dictGetEntryVal(de);
+    if (zobj->encoding == REDIS_ENCODING_ZIPLIST) {
+        if (zzlFind(zobj->ptr,c->argv[2],&score) != NULL)
+            addReplyDouble(c,score);
+        else
+            addReply(c,shared.nullbulk);
+    } else if (zobj->encoding == REDIS_ENCODING_SKIPLIST) {
+        zset *zs = zobj->ptr;
+        dictEntry *de;
 
-        addReplyDouble(c,*score);
+        c->argv[2] = tryObjectEncoding(c->argv[2]);
+        de = dictFind(zs->dict,c->argv[2]);
+        if (de != NULL) {
+            score = *(double*)dictGetEntryVal(de);
+            addReplyDouble(c,score);
+        } else {
+            addReply(c,shared.nullbulk);
+        }
+    } else {
+        redisPanic("Unknown sorted set encoding");
     }
 }
 
 void zrankGenericCommand(redisClient *c, int reverse) {
-    robj *o;
-    zset *zs;
-    zskiplist *zsl;
-    dictEntry *de;
+    robj *key = c->argv[1];
+    robj *ele = c->argv[2];
+    robj *zobj;
+    unsigned long llen;
     unsigned long rank;
-    double *score;
 
-    if ((o = lookupKeyReadOrReply(c,c->argv[1],shared.nullbulk)) == NULL ||
-        checkType(c,o,REDIS_ZSET)) return;
+    if ((zobj = lookupKeyReadOrReply(c,key,shared.nullbulk)) == NULL ||
+        checkType(c,zobj,REDIS_ZSET)) return;
+    llen = zsetLength(zobj);
+
+    redisAssert(ele->encoding == REDIS_ENCODING_RAW);
+    if (zobj->encoding == REDIS_ENCODING_ZIPLIST) {
+        unsigned char *zl = zobj->ptr;
+        unsigned char *eptr, *sptr;
+
+        eptr = ziplistIndex(zl,0);
+        redisAssert(eptr != NULL);
+        sptr = ziplistNext(zl,eptr);
+        redisAssert(sptr != NULL);
+
+        rank = 1;
+        while(eptr != NULL) {
+            if (ziplistCompare(eptr,ele->ptr,sdslen(ele->ptr)))
+                break;
+            rank++;
+            zzlNext(zl,&eptr,&sptr);
+        }
 
-    zs = o->ptr;
-    zsl = zs->zsl;
-    c->argv[2] = tryObjectEncoding(c->argv[2]);
-    de = dictFind(zs->dict,c->argv[2]);
-    if (!de) {
-        addReply(c,shared.nullbulk);
-        return;
-    }
+        if (eptr != NULL) {
+            if (reverse)
+                addReplyLongLong(c,llen-rank);
+            else
+                addReplyLongLong(c,rank-1);
+        } else {
+            addReply(c,shared.nullbulk);
+        }
+    } else if (zobj->encoding == REDIS_ENCODING_SKIPLIST) {
+        zset *zs = zobj->ptr;
+        zskiplist *zsl = zs->zsl;
+        dictEntry *de;
+        double score;
 
-    score = dictGetEntryVal(de);
-    rank = zslistTypeGetRank(zsl, *score, c->argv[2]);
-    if (rank) {
-        if (reverse) {
-            addReplyLongLong(c, zsl->length - rank);
+        ele = c->argv[2] = tryObjectEncoding(c->argv[2]);
+        de = dictFind(zs->dict,ele);
+        if (de != NULL) {
+            score = *(double*)dictGetEntryVal(de);
+            rank = zslGetRank(zsl,score,ele);
+            redisAssert(rank); /* Existing elements always have a rank. */
+            if (reverse)
+                addReplyLongLong(c,llen-rank);
+            else
+                addReplyLongLong(c,rank-1);
         } else {
-            addReplyLongLong(c, rank-1);
+            addReply(c,shared.nullbulk);
         }
     } else {
-        addReply(c,shared.nullbulk);
+        redisPanic("Unknown sorted set encoding");
     }
 }
 