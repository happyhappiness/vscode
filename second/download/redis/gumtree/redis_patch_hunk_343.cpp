         redisPanic("Unknown sorted set encoding");
     }
 
     addReplyLongLong(c, count);
 }
 
+void zlexcountCommand(redisClient *c) {
+    robj *key = c->argv[1];
+    robj *zobj;
+    zlexrangespec range;
+    int count = 0;
+
+    /* Parse the range arguments */
+    if (zslParseLexRange(c->argv[2],c->argv[3],&range) != REDIS_OK) {
+        addReplyError(c,"min or max not valid string range item");
+        return;
+    }
+
+    /* Lookup the sorted set */
+    if ((zobj = lookupKeyReadOrReply(c, key, shared.czero)) == NULL ||
+        checkType(c, zobj, REDIS_ZSET))
+    {
+        zslFreeLexRange(&range);
+        return;
+    }
+
+    if (zobj->encoding == REDIS_ENCODING_ZIPLIST) {
+        unsigned char *zl = zobj->ptr;
+        unsigned char *eptr, *sptr;
+
+        /* Use the first element in range as the starting point */
+        eptr = zzlFirstInLexRange(zl,&range);
+
+        /* No "first" element */
+        if (eptr == NULL) {
+            zslFreeLexRange(&range);
+            addReply(c, shared.czero);
+            return;
+        }
+
+        /* First element is in range */
+        sptr = ziplistNext(zl,eptr);
+        redisAssertWithInfo(c,zobj,zzlLexValueLteMax(eptr,&range));
+
+        /* Iterate over elements in range */
+        while (eptr) {
+            /* Abort when the node is no longer in range. */
+            if (!zzlLexValueLteMax(eptr,&range)) {
+                break;
+            } else {
+                count++;
+                zzlNext(zl,&eptr,&sptr);
+            }
+        }
+    } else if (zobj->encoding == REDIS_ENCODING_SKIPLIST) {
+        zset *zs = zobj->ptr;
+        zskiplist *zsl = zs->zsl;
+        zskiplistNode *zn;
+        unsigned long rank;
+
+        /* Find first element in range */
+        zn = zslFirstInLexRange(zsl, &range);
+
+        /* Use rank of first element, if any, to determine preliminary count */
+        if (zn != NULL) {
+            rank = zslGetRank(zsl, zn->score, zn->obj);
+            count = (zsl->length - (rank - 1));
+
+            /* Find last element in range */
+            zn = zslLastInLexRange(zsl, &range);
+
+            /* Use rank of last element, if any, to determine the actual count */
+            if (zn != NULL) {
+                rank = zslGetRank(zsl, zn->score, zn->obj);
+                count -= (zsl->length - rank);
+            }
+        }
+    } else {
+        redisPanic("Unknown sorted set encoding");
+    }
+
+    zslFreeLexRange(&range);
+    addReplyLongLong(c, count);
+}
+
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
+                zslFreeLexRange(&range);
+                addReply(c,shared.syntaxerr);
+                return;
+            }
+        }
+    }
+
+    /* Ok, lookup the key and get the range */
+    if ((zobj = lookupKeyReadOrReply(c,key,shared.emptymultibulk)) == NULL ||
+        checkType(c,zobj,REDIS_ZSET))
+    {
+        zslFreeLexRange(&range);
+        return;
+    }
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
+            eptr = zzlLastInLexRange(zl,&range);
+        } else {
+            eptr = zzlFirstInLexRange(zl,&range);
+        }
+
+        /* No "first" element in the specified interval. */
+        if (eptr == NULL) {
+            addReply(c, shared.emptymultibulk);
+            zslFreeLexRange(&range);
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
+            ln = zslLastInLexRange(zsl,&range);
+        } else {
+            ln = zslFirstInLexRange(zsl,&range);
+        }
+
+        /* No "first" element in the specified interval. */
+        if (ln == NULL) {
+            addReply(c, shared.emptymultibulk);
+            zslFreeLexRange(&range);
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
+    zslFreeLexRange(&range);
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
 
     if ((zobj = lookupKeyReadOrReply(c,key,shared.czero)) == NULL ||
         checkType(c,zobj,REDIS_ZSET)) return;
