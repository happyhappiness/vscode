
    /* Remove from list of modules. */
    serverLog(LL_NOTICE,"Module %s unloaded",module->name);
    dictDelete(modules,module->name);
    moduleFreeModuleStructure(module);

    return REDISMODULE_OK;
