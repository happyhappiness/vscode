            }
            zfree(data);
        }
        createMissingClients(c);
        aeMain(config.el);
        endBenchmark();

        prepareForBenchmark("SET");
        c = createClient(REDIS_REPLY_STATUS);
        c->obuf = sdscat(c->obuf,"*3\r\n$3\r\nSET\r\n$20\r\nfoo_rand000000000000\r\n");
        {
            char *data = zmalloc(config.datasize+2);
            memset(data,'x',config.datasize);
            data[config.datasize] = '\r';
            data[config.datasize+1] = '\n';
            c->obuf = sdscatprintf(c->obuf,"$%d\r\n",config.datasize);
            c->obuf = sdscatlen(c->obuf,data,config.datasize+2);
        }
        createMissingClients(c);
        aeMain(config.el);
        endBenchmark();

        prepareForBenchmark("GET");
        c = createClient(REDIS_REPLY_STRING);
        c->obuf = sdscat(c->obuf,"GET foo_rand000000000000\r\n");
        createMissingClients(c);
        aeMain(config.el);
        endBenchmark();

        prepareForBenchmark("INCR");
        c = createClient(REDIS_REPLY_INTEGER);
        c->obuf = sdscat(c->obuf,"INCR counter_rand000000000000\r\n");
        createMissingClients(c);
        aeMain(config.el);
        endBenchmark();

        prepareForBenchmark("LPUSH");
        c = createClient(REDIS_REPLY_INTEGER);
        c->obuf = sdscat(c->obuf,"LPUSH mylist bar\r\n");
        createMissingClients(c);
        aeMain(config.el);
        endBenchmark();

        prepareForBenchmark("LPOP");
        c = createClient(REDIS_REPLY_STRING);
        c->obuf = sdscat(c->obuf,"LPOP mylist\r\n");
        createMissingClients(c);
        aeMain(config.el);
        endBenchmark();

        prepareForBenchmark("SADD");
        c = createClient(REDIS_REPLY_STATUS);
        c->obuf = sdscat(c->obuf,"SADD myset counter_rand000000000000\r\n");
        createMissingClients(c);
        aeMain(config.el);
        endBenchmark();

        prepareForBenchmark("SPOP");
        c = createClient(REDIS_REPLY_STRING);
        c->obuf = sdscat(c->obuf,"SPOP myset\r\n");
        createMissingClients(c);
        aeMain(config.el);
        endBenchmark();

        prepareForBenchmark("LPUSH (again, in order to bench LRANGE)");
        c = createClient(REDIS_REPLY_STATUS);
        c->obuf = sdscat(c->obuf,"LPUSH mylist bar\r\n");
        createMissingClients(c);
        aeMain(config.el);
        endBenchmark();

        prepareForBenchmark("LRANGE (first 100 elements)");
        c = createClient(REDIS_REPLY_ARRAY);
        c->obuf = sdscat(c->obuf,"LRANGE mylist 0 99\r\n");
        createMissingClients(c);
        aeMain(config.el);
        endBenchmark();

        prepareForBenchmark("LRANGE (first 300 elements)");
        c = createClient(REDIS_REPLY_ARRAY);
        c->obuf = sdscat(c->obuf,"LRANGE mylist 0 299\r\n");
        createMissingClients(c);
        aeMain(config.el);
        endBenchmark();

        prepareForBenchmark("LRANGE (first 450 elements)");
        c = createClient(REDIS_REPLY_ARRAY);
        c->obuf = sdscat(c->obuf,"LRANGE mylist 0 449\r\n");
        createMissingClients(c);
        aeMain(config.el);
        endBenchmark();

        prepareForBenchmark("LRANGE (first 600 elements)");
        c = createClient(REDIS_REPLY_ARRAY);
        c->obuf = sdscat(c->obuf,"LRANGE mylist 0 599\r\n");
        createMissingClients(c);
        aeMain(config.el);
        endBenchmark();
