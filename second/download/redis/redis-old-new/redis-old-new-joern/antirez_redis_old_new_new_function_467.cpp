int moduleLoad(const char *path) {
    int (*onload)(void *);
    void *handle;
    RedisModuleCtx ctx = REDISMODULE_CTX_INIT;

    handle = dlopen(path,RTLD_NOW|RTLD_LOCAL);
    if (handle == NULL) {
        serverLog(LL_WARNING, "Module %s failed to load: %s", path, dlerror());
        return C_ERR;
    }
    onload = (int (*)(void *))(unsigned long) dlsym(handle,"RedisModule_OnLoad");
    if (onload == NULL) {
        serverLog(LL_WARNING,
            "Module %s does not export RedisModule_OnLoad() "
            "symbol. Module not loaded.",path);
        return C_ERR;
    }
    if (onload((void*)&ctx) == REDISMODULE_ERR) {
        if (ctx.module) moduleFreeModuleStructure(ctx.module);
        dlclose(handle);
        serverLog(LL_WARNING,
            "Module %s initialization failed. Module not loaded",path);
        return C_ERR;
    }

    /* Redis module loaded! Register it. */
    dictAdd(modules,ctx.module->name,ctx.module);
    ctx.module->handle = handle;
    serverLog(LL_NOTICE,"Module '%s' loaded from %s",ctx.module->name,path);
    return C_OK;
}