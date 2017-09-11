@@ -2946,6 +2946,7 @@ int moduleLoad(const char *path, void **module_argv, int module_argc) {
     dictAdd(modules,ctx.module->name,ctx.module);
     ctx.module->handle = handle;
     serverLog(LL_NOTICE,"Module '%s' loaded from %s",ctx.module->name,path);
+    moduleFreeContext(&ctx);
     return C_OK;
 }
 