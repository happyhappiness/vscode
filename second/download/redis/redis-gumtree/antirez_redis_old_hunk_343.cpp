    /* Remove from list of modules. */
    serverLog(LL_NOTICE,"Module %s unloaded",module->name);
    dictDelete(modules,module->name);

    /* Free the module structure. */
    zfree(module);

    return REDISMODULE_OK;
}

/* Redis MODULE command.
 *
 * MODULE LOAD <path> */
void moduleCommand(client *c) {
    char *subcmd = c->argv[1]->ptr;

    if (!strcasecmp(subcmd,"load") && c->argc == 3) {
        if (moduleLoad(c->argv[2]->ptr) == C_OK)
            addReply(c,shared.ok);
        else
            addReplyError(c,
