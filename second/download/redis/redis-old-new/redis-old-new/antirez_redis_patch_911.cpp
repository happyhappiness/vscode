@@ -431,6 +431,158 @@ static int zslParseRange(robj *min, robj *max, zrangespec *spec) {
     return REDIS_OK;
 }
 
+/* ------------------------ Lexicographic ranges ---------------------------- */
+
+/* Parse max or min argument of ZRANGEBYLEX.
+  * (foo means foo (open interval)
+  * [foo means foo (closed interval)
+  * - means the min string possible
+  * + means the max string possible
+  *
+  * If the string is valid the *dest pointer is set to the redis object
+  * that will be used for the comparision, and ex will be set to 0 or 1
+  * respectively if the item is exclusive or inclusive. REDIS_OK will be
+  * returned.
+  *
+  * If the stirng is not a valid range REDIS_ERR is returned, and the value
+  * of *dest and *ex is undefined. */
+int zslParseLexRangeItem(robj *item, robj **dest, int *ex) {
+    char *c = item->ptr;
+
+    switch(c[0]) {
+    case '+':
+        if (c[1] != '\0') return REDIS_ERR;
+        *ex = 0;
+        *dest = shared.maxstring;
+        incrRefCount(shared.maxstring);
+        return REDIS_OK;
+    case '-':
+        if (c[1] != '\0') return REDIS_ERR;
+        *ex = 0;
+        *dest = shared.minstring;
+        incrRefCount(shared.minstring);
+        return REDIS_OK;
+    case '(':
+        *ex = 1;
+        *dest = createStringObject(c+1,sdslen(c)-1);
+        return REDIS_OK;
+    case '[':
+        *ex = 0;
+        *dest = createStringObject(c+1,sdslen(c)-1);
+        return REDIS_OK;
+    default:
+        return REDIS_ERR;
+    }
+}
+
+/* Populate the rangespec according to the objects min and max. */
+static int zslParseLexRange(robj *min, robj *max, zlexrangespec *spec) {
+    if (min->encoding == REDIS_ENCODING_INT ||
+        max->encoding == REDIS_ENCODING_INT) return REDIS_ERR;
+
+    spec->min = spec->max = NULL;
+    if (zslParseLexRangeItem(min, &spec->min, &spec->minex) == REDIS_ERR ||
+        zslParseLexRangeItem(max, &spec->max, &spec->maxex) == REDIS_ERR) {
+        if (spec->min) decrRefCount(spec->min);
+        if (spec->max) decrRefCount(spec->max);
+        return REDIS_ERR;
+    } else {
+        return REDIS_OK;
+    }
+}
+
+/* This is just a wrapper to compareStringObjects() that is able to
+ * handle shared.minstring and shared.maxstring as the equivalent of
+ * -inf and +inf for strings */
+int compareStringObjectsForLexRange(robj *a, robj *b) {
+    if (a == b) return 0; /* This makes sure that we handle inf,inf and
+                             -inf,-inf ASAP. One special case less. */
+    if (a == shared.minstring || b == shared.maxstring) return -1;
+    if (a == shared.maxstring || b == shared.minstring) return 1;
+    return compareStringObjects(a,b);
+}
+
+static int zslLexValueGteMin(robj *value, zlexrangespec *spec) {
+    return spec->minex ?
+        (compareStringObjectsForLexRange(value,spec->min) > 0) :
+        (compareStringObjectsForLexRange(value,spec->min) >= 0);
+}
+
+static int zslLexValueLteMax(robj *value, zlexrangespec *spec) {
+    return spec->maxex ?
+        (compareStringObjectsForLexRange(value,spec->max) < 0) :
+        (compareStringObjectsForLexRange(value,spec->max) <= 0);
+}
+
+/* Returns if there is a part of the zset is in the lex range. */
+int zslIsInLexRange(zskiplist *zsl, zlexrangespec *range) {
+    zskiplistNode *x;
+
+    /* Test for ranges that will always be empty. */
+    if (compareStringObjectsForLexRange(range->min,range->max) > 1 ||
+            (compareStringObjects(range->min,range->max) == 0 &&
+            (range->minex || range->maxex)))
+        return 0;
+    x = zsl->tail;
+    if (x == NULL || !zslLexValueGteMin(x->obj,range))
+        return 0;
+    x = zsl->header->level[0].forward;
+    if (x == NULL || !zslLexValueLteMax(x->obj,range))
+        return 0;
+    return 1;
+}
+
+/* Find the first node that is contained in the specified lex range.
+ * Returns NULL when no element is contained in the range. */
+zskiplistNode *zslFirstInLexRange(zskiplist *zsl, zlexrangespec range) {
+    zskiplistNode *x;
+    int i;
+
+    /* If everything is out of range, return early. */
+    if (!zslIsInLexRange(zsl,&range)) return NULL;
+
+    x = zsl->header;
+    for (i = zsl->level-1; i >= 0; i--) {
+        /* Go forward while *OUT* of range. */
+        while (x->level[i].forward &&
+            !zslLexValueGteMin(x->level[i].forward->obj,&range))
+                x = x->level[i].forward;
+    }
+
+    /* This is an inner range, so the next node cannot be NULL. */
+    x = x->level[0].forward;
+    redisAssert(x != NULL);
+
+    /* Check if score <= max. */
+    if (!zslLexValueLteMax(x->obj,&range)) return NULL;
+    return x;
+}
+
+/* Find the last node that is contained in the specified range.
+ * Returns NULL when no element is contained in the range. */
+zskiplistNode *zslLastInLexRange(zskiplist *zsl, zlexrangespec range) {
+    zskiplistNode *x;
+    int i;
+
+    /* If everything is out of range, return early. */
+    if (!zslIsInLexRange(zsl,&range)) return NULL;
+
+    x = zsl->header;
+    for (i = zsl->level-1; i >= 0; i--) {
+        /* Go forward while *IN* range. */
+        while (x->level[i].forward &&
+            zslLexValueLteMax(x->level[i].forward->obj,&range))
+                x = x->level[i].forward;
+    }
+
+    /* This is an inner range, so this node cannot be NULL. */
+    redisAssert(x != NULL);
+
+    /* Check if score >= min. */
+    if (!zslLexValueGteMin(x->obj,&range)) return NULL;
+    return x;
+}
+
 /*-----------------------------------------------------------------------------
  * Ziplist-backed sorted set API
  *----------------------------------------------------------------------------*/
@@ -456,6 +608,24 @@ double zzlGetScore(unsigned char *sptr) {
     return score;
 }
 
+/* Return a ziplist element as a Redis string object.
+ * This simple abstraction can be used to simplifies some code at the
+ * cost of some performance. */
+robj *ziplistGetObject(unsigned char *sptr) {
+    unsigned char *vstr;
+    unsigned int vlen;
+    long long vlong;
+
+    redisAssert(sptr != NULL);
+    redisAssert(ziplistGet(sptr,&vstr,&vlen,&vlong));
+
+    if (vstr) {
+        return createStringObject((char*)vstr,vlen);
+    } else {
+        return createStringObjectFromLongLong(vlong);
+    }
+}
+
 /* Compare element in sorted set with given element. */
 int zzlCompareElements(unsigned char *eptr, unsigned char *cstr, unsigned int clen) {
     unsigned char *vstr;
@@ -606,6 +776,97 @@ unsigned char *zzlLastInRange(unsigned char *zl, zrangespec range) {
     return NULL;
 }
 
+static int zzlLexValueGteMin(unsigned char *p, zlexrangespec *spec) {
+    robj *value = ziplistGetObject(p);
+    int res = zslLexValueGteMin(value,spec);
+    decrRefCount(value);
+    return res;
+}
+
+static int zzlLexValueLteMax(unsigned char *p, zlexrangespec *spec) {
+    robj *value = ziplistGetObject(p);
+    int res = zslLexValueLteMax(value,spec);
+    decrRefCount(value);
+    return res;
+}
+
+/* Returns if there is a part of the zset is in range. Should only be used
+ * internally by zzlFirstInRange and zzlLastInRange. */
+int zzlIsInLexRange(unsigned char *zl, zlexrangespec *range) {
+    unsigned char *p;
+
+    /* Test for ranges that will always be empty. */
+    if (compareStringObjectsForLexRange(range->min,range->max) > 1 ||
+            (compareStringObjects(range->min,range->max) == 0 &&
+            (range->minex || range->maxex)))
+        return 0;
+
+    p = ziplistIndex(zl,-2); /* Last element. */
+    if (p == NULL) return 0;
+    if (!zzlLexValueGteMin(p,range))
+        return 0;
+
+    p = ziplistIndex(zl,0); /* First element. */
+    redisAssert(p != NULL);
+    if (!zzlLexValueLteMax(p,range))
+        return 0;
+
+    return 1;
+}
+
+/* Find pointer to the first element contained in the specified lex range.
+ * Returns NULL when no element is contained in the range. */
+unsigned char *zzlFirstInLexRange(unsigned char *zl, zlexrangespec range) {
+    unsigned char *eptr = ziplistIndex(zl,0), *sptr;
+
+    /* If everything is out of range, return early. */
+    if (!zzlIsInLexRange(zl,&range)) return NULL;
+
+    while (eptr != NULL) {
+        if (zzlLexValueGteMin(eptr,&range)) {
+            /* Check if score <= max. */
+            if (zzlLexValueLteMax(eptr,&range))
+                return eptr;
+            return NULL;
+        }
+
+        /* Move to next element. */
+        sptr = ziplistNext(zl,eptr); /* This element score. Skip it. */
+        redisAssert(sptr != NULL);
+        eptr = ziplistNext(zl,sptr); /* Next element. */
+    }
+
+    return NULL;
+}
+
+/* Find pointer to the last element contained in the specified lex range.
+ * Returns NULL when no element is contained in the range. */
+unsigned char *zzlLastInLexRange(unsigned char *zl, zlexrangespec range) {
+    unsigned char *eptr = ziplistIndex(zl,-2), *sptr;
+
+    /* If everything is out of range, return early. */
+    if (!zzlIsInLexRange(zl,&range)) return NULL;
+
+    while (eptr != NULL) {
+        if (zzlLexValueLteMax(eptr,&range)) {
+            /* Check if score >= min. */
+            if (zzlLexValueGteMin(eptr,&range))
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
 unsigned char *zzlFind(unsigned char *zl, robj *ele, double *score) {
     unsigned char *eptr = ziplistIndex(zl,0), *sptr;
 
@@ -2098,6 +2359,183 @@ void zcountCommand(redisClient *c) {
     addReplyLongLong(c, count);
 }
 
+/* This command implements ZRANGEBYLEX, ZREVRANGEBYLEX. */
+void genericZrangebylexCommand(redisClient *c, int reverse) {
+    zlexrangespec range;
+    robj *key = c->argv[1];
+    robj *zobj;
+    long offset = 0, limit = -1;
+    unsigned long rangelen = 0;
+    void *replylen = NULL;
+    int minidx, maxidx;
+
+    /* Parse the range arguments. */
+    if (reverse) {
+        /* Range is given as [max,min] */
+        maxidx = 2; minidx = 3;
+    } else {
+        /* Range is given as [min,max] */
+        minidx = 2; maxidx = 3;
+    }
+
+    if (zslParseLexRange(c->argv[minidx],c->argv[maxidx],&range) != REDIS_OK) {
+        addReplyError(c,"min or max not valid string range item");
+        return;
+    }
+
+    /* Parse optional extra arguments. Note that ZCOUNT will exactly have
+     * 4 arguments, so we'll never enter the following code path. */
+    if (c->argc > 4) {
+        int remaining = c->argc - 4;
+        int pos = 4;
+
+        while (remaining) {
+            if (remaining >= 3 && !strcasecmp(c->argv[pos]->ptr,"limit")) {
+                if ((getLongFromObjectOrReply(c, c->argv[pos+1], &offset, NULL) != REDIS_OK) ||
+                    (getLongFromObjectOrReply(c, c->argv[pos+2], &limit, NULL) != REDIS_OK)) return;
+                pos += 3; remaining -= 3;
+            } else {
+                addReply(c,shared.syntaxerr);
+                return;
+            }
+        }
+    }
+
+    /* Ok, lookup the key and get the range */
+    if ((zobj = lookupKeyReadOrReply(c,key,shared.emptymultibulk)) == NULL ||
+        checkType(c,zobj,REDIS_ZSET)) return;
+
+    if (zobj->encoding == REDIS_ENCODING_ZIPLIST) {
+        unsigned char *zl = zobj->ptr;
+        unsigned char *eptr, *sptr;
+        unsigned char *vstr;
+        unsigned int vlen;
+        long long vlong;
+
+        /* If reversed, get the last node in range as starting point. */
+        if (reverse) {
+            eptr = zzlLastInLexRange(zl,range);
+        } else {
+            eptr = zzlFirstInLexRange(zl,range);
+        }
+
+        /* No "first" element in the specified interval. */
+        if (eptr == NULL) {
+            addReply(c, shared.emptymultibulk);
+            return;
+        }
+
+        /* Get score pointer for the first element. */
+        redisAssertWithInfo(c,zobj,eptr != NULL);
+        sptr = ziplistNext(zl,eptr);
+
+        /* We don't know in advance how many matching elements there are in the
+         * list, so we push this object that will represent the multi-bulk
+         * length in the output buffer, and will "fix" it later */
+        replylen = addDeferredMultiBulkLength(c);
+
+        /* If there is an offset, just traverse the number of elements without
+         * checking the score because that is done in the next loop. */
+        while (eptr && offset--) {
+            if (reverse) {
+                zzlPrev(zl,&eptr,&sptr);
+            } else {
+                zzlNext(zl,&eptr,&sptr);
+            }
+        }
+
+        while (eptr && limit--) {
+            /* Abort when the node is no longer in range. */
+            if (reverse) {
+                if (!zzlLexValueGteMin(eptr,&range)) break;
+            } else {
+                if (!zzlLexValueLteMax(eptr,&range)) break;
+            }
+
+            /* We know the element exists, so ziplistGet should always
+             * succeed. */
+            redisAssertWithInfo(c,zobj,ziplistGet(eptr,&vstr,&vlen,&vlong));
+
+            rangelen++;
+            if (vstr == NULL) {
+                addReplyBulkLongLong(c,vlong);
+            } else {
+                addReplyBulkCBuffer(c,vstr,vlen);
+            }
+
+            /* Move to next node */
+            if (reverse) {
+                zzlPrev(zl,&eptr,&sptr);
+            } else {
+                zzlNext(zl,&eptr,&sptr);
+            }
+        }
+    } else if (zobj->encoding == REDIS_ENCODING_SKIPLIST) {
+        zset *zs = zobj->ptr;
+        zskiplist *zsl = zs->zsl;
+        zskiplistNode *ln;
+
+        /* If reversed, get the last node in range as starting point. */
+        if (reverse) {
+            ln = zslLastInLexRange(zsl,range);
+        } else {
+            ln = zslFirstInLexRange(zsl,range);
+        }
+
+        /* No "first" element in the specified interval. */
+        if (ln == NULL) {
+            addReply(c, shared.emptymultibulk);
+            return;
+        }
+
+        /* We don't know in advance how many matching elements there are in the
+         * list, so we push this object that will represent the multi-bulk
+         * length in the output buffer, and will "fix" it later */
+        replylen = addDeferredMultiBulkLength(c);
+
+        /* If there is an offset, just traverse the number of elements without
+         * checking the score because that is done in the next loop. */
+        while (ln && offset--) {
+            if (reverse) {
+                ln = ln->backward;
+            } else {
+                ln = ln->level[0].forward;
+            }
+        }
+
+        while (ln && limit--) {
+            /* Abort when the node is no longer in range. */
+            if (reverse) {
+                if (!zslLexValueGteMin(ln->obj,&range)) break;
+            } else {
+                if (!zslLexValueLteMax(ln->obj,&range)) break;
+            }
+
+            rangelen++;
+            addReplyBulk(c,ln->obj);
+
+            /* Move to next node */
+            if (reverse) {
+                ln = ln->backward;
+            } else {
+                ln = ln->level[0].forward;
+            }
+        }
+    } else {
+        redisPanic("Unknown sorted set encoding");
+    }
+
+    setDeferredMultiBulkLength(c, replylen, rangelen);
+}
+
+void zrangebylexCommand(redisClient *c) {
+    genericZrangebylexCommand(c,0);
+}
+
+void zrevrangebylexCommand(redisClient *c) {
+    genericZrangebylexCommand(c,1);
+}
+
 void zcardCommand(redisClient *c) {
     robj *key = c->argv[1];
     robj *zobj;