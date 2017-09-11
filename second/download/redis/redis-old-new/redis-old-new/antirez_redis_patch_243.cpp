@@ -327,7 +327,11 @@ int HelloMoreExpire_RedisCommand(RedisModuleCtx *ctx, RedisModuleString **argv,
 }
 
 /* HELLO.ZSUMRANGE key startscore endscore
- * Return the sum of all the scores elements between startscore and endscore. */
+ * Return the sum of all the scores elements between startscore and endscore.
+ *
+ * The computation is performed two times, one time from start to end and
+ * another time backward. The two scores, returned as a two element array,
+ * should match.*/
 int HelloZsumRange_RedisCommand(RedisModuleCtx *ctx, RedisModuleString **argv, int argc) {
     RedisModuleZsetRange zrange = REDISMODULE_ZSET_RANGE_INIT;
     zrange.type = REDISMODULE_ZSET_RANGE_SCORE;
@@ -344,18 +348,35 @@ int HelloZsumRange_RedisCommand(RedisModuleCtx *ctx, RedisModuleString **argv, i
         return RedisModule_ReplyWithError(ctx,REDISMODULE_ERRORMSG_WRONGTYPE);
     }
 
+    double scoresum_a = 0;
+    double scoresum_b = 0;
+
     RedisModule_ZsetFirstInRange(key,&zrange);
-    double scoresum = 0;
     while(!RedisModule_ZsetRangeEndReached(key)) {
         double score;
         RedisModuleString *ele = RedisModule_ZsetRangeCurrentElement(key,&score);
         RedisModule_FreeString(ctx,ele);
-        scoresum += score;
+        scoresum_a += score;
         RedisModule_ZsetRangeNext(key);
     }
     RedisModule_ZsetRangeStop(key);
+
+    RedisModule_ZsetLastInRange(key,&zrange);
+    while(!RedisModule_ZsetRangeEndReached(key)) {
+        double score;
+        RedisModuleString *ele = RedisModule_ZsetRangeCurrentElement(key,&score);
+        RedisModule_FreeString(ctx,ele);
+        scoresum_b += score;
+        RedisModule_ZsetRangePrev(key);
+    }
+
+    RedisModule_ZsetRangeStop(key);
+
     RedisModule_CloseKey(key);
-    RedisModule_ReplyWithDouble(ctx,scoresum);
+
+    RedisModule_ReplyWithArray(ctx,2);
+    RedisModule_ReplyWithDouble(ctx,scoresum_a);
+    RedisModule_ReplyWithDouble(ctx,scoresum_b);
     return REDISMODULE_OK;
 }
 