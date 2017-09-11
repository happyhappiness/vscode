@@ -333,14 +333,13 @@ int HelloMoreExpire_RedisCommand(RedisModuleCtx *ctx, RedisModuleString **argv,
  * another time backward. The two scores, returned as a two element array,
  * should match.*/
 int HelloZsumRange_RedisCommand(RedisModuleCtx *ctx, RedisModuleString **argv, int argc) {
-    RedisModuleZsetRange zrange = REDISMODULE_ZSET_RANGE_INIT;
-    zrange.type = REDISMODULE_ZSET_RANGE_SCORE;
-    if (RedisModule_StringToDouble(argv[2],&zrange.score_start) != REDISMODULE_OK ||
-        RedisModule_StringToDouble(argv[3],&zrange.score_end) != REDISMODULE_OK)
+    double score_start, score_end;
+
+    if (RedisModule_StringToDouble(argv[2],&score_start) != REDISMODULE_OK ||
+        RedisModule_StringToDouble(argv[3],&score_end) != REDISMODULE_OK)
     {
         return RedisModule_ReplyWithError(ctx,"ERR invalid range");
     }
-    zrange.flags = 0;
 
     RedisModuleKey *key = RedisModule_OpenKey(ctx,argv[1],
         REDISMODULE_READ|REDISMODULE_WRITE);
@@ -351,7 +350,7 @@ int HelloZsumRange_RedisCommand(RedisModuleCtx *ctx, RedisModuleString **argv, i
     double scoresum_a = 0;
     double scoresum_b = 0;
 
-    RedisModule_ZsetFirstInRange(key,&zrange);
+    RedisModule_ZsetFirstInScoreRange(key,score_start,score_end,0,0);
     while(!RedisModule_ZsetRangeEndReached(key)) {
         double score;
         RedisModuleString *ele = RedisModule_ZsetRangeCurrentElement(key,&score);
@@ -361,7 +360,7 @@ int HelloZsumRange_RedisCommand(RedisModuleCtx *ctx, RedisModuleString **argv, i
     }
     RedisModule_ZsetRangeStop(key);
 
-    RedisModule_ZsetLastInRange(key,&zrange);
+    RedisModule_ZsetLastInScoreRange(key,score_start,score_end,0,0);
     while(!RedisModule_ZsetRangeEndReached(key)) {
         double score;
         RedisModuleString *ele = RedisModule_ZsetRangeCurrentElement(key,&score);