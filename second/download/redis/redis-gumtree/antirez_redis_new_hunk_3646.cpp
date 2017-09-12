        prepareForBenchmark("SET");
        c = createClient();
        if (!c) exit(1);
        c->obuf = sdscat(c->obuf,"SET foo_rand000000000000 ");
        {
            char *data = zmalloc(config.datasize+2);
            memset(data,'x',config.datasize);
