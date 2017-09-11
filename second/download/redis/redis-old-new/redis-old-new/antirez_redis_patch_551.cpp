@@ -1171,33 +1171,82 @@ void zsetConvert(robj *zobj, int encoding) {
  *----------------------------------------------------------------------------*/
 
 /* This generic command implements both ZADD and ZINCRBY. */
-void zaddGenericCommand(redisClient *c, int incr) {
+#define ZADD_NONE 0
+#define ZADD_INCR (1<<0)    /* Increment the score instead of setting it. */
+#define ZADD_NX (1<<1)      /* Don't touch elements not already existing. */
+#define ZADD_XX (1<<2)      /* Only touch elements already exisitng. */
+#define ZADD_CH (1<<3)      /* Return num of elements added or updated. */
+void zaddGenericCommand(redisClient *c, int flags) {
     static char *nanerr = "resulting score is not a number (NaN)";
     robj *key = c->argv[1];
     robj *ele;
     robj *zobj;
     robj *curobj;
     double score = 0, *scores = NULL, curscore = 0.0;
-    int j, elements = (c->argc-2)/2;
-    int added = 0, updated = 0;
-
-    if (c->argc % 2) {
+    int j, elements;
+    int scoreidx = 0;
+    /* The following vars are used in order to track what the command actually
+     * did during the execution, to reply to the client and to trigger the
+     * notification of keyspace change. */
+    int added = 0;      /* Number of new elements added. */
+    int updated = 0;    /* Number of elements with updated score. */
+    int processed = 0;  /* Number of elements processed, may remain zero with
+                           options like XX. */
+
+    /* Parse options. At the end 'scoreidx' is set to the argument position
+     * of the score of the first score-element pair. */
+    scoreidx = 2;
+    while(scoreidx < c->argc) {
+        char *opt = c->argv[scoreidx]->ptr;
+        if (!strcasecmp(opt,"nx")) flags |= ZADD_NX;
+        else if (!strcasecmp(opt,"xx")) flags |= ZADD_XX;
+        else if (!strcasecmp(opt,"ch")) flags |= ZADD_CH;
+        else if (!strcasecmp(opt,"incr")) flags |= ZADD_INCR;
+        else break;
+        scoreidx++;
+    }
+
+    /* Turn options into simple to check vars. */
+    int incr = (flags & ZADD_INCR) != 0;
+    int nx = (flags & ZADD_NX) != 0;
+    int xx = (flags & ZADD_XX) != 0;
+    int ch = (flags & ZADD_CH) != 0;
+
+    /* After the options, we expect to have an even number of args, since
+     * we expect any number of score-element pairs. */
+    elements = c->argc-scoreidx;
+    if (elements % 2) {
         addReply(c,shared.syntaxerr);
         return;
     }
+    elements /= 2; /* Now this holds the number of score-element pairs. */
+
+    /* Check for incompatible options. */
+    if (nx && xx) {
+        addReplyError(c,
+            "XX and NX options at the same time are not compatible");
+        return;
+    }
+
+    if (incr && elements > 1) {
+        addReplyError(c,
+            "INCR option supports a single increment-element pair");
+        return;
+    }
 
     /* Start parsing all the scores, we need to emit any syntax error
      * before executing additions to the sorted set, as the command should
      * either execute fully or nothing at all. */
     scores = zmalloc(sizeof(double)*elements);
     for (j = 0; j < elements; j++) {
-        if (getDoubleFromObjectOrReply(c,c->argv[2+j*2],&scores[j],NULL)
+        if (getDoubleFromObjectOrReply(c,c->argv[scoreidx+j*2],&scores[j],NULL)
             != REDIS_OK) goto cleanup;
     }
 
     /* Lookup the key and create the sorted set if does not exist. */
     zobj = lookupKeyWrite(c->db,key);
     if (zobj == NULL) {
+        if (xx) goto reply_to_client; /* No key + XX option: nothing to do. */
         if (server.zset_max_ziplist_entries == 0 ||
             server.zset_max_ziplist_value < sdslen(c->argv[3]->ptr))
         {
@@ -1220,8 +1269,9 @@ void zaddGenericCommand(redisClient *c, int incr) {
             unsigned char *eptr;
 
             /* Prefer non-encoded element when dealing with ziplists. */
-            ele = c->argv[3+j*2];
+            ele = c->argv[scoreidx+1+j*2];
             if ((eptr = zzlFind(zobj->ptr,ele,&curscore)) != NULL) {
+                if (nx) continue;
                 if (incr) {
                     score += curscore;
                     if (isnan(score)) {
@@ -1237,7 +1287,8 @@ void zaddGenericCommand(redisClient *c, int incr) {
                     server.dirty++;
                     updated++;
                 }
-            } else {
+                processed++;
+            } else if (!xx) {
                 /* Optimize: check if the element is too large or the list
                  * becomes too long *before* executing zzlInsert. */
                 zobj->ptr = zzlInsert(zobj->ptr,ele,score);
@@ -1247,15 +1298,18 @@ void zaddGenericCommand(redisClient *c, int incr) {
                     zsetConvert(zobj,REDIS_ENCODING_SKIPLIST);
                 server.dirty++;
                 added++;
+                processed++;
             }
         } else if (zobj->encoding == REDIS_ENCODING_SKIPLIST) {
             zset *zs = zobj->ptr;
             zskiplistNode *znode;
             dictEntry *de;
 
-            ele = c->argv[3+j*2] = tryObjectEncoding(c->argv[3+j*2]);
+            ele = c->argv[scoreidx+1+j*2] =
+                tryObjectEncoding(c->argv[scoreidx+1+j*2]);
             de = dictFind(zs->dict,ele);
             if (de != NULL) {
+                if (nx) continue;
                 curobj = dictGetKey(de);
                 curscore = *(double*)dictGetVal(de);
 
@@ -1280,22 +1334,30 @@ void zaddGenericCommand(redisClient *c, int incr) {
                     server.dirty++;
                     updated++;
                 }
-            } else {
+                processed++;
+            } else if (!xx) {
                 znode = zslInsert(zs->zsl,score,ele);
                 incrRefCount(ele); /* Inserted in skiplist. */
                 redisAssertWithInfo(c,NULL,dictAdd(zs->dict,ele,&znode->score) == DICT_OK);
                 incrRefCount(ele); /* Added to dictionary. */
                 server.dirty++;
                 added++;
+                processed++;
             }
         } else {
             redisPanic("Unknown sorted set encoding");
         }
     }
-    if (incr) /* ZINCRBY */
-        addReplyDouble(c,score);
-    else /* ZADD */
-        addReplyLongLong(c,added);
+
+reply_to_client:
+    if (incr) { /* ZINCRBY or INCR option. */
+        if (processed)
+            addReplyDouble(c,score);
+        else
+            addReply(c,shared.nullbulk);
+    } else { /* ZADD. */
+        addReplyLongLong(c,ch ? added+updated : added);
+    }
 
 cleanup:
     zfree(scores);
@@ -1307,11 +1369,11 @@ void zaddGenericCommand(redisClient *c, int incr) {
 }
 
 void zaddCommand(redisClient *c) {
-    zaddGenericCommand(c,0);
+    zaddGenericCommand(c,ZADD_NONE);
 }
 
 void zincrbyCommand(redisClient *c) {
-    zaddGenericCommand(c,1);
+    zaddGenericCommand(c,ZADD_INCR);
 }
 
 void zremCommand(redisClient *c) {