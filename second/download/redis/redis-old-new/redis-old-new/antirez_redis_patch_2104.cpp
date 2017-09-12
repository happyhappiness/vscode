@@ -4231,8 +4231,8 @@ static void incrDecrCommand(redisClient *c, long long incr) {
     robj *o;
 
     o = lookupKeyWrite(c->db,c->argv[1]);
-
-    if (getLongLongFromObjectOrReply(c, o, &value, NULL) != REDIS_OK) return;
+    if (o != NULL && checkType(c,o,REDIS_STRING)) return;
+    if (getLongLongFromObjectOrReply(c,o,&value,NULL) != REDIS_OK) return;
 
     value += incr;
     o = createObject(REDIS_STRING,sdscatprintf(sdsempty(),"%lld",value));