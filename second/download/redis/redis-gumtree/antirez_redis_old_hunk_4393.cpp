            config.quiet = 1;
        } else if (!strcmp(argv[i],"-l")) {
            config.loop = 1;
        } else {
            printf("Wrong option '%s' or option argument missing\n\n",argv[i]);
            printf("Usage: redis-benchmark [-h <host>] [-p <port>] [-c <clients>] [-n <requests]> [-k <boolean>]\n\n");
