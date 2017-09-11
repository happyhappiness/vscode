    RedisModuleCtx ctx = REDISMODULE_CTX_INIT;

    handle = dlopen(path,RTLD_NOW|RTLD_LOCAL);
    if (handle == NULL) {
        serverLog(LL_WARNING, "Module %s failed to load: %s", path, dlerror());
        return C_ERR;
    }
    onload = (int (*)(void *))(unsigned long) dlsym(handle,"RedisModule_OnLoad");
    if (onload == NULL) {
        serverLog(LL_WARNING,
