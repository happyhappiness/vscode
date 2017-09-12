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

