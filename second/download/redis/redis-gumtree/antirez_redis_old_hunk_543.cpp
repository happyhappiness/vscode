    sds client;
    int j;

    serverLog(LL_WARNING, "--- CURRENT CLIENT INFO");
    client = catClientInfoString(sdsempty(),cc);
    serverLog(LL_WARNING,"client: %s", client);
    sdsfree(client);
    for (j = 0; j < cc->argc; j++) {
        robj *decoded;

        decoded = getDecodedObject(cc->argv[j]);
        serverLog(LL_WARNING,"argv[%d]: '%s'", j, (char*)decoded->ptr);
        decrRefCount(decoded);
    }
    /* Check if the first argument, usually a key, is found inside the
