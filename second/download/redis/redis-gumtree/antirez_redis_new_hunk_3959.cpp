            config.interactive = 1;
        } else if (!strcmp(argv[i],"-c")) {
            config.argn_from_stdin = 1;
        } else if (!strcmp(argv[i],"-v")) {
            printf("redis-cli shipped with Redis verison %s\n", REDIS_VERSION);
            exit(0);
        } else {
            break;
        }
