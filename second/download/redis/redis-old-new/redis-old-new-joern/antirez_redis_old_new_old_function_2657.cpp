int parseOptions(int argc, const char **argv) {
    int i;
    int lastarg;
    int exit_status = 1;

    for (i = 1; i < argc; i++) {
        lastarg = (i == (argc-1));

        if (!strcmp(argv[i],"-c")) {
            if (lastarg) goto invalid;
            config.numclients = atoi(argv[++i]);
        } else if (!strcmp(argv[i],"-n")) {
            if (lastarg) goto invalid;
            config.requests = atoi(argv[++i]);
        } else if (!strcmp(argv[i],"-k")) {
            if (lastarg) goto invalid;
            config.keepalive = atoi(argv[++i]);
        } else if (!strcmp(argv[i],"-h")) {
            if (lastarg) goto invalid;
            config.hostip = strdup(argv[++i]);
        } else if (!strcmp(argv[i],"-p")) {
            if (lastarg) goto invalid;
            config.hostport = atoi(argv[++i]);
        } else if (!strcmp(argv[i],"-s")) {
            if (lastarg) goto invalid;
            config.hostsocket = strdup(argv[++i]);
        } else if (!strcmp(argv[i],"-d")) {
            if (lastarg) goto invalid;
            config.datasize = atoi(argv[++i]);
            if (config.datasize < 1) config.datasize=1;
            if (config.datasize > 1024*1024*1024) config.datasize = 1024*1024*1024;
        } else if (!strcmp(argv[i],"-r")) {
            if (lastarg) goto invalid;
            config.randomkeys = 1;
            config.randomkeys_keyspacelen = atoi(argv[++i]);
            if (config.randomkeys_keyspacelen < 0)
                config.randomkeys_keyspacelen = 0;
        } else if (!strcmp(argv[i],"-q")) {
            config.quiet = 1;
        } else if (!strcmp(argv[i],"--csv")) {
            config.csv = 1;
        } else if (!strcmp(argv[i],"-l")) {
            config.loop = 1;
        } else if (!strcmp(argv[i],"-I")) {
            config.idlemode = 1;
        } else if (!strcmp(argv[i],"--help")) {
            exit_status = 0;
            goto usage;
        } else {
            /* Assume the user meant to provide an option when the arg starts
             * with a dash. We're done otherwise and should use the remainder
             * as the command and arguments for running the benchmark. */
            if (argv[i][0] == '-') goto invalid;
            return i;
        }
    }

    return i;

invalid:
    printf("Invalid option \"%s\" or option argument missing\n\n",argv[i]);

usage:
    printf("Usage: redis-benchmark [-h <host>] [-p <port>] [-c <clients>] [-n <requests]> [-k <boolean>]\n\n");
    printf(" -h <hostname>      Server hostname (default 127.0.0.1)\n");
    printf(" -p <port>          Server port (default 6379)\n");
    printf(" -s <socket>        Server socket (overrides host and port)\n");
    printf(" -c <clients>       Number of parallel connections (default 50)\n");
    printf(" -n <requests>      Total number of requests (default 10000)\n");
    printf(" -d <size>          Data size of SET/GET value in bytes (default 2)\n");
    printf(" -k <boolean>       1=keep alive 0=reconnect (default 1)\n");
    printf(" -r <keyspacelen>   Use random keys for SET/GET/INCR, random values for SADD\n");
    printf("  Using this option the benchmark will get/set keys\n");
    printf("  in the form mykey_rand000000012456 instead of constant\n");
    printf("  keys, the <keyspacelen> argument determines the max\n");
    printf("  number of values for the random number. For instance\n");
    printf("  if set to 10 only rand000000000000 - rand000000000009\n");
    printf("  range will be allowed.\n");
    printf(" -q                 Quiet. Just show query/sec values\n");
    printf(" --csv              Output in CSV format\n");
    printf(" -l                 Loop. Run the tests forever\n");
    printf(" -I                 Idle mode. Just open N idle connections and wait.\n");
    exit(exit_status);
}