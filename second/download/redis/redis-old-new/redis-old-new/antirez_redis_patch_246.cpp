@@ -97,7 +97,8 @@ int HelloListSplice_RedisCommand(RedisModuleCtx *ctx, RedisModuleString **argv,
     }
 
     long long count;
-    if (RedisModule_StringToLongLong(argv[3],&count) != REDISMODULE_OK) {
+    if ((RedisModule_StringToLongLong(argv[3],&count) != REDISMODULE_OK) ||
+        (count < 0)) {
         RedisModule_CloseKey(srckey);
         RedisModule_CloseKey(dstkey);
         return RedisModule_ReplyWithError(ctx,"ERR invalid count");
@@ -141,8 +142,11 @@ int HelloListSpliceAuto_RedisCommand(RedisModuleCtx *ctx, RedisModuleString **ar
     }
 
     long long count;
-    if (RedisModule_StringToLongLong(argv[3],&count) != REDISMODULE_OK)
+    if ((RedisModule_StringToLongLong(argv[3],&count) != REDISMODULE_OK) ||
+        (count < 0))
+    {
         return RedisModule_ReplyWithError(ctx,"ERR invalid count");
+    }
 
     while(count-- > 0) {
         RedisModuleString *ele;