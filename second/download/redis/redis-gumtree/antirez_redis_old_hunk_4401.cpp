        c = createClient();
        if (!c) exit(1);
        c->obuf = sdscat(c->obuf,"PING\r\n");
        c->replytype = REPLY_RETCODE;
        createMissingClients(c);
        aeMain(config.el);
        endBenchmark("PING");

        printf("\n");
    } while(config.loop);

