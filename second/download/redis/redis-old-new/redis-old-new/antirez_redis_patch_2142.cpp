@@ -3065,6 +3065,77 @@ static size_t stringObjectLen(robj *o) {
     }
 }
 
+static int getDoubleFromObject(redisClient *c, robj *o, double *value) {
+    double parsedValue;
+    char *eptr = NULL;
+
+    if (o && o->type != REDIS_STRING) {
+        addReplySds(c,sdsnew("-ERR value is not a double\r\n"));
+        return REDIS_ERR;
+    }
+
+    if (o == NULL)
+        parsedValue = 0;
+    else if (o->encoding == REDIS_ENCODING_RAW)
+        parsedValue = strtod(o->ptr, &eptr);
+    else if (o->encoding == REDIS_ENCODING_INT)
+        parsedValue = (long)o->ptr;
+    else
+        redisAssert(1 != 1);
+
+    if (eptr != NULL && *eptr != '\0') {
+        addReplySds(c,sdsnew("-ERR value is not a double\r\n"));
+        return REDIS_ERR;
+    }
+
+    *value = parsedValue;
+
+    return REDIS_OK;
+}
+
+static int getLongLongFromObject(redisClient *c, robj *o, long long *value) {
+    long long parsedValue;
+    char *eptr = NULL;
+
+    if (o && o->type != REDIS_STRING) {
+        addReplySds(c,sdsnew("-ERR value is not an integer\r\n"));
+        return REDIS_ERR;
+    }
+
+    if (o == NULL)
+        parsedValue = 0;
+    else if (o->encoding == REDIS_ENCODING_RAW)
+        parsedValue = strtoll(o->ptr, &eptr, 10);
+    else if (o->encoding == REDIS_ENCODING_INT)
+        parsedValue = (long)o->ptr;
+    else
+        redisAssert(1 != 1);
+
+    if (eptr != NULL && *eptr != '\0') {
+        addReplySds(c,sdsnew("-ERR value is not an integer\r\n"));
+        return REDIS_ERR;
+    }
+
+    *value = parsedValue;
+
+    return REDIS_OK;
+}
+
+static int getLongFromObject(redisClient *c, robj *o, long *value) {
+    long long actualValue;
+
+    if (getLongLongFromObject(c, o, &actualValue) != REDIS_OK) return REDIS_ERR;
+
+    if (actualValue < LONG_MIN || actualValue > LONG_MAX) {
+        addReplySds(c,sdsnew("-ERR value is out of range\r\n"));
+        return REDIS_ERR;
+    }
+
+    *value = actualValue;
+
+    return REDIS_OK;
+}
+
 /*============================ RDB saving/loading =========================== */
 
 static int rdbSaveType(FILE *fp, unsigned char type) {
@@ -3950,22 +4021,8 @@ static void incrDecrCommand(redisClient *c, long long incr) {
     robj *o;
 
     o = lookupKeyWrite(c->db,c->argv[1]);
-    if (o == NULL) {
-        value = 0;
-    } else {
-        if (o->type != REDIS_STRING) {
-            value = 0;
-        } else {
-            char *eptr;
 
-            if (o->encoding == REDIS_ENCODING_RAW)
-                value = strtoll(o->ptr, &eptr, 10);
-            else if (o->encoding == REDIS_ENCODING_INT)
-                value = (long)o->ptr;
-            else
-                redisAssert(1 != 1);
-        }
-    }
+    if (getLongLongFromObject(c, o, &value) != REDIS_OK) return;
 
     value += incr;
     o = createObject(REDIS_STRING,sdscatprintf(sdsempty(),"%lld",value));
@@ -3992,12 +4049,18 @@ static void decrCommand(redisClient *c) {
 }
 
 static void incrbyCommand(redisClient *c) {
-    long long incr = strtoll(c->argv[2]->ptr, NULL, 10);
+    long long incr;
+
+    if (getLongLongFromObject(c, c->argv[2], &incr) != REDIS_OK) return;
+
     incrDecrCommand(c,incr);
 }
 
 static void decrbyCommand(redisClient *c) {
-    long long incr = strtoll(c->argv[2]->ptr, NULL, 10);
+    long long incr;
+
+    if (getLongLongFromObject(c, c->argv[2], &incr) != REDIS_OK) return;
+
     incrDecrCommand(c,-incr);
 }
 
@@ -5395,14 +5458,16 @@ static void zaddGenericCommand(redisClient *c, robj *key, robj *ele, double scor
 static void zaddCommand(redisClient *c) {
     double scoreval;
 
-    scoreval = strtod(c->argv[2]->ptr,NULL);
+    if (getDoubleFromObject(c, c->argv[2], &scoreval) != REDIS_OK) return;
+
     zaddGenericCommand(c,c->argv[1],c->argv[3],scoreval,0);
 }
 
 static void zincrbyCommand(redisClient *c) {
     double scoreval;
 
-    scoreval = strtod(c->argv[2]->ptr,NULL);
+    if (getDoubleFromObject(c, c->argv[2], &scoreval) != REDIS_OK) return;
+
     zaddGenericCommand(c,c->argv[1],c->argv[3],scoreval,1);
 }
 
@@ -5436,12 +5501,15 @@ static void zremCommand(redisClient *c) {
 }
 
 static void zremrangebyscoreCommand(redisClient *c) {
-    double min = strtod(c->argv[2]->ptr,NULL);
-    double max = strtod(c->argv[3]->ptr,NULL);
+    double min;
+    double max;
     long deleted;
     robj *zsetobj;
     zset *zs;
 
+    if ((getDoubleFromObject(c, c->argv[2], &min) != REDIS_OK) ||
+        (getDoubleFromObject(c, c->argv[3], &max) != REDIS_OK)) return;
+
     if ((zsetobj = lookupKeyWriteOrReply(c,c->argv[1],shared.czero)) == NULL ||
         checkType(c,zsetobj,REDIS_ZSET)) return;
 
@@ -5454,13 +5522,16 @@ static void zremrangebyscoreCommand(redisClient *c) {
 }
 
 static void zremrangebyrankCommand(redisClient *c) {
-    int start = atoi(c->argv[2]->ptr);
-    int end = atoi(c->argv[3]->ptr);
+    long start;
+    long end;
     int llen;
     long deleted;
     robj *zsetobj;
     zset *zs;
 
+    if ((getLongFromObject(c, c->argv[2], &start) != REDIS_OK) ||
+        (getLongFromObject(c, c->argv[3], &end) != REDIS_OK)) return;
+
     if ((zsetobj = lookupKeyWriteOrReply(c,c->argv[1],shared.czero)) == NULL ||
         checkType(c,zsetobj,REDIS_ZSET)) return;
     zs = zsetobj->ptr;
@@ -5567,7 +5638,8 @@ static void zunionInterGenericCommand(redisClient *c, robj *dstkey, int op) {
             if (remaining >= (zsetnum + 1) && !strcasecmp(c->argv[j]->ptr,"weights")) {
                 j++; remaining--;
                 for (i = 0; i < zsetnum; i++, j++, remaining--) {
-                    src[i].weight = strtod(c->argv[j]->ptr, NULL);
+                    if (getDoubleFromObject(c, c->argv[j], &src[i].weight) != REDIS_OK)
+                        return;
                 }
             } else if (remaining >= 2 && !strcasecmp(c->argv[j]->ptr,"aggregate")) {
                 j++; remaining--;
@@ -5689,8 +5761,8 @@ static void zinterCommand(redisClient *c) {
 
 static void zrangeGenericCommand(redisClient *c, int reverse) {
     robj *o;
-    int start = atoi(c->argv[2]->ptr);
-    int end = atoi(c->argv[3]->ptr);
+    long start;
+    long end;
     int withscores = 0;
     int llen;
     int rangelen, j;
@@ -5699,6 +5771,9 @@ static void zrangeGenericCommand(redisClient *c, int reverse) {
     zskiplistNode *ln;
     robj *ele;
 
+    if ((getLongFromObject(c, c->argv[2], &start) != REDIS_OK) ||
+        (getLongFromObject(c, c->argv[3], &end) != REDIS_OK)) return;
+
     if (c->argc == 5 && !strcasecmp(c->argv[4]->ptr,"withscores")) {
         withscores = 1;
     } else if (c->argc >= 5) {
@@ -6085,7 +6160,8 @@ static void hincrbyCommand(redisClient *c) {
         }
     }
 
-    incr = strtoll(c->argv[3]->ptr, NULL, 10);
+    if (getLongLongFromObject(c, c->argv[3], &incr) != REDIS_OK) return;
+
     if (o->encoding == REDIS_ENCODING_ZIPMAP) {
         unsigned char *zm = o->ptr;
         unsigned char *zval;
@@ -6917,8 +6993,13 @@ static int deleteIfVolatile(redisDb *db, robj *key) {
     return dictDelete(db->dict,key) == DICT_OK;
 }
 
-static void expireGenericCommand(redisClient *c, robj *key, time_t seconds) {
+static void expireGenericCommand(redisClient *c, robj *key, robj *param, long offset) {
     dictEntry *de;
+    time_t seconds;
+
+    if (getLongFromObject(c, param, &seconds) != REDIS_OK) return;
+
+    seconds -= offset;
 
     de = dictFind(c->db->dict,key);
     if (de == NULL) {
@@ -6942,11 +7023,11 @@ static void expireGenericCommand(redisClient *c, robj *key, time_t seconds) {
 }
 
 static void expireCommand(redisClient *c) {
-    expireGenericCommand(c,c->argv[1],strtol(c->argv[2]->ptr,NULL,10));
+    expireGenericCommand(c,c->argv[1],c->argv[2],0);
 }
 
 static void expireatCommand(redisClient *c) {
-    expireGenericCommand(c,c->argv[1],strtol(c->argv[2]->ptr,NULL,10)-time(NULL));
+    expireGenericCommand(c,c->argv[1],c->argv[2],time(NULL));
 }
 
 static void ttlCommand(redisClient *c) {