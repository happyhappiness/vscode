
    listRewind(server.loadmodule_queue,&li);
    while((ln = listNext(&li))) {
        sds modulepath = ln->value;
        if (moduleLoad(modulepath) == C_ERR) {
            serverLog(LL_WARNING,
                "Can't load module from %s: server aborting",
                modulepath);
            exit(1);
        }
    }
}

void moduleFreeModuleStructure(struct RedisModule *module) {
    sdsfree(module->name);
    zfree(module);
}

/* Load a module and initialize it. On success C_OK is returned, otherwise
 * C_ERR is returned. */
int moduleLoad(const char *path) {
    int (*onload)(void *);
    void *handle;
    RedisModuleCtx ctx = REDISMODULE_CTX_INIT;

