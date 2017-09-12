int main(int argc, const char **argv) {
    int i;
    char *data, *cmd;
    int len;

    client c;

    signal(SIGHUP, SIG_IGN);
    signal(SIGPIPE, SIG_IGN);

    config.numclients = 50;
    config.requests = 10000;
    config.liveclients = 0;
    config.el = aeCreateEventLoop();
    aeCreateTimeEvent(config.el,1,showThroughput,NULL,NULL);
    config.keepalive = 1;
    config.datasize = 3;
    config.randomkeys = 0;
    config.randomkeys_keyspacelen = 0;
    config.quiet = 0;
    config.csv = 0;
    config.loop = 0;
    config.idlemode = 0;
    config.latency = NULL;
    config.clients = listCreate();
    config.hostip = "127.0.0.1";
    config.hostport = 6379;
    config.hostsocket = NULL;
    config.tests = NULL;

    i = parseOptions(argc,argv);
    argc -= i;
    argv += i;

    config.latency = zmalloc(sizeof(long long)*config.requests);

    if (config.keepalive == 0) {
        printf("WARNING: keepalive disabled, you probably need 'echo 1 > /proc/sys/net/ipv4/tcp_tw_reuse' for Linux and 'sudo sysctl -w net.inet.tcp.msl=1000' for Mac OS X in order to use a lot of clients/requests\n");
    }

    if (config.idlemode) {
        printf("Creating %d idle connections and waiting forever (Ctrl+C when done)\n", config.numclients);
        c = createClient("",0); /* will never receive a reply */
        createMissingClients(c);
        aeMain(config.el);
        /* and will wait for every */
    }

    /* Run benchmark with command in the remainder of the arguments. */
    if (argc) {
        sds title = sdsnew(argv[0]);
        for (i = 1; i < argc; i++) {
            title = sdscatlen(title, " ", 1);
            title = sdscatlen(title, (char*)argv[i], strlen(argv[i]));
        }

        do {
            len = redisFormatCommandArgv(&cmd,argc,argv,NULL);
            benchmark(title,cmd,len);
            free(cmd);
        } while(config.loop);

        return 0;
    }

    /* Run default benchmark suite. */
    do {
        data = zmalloc(config.datasize+1);
        memset(data,'x',config.datasize);
        data[config.datasize] = '\0';

        if (test_is_selected("ping_inline") || test_is_selected("ping"))
            benchmark("PING_INLINE","PING\r\n",6);

        if (test_is_selected("ping_mbulk") || test_is_selected("ping")) {
            len = redisFormatCommand(&cmd,"PING");
            benchmark("PING_BULK",cmd,len);
            free(cmd);
        }

        if (test_is_selected("set")) {
            len = redisFormatCommand(&cmd,"SET foo:rand:000000000000 %s",data);
            benchmark("SET",cmd,len);
            free(cmd);
        }

        if (test_is_selected("get")) {
            len = redisFormatCommand(&cmd,"GET foo:rand:000000000000");
            benchmark("GET",cmd,len);
            free(cmd);
        }

        if (test_is_selected("incr")) {
            len = redisFormatCommand(&cmd,"INCR counter:rand:000000000000");
            benchmark("INCR",cmd,len);
            free(cmd);
        }

        if (test_is_selected("lpush")) {
            len = redisFormatCommand(&cmd,"LPUSH mylist %s",data);
            benchmark("LPUSH",cmd,len);
            free(cmd);
        }

        if (test_is_selected("lpop")) {
            len = redisFormatCommand(&cmd,"LPOP mylist");
            benchmark("LPOP",cmd,len);
            free(cmd);
        }

        if (test_is_selected("sadd")) {
            len = redisFormatCommand(&cmd,
                "SADD myset counter:rand:000000000000");
            benchmark("SADD",cmd,len);
            free(cmd);
        }

        if (test_is_selected("spop")) {
            len = redisFormatCommand(&cmd,"SPOP myset");
            benchmark("SPOP",cmd,len);
            free(cmd);
        }

        if (test_is_selected("lrange") ||
            test_is_selected("lrange_100") ||
            test_is_selected("lrange_300") ||
            test_is_selected("lrange_500") ||
            test_is_selected("lrange_600"))
        {
            len = redisFormatCommand(&cmd,"LPUSH mylist %s",data);
            benchmark("LPUSH (needed to benchmark LRANGE)",cmd,len);
            free(cmd);
        }

        if (test_is_selected("lrange") || test_is_selected("lrange_100")) {
            len = redisFormatCommand(&cmd,"LRANGE mylist 0 99");
            benchmark("LRANGE_100 (first 100 elements)",cmd,len);
            free(cmd);
        }

        if (test_is_selected("lrange") || test_is_selected("lrange_300")) {
            len = redisFormatCommand(&cmd,"LRANGE mylist 0 299");
            benchmark("LRANGE_300 (first 300 elements)",cmd,len);
            free(cmd);
        }

        if (test_is_selected("lrange") || test_is_selected("lrange_500")) {
            len = redisFormatCommand(&cmd,"LRANGE mylist 0 449");
            benchmark("LRANGE_500 (first 450 elements)",cmd,len);
            free(cmd);
        }

        if (test_is_selected("lrange") || test_is_selected("lrange_600")) {
            len = redisFormatCommand(&cmd,"LRANGE mylist 0 599");
            benchmark("LRANGE_600 (first 600 elements)",cmd,len);
            free(cmd);
        }

        if (test_is_selected("mset")) {
            const char *argv[21];
            argv[0] = "MSET";
            for (i = 1; i < 21; i += 2) {
                argv[i] = "foo:rand:000000000000";
                argv[i+1] = data;
            }
            len = redisFormatCommandArgv(&cmd,21,argv,NULL);
            benchmark("MSET (10 keys)",cmd,len);
            free(cmd);
        }

        if (!config.csv) printf("\n");
    } while(config.loop);

    return 0;
}