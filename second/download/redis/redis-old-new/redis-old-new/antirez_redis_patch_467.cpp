@@ -440,27 +440,27 @@ static int zslParseRange(robj *min, robj *max, zrangespec *spec) {
     } else {
         if (((char*)min->ptr)[0] == '(') {
             spec->min = strtod((char*)min->ptr+1,&eptr);
-            if (eptr[0] != '\0' || isnan(spec->min)) return REDIS_ERR;
+            if (eptr[0] != '\0' || isnan(spec->min)) return C_ERR;
             spec->minex = 1;
         } else {
             spec->min = strtod((char*)min->ptr,&eptr);
-            if (eptr[0] != '\0' || isnan(spec->min)) return REDIS_ERR;
+            if (eptr[0] != '\0' || isnan(spec->min)) return C_ERR;
         }
     }
     if (max->encoding == OBJ_ENCODING_INT) {
         spec->max = (long)max->ptr;
     } else {
         if (((char*)max->ptr)[0] == '(') {
             spec->max = strtod((char*)max->ptr+1,&eptr);
-            if (eptr[0] != '\0' || isnan(spec->max)) return REDIS_ERR;
+            if (eptr[0] != '\0' || isnan(spec->max)) return C_ERR;
             spec->maxex = 1;
         } else {
             spec->max = strtod((char*)max->ptr,&eptr);
-            if (eptr[0] != '\0' || isnan(spec->max)) return REDIS_ERR;
+            if (eptr[0] != '\0' || isnan(spec->max)) return C_ERR;
         }
     }
 
-    return REDIS_OK;
+    return C_OK;
 }
 
 /* ------------------------ Lexicographic ranges ---------------------------- */
@@ -473,64 +473,64 @@ static int zslParseRange(robj *min, robj *max, zrangespec *spec) {
   *
   * If the string is valid the *dest pointer is set to the redis object
   * that will be used for the comparision, and ex will be set to 0 or 1
-  * respectively if the item is exclusive or inclusive. REDIS_OK will be
+  * respectively if the item is exclusive or inclusive. C_OK will be
   * returned.
   *
-  * If the string is not a valid range REDIS_ERR is returned, and the value
+  * If the string is not a valid range C_ERR is returned, and the value
   * of *dest and *ex is undefined. */
 int zslParseLexRangeItem(robj *item, robj **dest, int *ex) {
     char *c = item->ptr;
 
     switch(c[0]) {
     case '+':
-        if (c[1] != '\0') return REDIS_ERR;
+        if (c[1] != '\0') return C_ERR;
         *ex = 0;
         *dest = shared.maxstring;
         incrRefCount(shared.maxstring);
-        return REDIS_OK;
+        return C_OK;
     case '-':
-        if (c[1] != '\0') return REDIS_ERR;
+        if (c[1] != '\0') return C_ERR;
         *ex = 0;
         *dest = shared.minstring;
         incrRefCount(shared.minstring);
-        return REDIS_OK;
+        return C_OK;
     case '(':
         *ex = 1;
         *dest = createStringObject(c+1,sdslen(c)-1);
-        return REDIS_OK;
+        return C_OK;
     case '[':
         *ex = 0;
         *dest = createStringObject(c+1,sdslen(c)-1);
-        return REDIS_OK;
+        return C_OK;
     default:
-        return REDIS_ERR;
+        return C_ERR;
     }
 }
 
 /* Populate the rangespec according to the objects min and max.
  *
- * Return REDIS_OK on success. On error REDIS_ERR is returned.
+ * Return C_OK on success. On error C_ERR is returned.
  * When OK is returned the structure must be freed with zslFreeLexRange(),
  * otherwise no release is needed. */
 static int zslParseLexRange(robj *min, robj *max, zlexrangespec *spec) {
     /* The range can't be valid if objects are integer encoded.
      * Every item must start with ( or [. */
     if (min->encoding == OBJ_ENCODING_INT ||
-        max->encoding == OBJ_ENCODING_INT) return REDIS_ERR;
+        max->encoding == OBJ_ENCODING_INT) return C_ERR;
 
     spec->min = spec->max = NULL;
-    if (zslParseLexRangeItem(min, &spec->min, &spec->minex) == REDIS_ERR ||
-        zslParseLexRangeItem(max, &spec->max, &spec->maxex) == REDIS_ERR) {
+    if (zslParseLexRangeItem(min, &spec->min, &spec->minex) == C_ERR ||
+        zslParseLexRangeItem(max, &spec->max, &spec->maxex) == C_ERR) {
         if (spec->min) decrRefCount(spec->min);
         if (spec->max) decrRefCount(spec->max);
-        return REDIS_ERR;
+        return C_ERR;
     } else {
-        return REDIS_OK;
+        return C_OK;
     }
 }
 
 /* Free a lex range structure, must be called only after zelParseLexRange()
- * populated the structure with success (REDIS_OK returned). */
+ * populated the structure with success (C_OK returned). */
 void zslFreeLexRange(zlexrangespec *spec) {
     decrRefCount(spec->min);
     decrRefCount(spec->max);
@@ -1167,23 +1167,23 @@ void zsetConvert(robj *zobj, int encoding) {
 }
 
 /* Return (by reference) the score of the specified member of the sorted set
- * storing it into *score. If the element does not exist REDIS_ERR is returned
- * otherwise REDIS_OK is returned and *score is correctly populated.
- * If 'zobj' or 'member' is NULL, REDIS_ERR is returned. */
+ * storing it into *score. If the element does not exist C_ERR is returned
+ * otherwise C_OK is returned and *score is correctly populated.
+ * If 'zobj' or 'member' is NULL, C_ERR is returned. */
 int zsetScore(robj *zobj, robj *member, double *score) {
-    if (!zobj || !member) return REDIS_ERR;
+    if (!zobj || !member) return C_ERR;
 
     if (zobj->encoding == OBJ_ENCODING_ZIPLIST) {
-        if (zzlFind(zobj->ptr, member, score) == NULL) return REDIS_ERR;
+        if (zzlFind(zobj->ptr, member, score) == NULL) return C_ERR;
     } else if (zobj->encoding == OBJ_ENCODING_SKIPLIST) {
         zset *zs = zobj->ptr;
         dictEntry *de = dictFind(zs->dict, member);
-        if (de == NULL) return REDIS_ERR;
+        if (de == NULL) return C_ERR;
         *score = *(double*)dictGetVal(de);
     } else {
         redisPanic("Unknown sorted set encoding");
     }
-    return REDIS_OK;
+    return C_OK;
 }
 
 /*-----------------------------------------------------------------------------
@@ -1260,7 +1260,7 @@ void zaddGenericCommand(client *c, int flags) {
     scores = zmalloc(sizeof(double)*elements);
     for (j = 0; j < elements; j++) {
         if (getDoubleFromObjectOrReply(c,c->argv[scoreidx+j*2],&scores[j],NULL)
-            != REDIS_OK) goto cleanup;
+            != C_OK) goto cleanup;
     }
 
     /* Lookup the key and create the sorted set if does not exist. */
@@ -1471,16 +1471,16 @@ void zremrangeGenericCommand(client *c, int rangetype) {
 
     /* Step 1: Parse the range. */
     if (rangetype == ZRANGE_RANK) {
-        if ((getLongFromObjectOrReply(c,c->argv[2],&start,NULL) != REDIS_OK) ||
-            (getLongFromObjectOrReply(c,c->argv[3],&end,NULL) != REDIS_OK))
+        if ((getLongFromObjectOrReply(c,c->argv[2],&start,NULL) != C_OK) ||
+            (getLongFromObjectOrReply(c,c->argv[3],&end,NULL) != C_OK))
             return;
     } else if (rangetype == ZRANGE_SCORE) {
-        if (zslParseRange(c->argv[2],c->argv[3],&range) != REDIS_OK) {
+        if (zslParseRange(c->argv[2],c->argv[3],&range) != C_OK) {
             addReplyError(c,"min or max is not a float");
             return;
         }
     } else if (rangetype == ZRANGE_LEX) {
-        if (zslParseLexRange(c->argv[2],c->argv[3],&lexrange) != REDIS_OK) {
+        if (zslParseLexRange(c->argv[2],c->argv[3],&lexrange) != C_OK) {
             addReplyError(c,"min or max not valid string range item");
             return;
         }
@@ -1936,7 +1936,7 @@ void zunionInterGenericCommand(client *c, robj *dstkey, int op) {
     int touched = 0;
 
     /* expect setnum input keys to be given */
-    if ((getLongFromObjectOrReply(c, c->argv[2], &setnum, NULL) != REDIS_OK))
+    if ((getLongFromObjectOrReply(c, c->argv[2], &setnum, NULL) != C_OK))
         return;
 
     if (setnum < 1) {
@@ -1982,7 +1982,7 @@ void zunionInterGenericCommand(client *c, robj *dstkey, int op) {
                 j++; remaining--;
                 for (i = 0; i < setnum; i++, j++, remaining--) {
                     if (getDoubleFromObjectOrReply(c,c->argv[j],&src[i].weight,
-                            "weight value is not a float") != REDIS_OK)
+                            "weight value is not a float") != C_OK)
                     {
                         zfree(src);
                         return;
@@ -2180,8 +2180,8 @@ void zrangeGenericCommand(client *c, int reverse) {
     int llen;
     int rangelen;
 
-    if ((getLongFromObjectOrReply(c, c->argv[2], &start, NULL) != REDIS_OK) ||
-        (getLongFromObjectOrReply(c, c->argv[3], &end, NULL) != REDIS_OK)) return;
+    if ((getLongFromObjectOrReply(c, c->argv[2], &start, NULL) != C_OK) ||
+        (getLongFromObjectOrReply(c, c->argv[3], &end, NULL) != C_OK)) return;
 
     if (c->argc == 5 && !strcasecmp(c->argv[4]->ptr,"withscores")) {
         withscores = 1;
@@ -2301,7 +2301,7 @@ void genericZrangebyscoreCommand(client *c, int reverse) {
         minidx = 2; maxidx = 3;
     }
 
-    if (zslParseRange(c->argv[minidx],c->argv[maxidx],&range) != REDIS_OK) {
+    if (zslParseRange(c->argv[minidx],c->argv[maxidx],&range) != C_OK) {
         addReplyError(c,"min or max is not a float");
         return;
     }
@@ -2317,8 +2317,8 @@ void genericZrangebyscoreCommand(client *c, int reverse) {
                 pos++; remaining--;
                 withscores = 1;
             } else if (remaining >= 3 && !strcasecmp(c->argv[pos]->ptr,"limit")) {
-                if ((getLongFromObjectOrReply(c, c->argv[pos+1], &offset, NULL) != REDIS_OK) ||
-                    (getLongFromObjectOrReply(c, c->argv[pos+2], &limit, NULL) != REDIS_OK)) return;
+                if ((getLongFromObjectOrReply(c, c->argv[pos+1], &offset, NULL) != C_OK) ||
+                    (getLongFromObjectOrReply(c, c->argv[pos+2], &limit, NULL) != C_OK)) return;
                 pos += 3; remaining -= 3;
             } else {
                 addReply(c,shared.syntaxerr);
@@ -2483,7 +2483,7 @@ void zcountCommand(client *c) {
     int count = 0;
 
     /* Parse the range arguments */
-    if (zslParseRange(c->argv[2],c->argv[3],&range) != REDIS_OK) {
+    if (zslParseRange(c->argv[2],c->argv[3],&range) != C_OK) {
         addReplyError(c,"min or max is not a float");
         return;
     }
@@ -2560,7 +2560,7 @@ void zlexcountCommand(client *c) {
     int count = 0;
 
     /* Parse the range arguments */
-    if (zslParseLexRange(c->argv[2],c->argv[3],&range) != REDIS_OK) {
+    if (zslParseLexRange(c->argv[2],c->argv[3],&range) != C_OK) {
         addReplyError(c,"min or max not valid string range item");
         return;
     }
@@ -2651,7 +2651,7 @@ void genericZrangebylexCommand(client *c, int reverse) {
         minidx = 2; maxidx = 3;
     }
 
-    if (zslParseLexRange(c->argv[minidx],c->argv[maxidx],&range) != REDIS_OK) {
+    if (zslParseLexRange(c->argv[minidx],c->argv[maxidx],&range) != C_OK) {
         addReplyError(c,"min or max not valid string range item");
         return;
     }
@@ -2664,8 +2664,8 @@ void genericZrangebylexCommand(client *c, int reverse) {
 
         while (remaining) {
             if (remaining >= 3 && !strcasecmp(c->argv[pos]->ptr,"limit")) {
-                if ((getLongFromObjectOrReply(c, c->argv[pos+1], &offset, NULL) != REDIS_OK) ||
-                    (getLongFromObjectOrReply(c, c->argv[pos+2], &limit, NULL) != REDIS_OK)) return;
+                if ((getLongFromObjectOrReply(c, c->argv[pos+1], &offset, NULL) != C_OK) ||
+                    (getLongFromObjectOrReply(c, c->argv[pos+2], &limit, NULL) != C_OK)) return;
                 pos += 3; remaining -= 3;
             } else {
                 zslFreeLexRange(&range);
@@ -2835,7 +2835,7 @@ void zscoreCommand(client *c) {
     if ((zobj = lookupKeyReadOrReply(c,key,shared.nullbulk)) == NULL ||
         checkType(c,zobj,OBJ_ZSET)) return;
 
-    if (zsetScore(zobj,c->argv[2],&score) == REDIS_ERR) {
+    if (zsetScore(zobj,c->argv[2],&score) == C_ERR) {
         addReply(c,shared.nullbulk);
     } else {
         addReplyDouble(c,score);
@@ -2916,7 +2916,7 @@ void zscanCommand(client *c) {
     robj *o;
     unsigned long cursor;
 
-    if (parseScanCursorOrReply(c,c->argv[2],&cursor) == REDIS_ERR) return;
+    if (parseScanCursorOrReply(c,c->argv[2],&cursor) == C_ERR) return;
     if ((o = lookupKeyReadOrReply(c,c->argv[1],shared.emptyscan)) == NULL ||
         checkType(c,o,OBJ_ZSET)) return;
     scanGenericCommand(c,o,cursor);