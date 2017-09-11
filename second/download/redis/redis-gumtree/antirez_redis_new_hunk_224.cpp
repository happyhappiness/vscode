    return REDISMODULE_OK;
}

/* TEST.STRING.PRINTF -- Test string formatting. */
int TestStringPrintf(RedisModuleCtx *ctx, RedisModuleString **argv, int argc) {
    RedisModule_AutoMemory(ctx);
    if (argc < 3) {
        return RedisModule_WrongArity(ctx);
    }
    RedisModuleString *s = RedisModule_CreateStringPrintf(ctx, 
        "Got %d args. argv[1]: %s, argv[2]: %s", 
        argc, 
        RedisModule_StringPtrLen(argv[1], NULL),
        RedisModule_StringPtrLen(argv[2], NULL)
    );

    RedisModule_ReplyWithString(ctx,s);

    return REDISMODULE_OK;
}


/* ----------------------------- Test framework ----------------------------- */

/* Return 1 if the reply matches the specified string, otherwise log errors
