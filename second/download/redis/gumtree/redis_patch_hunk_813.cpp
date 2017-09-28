             addReply(c,shared.wrongtypeerr);
             goto cleanup;
         }
     }
 
     for (j = 0; j < elements; j++) {
+        double newscore;
         score = scores[j];
+        int retflags = flags;
 
-        if (zobj->encoding == OBJ_ENCODING_ZIPLIST) {
-            unsigned char *eptr;
-
-            /* Prefer non-encoded element when dealing with ziplists. */
-            ele = c->argv[scoreidx+1+j*2];
-            if ((eptr = zzlFind(zobj->ptr,ele,&curscore)) != NULL) {
-                if (nx) continue;
-                if (incr) {
-                    score += curscore;
-                    if (isnan(score)) {
-                        addReplyError(c,nanerr);
-                        goto cleanup;
-                    }
-                }
-
-                /* Remove and re-insert when score changed. */
-                if (score != curscore) {
-                    zobj->ptr = zzlDelete(zobj->ptr,eptr);
-                    zobj->ptr = zzlInsert(zobj->ptr,ele,score);
-                    server.dirty++;
-                    updated++;
-                }
-                processed++;
-            } else if (!xx) {
-                /* Optimize: check if the element is too large or the list
-                 * becomes too long *before* executing zzlInsert. */
-                zobj->ptr = zzlInsert(zobj->ptr,ele,score);
-                if (zzlLength(zobj->ptr) > server.zset_max_ziplist_entries)
-                    zsetConvert(zobj,OBJ_ENCODING_SKIPLIST);
-                if (sdslen(ele->ptr) > server.zset_max_ziplist_value)
-                    zsetConvert(zobj,OBJ_ENCODING_SKIPLIST);
-                server.dirty++;
-                added++;
-                processed++;
-            }
-        } else if (zobj->encoding == OBJ_ENCODING_SKIPLIST) {
-            zset *zs = zobj->ptr;
-            zskiplistNode *znode;
-            dictEntry *de;
-
-            ele = c->argv[scoreidx+1+j*2] =
-                tryObjectEncoding(c->argv[scoreidx+1+j*2]);
-            de = dictFind(zs->dict,ele);
-            if (de != NULL) {
-                if (nx) continue;
-                curobj = dictGetKey(de);
-                curscore = *(double*)dictGetVal(de);
-
-                if (incr) {
-                    score += curscore;
-                    if (isnan(score)) {
-                        addReplyError(c,nanerr);
-                        /* Don't need to check if the sorted set is empty
-                         * because we know it has at least one element. */
-                        goto cleanup;
-                    }
-                }
-
-                /* Remove and re-insert when score changed. We can safely
-                 * delete the key object from the skiplist, since the
-                 * dictionary still has a reference to it. */
-                if (score != curscore) {
-                    serverAssertWithInfo(c,curobj,zslDelete(zs->zsl,curscore,curobj));
-                    znode = zslInsert(zs->zsl,score,curobj);
-                    incrRefCount(curobj); /* Re-inserted in skiplist. */
-                    dictGetVal(de) = &znode->score; /* Update score ptr. */
-                    server.dirty++;
-                    updated++;
-                }
-                processed++;
-            } else if (!xx) {
-                znode = zslInsert(zs->zsl,score,ele);
-                incrRefCount(ele); /* Inserted in skiplist. */
-                serverAssertWithInfo(c,NULL,dictAdd(zs->dict,ele,&znode->score) == DICT_OK);
-                incrRefCount(ele); /* Added to dictionary. */
-                server.dirty++;
-                added++;
-                processed++;
-            }
-        } else {
-            serverPanic("Unknown sorted set encoding");
+        ele = c->argv[scoreidx+1+j*2]->ptr;
+        int retval = zsetAdd(zobj, score, ele, &retflags, &newscore);
+        if (retval == 0) {
+            addReplyError(c,nanerr);
+            goto cleanup;
         }
+        if (retflags & ZADD_ADDED) added++;
+        if (retflags & ZADD_UPDATED) updated++;
+        if (!(retflags & ZADD_NOP)) processed++;
+        score = newscore;
     }
+    server.dirty += (added+updated);
 
 reply_to_client:
     if (incr) { /* ZINCRBY or INCR option. */
         if (processed)
             addReplyDouble(c,score);
         else
