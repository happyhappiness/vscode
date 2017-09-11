
    handle = dlopen(path,RTLD_LAZY);
    if (handle == NULL) return C_ERR;
    onload = (int (*)(void *)) dlsym(handle,"RedisModule_OnLoad");
    if (onload == NULL) {
        serverLog(LL_WARNING,
            "Module %s does not export RedisModule_OnLoad() "
