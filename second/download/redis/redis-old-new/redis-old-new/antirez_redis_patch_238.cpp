@@ -387,7 +387,7 @@ int HelloZsumRange_RedisCommand(RedisModuleCtx *ctx, RedisModuleString **argv, i
  * The command will return all the sorted set items that are lexicographically
  * between the specified range (using the same format as ZRANGEBYLEX)
  * and having an age between min_age and max_age. */
-int HelloZsumRange_RedisCommand(RedisModuleCtx *ctx, RedisModuleString **argv, int argc) {
+int HelloLexRange_RedisCommand(RedisModuleCtx *ctx, RedisModuleString **argv, int argc) {
     RedisModule_AutoMemory(ctx); /* Use automatic memory management. */
 
     if (argc != 6) return RedisModule_WrongArity(ctx);
@@ -398,9 +398,12 @@ int HelloZsumRange_RedisCommand(RedisModuleCtx *ctx, RedisModuleString **argv, i
         return RedisModule_ReplyWithError(ctx,REDISMODULE_ERRORMSG_WRONGTYPE);
     }
 
-    RedisModule_ReplyWithArray(ctx,REDISMODULE_POSTPONED_ARRAY_LEN);
-    RedisModule_ZsetFirstInLexRange(key,argv[2],argv[3]);
+    if (RedisModule_ZsetFirstInLexRange(key,argv[2],argv[3]) != REDISMODULE_OK) {
+        return RedisModule_ReplyWithError(ctx,"invalid range");
+    }
+
     int arraylen = 0;
+    RedisModule_ReplyWithArray(ctx,REDISMODULE_POSTPONED_ARRAY_LEN);
     while(!RedisModule_ZsetRangeEndReached(key)) {
         double score;
         RedisModuleString *ele = RedisModule_ZsetRangeCurrentElement(key,&score);
@@ -410,7 +413,7 @@ int HelloZsumRange_RedisCommand(RedisModuleCtx *ctx, RedisModuleString **argv, i
         arraylen++;
     }
     RedisModule_ZsetRangeStop(key);
-    RedisModule_SetArrayLength(ctx,arraylen);
+    RedisModule_ReplySetArrayLength(ctx,arraylen);
     RedisModule_CloseKey(key);
     return REDISMODULE_OK;
 }
@@ -473,5 +476,9 @@ int RedisModule_OnLoad(RedisModuleCtx *ctx) {
         HelloZsumRange_RedisCommand) == REDISMODULE_ERR)
         return REDISMODULE_ERR;
 
+    if (RedisModule_CreateCommand(ctx,"hello.lexrange",
+        HelloLexRange_RedisCommand) == REDISMODULE_ERR)
+        return REDISMODULE_ERR;
+
     return REDISMODULE_OK;
 }