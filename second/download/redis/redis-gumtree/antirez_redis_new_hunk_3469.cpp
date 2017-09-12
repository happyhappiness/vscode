        prepareForBenchmark("MSET (10 keys, multi bulk)");
        c = createClient(REDIS_REPLY_ARRAY);
        c->obuf = sdscatprintf(c->obuf,"*%d\r\n$4\r\nMSET\r\n", 11);
        for (i = 0; i < 10; i++) {
            c->obuf = sdscatprintf(c->obuf,"$%d\r\n%s\r\n",config.datasize,data);
        createMissingClients(c);
        aeMain(config.el);
        endBenchmark();

        prepareForBenchmark("SET");
        c = createClient(REDIS_REPLY_STATUS);
        c->obuf = sdscat(c->obuf,"*3\r\n$3\r\nSET\r\n$20\r\nfoo_rand000000000000\r\n");
        c->obuf = sdscatprintf(c->obuf,"$%d\r\n%s\r\n",config.datasize,data);
        createMissingClients(c);
        aeMain(config.el);
        endBenchmark();
