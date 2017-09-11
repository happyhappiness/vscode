
    /* Remove from list of modules. */
    serverLog(LL_NOTICE,"Module %s unloaded",module->name);
    dictDelete(modules,module->name);
    module->name = NULL; /* The name was already freed by dictDelete(). */
    moduleFreeModuleStructure(module);

    return REDISMODULE_OK;
