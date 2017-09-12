        } else if (!strcmp(argv[i],"-a") && !lastarg) {
            config.auth = argv[i+1];
            i++;
        } else if (!strcmp(argv[i],"--raw")) {
            config.raw_output = 1;
        } else if (!strcmp(argv[i],"-v") || !strcmp(argv[i], "--version")) {
            sds version = cliVersion();
            printf("redis-cli %s\n", version);
