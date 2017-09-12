@@ -641,6 +641,7 @@ static void zaddCommand(redisClient *c);
 static void zincrbyCommand(redisClient *c);
 static void zrangeCommand(redisClient *c);
 static void zrangebyscoreCommand(redisClient *c);
+static void zcountCommand(redisClient *c);
 static void zrevrangeCommand(redisClient *c);
 static void zcardCommand(redisClient *c);
 static void zremCommand(redisClient *c);
@@ -699,6 +700,7 @@ static struct redisCommand cmdTable[] = {
     {"zremrangebyscore",zremrangebyscoreCommand,4,REDIS_CMD_INLINE},
     {"zrange",zrangeCommand,-4,REDIS_CMD_INLINE},
     {"zrangebyscore",zrangebyscoreCommand,-4,REDIS_CMD_INLINE},
+    {"zcount",zcountCommand,4,REDIS_CMD_INLINE},
     {"zrevrange",zrevrangeCommand,-4,REDIS_CMD_INLINE},
     {"zcard",zcardCommand,2,REDIS_CMD_INLINE},
     {"zscore",zscoreCommand,3,REDIS_CMD_BULK|REDIS_CMD_DENYOOM},
@@ -2408,6 +2410,14 @@ static void addReplyDouble(redisClient *c, double d) {
         (unsigned long) strlen(buf),buf));
 }
 
+static void addReplyLong(redisClient *c, long l) {
+    char buf[128];
+    size_t len;
+
+    len = snprintf(buf,sizeof(buf),":%ld\r\n",l);
+    addReplySds(c,sdsnewlen(buf,len));
+}
+
 static void addReplyBulkLen(redisClient *c, robj *obj) {
     size_t len;
 
@@ -5192,30 +5202,51 @@ static void zrevrangeCommand(redisClient *c) {
     zrangeGenericCommand(c,1);
 }
 
-static void zrangebyscoreCommand(redisClient *c) {
+/* This command implements both ZRANGEBYSCORE and ZCOUNT.
+ * If justcount is non-zero, just the count is returned. */
+static void genericZrangebyscoreCommand(redisClient *c, int justcount) {
     robj *o;
-    double min = strtod(c->argv[2]->ptr,NULL);
-    double max = strtod(c->argv[3]->ptr,NULL);
+    double min, max;
+    int minex = 0, maxex = 0; /* are min or max exclusive? */
     int offset = 0, limit = -1;
     int withscores = 0;
     int badsyntax = 0;
 
+    /* Parse the min-max interval. If one of the values is prefixed
+     * by the "(" character, it's considered "open". For instance
+     * ZRANGEBYSCORE zset (1.5 (2.5 will match min < x < max
+     * ZRANGEBYSCORE zset 1.5 2.5 will instead match min <= x <= max */
+    if (((char*)c->argv[2]->ptr)[0] == '(') {
+        min = strtod((char*)c->argv[2]->ptr+1,NULL);
+        minex = 1;
+    } else {
+        min = strtod(c->argv[2]->ptr,NULL);
+    }
+    if (((char*)c->argv[3]->ptr)[0] == '(') {
+        max = strtod((char*)c->argv[3]->ptr+1,NULL);
+        maxex = 1;
+    } else {
+        max = strtod(c->argv[3]->ptr,NULL);
+    }
+
+    /* Parse "WITHSCORES": note that if the command was called with
+     * the name ZCOUNT then we are sure that c->argc == 4, so we'll never
+     * enter the following paths to parse WITHSCORES and LIMIT. */
     if (c->argc == 5 || c->argc == 8) {
         if (strcasecmp(c->argv[c->argc-1]->ptr,"withscores") == 0)
             withscores = 1;
         else
             badsyntax = 1;
     }
-
     if (c->argc != (4 + withscores) && c->argc != (7 + withscores))
         badsyntax = 1;
-
     if (badsyntax) {
         addReplySds(c,
             sdsnew("-ERR wrong number of arguments for ZRANGEBYSCORE\r\n"));
         return;
     }
 
+    /* Parse "LIMIT" */
     if (c->argc == (7 + withscores) && strcasecmp(c->argv[4]->ptr,"limit")) {
         addReply(c,shared.syntaxerr);
         return;
@@ -5225,58 +5256,78 @@ static void zrangebyscoreCommand(redisClient *c) {
         if (offset < 0) offset = 0;
     }
 
+    /* Ok, lookup the key and get the range */
     o = lookupKeyRead(c->db,c->argv[1]);
     if (o == NULL) {
-        addReply(c,shared.nullmultibulk);
+        addReply(c,justcount ? shared.czero : shared.nullmultibulk);
     } else {
         if (o->type != REDIS_ZSET) {
             addReply(c,shared.wrongtypeerr);
         } else {
             zset *zsetobj = o->ptr;
             zskiplist *zsl = zsetobj->zsl;
             zskiplistNode *ln;
-            robj *ele, *lenobj;
-            unsigned int rangelen = 0;
+            robj *ele, *lenobj = NULL;
+            unsigned long rangelen = 0;
 
-            /* Get the first node with the score >= min */
+            /* Get the first node with the score >= min, or with
+             * score > min if 'minex' is true. */
             ln = zslFirstWithScore(zsl,min);
+            while (minex && ln && ln->score == min) ln = ln->forward[0];
+
             if (ln == NULL) {
                 /* No element matching the speciifed interval */
-                addReply(c,shared.emptymultibulk);
+                addReply(c,justcount ? shared.czero : shared.emptymultibulk);
                 return;
             }
 
             /* We don't know in advance how many matching elements there
              * are in the list, so we push this object that will represent
              * the multi-bulk length in the output buffer, and will "fix"
              * it later */
-            lenobj = createObject(REDIS_STRING,NULL);
-            addReply(c,lenobj);
-            decrRefCount(lenobj);
+            if (!justcount) {
+                lenobj = createObject(REDIS_STRING,NULL);
+                addReply(c,lenobj);
+                decrRefCount(lenobj);
+            }
 
-            while(ln && ln->score <= max) {
+            while(ln && (maxex ? (ln->score < max) : (ln->score <= max))) {
                 if (offset) {
                     offset--;
                     ln = ln->forward[0];
                     continue;
                 }
                 if (limit == 0) break;
-                ele = ln->obj;
-                addReplyBulkLen(c,ele);
-                addReply(c,ele);
-                addReply(c,shared.crlf);
-                if (withscores)
-                    addReplyDouble(c,ln->score);
+                if (!justcount) {
+                    ele = ln->obj;
+                    addReplyBulkLen(c,ele);
+                    addReply(c,ele);
+                    addReply(c,shared.crlf);
+                    if (withscores)
+                        addReplyDouble(c,ln->score);
+                }
                 ln = ln->forward[0];
                 rangelen++;
                 if (limit > 0) limit--;
             }
-            lenobj->ptr = sdscatprintf(sdsempty(),"*%d\r\n",
-		 withscores ? (rangelen*2) : rangelen);
+            if (justcount) {
+                addReplyLong(c,(long)rangelen);
+            } else {
+                lenobj->ptr = sdscatprintf(sdsempty(),"*%lu\r\n",
+                     withscores ? (rangelen*2) : rangelen);
+            }
         }
     }
 }
 
+static void zrangebyscoreCommand(redisClient *c) {
+    genericZrangebyscoreCommand(c,0);
+}
+
+static void zcountCommand(redisClient *c) {
+    genericZrangebyscoreCommand(c,1);
+}
+
 static void zcardCommand(redisClient *c) {
     robj *o;
     zset *zs;