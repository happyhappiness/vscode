int main(int argc, char **argv) {
    int i;
    client c;

    signal(SIGHUP, SIG_IGN);
    signal(SIGPIPE, SIG_IGN);

    config.debug = 0;
    config.numclients = 50;
    config.requests = 10000;
    config.liveclients = 0;
    config.el = aeCreateEventLoop();
    aeCreateTimeEvent(config.el,1,showThroughput,NULL,NULL);
    config.keepalive = 1;
    config.donerequests = 0;
    config.datasize = 3;
    config.randomkeys = 0;
    config.randomkeys_keyspacelen = 0;
    config.quiet = 0;
    config.loop = 0;
    config.idlemode = 0;
    config.latency = NULL;
    config.clients = listCreate();
    config.hostip = "127.0.0.1";
    config.hostport = 6379;
    config.hostsocket = NULL;

    parseOptions(argc,argv);
    config.latency = zmalloc(sizeof(long long)*config.requests);

    if (config.keepalive == 0) {
        printf("WARNING: keepalive disabled, you probably need 'echo 1 > /proc/sys/net/ipv4/tcp_tw_reuse' for Linux and 'sudo sysctl -w net.inet.tcp.msl=1000' for Mac OS X in order to use a lot of clients/requests\n");
    }

    if (config.idlemode) {
        printf("Creating %d idle connections and waiting forever (Ctrl+C when done)\n", config.numclients);
        prepareForBenchmark("IDLE");
        c = createClient(0); /* will never receive a reply */
        c->obuf = sdsempty();
        createMissingClients(c);
        aeMain(config.el);
        /* and will wait for every */
    }

    do {
        char *data, *cmd;
        int len;

        data = zmalloc(config.datasize+1);
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

    return 0;
}