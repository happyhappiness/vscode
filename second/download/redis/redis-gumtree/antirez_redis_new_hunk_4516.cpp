        prepareForBenchmark();
        c = createClient();
        if (!c) exit(1);
        c->obuf = sdscatprintf(c->obuf,"SET foo_rand000000000000 %d\r\n",config.datasize);
        {
            char *data = zmalloc(config.datasize+2);
            memset(data,'x',config.datasize);
