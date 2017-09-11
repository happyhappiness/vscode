@@ -93,6 +93,25 @@ int TestStringAppendAM(RedisModuleCtx *ctx, RedisModuleString **argv, int argc)
     return REDISMODULE_OK;
 }
 
+/* TEST.STRING.PRINTF -- Test string formatting. */
+int TestStringPrintf(RedisModuleCtx *ctx, RedisModuleString **argv, int argc) {
+    RedisModule_AutoMemory(ctx);
+    if (argc < 3) {
+        return RedisModule_WrongArity(ctx);
+    }
+    RedisModuleString *s = RedisModule_CreateStringPrintf(ctx, 
+        "Got %d args. argv[1]: %s, argv[2]: %s", 
+        argc, 
+        RedisModule_StringPtrLen(argv[1], NULL),
+        RedisModule_StringPtrLen(argv[2], NULL)
+    );
+
+    RedisModule_ReplyWithString(ctx,s);
+
+    return REDISMODULE_OK;
+}
+
+
 /* ----------------------------- Test framework ----------------------------- */
 
 /* Return 1 if the reply matches the specified string, otherwise log errors
@@ -163,6 +182,9 @@ int TestIt(RedisModuleCtx *ctx, RedisModuleString **argv, int argc) {
     T("test.string.append.am","");
     if (!TestAssertStringReply(ctx,reply,"foobar",6)) goto fail;
 
+    T("test.string.printf", "cc", "foo", "bar");
+    if (!TestAssertStringReply(ctx,reply,"Got 3 args. argv[1]: foo, argv[2]: bar",38)) goto fail;
+
     RedisModule_ReplyWithSimpleString(ctx,"ALL TESTS PASSED");
     return REDISMODULE_OK;
 
@@ -188,6 +210,10 @@ int RedisModule_OnLoad(RedisModuleCtx *ctx, RedisModuleString **argv, int argc)
         TestStringAppendAM,"write deny-oom",1,1,1) == REDISMODULE_ERR)
         return REDISMODULE_ERR;
 
+    if (RedisModule_CreateCommand(ctx,"test.string.printf",
+        TestStringPrintf,"write deny-oom",1,1,1) == REDISMODULE_ERR)
+        return REDISMODULE_ERR;
+
     if (RedisModule_CreateCommand(ctx,"test.it",
         TestIt,"readonly",1,1,1) == REDISMODULE_ERR)
         return REDISMODULE_ERR;