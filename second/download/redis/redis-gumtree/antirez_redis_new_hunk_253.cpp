
    /* Remove from list of modules. */
    serverLog(LL_NOTICE,"Module %s unloaded",module->name);
    dictDeleteNoFree(modules,module->name);
    moduleFreeModuleStructure(module);

    return REDISMODULE_OK;
