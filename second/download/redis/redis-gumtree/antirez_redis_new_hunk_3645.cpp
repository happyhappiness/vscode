        aeMain(config.el);
        endBenchmark();

        prepareForBenchmark("MSET (10 keys, multi bulk)");
        c = createClient();
        if (!c) exit(1);
        c->obuf = sdscatprintf(c->obuf,"*%d\r\n$4\r\nMSET\r\n", 11);
        {
            int i;
            char *data = zmalloc(config.datasize+2);
            memset(data,'x',config.datasize);
            for (i = 0; i < 10; i++) {
                c->obuf = sdscatprintf(c->obuf,"$%d\r\n%s\r\n",config.datasize,data);
            }
            zfree(data);
        }
        prepareClientForReply(c,REPLY_RETCODE);
        createMissingClients(c);
        aeMain(config.el);
        endBenchmark();

        prepareForBenchmark("SET");
        c = createClient();
        if (!c) exit(1);
