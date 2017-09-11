@@ -810,11 +810,29 @@ void zaddGenericCommand(redisClient *c, int incr) {
     robj *ele;
     robj *zobj;
     robj *curobj;
-    double score, curscore = 0.0;
+    double score = 0, *scores, curscore = 0.0;
+    int j, elements = (c->argc-2)/2;
+    int added = 0;
 
-    if (getDoubleFromObjectOrReply(c,c->argv[2],&score,NULL) != REDIS_OK)
+    if (c->argc % 2) {
+        addReply(c,shared.syntaxerr);
         return;
+    }
+
+    /* Start parsing all the scores, we need to emit any syntax error
+     * before executing additions to the sorted set, as the command should
+     * either execute fully or nothing at all. */
+    scores = zmalloc(sizeof(double)*elements);
+    for (j = 0; j < elements; j++) {
+        if (getDoubleFromObjectOrReply(c,c->argv[2+j*2],&scores[j],NULL)
+            != REDIS_OK)
+        {
+            zfree(scores);
+            return;
+        }
+    }
 
+    /* Lookup the key and create the sorted set if does not exist. */
     zobj = lookupKeyWrite(c->db,key);
     if (zobj == NULL) {
         if (server.zset_max_ziplist_entries == 0 ||
@@ -828,111 +846,105 @@ void zaddGenericCommand(redisClient *c, int incr) {
     } else {
         if (zobj->type != REDIS_ZSET) {
             addReply(c,shared.wrongtypeerr);
+            zfree(scores);
             return;
         }
     }
 
-    if (zobj->encoding == REDIS_ENCODING_ZIPLIST) {
-        unsigned char *eptr;
+    for (j = 0; j < elements; j++) {
+        score = scores[j];
 
-        /* Prefer non-encoded element when dealing with ziplists. */
-        ele = c->argv[3];
-        if ((eptr = zzlFind(zobj->ptr,ele,&curscore)) != NULL) {
-            if (incr) {
-                score += curscore;
-                if (isnan(score)) {
-                    addReplyError(c,nanerr);
-                    /* Don't need to check if the sorted set is empty, because
-                     * we know it has at least one element. */
-                    return;
+        if (zobj->encoding == REDIS_ENCODING_ZIPLIST) {
+            unsigned char *eptr;
+
+            /* Prefer non-encoded element when dealing with ziplists. */
+            ele = c->argv[3+j*2];
+            if ((eptr = zzlFind(zobj->ptr,ele,&curscore)) != NULL) {
+                if (incr) {
+                    score += curscore;
+                    if (isnan(score)) {
+                        addReplyError(c,nanerr);
+                        /* Don't need to check if the sorted set is empty
+                         * because we know it has at least one element. */
+                        zfree(scores);
+                        return;
+                    }
                 }
-            }
 
-            /* Remove and re-insert when score changed. */
-            if (score != curscore) {
-                zobj->ptr = zzlDelete(zobj->ptr,eptr);
+                /* Remove and re-insert when score changed. */
+                if (score != curscore) {
+                    zobj->ptr = zzlDelete(zobj->ptr,eptr);
+                    zobj->ptr = zzlInsert(zobj->ptr,ele,score);
+
+                    signalModifiedKey(c->db,key);
+                    server.dirty++;
+                }
+            } else {
+                /* Optimize: check if the element is too large or the list
+                 * becomes too long *before* executing zzlInsert. */
                 zobj->ptr = zzlInsert(zobj->ptr,ele,score);
+                if (zzlLength(zobj->ptr) > server.zset_max_ziplist_entries)
+                    zsetConvert(zobj,REDIS_ENCODING_SKIPLIST);
+                if (sdslen(ele->ptr) > server.zset_max_ziplist_value)
+                    zsetConvert(zobj,REDIS_ENCODING_SKIPLIST);
 
                 signalModifiedKey(c->db,key);
                 server.dirty++;
+                if (!incr) added++;
             }
+        } else if (zobj->encoding == REDIS_ENCODING_SKIPLIST) {
+            zset *zs = zobj->ptr;
+            zskiplistNode *znode;
+            dictEntry *de;
 
-            if (incr) /* ZINCRBY */
-                addReplyDouble(c,score);
-            else /* ZADD */
-                addReply(c,shared.czero);
-        } else {
-            /* Optimize: check if the element is too large or the list becomes
-             * too long *before* executing zzlInsert. */
-            zobj->ptr = zzlInsert(zobj->ptr,ele,score);
-            if (zzlLength(zobj->ptr) > server.zset_max_ziplist_entries)
-                zsetConvert(zobj,REDIS_ENCODING_SKIPLIST);
-            if (sdslen(ele->ptr) > server.zset_max_ziplist_value)
-                zsetConvert(zobj,REDIS_ENCODING_SKIPLIST);
-
-            signalModifiedKey(c->db,key);
-            server.dirty++;
-
-            if (incr) /* ZINCRBY */
-                addReplyDouble(c,score);
-            else /* ZADD */
-                addReply(c,shared.cone);
-        }
-    } else if (zobj->encoding == REDIS_ENCODING_SKIPLIST) {
-        zset *zs = zobj->ptr;
-        zskiplistNode *znode;
-        dictEntry *de;
-
-        ele = c->argv[3] = tryObjectEncoding(c->argv[3]);
-        de = dictFind(zs->dict,ele);
-        if (de != NULL) {
-            curobj = dictGetEntryKey(de);
-            curscore = *(double*)dictGetEntryVal(de);
-
-            if (incr) {
-                score += curscore;
-                if (isnan(score)) {
-                    addReplyError(c,nanerr);
-                    /* Don't need to check if the sorted set is empty, because
-                     * we know it has at least one element. */
-                    return;
+            ele = c->argv[3+j*2] = tryObjectEncoding(c->argv[3+j*2]);
+            de = dictFind(zs->dict,ele);
+            if (de != NULL) {
+                curobj = dictGetEntryKey(de);
+                curscore = *(double*)dictGetEntryVal(de);
+
+                if (incr) {
+                    score += curscore;
+                    if (isnan(score)) {
+                        addReplyError(c,nanerr);
+                        /* Don't need to check if the sorted set is empty
+                         * because we know it has at least one element. */
+                        zfree(scores);
+                        return;
+                    }
                 }
-            }
 
-            /* Remove and re-insert when score changed. We can safely delete
-             * the key object from the skiplist, since the dictionary still has
-             * a reference to it. */
-            if (score != curscore) {
-                redisAssert(zslDelete(zs->zsl,curscore,curobj));
-                znode = zslInsert(zs->zsl,score,curobj);
-                incrRefCount(curobj); /* Re-inserted in skiplist. */
-                dictGetEntryVal(de) = &znode->score; /* Update score ptr. */
+                /* Remove and re-insert when score changed. We can safely
+                 * delete the key object from the skiplist, since the
+                 * dictionary still has a reference to it. */
+                if (score != curscore) {
+                    redisAssert(zslDelete(zs->zsl,curscore,curobj));
+                    znode = zslInsert(zs->zsl,score,curobj);
+                    incrRefCount(curobj); /* Re-inserted in skiplist. */
+                    dictGetEntryVal(de) = &znode->score; /* Update score ptr. */
+
+                    signalModifiedKey(c->db,key);
+                    server.dirty++;
+                }
+            } else {
+                znode = zslInsert(zs->zsl,score,ele);
+                incrRefCount(ele); /* Inserted in skiplist. */
+                redisAssert(dictAdd(zs->dict,ele,&znode->score) == DICT_OK);
+                incrRefCount(ele); /* Added to dictionary. */
 
                 signalModifiedKey(c->db,key);
                 server.dirty++;
+                if (!incr) added++;
             }
-
-            if (incr) /* ZINCRBY */
-                addReplyDouble(c,score);
-            else /* ZADD */
-                addReply(c,shared.czero);
         } else {
-            znode = zslInsert(zs->zsl,score,ele);
-            incrRefCount(ele); /* Inserted in skiplist. */
-            redisAssert(dictAdd(zs->dict,ele,&znode->score) == DICT_OK);
-            incrRefCount(ele); /* Added to dictionary. */
-
-            signalModifiedKey(c->db,key);
-            server.dirty++;
-
-            if (incr) /* ZINCRBY */
-                addReplyDouble(c,score);
-            else /* ZADD */
-                addReply(c,shared.cone);
+            redisPanic("Unknown sorted set encoding");
         }
-    } else {
-        redisPanic("Unknown sorted set encoding");
     }
+    zfree(scores);
+    if (incr) /* ZINCRBY */
+        addReplyDouble(c,score);
+    else /* ZADD */
+        addReplyLongLong(c,added);
 }
 
 void zaddCommand(redisClient *c) {