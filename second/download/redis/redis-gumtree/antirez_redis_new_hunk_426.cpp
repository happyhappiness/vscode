    return REDISMODULE_OK;
}

/* Free the context after the user function was called. */
void moduleFreeContext(RedisModuleCtx *ctx) {
    autoMemoryCollect(ctx);
    if (ctx->postponed_arrays) {
        zfree(ctx->postponed_arrays);
        ctx->postponed_arrays_count = 0;
        serverLog(LL_WARNING,
            "API misuse detected in module %s: "
            "RedisModule_ReplyWithArray(REDISMODULE_POSTPONED_ARRAY_LEN) "
            "not matched by the same number of RedisModule_SetReplyArrayLen() "
            "calls.",
            ctx->module->name);
    }
}

/* This Redis command binds the normal Redis command invocation with commands
 * exported by modules. */
void RedisModuleCommandDispatcher(client *c) {
