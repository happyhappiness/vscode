RedisModuleString *s = RedisModule_CreateStringPrintf(ctx, 
        "Got %d args. argv[1]: %s, argv[2]: %s", 
        argc, 
        RedisModule_StringPtrLen(argv[1], NULL),
        RedisModule_StringPtrLen(argv[2], NULL)
    );