@@ -438,10 +438,13 @@ int HelloHCopy_RedisCommand(RedisModuleCtx *ctx, RedisModuleString **argv, int a
         return RedisModule_ReplyWithError(ctx,REDISMODULE_ERRORMSG_WRONGTYPE);
     }
 
-    /* XXX modify me. */
-    RedisModule_HashSet(key,REDISMODULE_HSET_NONE,argv[2],argv[3],NULL);
-    RedisModule_HashSet(key,REDISMODULE_HSET_CFIELDS,"foo",argv[3],NULL);
-    RedisModule_ReplyWithLongLong(ctx,0);
+    /* Get the old field value. */
+    RedisModuleString *oldval;
+    RedisModule_HashGet(key,REDISMODULE_HGET_NONE,argv[2],&oldval,NULL);
+    if (oldval) {
+        RedisModule_HashSet(key,REDISMODULE_HSET_NONE,argv[3],oldval,NULL);
+    }
+    RedisModule_ReplyWithLongLong(ctx,oldval != NULL);
     return REDISMODULE_OK;
 }
 