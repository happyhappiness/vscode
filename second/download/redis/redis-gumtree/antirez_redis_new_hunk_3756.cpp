"automatically used as last argument.\n"
            );
        } else if (!strcmp(argv[i],"-v")) {
            printf("redis-cli shipped with Redis version %s\n", REDIS_VERSION);
            exit(0);
        } else {
            break;
