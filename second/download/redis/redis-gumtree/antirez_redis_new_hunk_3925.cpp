    }

    do {
        prepareForBenchmark("PING");
        c = createClient();
        if (!c) exit(1);
        c->obuf = sdscat(c->obuf,"PING\r\n");
        prepareClientForReply(c,REPLY_RETCODE);
        createMissingClients(c);
        aeMain(config.el);
        endBenchmark();

        prepareForBenchmark("PING (multi bulk)");
        c = createClient();
        if (!c) exit(1);
        c->obuf = sdscat(c->obuf,"*1\r\n$4\r\nPING\r\n");
        prepareClientForReply(c,REPLY_RETCODE);
        createMissingClients(c);
        aeMain(config.el);
        endBenchmark();

        prepareForBenchmark("SET");
        c = createClient();
        if (!c) exit(1);
        c->obuf = sdscatprintf(c->obuf,"SET foo_rand000000000000 %d\r\n",config.datasize);
