    RedisModuleCtx ctx = REDISMODULE_CTX_INIT;

    handle = dlopen(path,RTLD_NOW|RTLD_LOCAL);
    if (handle == NULL) return C_ERR;
    onload = (int (*)(void *))(unsigned long) dlsym(handle,"RedisModule_OnLoad");
    if (onload == NULL) {
        serverLog(LL_WARNING,
