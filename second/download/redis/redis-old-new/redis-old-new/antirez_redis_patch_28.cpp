@@ -953,21 +953,44 @@ int RM_WrongArity(RedisModuleCtx *ctx) {
     return REDISMODULE_OK;
 }
 
+/* Return the client object the `RM_Reply*` functions should target.
+ * Normally this is just `ctx->client`, that is the client that called
+ * the module command, however in the case of thread safe contexts there
+ * is no directly associated client (since it would not be safe to access
+ * the client from a thread), so instead the blocked client object referenced
+ * in the thread safe context, has a fake client that we just use to accumulate
+ * the replies. Later, when the client is unblocked, the accumulated replies
+ * are appended to the actual client.
+ *
+ * The function returns the client pointer depending on the context, or
+ * NULL if there is no potential client. This happens when we are in the
+ * context of a thread safe context that was not initialized with a blocked
+ * client object. */
+client *moduleGetReplyClient(RedisModuleCtx *ctx) {
+    if (ctx->client) return ctx->client;
+    if (ctx->blocked_client) return ctx->blocked_client->reply_client;
+    return NULL;
+}
+
 /* Send an integer reply to the client, with the specified long long value.
  * The function always returns REDISMODULE_OK. */
 int RM_ReplyWithLongLong(RedisModuleCtx *ctx, long long ll) {
-    addReplyLongLong(ctx->client,ll);
+    client *c = moduleGetReplyClient(ctx);
+    if (c == NULL) return REDISMODULE_OK;
+    addReplyLongLong(c,ll);
     return REDISMODULE_OK;
 }
 
 /* Reply with an error or simple string (status message). Used to implement
  * ReplyWithSimpleString() and ReplyWithError().
  * The function always returns REDISMODULE_OK. */
 int replyWithStatus(RedisModuleCtx *ctx, const char *msg, char *prefix) {
+    client *c = moduleGetReplyClient(ctx);
+    if (c == NULL) return REDISMODULE_OK;
     sds strmsg = sdsnewlen(prefix,1);
     strmsg = sdscat(strmsg,msg);
     strmsg = sdscatlen(strmsg,"\r\n",2);
-    addReplySds(ctx->client,strmsg);
+    addReplySds(c,strmsg);
     return REDISMODULE_OK;
 }
 
@@ -1010,14 +1033,16 @@ int RM_ReplyWithSimpleString(RedisModuleCtx *ctx, const char *msg) {
  *
  * The function always returns REDISMODULE_OK. */
 int RM_ReplyWithArray(RedisModuleCtx *ctx, long len) {
+    client *c = moduleGetReplyClient(ctx);
+    if (c == NULL) return REDISMODULE_OK;
     if (len == REDISMODULE_POSTPONED_ARRAY_LEN) {
         ctx->postponed_arrays = zrealloc(ctx->postponed_arrays,sizeof(void*)*
                 (ctx->postponed_arrays_count+1));
         ctx->postponed_arrays[ctx->postponed_arrays_count] =
-            addDeferredMultiBulkLength(ctx->client);
+            addDeferredMultiBulkLength(c);
         ctx->postponed_arrays_count++;
     } else {
-        addReplyMultiBulkLen(ctx->client,len);
+        addReplyMultiBulkLen(c,len);
     }
     return REDISMODULE_OK;
 }
@@ -1049,6 +1074,8 @@ int RM_ReplyWithArray(RedisModuleCtx *ctx, long len) {
  * that is not easy to calculate in advance the number of elements.
  */
 void RM_ReplySetArrayLength(RedisModuleCtx *ctx, long len) {
+    client *c = moduleGetReplyClient(ctx);
+    if (c == NULL) return;
     if (ctx->postponed_arrays_count == 0) {
         serverLog(LL_WARNING,
             "API misuse detected in module %s: "
@@ -1058,7 +1085,7 @@ void RM_ReplySetArrayLength(RedisModuleCtx *ctx, long len) {
             return;
     }
     ctx->postponed_arrays_count--;
-    setDeferredMultiBulkLength(ctx->client,
+    setDeferredMultiBulkLength(c,
             ctx->postponed_arrays[ctx->postponed_arrays_count],
             len);
     if (ctx->postponed_arrays_count == 0) {
@@ -1071,15 +1098,19 @@ void RM_ReplySetArrayLength(RedisModuleCtx *ctx, long len) {
  *
  * The function always returns REDISMODULE_OK. */
 int RM_ReplyWithStringBuffer(RedisModuleCtx *ctx, const char *buf, size_t len) {
-    addReplyBulkCBuffer(ctx->client,(char*)buf,len);
+    client *c = moduleGetReplyClient(ctx);
+    if (c == NULL) return REDISMODULE_OK;
+    addReplyBulkCBuffer(c,(char*)buf,len);
     return REDISMODULE_OK;
 }
 
 /* Reply with a bulk string, taking in input a RedisModuleString object.
  *
  * The function always returns REDISMODULE_OK. */
 int RM_ReplyWithString(RedisModuleCtx *ctx, RedisModuleString *str) {
-    addReplyBulk(ctx->client,str);
+    client *c = moduleGetReplyClient(ctx);
+    if (c == NULL) return REDISMODULE_OK;
+    addReplyBulk(c,str);
     return REDISMODULE_OK;
 }
 
@@ -1088,7 +1119,9 @@ int RM_ReplyWithString(RedisModuleCtx *ctx, RedisModuleString *str) {
  *
  * The function always returns REDISMODULE_OK. */
 int RM_ReplyWithNull(RedisModuleCtx *ctx) {
-    addReply(ctx->client,shared.nullbulk);
+    client *c = moduleGetReplyClient(ctx);
+    if (c == NULL) return REDISMODULE_OK;
+    addReply(c,shared.nullbulk);
     return REDISMODULE_OK;
 }
 
@@ -1099,8 +1132,10 @@ int RM_ReplyWithNull(RedisModuleCtx *ctx) {
  *
  * The function always returns REDISMODULE_OK. */
 int RM_ReplyWithCallReply(RedisModuleCtx *ctx, RedisModuleCallReply *reply) {
+    client *c = moduleGetReplyClient(ctx);
+    if (c == NULL) return REDISMODULE_OK;
     sds proto = sdsnewlen(reply->proto, reply->protolen);
-    addReplySds(ctx->client,proto);
+    addReplySds(c,proto);
     return REDISMODULE_OK;
 }
 
@@ -1111,7 +1146,9 @@ int RM_ReplyWithCallReply(RedisModuleCtx *ctx, RedisModuleCallReply *reply) {
  *
  * The function always returns REDISMODULE_OK. */
 int RM_ReplyWithDouble(RedisModuleCtx *ctx, double d) {
-    addReplyDouble(ctx->client,d);
+    client *c = moduleGetReplyClient(ctx);
+    if (c == NULL) return REDISMODULE_OK;
+    addReplyDouble(c,d);
     return REDISMODULE_OK;
 }
 
@@ -3173,7 +3210,8 @@ RedisModuleBlockedClient *RM_BlockClient(RedisModuleCtx *ctx, RedisModuleCmdFunc
     bc->timeout_callback = timeout_callback;
     bc->free_privdata = free_privdata;
     bc->privdata = NULL;
-    bc->reply_client = NULL;
+    bc->reply_client = createClient(-1);
+    bc->reply_client->flags |= CLIENT_MODULE;
     c->bpop.timeout = timeout_ms ? (mstime()+timeout_ms) : 0;
 
     blockClient(c,BLOCKED_MODULE);
@@ -3236,7 +3274,9 @@ void moduleHandleBlockedClients(void) {
         /* Release the lock during the loop, as long as we don't
          * touch the shared list. */
 
-        if (c != NULL && bc->reply_callback != NULL) {
+        /* Call the reply callback if the client is valid and we have
+         * any callback. */
+        if (c && bc->reply_callback) {
             RedisModuleCtx ctx = REDISMODULE_CTX_INIT;
             ctx.flags |= REDISMODULE_CTX_BLOCKED_REPLY;
             ctx.blocked_privdata = bc->privdata;
@@ -3246,8 +3286,24 @@ void moduleHandleBlockedClients(void) {
             moduleHandlePropagationAfterCommandCallback(&ctx);
             moduleFreeContext(&ctx);
         }
+
+        /* Free privdata if any. */
         if (bc->privdata && bc->free_privdata)
             bc->free_privdata(bc->privdata);
+
+        /* It is possible that this blocked client object accumulated
+         * replies to send to the client in a thread safe context.
+         * We need to glue such replies to the client output buffer and
+         * free the temporary client we just used for the replies. */
+        if (c) {
+            if (bc->reply_client->bufpos)
+                addReplyString(c,bc->reply_client->buf,
+                                 bc->reply_client->bufpos);
+            if (listLength(bc->reply_client->reply))
+                listJoin(c->reply,bc->reply_client->reply);
+        }
+        freeClient(bc->reply_client);
+
         if (c != NULL) unblockClient(c);
         /* Free 'bc' only after unblocking the client, since it is
          * referenced in the client blocking context, and must be valid
@@ -3332,8 +3388,7 @@ RedisModuleCtx *RM_GetThreadSafeContext(RedisModuleBlockedClient *bc) {
     memcpy(ctx,&empty,sizeof(empty));
     if (bc) {
         ctx->blocked_client = bc;
-        if (bc->reply_client == NULL)
-            bc->reply_client = createClient(-1);
+        ctx->module = bc->module;
     }
     ctx->flags |= REDISMODULE_CTX_THREAD_SAFE;
     return ctx;