@@ -50,10 +50,12 @@ struct RedisModuleCtx {
     int amqueue_len;                /* Number of slots in amqueue. */
     int amqueue_used;               /* Number of used slots in amqueue. */
     int flags;                      /* REDISMODULE_CTX_... flags. */
+    void **postponed_arrays;        /* To set with RM_ReplySetArrayLength(). */
+    int postponed_arrays_count;     /* Number of entries in postponed_arrays. */
 };
 typedef struct RedisModuleCtx RedisModuleCtx;
 
-#define REDISMODULE_CTX_INIT {(void*)(unsigned long)&RM_GetApi, NULL, NULL, NULL, 0, 0, 0}
+#define REDISMODULE_CTX_INIT {(void*)(unsigned long)&RM_GetApi, NULL, NULL, NULL, 0, 0, 0, NULL, 0}
 #define REDISMODULE_CTX_MULTI_EMITTED (1<<0)
 #define REDISMODULE_CTX_AUTO_MEMORY (1<<1)
 
@@ -227,6 +229,21 @@ int RM_GetApi(const char *funcname, void **targetPtrPtr) {
     return REDISMODULE_OK;
 }
 
+/* Free the context after the user function was called. */
+void moduleFreeContext(RedisModuleCtx *ctx) {
+    autoMemoryCollect(ctx);
+    if (ctx->postponed_arrays) {
+        zfree(ctx->postponed_arrays);
+        ctx->postponed_arrays_count = 0;
+        serverLog(LL_WARNING,
+            "API misuse detected in module %s: "
+            "RedisModule_ReplyWithArray(REDISMODULE_POSTPONED_ARRAY_LEN) "
+            "not matched by the same number of RedisModule_SetReplyArrayLen() "
+            "calls.",
+            ctx->module->name);
+    }
+}
+
 /* This Redis command binds the normal Redis command invocation with commands
  * exported by modules. */
 void RedisModuleCommandDispatcher(client *c) {
@@ -236,7 +253,6 @@ void RedisModuleCommandDispatcher(client *c) {
     ctx.module = cp->module;
     ctx.client = c;
     cp->func(&ctx,(void**)c->argv,c->argc);
-    autoMemoryCollect(&ctx);
     preventCommandPropagation(c);
 
     /* Handle the replication of the final EXEC, since whatever a command
@@ -248,6 +264,7 @@ void RedisModuleCommandDispatcher(client *c) {
             PROPAGATE_AOF|PROPAGATE_REPL);
         decrRefCount(propargv[0]);
     }
+    moduleFreeContext(&ctx);
 }
 
 /* Register a new command in the Redis server, that will be handled by
@@ -519,12 +536,71 @@ int RM_ReplyWithSimpleString(RedisModuleCtx *ctx, const char *msg) {
  * to ReplyWith* style functions must follow in order to emit the elements
  * of the array.
  *
+ * When producing arrays with a number of element that is not known beforehand
+ * the function can be called with the special count
+ * REDISMODULE_POSTPONED_ARRAY_LEN, and the actual number of elements can be
+ * later set with RedisModule_ReplySetArrayLength() (which will set the
+ * latest "open" count if there are multiple ones).
+ *
  * The function always returns REDISMODULE_OK. */
 int RM_ReplyWithArray(RedisModuleCtx *ctx, long len) {
-    addReplyMultiBulkLen(ctx->client,len);
+    if (len == REDISMODULE_POSTPONED_ARRAY_LEN) {
+        ctx->postponed_arrays = zrealloc(ctx->postponed_arrays,sizeof(void*)*
+                (ctx->postponed_arrays_count+1));
+        ctx->postponed_arrays[ctx->postponed_arrays_count] =
+            addDeferredMultiBulkLength(ctx->client);
+        ctx->postponed_arrays_count++;
+    } else {
+        addReplyMultiBulkLen(ctx->client,len);
+    }
     return REDISMODULE_OK;
 }
 
+/* When RedisModule_ReplyWithArray() is used with the argument
+ * REDISMODULE_POSTPONED_ARRAY_LEN, because we don't know beforehand the number
+ * of items we are going to output as elements of the array, this function
+ * will take care to set the array length.
+ *
+ * Since it is possible to have multiple array replies pending with unknown
+ * length, this function guarantees to always set the latest array length
+ * that was created in a postponed way.
+ *
+ * For example in order to output an array like [1,[10,20,30]] we
+ * could write:
+ *
+ *  RedisModule_ReplyWithArray(ctx,REDISMODULE_POSTPONED_ARRAY_LEN);
+ *  RedisModule_ReplyWithLongLong(ctx,1);
+ *  RedisModule_ReplyWithArray(ctx,REDISMODULE_POSTPONED_ARRAY_LEN);
+ *  RedisModule_ReplyWithLongLong(ctx,10);
+ *  RedisModule_ReplyWithLongLong(ctx,20);
+ *  RedisModule_ReplyWithLongLong(ctx,30);
+ *  RedisModule_ReplySetArrayLength(ctx,3); // Set len of 10,20,30 array.
+ *  RedisModule_ReplySetArrayLength(ctx,2); // Set len of top array
+ *
+ * Note that in the above example there is no reason to postpone the array
+ * length, since we produce a fixed number of elements, but in the practice
+ * the code may use an interator or other ways of creating the output so
+ * that is not easy to calculate in advance the number of elements.
+ */
+void RM_ReplySetArrayLength(RedisModuleCtx *ctx, long len) {
+    if (ctx->postponed_arrays_count == 0) {
+        serverLog(LL_WARNING,
+            "API misuse detected in module %s: "
+            "RedisModule_ReplySetArrayLength() called without previous "
+            "RedisModule_ReplyWithArray(ctx,REDISMODULE_POSTPONED_ARRAY_LEN) "
+            "call.", ctx->module->name);
+            return;
+    }
+    ctx->postponed_arrays_count--;
+    setDeferredMultiBulkLength(ctx->client,
+            ctx->postponed_arrays[ctx->postponed_arrays_count],
+            len);
+    if (ctx->postponed_arrays_count == 0) {
+        zfree(ctx->postponed_arrays);
+        ctx->postponed_arrays = NULL;
+    }
+}
+
 /* Reply with a bulk string, taking in input a C buffer pointer and length.
  *
  * The function always returns REDISMODULE_OK. */
@@ -1798,6 +1874,7 @@ void moduleRegisterCoreAPI(void) {
     REGISTER_API(ReplyWithError);
     REGISTER_API(ReplyWithSimpleString);
     REGISTER_API(ReplyWithArray);
+    REGISTER_API(ReplySetArrayLength);
     REGISTER_API(ReplyWithString);
     REGISTER_API(ReplyWithStringBuffer);
     REGISTER_API(ReplyWithNull);