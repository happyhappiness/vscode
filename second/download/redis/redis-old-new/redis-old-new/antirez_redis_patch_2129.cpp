@@ -3104,74 +3104,100 @@ static size_t stringObjectLen(robj *o) {
     }
 }
 
-static int getDoubleFromObject(redisClient *c, robj *o, double *value) {
-    double parsedValue;
+static int getDoubleFromObject(robj *o, double *target) {
+    double value;
     char *eptr = NULL;
 
-    if (o && o->type != REDIS_STRING) {
-        addReplySds(c,sdsnew("-ERR value is not a double\r\n"));
+    if (o == NULL) {
+        value = 0;
+    } else {
+        redisAssert(o->type == REDIS_STRING);
+        if (o->encoding == REDIS_ENCODING_RAW) {
+            value = strtod(o->ptr, &eptr);
+        } else if (o->encoding == REDIS_ENCODING_INT) {
+            value = (long)o->ptr;
+        } else {
+            redisAssert(1 != 1);
+        }
+    }
+
+    if (eptr != NULL && eptr[0] != '\0') {
         return REDIS_ERR;
     }
 
-    if (o == NULL)
-        parsedValue = 0;
-    else if (o->encoding == REDIS_ENCODING_RAW)
-        parsedValue = strtod(o->ptr, &eptr);
-    else if (o->encoding == REDIS_ENCODING_INT)
-        parsedValue = (long)o->ptr;
-    else
-        redisAssert(1 != 1);
+    *target = value;
+    return REDIS_OK;
+}
 
-    if (eptr != NULL && *eptr != '\0') {
-        addReplySds(c,sdsnew("-ERR value is not a double\r\n"));
+static int getDoubleFromObjectOrReply(redisClient *c, robj *o, double *target, const char *msg) {
+    double value;
+    if (getDoubleFromObject(o, &value) != REDIS_OK) {
+        if (msg != NULL) {
+            addReplySds(c, sdscatprintf(sdsempty(), "-ERR %s\r\n", msg));
+        } else {
+            addReplySds(c, sdsnew("-ERR value is not a double\r\n"));
+        }
         return REDIS_ERR;
     }
 
-    *value = parsedValue;
-
+    *target = value;
     return REDIS_OK;
 }
 
-static int getLongLongFromObject(redisClient *c, robj *o, long long *value) {
-    long long parsedValue;
+static int getLongLongFromObject(robj *o, long long *target) {
+    long long value;
     char *eptr = NULL;
 
-    if (o && o->type != REDIS_STRING) {
-        addReplySds(c,sdsnew("-ERR value is not an integer\r\n"));
+    if (o == NULL) {
+        value = 0;
+    } else {
+        redisAssert(o->type == REDIS_STRING);
+        if (o->encoding == REDIS_ENCODING_RAW) {
+            value = strtoll(o->ptr, &eptr, 10);
+        } else if (o->encoding == REDIS_ENCODING_INT) {
+            value = (long)o->ptr;
+        } else {
+            redisAssert(1 != 1);
+        }
+    }
+
+    if (eptr != NULL && eptr[0] != '\0') {
         return REDIS_ERR;
     }
 
-    if (o == NULL)
-        parsedValue = 0;
-    else if (o->encoding == REDIS_ENCODING_RAW)
-        parsedValue = strtoll(o->ptr, &eptr, 10);
-    else if (o->encoding == REDIS_ENCODING_INT)
-        parsedValue = (long)o->ptr;
-    else
-        redisAssert(1 != 1);
+    *target = value;
+    return REDIS_OK;
+}
 
-    if (eptr != NULL && *eptr != '\0') {
-        addReplySds(c,sdsnew("-ERR value is not an integer\r\n"));
+static int getLongLongFromObjectOrReply(redisClient *c, robj *o, long long *target, const char *msg) {
+    long long value;
+    if (getLongLongFromObject(o, &value) != REDIS_OK) {
+        if (msg != NULL) {
+            addReplySds(c, sdscatprintf(sdsempty(), "-ERR %s\r\n", msg));
+        } else {
+            addReplySds(c, sdsnew("-ERR value is not an integer\r\n"));
+        }
         return REDIS_ERR;
     }
 
-    *value = parsedValue;
-
+    *target = value;
     return REDIS_OK;
 }
 
-static int getLongFromObject(redisClient *c, robj *o, long *value) {
-    long long actualValue;
-
-    if (getLongLongFromObject(c, o, &actualValue) != REDIS_OK) return REDIS_ERR;
+static int getLongFromObjectOrReply(redisClient *c, robj *o, long *target, const char *msg) {
+    long long value;
 
-    if (actualValue < LONG_MIN || actualValue > LONG_MAX) {
-        addReplySds(c,sdsnew("-ERR value is out of range\r\n"));
+    if (getLongLongFromObjectOrReply(c, o, &value, msg) != REDIS_OK) return REDIS_ERR;
+    if (value < LONG_MIN || value > LONG_MAX) {
+        if (msg != NULL) {
+            addReplySds(c, sdscatprintf(sdsempty(), "-ERR %s\r\n", msg));
+        } else {
+            addReplySds(c, sdsnew("-ERR value is out of range\r\n"));
+        }
         return REDIS_ERR;
     }
 
-    *value = actualValue;
-
+    *target = value;
     return REDIS_OK;
 }
 
@@ -4061,7 +4087,7 @@ static void incrDecrCommand(redisClient *c, long long incr) {
 
     o = lookupKeyWrite(c->db,c->argv[1]);
 
-    if (getLongLongFromObject(c, o, &value) != REDIS_OK) return;
+    if (getLongLongFromObjectOrReply(c, o, &value, NULL) != REDIS_OK) return;
 
     value += incr;
     o = createObject(REDIS_STRING,sdscatprintf(sdsempty(),"%lld",value));
@@ -4090,16 +4116,14 @@ static void decrCommand(redisClient *c) {
 static void incrbyCommand(redisClient *c) {
     long long incr;
 
-    if (getLongLongFromObject(c, c->argv[2], &incr) != REDIS_OK) return;
-
+    if (getLongLongFromObjectOrReply(c, c->argv[2], &incr, NULL) != REDIS_OK) return;
     incrDecrCommand(c,incr);
 }
 
 static void decrbyCommand(redisClient *c) {
     long long incr;
 
-    if (getLongLongFromObject(c, c->argv[2], &incr) != REDIS_OK) return;
-
+    if (getLongLongFromObjectOrReply(c, c->argv[2], &incr, NULL) != REDIS_OK) return;
     incrDecrCommand(c,-incr);
 }
 
@@ -5497,16 +5521,14 @@ static void zaddGenericCommand(redisClient *c, robj *key, robj *ele, double scor
 static void zaddCommand(redisClient *c) {
     double scoreval;
 
-    if (getDoubleFromObject(c, c->argv[2], &scoreval) != REDIS_OK) return;
-
+    if (getDoubleFromObjectOrReply(c, c->argv[2], &scoreval, NULL) != REDIS_OK) return;
     zaddGenericCommand(c,c->argv[1],c->argv[3],scoreval,0);
 }
 
 static void zincrbyCommand(redisClient *c) {
     double scoreval;
 
-    if (getDoubleFromObject(c, c->argv[2], &scoreval) != REDIS_OK) return;
-
+    if (getDoubleFromObjectOrReply(c, c->argv[2], &scoreval, NULL) != REDIS_OK) return;
     zaddGenericCommand(c,c->argv[1],c->argv[3],scoreval,1);
 }
 
@@ -5546,8 +5568,8 @@ static void zremrangebyscoreCommand(redisClient *c) {
     robj *zsetobj;
     zset *zs;
 
-    if ((getDoubleFromObject(c, c->argv[2], &min) != REDIS_OK) ||
-        (getDoubleFromObject(c, c->argv[3], &max) != REDIS_OK)) return;
+    if ((getDoubleFromObjectOrReply(c, c->argv[2], &min, NULL) != REDIS_OK) ||
+        (getDoubleFromObjectOrReply(c, c->argv[3], &max, NULL) != REDIS_OK)) return;
 
     if ((zsetobj = lookupKeyWriteOrReply(c,c->argv[1],shared.czero)) == NULL ||
         checkType(c,zsetobj,REDIS_ZSET)) return;
@@ -5568,8 +5590,8 @@ static void zremrangebyrankCommand(redisClient *c) {
     robj *zsetobj;
     zset *zs;
 
-    if ((getLongFromObject(c, c->argv[2], &start) != REDIS_OK) ||
-        (getLongFromObject(c, c->argv[3], &end) != REDIS_OK)) return;
+    if ((getLongFromObjectOrReply(c, c->argv[2], &start, NULL) != REDIS_OK) ||
+        (getLongFromObjectOrReply(c, c->argv[3], &end, NULL) != REDIS_OK)) return;
 
     if ((zsetobj = lookupKeyWriteOrReply(c,c->argv[1],shared.czero)) == NULL ||
         checkType(c,zsetobj,REDIS_ZSET)) return;
@@ -5677,7 +5699,7 @@ static void zunionInterGenericCommand(redisClient *c, robj *dstkey, int op) {
             if (remaining >= (zsetnum + 1) && !strcasecmp(c->argv[j]->ptr,"weights")) {
                 j++; remaining--;
                 for (i = 0; i < zsetnum; i++, j++, remaining--) {
-                    if (getDoubleFromObject(c, c->argv[j], &src[i].weight) != REDIS_OK)
+                    if (getDoubleFromObjectOrReply(c, c->argv[j], &src[i].weight, NULL) != REDIS_OK)
                         return;
                 }
             } else if (remaining >= 2 && !strcasecmp(c->argv[j]->ptr,"aggregate")) {
@@ -5810,8 +5832,8 @@ static void zrangeGenericCommand(redisClient *c, int reverse) {
     zskiplistNode *ln;
     robj *ele;
 
-    if ((getLongFromObject(c, c->argv[2], &start) != REDIS_OK) ||
-        (getLongFromObject(c, c->argv[3], &end) != REDIS_OK)) return;
+    if ((getLongFromObjectOrReply(c, c->argv[2], &start, NULL) != REDIS_OK) ||
+        (getLongFromObjectOrReply(c, c->argv[3], &end, NULL) != REDIS_OK)) return;
 
     if (c->argc == 5 && !strcasecmp(c->argv[4]->ptr,"withscores")) {
         withscores = 1;
@@ -6318,7 +6340,7 @@ static void hincrbyCommand(redisClient *c) {
     long long value, incr;
     robj *o, *current, *new;
 
-    if (getLongLongFromObject(c,c->argv[3],&incr) != REDIS_OK) return;
+    if (getLongLongFromObjectOrReply(c,c->argv[3],&incr,NULL) != REDIS_OK) return;
     if ((o = hashLookupWriteOrCreate(c,c->argv[1])) == NULL) return;
     if ((current = hashGet(o,c->argv[2])) != NULL) {
         if (current->encoding == REDIS_ENCODING_RAW)
@@ -7096,7 +7118,7 @@ static void expireGenericCommand(redisClient *c, robj *key, robj *param, long of
     dictEntry *de;
     time_t seconds;
 
-    if (getLongFromObject(c, param, &seconds) != REDIS_OK) return;
+    if (getLongFromObjectOrReply(c, param, &seconds, NULL) != REDIS_OK) return;
 
     seconds -= offset;
 