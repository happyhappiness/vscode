@@ -307,7 +307,8 @@ zskiplistNode* zslistTypeGetElementByRank(zskiplist *zsl, unsigned long rank) {
 }
 
 /* Populate the rangespec according to the objects min and max. */
-int zslParseRange(robj *min, robj *max, zrangespec *spec) {
+static int zslParseRange(robj *min, robj *max, zrangespec *spec) {
+    char *eptr;
     spec->minex = spec->maxex = 0;
 
     /* Parse the min-max interval. If one of the values is prefixed
@@ -318,20 +319,24 @@ int zslParseRange(robj *min, robj *max, zrangespec *spec) {
         spec->min = (long)min->ptr;
     } else {
         if (((char*)min->ptr)[0] == '(') {
-            spec->min = strtod((char*)min->ptr+1,NULL);
+            spec->min = strtod((char*)min->ptr+1,&eptr);
+            if (eptr[0] != '\0' || isnan(spec->min)) return REDIS_ERR;
             spec->minex = 1;
         } else {
-            spec->min = strtod((char*)min->ptr,NULL);
+            spec->min = strtod((char*)min->ptr,&eptr);
+            if (eptr[0] != '\0' || isnan(spec->min)) return REDIS_ERR;
         }
     }
     if (max->encoding == REDIS_ENCODING_INT) {
         spec->max = (long)max->ptr;
     } else {
         if (((char*)max->ptr)[0] == '(') {
-            spec->max = strtod((char*)max->ptr+1,NULL);
+            spec->max = strtod((char*)max->ptr+1,&eptr);
+            if (eptr[0] != '\0' || isnan(spec->max)) return REDIS_ERR;
             spec->maxex = 1;
         } else {
-            spec->max = strtod((char*)max->ptr,NULL);
+            spec->max = strtod((char*)max->ptr,&eptr);
+            if (eptr[0] != '\0' || isnan(spec->max)) return REDIS_ERR;
         }
     }
 
@@ -481,7 +486,10 @@ void zremrangebyscoreCommand(redisClient *c) {
     zset *zs;
 
     /* Parse the range arguments. */
-    zslParseRange(c->argv[2],c->argv[3],&range);
+    if (zslParseRange(c->argv[2],c->argv[3],&range) != REDIS_OK) {
+        addReplyError(c,"min or max is not a double");
+        return;
+    }
 
     if ((o = lookupKeyWriteOrReply(c,c->argv[1],shared.czero)) == NULL ||
         checkType(c,o,REDIS_ZSET)) return;
@@ -838,7 +846,10 @@ void genericZrangebyscoreCommand(redisClient *c, int reverse, int justcount) {
     void *replylen = NULL;
 
     /* Parse the range arguments. */
-    zslParseRange(c->argv[2],c->argv[3],&range);
+    if (zslParseRange(c->argv[2],c->argv[3],&range) != REDIS_OK) {
+        addReplyError(c,"min or max is not a double");
+        return;
+    }
 
     /* Parse optional extra arguments. Note that ZCOUNT will exactly have
      * 4 arguments, so we'll never enter the following code path. */