@@ -418,6 +418,33 @@ int HelloLexRange_RedisCommand(RedisModuleCtx *ctx, RedisModuleString **argv, in
     return REDISMODULE_OK;
 }
 
+/* HELLO.HCOPY key srcfield dstfield
+ * This is just an example command that sets the hash field dstfield to the
+ * same value of srcfield. If srcfield does not exist no operation is
+ * performed.
+ *
+ * The command returns 1 if the copy is performed (srcfield exists) otherwise
+ * 0 is returned. */
+int HelloHCopy_RedisCommand(RedisModuleCtx *ctx, RedisModuleString **argv, int argc) {
+    RedisModule_AutoMemory(ctx); /* Use automatic memory management. */
+
+    if (argc != 4) return RedisModule_WrongArity(ctx);
+    RedisModuleKey *key = RedisModule_OpenKey(ctx,argv[1],
+        REDISMODULE_READ|REDISMODULE_WRITE);
+    int type = RedisModule_KeyType(key);
+    if (type != REDISMODULE_KEYTYPE_HASH &&
+        type != REDISMODULE_KEYTYPE_EMPTY)
+    {
+        return RedisModule_ReplyWithError(ctx,REDISMODULE_ERRORMSG_WRONGTYPE);
+    }
+
+    /* XXX modify me. */
+    RedisModule_HashSet(key,REDISMODULE_HSET_NONE,argv[2],argv[3],NULL);
+    RedisModule_HashSet(key,REDISMODULE_HSET_CFIELDS,"foo",argv[3],NULL);
+    RedisModule_ReplyWithLongLong(ctx,0);
+    return REDISMODULE_OK;
+}
+
 /* This function must be present on each Redis module. It is used in order to
  * register the commands into the Redis server. */
 int RedisModule_OnLoad(RedisModuleCtx *ctx) {
@@ -480,5 +507,9 @@ int RedisModule_OnLoad(RedisModuleCtx *ctx) {
         HelloLexRange_RedisCommand) == REDISMODULE_ERR)
         return REDISMODULE_ERR;
 
+    if (RedisModule_CreateCommand(ctx,"hello.hcopy",
+        HelloHCopy_RedisCommand) == REDISMODULE_ERR)
+        return REDISMODULE_ERR;
+
     return REDISMODULE_OK;
 }