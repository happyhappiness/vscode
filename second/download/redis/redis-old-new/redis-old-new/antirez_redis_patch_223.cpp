@@ -2897,11 +2897,11 @@ void moduleLoadFromQueue(void) {
 
     listRewind(server.loadmodule_queue,&li);
     while((ln = listNext(&li))) {
-        sds modulepath = ln->value;
-        if (moduleLoad(modulepath) == C_ERR) {
+        struct loadmodule *loadmod = ln->value;
+        if (moduleLoad(loadmod->path,(void **)loadmod->argv,loadmod->argc) == C_ERR) {
             serverLog(LL_WARNING,
                 "Can't load module from %s: server aborting",
-                modulepath);
+                loadmod->path);
             exit(1);
         }
     }
@@ -2915,8 +2915,8 @@ void moduleFreeModuleStructure(struct RedisModule *module) {
 
 /* Load a module and initialize it. On success C_OK is returned, otherwise
  * C_ERR is returned. */
-int moduleLoad(const char *path) {
-    int (*onload)(void *);
+int moduleLoad(const char *path, void **module_argv, int module_argc) {
+    int (*onload)(void *, void **, int);
     void *handle;
     RedisModuleCtx ctx = REDISMODULE_CTX_INIT;
 
@@ -2925,14 +2925,14 @@ int moduleLoad(const char *path) {
         serverLog(LL_WARNING, "Module %s failed to load: %s", path, dlerror());
         return C_ERR;
     }
-    onload = (int (*)(void *))(unsigned long) dlsym(handle,"RedisModule_OnLoad");
+    onload = (int (*)(void *, void **, int))(unsigned long) dlsym(handle,"RedisModule_OnLoad");
     if (onload == NULL) {
         serverLog(LL_WARNING,
             "Module %s does not export RedisModule_OnLoad() "
             "symbol. Module not loaded.",path);
         return C_ERR;
     }
-    if (onload((void*)&ctx) == REDISMODULE_ERR) {
+    if (onload((void*)&ctx,module_argv,module_argc) == REDISMODULE_ERR) {
         if (ctx.module) moduleFreeModuleStructure(ctx.module);
         dlclose(handle);
         serverLog(LL_WARNING,
@@ -3006,16 +3006,30 @@ int moduleUnload(sds name) {
 
 /* Redis MODULE command.
  *
- * MODULE LOAD <path> */
+ * MODULE LOAD <path> [args...] */
 void moduleCommand(client *c) {
     char *subcmd = c->argv[1]->ptr;
 
-    if (!strcasecmp(subcmd,"load") && c->argc == 3) {
-        if (moduleLoad(c->argv[2]->ptr) == C_OK)
+    if (!strcasecmp(subcmd,"load") && c->argc >= 3) {
+        sds *argv = NULL;
+        int argc = 0;
+        int i;
+
+        if (c->argc > 3) {
+            argc = c->argc - 3;
+            argv = zmalloc(sizeof(sds)*argc);
+            for (i=0; i<argc; i++) {
+                argv[i] = (sds) c->argv[i+3]->ptr;
+            }
+        }
+
+        if (moduleLoad(c->argv[2]->ptr,(void **)argv,argc) == C_OK)
             addReply(c,shared.ok);
         else
             addReplyError(c,
                 "Error loading the extension. Please check the server logs.");
+        if (argv)
+            zfree(argv);
     } else if (!strcasecmp(subcmd,"unload") && c->argc == 3) {
         if (moduleUnload(c->argv[2]->ptr) == C_OK)
             addReply(c,shared.ok);