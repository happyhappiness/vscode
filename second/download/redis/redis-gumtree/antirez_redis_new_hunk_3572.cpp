    if (config.idlemode) {
        printf("Creating %d idle connections and waiting forever (Ctrl+C when done)\n", config.numclients);
        prepareForBenchmark("IDLE");
        c = createClient(0); /* will never receive a reply */
        c->obuf = sdsempty();
        createMissingClients(c);
        aeMain(config.el);
        /* and will wait for every */
    }

    do {
        prepareForBenchmark("PING");
        c = createClient(REDIS_REPLY_STATUS);
        c->obuf = sdscat(c->obuf,"PING\r\n");
        createMissingClients(c);
        aeMain(config.el);
        endBenchmark();

        prepareForBenchmark("PING (multi bulk)");
        c = createClient(REDIS_REPLY_STATUS);
        c->obuf = sdscat(c->obuf,"*1\r\n$4\r\nPING\r\n");
        createMissingClients(c);
        aeMain(config.el);
        endBenchmark();

        prepareForBenchmark("MSET (10 keys, multi bulk)");
        c = createClient(REDIS_REPLY_ARRAY);
        c->obuf = sdscatprintf(c->obuf,"*%d\r\n$4\r\nMSET\r\n", 11);
        {
            int i;
