        prepareClientForReply(c,REPLY_RETCODE);
        createMissingClients(c);
        aeMain(config.el);
        endBenchmark("SET");

        prepareForBenchmark();
        c = createClient();
        if (!c) exit(1);
        c->obuf = sdscat(c->obuf,"GET foo_rand000000000000\r\n");
        prepareClientForReply(c,REPLY_BULK);
        createMissingClients(c);
        aeMain(config.el);
        endBenchmark("GET");

        prepareForBenchmark();
        c = createClient();
        if (!c) exit(1);
        c->obuf = sdscat(c->obuf,"INCR counter_rand000000000000\r\n");
        prepareClientForReply(c,REPLY_INT);
        createMissingClients(c);
        aeMain(config.el);
        endBenchmark("INCR");

        prepareForBenchmark();
        c = createClient();
        if (!c) exit(1);
        c->obuf = sdscat(c->obuf,"LPUSH mylist 3\r\nbar\r\n");
        prepareClientForReply(c,REPLY_INT);
        createMissingClients(c);
        aeMain(config.el);
        endBenchmark("LPUSH");

        prepareForBenchmark();
        c = createClient();
        if (!c) exit(1);
        c->obuf = sdscat(c->obuf,"LPOP mylist\r\n");
        prepareClientForReply(c,REPLY_BULK);
        createMissingClients(c);
        aeMain(config.el);
        endBenchmark("LPOP");

        prepareForBenchmark();
        c = createClient();
        if (!c) exit(1);
        c->obuf = sdscat(c->obuf,"SADD myset 24\r\ncounter_rand000000000000\r\n");
        prepareClientForReply(c,REPLY_RETCODE);
        createMissingClients(c);
        aeMain(config.el);
        endBenchmark("SADD");

        prepareForBenchmark();
        c = createClient();
        if (!c) exit(1);
        c->obuf = sdscat(c->obuf,"SPOP myset\r\n");
        prepareClientForReply(c,REPLY_BULK);
        createMissingClients(c);
        aeMain(config.el);
        endBenchmark("SPOP");

        prepareForBenchmark();
        c = createClient();
        if (!c) exit(1);
        c->obuf = sdscat(c->obuf,"LPUSH mylist 3\r\nbar\r\n");
        prepareClientForReply(c,REPLY_RETCODE);
        createMissingClients(c);
        aeMain(config.el);
        endBenchmark("LPUSH (again, in order to bench LRANGE)");

        prepareForBenchmark();
        c = createClient();
        if (!c) exit(1);
        c->obuf = sdscat(c->obuf,"LRANGE mylist 0 99\r\n");
        prepareClientForReply(c,REPLY_MBULK);
        createMissingClients(c);
        aeMain(config.el);
        endBenchmark("LRANGE (first 100 elements)");

        prepareForBenchmark();
        c = createClient();
        if (!c) exit(1);
        c->obuf = sdscat(c->obuf,"LRANGE mylist 0 299\r\n");
        prepareClientForReply(c,REPLY_MBULK);
        createMissingClients(c);
        aeMain(config.el);
        endBenchmark("LRANGE (first 300 elements)");

        prepareForBenchmark();
        c = createClient();
        if (!c) exit(1);
        c->obuf = sdscat(c->obuf,"LRANGE mylist 0 449\r\n");
        prepareClientForReply(c,REPLY_MBULK);
        createMissingClients(c);
        aeMain(config.el);
        endBenchmark("LRANGE (first 450 elements)");

        prepareForBenchmark();
        c = createClient();
        if (!c) exit(1);
        c->obuf = sdscat(c->obuf,"LRANGE mylist 0 599\r\n");
        prepareClientForReply(c,REPLY_MBULK);
        createMissingClients(c);
        aeMain(config.el);
        endBenchmark("LRANGE (first 600 elements)");

        printf("\n");
    } while(config.loop);
