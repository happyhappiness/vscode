@@ -3085,7 +3085,7 @@ int moduleUnload(sds name) {
 
     /* Remove from list of modules. */
     serverLog(LL_NOTICE,"Module %s unloaded",module->name);
-    dictDelete(modules,module->name);
+    dictDeleteNoFree(modules,module->name);
     moduleFreeModuleStructure(module);
 
     return REDISMODULE_OK;