@@ -53,7 +53,7 @@ struct RedisModuleCtx {
 };
 typedef struct RedisModuleCtx RedisModuleCtx;
 
-#define REDISMODULE_CTX_INIT {(void*)&RedisModule_GetApi, NULL, NULL, NULL, 0, 0, 0}
+#define REDISMODULE_CTX_INIT {(void*)(unsigned long)&RedisModule_GetApi, NULL, NULL, NULL, 0, 0, 0}
 #define REDISMODULE_CTX_MULTI_EMITTED (1<<0)
 #define REDISMODULE_CTX_AUTO_MEMORY (1<<1)
 
@@ -201,7 +201,7 @@ int RedisModule_GetApi(const char *funcname, void **targetPtrPtr) {
 /* This Redis command binds the normal Redis command invocation with commands
  * exported by modules. */
 void RedisModuleCommandDispatcher(client *c) {
-    RedisModuleCommandProxy *cp = (void*)c->cmd->getkeys_proc;
+    RedisModuleCommandProxy *cp = (void*)(unsigned long)c->cmd->getkeys_proc;
     RedisModuleCtx ctx = REDISMODULE_CTX_INIT;
 
     ctx.module = cp->module;
@@ -251,7 +251,7 @@ int RedisModule_CreateCommand(RedisModuleCtx *ctx, const char *name, RedisModule
     cp->rediscmd->proc = RedisModuleCommandDispatcher;
     cp->rediscmd->arity = -1;
     cp->rediscmd->flags = 0;
-    cp->rediscmd->getkeys_proc = (redisGetKeysProc*)cp;
+    cp->rediscmd->getkeys_proc = (redisGetKeysProc*)(unsigned long)cp;
     cp->rediscmd->firstkey = 1;
     cp->rediscmd->lastkey = 1;
     cp->rediscmd->keystep = 1;
@@ -1177,7 +1177,7 @@ int moduleRegisterApi(const char *funcname, void *funcptr) {
 }
 
 #define REGISTER_API(name) \
-    moduleRegisterApi("RedisModule_" #name, (void *)RedisModule_ ## name)
+    moduleRegisterApi("RedisModule_" #name, (void *)(unsigned long)RedisModule_ ## name)
 
 /* Register all the APIs we export. */
 void moduleRegisterCoreAPI(void) {
@@ -1268,7 +1268,7 @@ int moduleLoad(const char *path) {
 
     handle = dlopen(path,RTLD_LAZY);
     if (handle == NULL) return C_ERR;
-    onload = (int (*)(void *)) dlsym(handle,"RedisModule_OnLoad");
+    onload = (int (*)(void *))(unsigned long) dlsym(handle,"RedisModule_OnLoad");
     if (onload == NULL) {
         serverLog(LL_WARNING,
             "Module %s does not export RedisModule_OnLoad() "
@@ -1308,7 +1308,8 @@ int moduleUnload(sds name) {
     while ((de = dictNext(di)) != NULL) {
         struct redisCommand *cmd = dictGetVal(de);
         if (cmd->proc == RedisModuleCommandDispatcher) {
-            RedisModuleCommandProxy *cp = (void*)cmd->getkeys_proc;
+            RedisModuleCommandProxy *cp = 
+                (void*)(unsigned long)cmd->getkeys_proc;
             sds cmdname = cp->rediscmd->name;
             if (cp->module == module) {
                 dictDelete(server.commands,cmdname);