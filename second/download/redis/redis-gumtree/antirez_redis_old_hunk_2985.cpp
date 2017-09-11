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
    printf(" -l                 Loop. Run the tests forever\n");
    printf(" -I                 Idle mode. Just open N idle connections and wait.\n");
    exit(exit_status);
}

