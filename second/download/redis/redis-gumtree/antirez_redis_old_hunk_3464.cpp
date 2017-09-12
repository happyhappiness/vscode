        memset(data,'x',config.datasize);
        data[config.datasize] = '\0';

        prepareForBenchmark("PING (inline)");
        c = createClient(REDIS_REPLY_STATUS);
        c->obuf = sdscat(sdsempty(),"PING\r\n");
        createMissingClients(c);
        aeMain(config.el);
        endBenchmark();

        prepareForBenchmark("PING");
        c = createClient(REDIS_REPLY_STATUS);
        len = redisFormatCommand(&cmd,"PING");
        c->obuf = sdsnewlen(cmd,len);
        free(cmd);
        createMissingClients(c);
        aeMain(config.el);
        endBenchmark();

        prepareForBenchmark("MSET (10 keys)");
        c = createClient(REDIS_REPLY_ARRAY);
        {
            const char *argv[11];
            argv[0] = "MSET";
            for (i = 1; i < 11; i++)
                argv[i] = data;
            len = redisFormatCommandArgv(&cmd,11,argv,NULL);
            c->obuf = sdsnewlen(cmd,len);
            free(cmd);
        }
        createMissingClients(c);
        aeMain(config.el);
        endBenchmark();

        prepareForBenchmark("SET");
        c = createClient(REDIS_REPLY_STATUS);
        len = redisFormatCommand(&cmd,"SET foo:rand:000000000000 %s",data);
        c->obuf = sdsnewlen(cmd,len);
        free(cmd);
        createMissingClients(c);
        aeMain(config.el);
        endBenchmark();

        prepareForBenchmark("GET");
        c = createClient(REDIS_REPLY_STRING);
        len = redisFormatCommand(&cmd,"GET foo:rand:000000000000");
        c->obuf = sdsnewlen(cmd,len);
        free(cmd);
        createMissingClients(c);
        aeMain(config.el);
        endBenchmark();

        prepareForBenchmark("INCR");
        c = createClient(REDIS_REPLY_INTEGER);
        len = redisFormatCommand(&cmd,"INCR counter:rand:000000000000");
        c->obuf = sdsnewlen(cmd,len);
        free(cmd);
        createMissingClients(c);
        aeMain(config.el);
        endBenchmark();

        prepareForBenchmark("LPUSH");
        c = createClient(REDIS_REPLY_INTEGER);
        len = redisFormatCommand(&cmd,"LPUSH mylist %s",data);
        c->obuf = sdsnewlen(cmd,len);
        free(cmd);
        createMissingClients(c);
        aeMain(config.el);
        endBenchmark();

        prepareForBenchmark("LPOP");
        c = createClient(REDIS_REPLY_STRING);
        len = redisFormatCommand(&cmd,"LPOP mylist");
        c->obuf = sdsnewlen(cmd,len);
        free(cmd);
        createMissingClients(c);
        aeMain(config.el);
        endBenchmark();

        prepareForBenchmark("SADD");
        c = createClient(REDIS_REPLY_STATUS);
        len = redisFormatCommand(&cmd,"SADD myset counter:rand:000000000000");
        c->obuf = sdsnewlen(cmd,len);
        free(cmd);
        createMissingClients(c);
        aeMain(config.el);
        endBenchmark();

        prepareForBenchmark("SPOP");
        c = createClient(REDIS_REPLY_STRING);
        len = redisFormatCommand(&cmd,"SPOP myset");
        c->obuf = sdsnewlen(cmd,len);
        free(cmd);
        createMissingClients(c);
        aeMain(config.el);
        endBenchmark();

        prepareForBenchmark("LPUSH (again, in order to bench LRANGE)");
        c = createClient(REDIS_REPLY_STATUS);
        len = redisFormatCommand(&cmd,"LPUSH mylist %s",data);
        c->obuf = sdsnewlen(cmd,len);
        free(cmd);
        createMissingClients(c);
        aeMain(config.el);
        endBenchmark();

        prepareForBenchmark("LRANGE (first 100 elements)");
        c = createClient(REDIS_REPLY_ARRAY);
        len = redisFormatCommand(&cmd,"LRANGE mylist 0 99");
        c->obuf = sdsnewlen(cmd,len);
        free(cmd);
        createMissingClients(c);
        aeMain(config.el);
        endBenchmark();

        prepareForBenchmark("LRANGE (first 300 elements)");
        c = createClient(REDIS_REPLY_ARRAY);
        len = redisFormatCommand(&cmd,"LRANGE mylist 0 299");
        c->obuf = sdsnewlen(cmd,len);
        free(cmd);
        createMissingClients(c);
        aeMain(config.el);
        endBenchmark();

        prepareForBenchmark("LRANGE (first 450 elements)");
        c = createClient(REDIS_REPLY_ARRAY);
        len = redisFormatCommand(&cmd,"LRANGE mylist 0 449");
        c->obuf = sdsnewlen(cmd,len);
        free(cmd);
        createMissingClients(c);
        aeMain(config.el);
        endBenchmark();

        prepareForBenchmark("LRANGE (first 600 elements)");
        c = createClient(REDIS_REPLY_ARRAY);
        len = redisFormatCommand(&cmd,"LRANGE mylist 0 599");
        c->obuf = sdsnewlen(cmd,len);
        free(cmd);
        createMissingClients(c);
        aeMain(config.el);
        endBenchmark();

        printf("\n");
    } while(config.loop);
