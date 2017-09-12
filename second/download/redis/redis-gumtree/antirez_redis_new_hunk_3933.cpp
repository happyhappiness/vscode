"by default when redis-cli is executed without a command to execute.\n"
            );
        } else if (!strcmp(argv[i],"-c")) {
            fprintf(stderr,
"Reading last argument from standard input using -c is deprecated.\n"
"When standard input is connected to a pipe or regular file, it is\n"
"automatically used as last argument.\n"
            );
        } else if (!strcmp(argv[i],"-v")) {
            printf("redis-cli shipped with Redis verison %s\n", REDIS_VERSION);
            exit(0);
