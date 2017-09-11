    sds client;
    int j;

    serverLogRaw(LL_WARNING|LL_RAW, "\n------ CURRENT CLIENT INFO ------\n");
    client = catClientInfoString(sdsempty(),cc);
    serverLog(LL_WARNING|LL_RAW,"%s\n", client);
    sdsfree(client);
    for (j = 0; j < cc->argc; j++) {
        robj *decoded;

        decoded = getDecodedObject(cc->argv[j]);
        serverLog(LL_WARNING|LL_RAW,"argv[%d]: '%s'\n", j,
            (char*)decoded->ptr);
        decrRefCount(decoded);
    }
    /* Check if the first argument, usually a key, is found inside the
