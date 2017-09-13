int main(int argc, char **argv) {
    client c;

    signal(SIGHUP, SIG_IGN);
    signal(SIGPIPE, SIG_IGN);

    config.debug = 0;
    config.numclients = 50;
    config.requests = 10000;
    config.liveclients = 0;
    config.el = aeCreateEventLoop();
    config.keepalive = 1;
    config.donerequests = 0;
    config.datasize = 3;
    config.randomkeys = 0;
    config.randomkeys_keyspacelen = 0;
    config.quiet = 0;
    config.loop = 0;
    config.latency = NULL;
    config.clients = listCreate();
    config.latency = zmalloc(sizeof(int)*(MAX_LATENCY+1));

    config.hostip = "127.0.0.1";
    config.hostport = 6379;

    parseOptions(argc,argv);

    if (config.keepalive == 0) {
        printf("WARNING: keepalive disabled, you probably need 'echo 1 > /proc/sys/net/ipv4/tcp_tw_reuse' for Linux and 'sudo sysctl -w net.inet.tcp.msl=1000' for Mac OS X in order to use a lot of clients/requests\n");
    }

    do {
        prepareForBenchmark();
        c = createClient();
        if (!c) exit(1);
        c->obuf = sdscatprintf(c->obuf,"SET foo_rand000000000000 %d\r\n",config.datasize);
        {
            char *data = zmalloc(config.datasize+2);
            memset(data,'x',config.datasize);
            data[config.datasize] = '\r';
            data[config.datasize+1] = '\n';
            c->obuf = sdscatlen(c->obuf,data,config.datasize+2);
        }
        prepareClientForReply(c,REPLY_RETCODE);
        createMissingClients(c);
        aeMain(config.el);
        endBenchmark("SET");

        prepareForBenchmark();
        c = createClient();
        if (!c) exit(1);
        c->obuf = sdscat(c->obuf,"GET foo_rand000000000000\r\n");
        prepareClientForReply(c,REPLY_BULK);
        createMissingClients(c);
        aeMain(config.el);
        endBenchmark("GET");

        prepareForBenchmark();
        c = createClient();
        if (!c) exit(1);
        c->obuf = sdscat(c->obuf,"INCR counter_rand000000000000\r\n");
        prepareClientForReply(c,REPLY_INT);
        createMissingClients(c);
        aeMain(config.el);
        endBenchmark("INCR");

        prepareForBenchmark();
        c = createClient();
        if (!c) exit(1);
        c->obuf = sdscat(c->obuf,"LPUSH mylist 3\r\nbar\r\n");
        prepareClientForReply(c,REPLY_INT);
        createMissingClients(c);
        aeMain(config.el);
        endBenchmark("LPUSH");

        prepareForBenchmark();
        c = createClient();
        if (!c) exit(1);
        c->obuf = sdscat(c->obuf,"LPOP mylist\r\n");
        prepareClientForReply(c,REPLY_BULK);
        createMissingClients(c);
        aeMain(config.el);
        endBenchmark("LPOP");

        prepareForBenchmark();
        c = createClient();
        if (!c) exit(1);
        c->obuf = sdscat(c->obuf,"PING\r\n");
        prepareClientForReply(c,REPLY_RETCODE);
        createMissingClients(c);
        aeMain(config.el);
        endBenchmark("PING");

        prepareForBenchmark();
        c = createClient();
        if (!c) exit(1);
        c->obuf = sdscat(c->obuf,"LPUSH mylist 3\r\nbar\r\n");
        prepareClientForReply(c,REPLY_RETCODE);
        createMissingClients(c);
        aeMain(config.el);
        endBenchmark("LPUSH (again, in order to bench LRANGE)");

        prepareForBenchmark();
        c = createClient();
        if (!c) exit(1);
        c->obuf = sdscat(c->obuf,"LRANGE mylist 0 99\r\n");
        prepareClientForReply(c,REPLY_MBULK);
        createMissingClients(c);
        aeMain(config.el);
        endBenchmark("LRANGE (first 100 elements)");

        prepareForBenchmark();
        c = createClient();
        if (!c) exit(1);
        c->obuf = sdscat(c->obuf,"LRANGE mylist 0 299\r\n");
        prepareClientForReply(c,REPLY_MBULK);
        createMissingClients(c);
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

    return 0;
}