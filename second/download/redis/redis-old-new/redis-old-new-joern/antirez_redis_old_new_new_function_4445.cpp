void parseOptions(int argc, char **argv) {
    int i;

    for (i = 1; i < argc; i++) {
        int lastarg = i==argc-1;
        
        if (!strcmp(argv[i],"-c") && !lastarg) {
            config.numclients = atoi(argv[i+1]);
            i++;
        } else if (!strcmp(argv[i],"-n") && !lastarg) {
            config.requests = atoi(argv[i+1]);
            i++;
        } else if (!strcmp(argv[i],"-k") && !lastarg) {
            config.keepalive = atoi(argv[i+1]);
            i++;
        } else if (!strcmp(argv[i],"-h") && !lastarg) {
            char *ip = zmalloc(32);
            if (anetResolve(NULL,argv[i+1],ip) == ANET_ERR) {
                printf("Can't resolve %s\n", argv[i]);
                exit(1);
            }
            config.hostip = ip;
            i++;
        } else if (!strcmp(argv[i],"-p") && !lastarg) {
            config.hostport = atoi(argv[i+1]);
            i++;
        } else if (!strcmp(argv[i],"-d") && !lastarg) {
            config.datasize = atoi(argv[i+1]);
            i++;
            if (config.datasize < 1) config.datasize=1;
            if (config.datasize > 1024*1024) config.datasize = 1024*1024;
        } else if (!strcmp(argv[i],"-r") && !lastarg) {
            config.randomkeys = 1;
            config.randomkeys_keyspacelen = atoi(argv[i+1]);
            if (config.randomkeys_keyspacelen < 0)
                config.randomkeys_keyspacelen = 0;
            i++;
        } else if (!strcmp(argv[i],"-q")) {
            config.quiet = 1;
        } else if (!strcmp(argv[i],"-l")) {
            config.loop = 1;
        } else {
            printf("Wrong option '%s' or option argument missing\n\n",argv[i]);
            printf("Usage: redis-benchmark [-h <host>] [-p <port>] [-c <clients>] [-n <requests]> [-k <boolean>]\n\n");
            printf(" -h <hostname>      Server hostname (default 127.0.0.1)\n");
            printf(" -p <hostname>      Server port (default 6379)\n");
            printf(" -c <clients>       Number of parallel connections (default 50)\n");
            printf(" -n <requests>      Total number of requests (default 10000)\n");
            printf(" -d <size>          Data size of SET/GET value in bytes (default 2)\n");
            printf(" -k <boolean>       1=keep alive 0=reconnect (default 1)\n");
            printf(" -r <keyspacelen>   Use random keys for SET/GET/INCR\n");
            printf("  Using this option the benchmark will get/set keys\n");
            printf("  in the form mykey_rand000000012456 instead of constant\n");
            printf("  keys, the <keyspacelen> argument determines the max\n");
            printf("  number of values for the random number. For instance\n");
            printf("  if set to 10 only rand000000000000 - rand000000000009\n");
            printf("  range will be allowed.\n");
            printf(" -q                 Quiet. Just show query/sec values\n");
            printf(" -l                 Loop. Run the tests forever\n");
            exit(1);
        }
    }
}