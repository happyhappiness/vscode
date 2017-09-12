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
        char *data = zmalloc(config.datasize+1);
        memset(data,'x',config.datasize);
        data[config.datasize] = '\0';

        prepareForBenchmark("PING");
        c = createClient(REDIS_REPLY_STATUS);
        c->obuf = sdscat(c->obuf,"PING\r\n");
        createMissingClients(c);
        aeMain(config.el);
        endBenchmark();

        prepareForBenchmark("PING (multi bulk)");
        c = createClient(REDIS_REPLY_STATUS);
        c->obuf = sdscat(c->obuf,"*1\r\n$4\r\nPING\r\n");
        createMissingClients(c);
        aeMain(config.el);
        endBenchmark();

        prepareForBenchmark("MSET (10 keys, multi bulk)");
        c = createClient(REDIS_REPLY_ARRAY);
        c->obuf = sdscatprintf(c->obuf,"*%d\r\n$4\r\nMSET\r\n", 11);
        for (i = 0; i < 10; i++) {
            c->obuf = sdscatprintf(c->obuf,"$%d\r\n%s\r\n",config.datasize,data);
        createMissingClients(c);
        aeMain(config.el);
        endBenchmark();

        prepareForBenchmark("SET");
        c = createClient(REDIS_REPLY_STATUS);
        c->obuf = sdscat(c->obuf,"*3\r\n$3\r\nSET\r\n$20\r\nfoo_rand000000000000\r\n");
        c->obuf = sdscatprintf(c->obuf,"$%d\r\n%s\r\n",config.datasize,data);
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

        printf("\n");
    } while(config.loop);

    return 0;
}