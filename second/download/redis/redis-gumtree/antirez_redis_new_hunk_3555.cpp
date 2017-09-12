"automatically used as last argument.\n"
            );
        } else if (!strcmp(argv[i],"-v")) {
            printf("redis-cli shipped with Redis version %s (%s)\n", REDIS_VERSION, redisGitSHA1());
            exit(0);
        } else {
            break;
