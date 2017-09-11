@@ -3332,10 +3332,15 @@ void unblockClientFromModule(client *c) {
  */
 RedisModuleBlockedClient *RM_BlockClient(RedisModuleCtx *ctx, RedisModuleCmdFunc reply_callback, RedisModuleCmdFunc timeout_callback, void (*free_privdata)(void*), long long timeout_ms) {
     client *c = ctx->client;
+    int islua = c->flags & CLIENT_LUA;
+
     c->bpop.module_blocked_handle = zmalloc(sizeof(RedisModuleBlockedClient));
     RedisModuleBlockedClient *bc = c->bpop.module_blocked_handle;
 
-    bc->client = c;
+    /* We need to handle the invalid operation of calling modules blocking
+     * commands from Lua. We actually create an already aborted (client set to
+     * NULL) blocked client handle, and actually reply to Lua with an error. */
+    bc->client = islua ? NULL : c;
     bc->module = ctx->module;
     bc->reply_callback = reply_callback;
     bc->timeout_callback = timeout_callback;
@@ -3346,7 +3351,12 @@ RedisModuleBlockedClient *RM_BlockClient(RedisModuleCtx *ctx, RedisModuleCmdFunc
     bc->dbid = c->db->id;
     c->bpop.timeout = timeout_ms ? (mstime()+timeout_ms) : 0;
 
-    blockClient(c,BLOCKED_MODULE);
+    if (islua) {
+        c->bpop.module_blocked_handle = NULL;
+        addReplyError(c,"Blocking module command called from Lua script");
+    } else {
+        blockClient(c,BLOCKED_MODULE);
+    }
     return bc;
 }
 