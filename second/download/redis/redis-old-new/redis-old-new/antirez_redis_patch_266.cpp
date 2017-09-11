@@ -1215,22 +1215,187 @@ int zsetScore(robj *zobj, sds member, double *score) {
     return C_OK;
 }
 
+/* Input flags. */
+#define ZADD_NONE 0
+#define ZADD_INCR (1<<0)    /* Increment the score instead of setting it. */
+#define ZADD_NX (1<<1)      /* Don't touch elements not already existing. */
+#define ZADD_XX (1<<2)      /* Only touch elements already exisitng. */
+
+/* Output flags. */
+#define ZADD_NOP (1<<3)     /* Operation not performed because of conditionals.*/
+#define ZADD_NAN (1<<4)     /* Only touch elements already exisitng. */
+#define ZADD_ADDED (1<<5)   /* The element was new and was added. */
+#define ZADD_UPDATED (1<<6) /* The element already existed, score updated. */
+
+/* Flags only used by the ZADD command but now by zsetAdd() API: */
+#define ZADD_CH (1<<16)      /* Return num of elements added or updated. */
+
+/* Add a new element or update the score of an existing element in a sorted
+ * set, regardless of its encoding.
+ *
+ * The set of flags change the command behavior. They are passed with an integer
+ * pointer since the function will clear the flags and populate them with
+ * other flags to indicate different conditions.
+ *
+ * The input flags are the following:
+ *
+ * ZADD_INCR: Increment the current element score by 'score' instead of updating
+ *            the current element score. If the element does not exist, we
+ *            assume 0 as previous score.
+ * ZADD_NX:   Perform the operation only if the element does not exist.
+ * ZADD_XX:   Perform the operation only if the element already exist.
+ *
+ * When ZADD_INCR is used, the new score of the element is stored in
+ * '*newscore' if 'newscore' is not NULL.
+ *
+ * The returned flags are the following:
+ *
+ * ZADD_NAN:     The resulting score is not a number.
+ * ZADD_ADDED:   The element was added (not present before the call).
+ * ZADD_UPDATED: The element score was updated.
+ * ZADD_NOP:     No operation was performed because of NX or XX.
+ *
+ * Return value:
+ *
+ * The function returns 1 on success, and sets the appropriate flags
+ * ADDED or UPDATED to signal what happened during the operation (note that
+ * none could be set if we re-added an element using the same score it used
+ * to have, or in the case a zero increment is used).
+ *
+ * The function returns 0 on erorr, currently only when the increment
+ * produces a NAN condition, or when the 'score' value is NAN since the
+ * start.
+ *
+ * The commad as a side effect of adding a new element may convert the sorted
+ * set internal encoding from ziplist to hashtable+skiplist.
+ *
+ * Memory managemnet of 'ele':
+ *
+ * The function does not take ownership of the 'ele' SDS string, but copies
+ * it if needed. */
+int zsetAdd(robj *zobj, double score, sds ele, int *flags, double *newscore) {
+    /* Turn options into simple to check vars. */
+    int incr = (*flags & ZADD_INCR) != 0;
+    int nx = (*flags & ZADD_NX) != 0;
+    int xx = (*flags & ZADD_XX) != 0;
+    *flags = 0; /* We'll return our response flags. */
+    double curscore;
+
+    /* NaN as input is an error regardless of all the other parameters. */
+    if (isnan(score)) {
+        *flags = ZADD_NAN;
+        return 0;
+    }
+
+    /* Update the sorted set according to its encoding. */
+    if (zobj->encoding == OBJ_ENCODING_ZIPLIST) {
+        unsigned char *eptr;
+
+        if ((eptr = zzlFind(zobj->ptr,ele,&curscore)) != NULL) {
+            /* NX? Return, same element already exists. */
+            if (nx) {
+                *flags |= ZADD_NOP;
+                return 1;
+            }
+
+            /* Prepare the score for the increment if needed. */
+            if (incr) {
+                score += curscore;
+                if (isnan(score)) {
+                    *flags |= ZADD_NAN;
+                    return 0;
+                }
+                if (newscore) *newscore = score;
+            }
+
+            /* Remove and re-insert when score changed. */
+            if (score != curscore) {
+                zobj->ptr = zzlDelete(zobj->ptr,eptr);
+                zobj->ptr = zzlInsert(zobj->ptr,ele,score);
+                *flags |= ZADD_UPDATED;
+            }
+            return 1;
+        } else if (!xx) {
+            /* Optimize: check if the element is too large or the list
+             * becomes too long *before* executing zzlInsert. */
+            zobj->ptr = zzlInsert(zobj->ptr,ele,score);
+            if (zzlLength(zobj->ptr) > server.zset_max_ziplist_entries)
+                zsetConvert(zobj,OBJ_ENCODING_SKIPLIST);
+            if (sdslen(ele) > server.zset_max_ziplist_value)
+                zsetConvert(zobj,OBJ_ENCODING_SKIPLIST);
+            *flags |= ZADD_ADDED;
+            return 1;
+        } else {
+            *flags |= ZADD_NOP;
+            return 1;
+        }
+    } else if (zobj->encoding == OBJ_ENCODING_SKIPLIST) {
+        zset *zs = zobj->ptr;
+        zskiplistNode *znode;
+        dictEntry *de;
+
+        de = dictFind(zs->dict,ele);
+        if (de != NULL) {
+            /* NX? Return, same element already exists. */
+            if (nx) {
+                *flags |= ZADD_NOP;
+                return 1;
+            }
+            curscore = *(double*)dictGetVal(de);
+
+            /* Prepare the score for the increment if needed. */
+            if (incr) {
+                score += curscore;
+                if (isnan(score)) {
+                    *flags |= ZADD_NAN;
+                    return 0;
+                }
+                if (newscore) *newscore = score;
+            }
+
+            /* Remove and re-insert when score changes. */
+            if (score != curscore) {
+                zskiplistNode *node;
+                serverAssert(zslDelete(zs->zsl,curscore,ele,&node));
+                znode = zslInsert(zs->zsl,score,node->ele);
+                /* We reused the node->ele SDS string, free the node now
+                 * since zslInsert created a new one. */
+                node->ele = NULL;
+                zslFreeNode(node);
+                /* Note that we did not removed the original element from
+                 * the hash table representing the sorted set, so we just
+                 * update the score. */
+                dictGetVal(de) = &znode->score; /* Update score ptr. */
+                *flags |= ZADD_UPDATED;
+            }
+            return 1;
+        } else if (!xx) {
+            ele = sdsdup(ele);
+            znode = zslInsert(zs->zsl,score,ele);
+            serverAssert(dictAdd(zs->dict,ele,&znode->score) == DICT_OK);
+            *flags |= ZADD_ADDED;
+            return 1;
+        } else {
+            *flags |= ZADD_NOP;
+            return 1;
+        }
+    } else {
+        serverPanic("Unknown sorted set encoding");
+    }
+    return 0; /* Never reached. */
+}
+
 /*-----------------------------------------------------------------------------
  * Sorted set commands
  *----------------------------------------------------------------------------*/
 
 /* This generic command implements both ZADD and ZINCRBY. */
-#define ZADD_NONE 0
-#define ZADD_INCR (1<<0)    /* Increment the score instead of setting it. */
-#define ZADD_NX (1<<1)      /* Don't touch elements not already existing. */
-#define ZADD_XX (1<<2)      /* Only touch elements already exisitng. */
-#define ZADD_CH (1<<3)      /* Return num of elements added or updated. */
 void zaddGenericCommand(client *c, int flags) {
     static char *nanerr = "resulting score is not a number (NaN)";
     robj *key = c->argv[1];
     robj *zobj;
     sds ele;
-    double score = 0, *scores = NULL, curscore = 0.0;
+    double score = 0, *scores = NULL;
     int j, elements;
     int scoreidx = 0;
     /* The following vars are used in order to track what the command actually
@@ -1311,91 +1476,22 @@ void zaddGenericCommand(client *c, int flags) {
     }
 
     for (j = 0; j < elements; j++) {
+        double newscore;
         score = scores[j];
+        int retflags = flags;
 
         ele = c->argv[scoreidx+1+j*2]->ptr;
-        if (zobj->encoding == OBJ_ENCODING_ZIPLIST) {
-            unsigned char *eptr;
-
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
-                if (sdslen(ele) > server.zset_max_ziplist_value)
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
-            de = dictFind(zs->dict,ele);
-            if (de != NULL) {
-                if (nx) continue;
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
-                /* Remove and re-insert when score changes. */
-                if (score != curscore) {
-                    zskiplistNode *node;
-                    serverAssert(zslDelete(zs->zsl,curscore,ele,&node));
-                    znode = zslInsert(zs->zsl,score,node->ele);
-                    /* We reused the node->ele SDS string, free the node now
-                     * since zslInsert created a new one. */
-                    node->ele = NULL;
-                    zslFreeNode(node);
-                    /* Note that we did not removed the original element from
-                     * the hash table representing the sorted set, so we just
-                     * update the score. */
-                    dictGetVal(de) = &znode->score; /* Update score ptr. */
-                    server.dirty++;
-                    updated++;
-                }
-                processed++;
-            } else if (!xx) {
-                ele = sdsdup(ele);
-                znode = zslInsert(zs->zsl,score,ele);
-                serverAssert(dictAdd(zs->dict,ele,&znode->score) == DICT_OK);
-                server.dirty++;
-                added++;
-                processed++;
-            }
-        } else {
-            serverPanic("Unknown sorted set encoding");
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