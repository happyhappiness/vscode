
        prepareForBenchmark("SET");
        c = createClient(REDIS_REPLY_STATUS);
        c->obuf = sdscat(c->obuf,"SET foo_rand000000000000 ");
        {
            char *data = zmalloc(config.datasize+2);
            memset(data,'x',config.datasize);
            data[config.datasize] = '\r';
            data[config.datasize+1] = '\n';
            c->obuf = sdscatlen(c->obuf,data,config.datasize+2);
        }
        createMissingClients(c);
