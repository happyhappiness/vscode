            printf(" -n <requests>      Total number of requests (default 10000)\n");
            printf(" -d <size>          Data size of SET/GET value in bytes (default 2)\n");
            printf(" -k <boolean>       1=keep alive 0=reconnect (default 1)\n");
            printf(" -r <keyspacelen>   Use random keys for SET/GET/INCR\n");
            printf("  Using this option the benchmark will get/set keys\n");
            printf("  in the form mykey_rand000000012456 instead of constant\n");
            printf("  keys, the <keyspacelen> argument determines the max\n");
