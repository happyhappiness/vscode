            printf("Wrong option '%s' or option argument missing\n\n",argv[i]);
            printf("Usage: redis-benchmark [-h <host>] [-p <port>] [-c <clients>] [-n <requests]> [-k <boolean>]\n\n");
            printf(" -h <hostname>      Server hostname (default 127.0.0.1)\n");
            printf(" -p <port>          Server port (default 6379)\n");
            printf(" -s <socket>        Server socket (overrides host and port)\n");
            printf(" -c <clients>       Number of parallel connections (default 50)\n");
            printf(" -n <requests>      Total number of requests (default 10000)\n");
            printf(" -d <size>          Data size of SET/GET value in bytes (default 2)\n");
