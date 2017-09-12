@@ -4334,8 +4334,7 @@ static void incrDecrCommand(redisClient *c, long long incr) {
     if (getLongLongFromObjectOrReply(c,o,&value,NULL) != REDIS_OK) return;
 
     value += incr;
-    o = createObject(REDIS_STRING,sdscatprintf(sdsempty(),"%lld",value));
-    o = tryObjectEncoding(o);
+    o = createStringObjectFromLongLong(value);
     retval = dictAdd(c->db->dict,c->argv[1],o);
     if (retval == DICT_ERR) {
         dictReplace(c->db->dict,c->argv[1],o);