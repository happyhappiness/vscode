 void zaddGenericCommand(redisClient *c, int incr) {
     static char *nanerr = "resulting score is not a number (NaN)";
     robj *key = c->argv[1];
     robj *ele;
     robj *zobj;
     robj *curobj;
-    double score = 0, *scores, curscore = 0.0;
+    double score = 0, *scores = NULL, curscore = 0.0;
     int j, elements = (c->argc-2)/2;
-    int added = 0;
+    int added = 0, updated = 0;
 
     if (c->argc % 2) {
         addReply(c,shared.syntaxerr);
         return;
     }
 
     /* Start parsing all the scores, we need to emit any syntax error
      * before executing additions to the sorted set, as the command should
      * either execute fully or nothing at all. */
     scores = zmalloc(sizeof(double)*elements);
     for (j = 0; j < elements; j++) {
         if (getDoubleFromObjectOrReply(c,c->argv[2+j*2],&scores[j],NULL)
-            != REDIS_OK)
-        {
-            zfree(scores);
-            return;
-        }
+            != REDIS_OK) goto cleanup;
     }
 
     /* Lookup the key and create the sorted set if does not exist. */
     zobj = lookupKeyWrite(c->db,key);
     if (zobj == NULL) {
         if (server.zset_max_ziplist_entries == 0 ||
