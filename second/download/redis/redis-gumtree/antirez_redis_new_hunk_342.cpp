    dictAdd(modules,ctx.module->name,ctx.module);
    ctx.module->handle = handle;
    serverLog(LL_NOTICE,"Module '%s' loaded from %s",ctx.module->name,path);
    moduleFreeContext(&ctx);
    return C_OK;
}

/* Unload the module registered with the specified name. On success
 * C_OK is returned, otherwise C_ERR is returned and errno is set
 * to the following values depending on the type of error:
 *
 * ENONET: No such module having the specified name.
 * EBUSY: The module exports a new data type and can only be reloaded. */
int moduleUnload(sds name) {
    struct RedisModule *module = dictFetchValue(modules,name);

    if (module == NULL) {
        errno = ENOENT;
        return REDISMODULE_ERR;
    }

    if (listLength(module->types)) {
        errno = EBUSY;
        return REDISMODULE_ERR;
    }

    /* Unregister all the commands registered by this module. */
    dictIterator *di = dictGetSafeIterator(server.commands);
    dictEntry *de;
