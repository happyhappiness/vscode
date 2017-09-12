    } else if (argc > 2) {
        fprintf(stderr,"Usage: ./redis-server [/path/to/redis.conf]\n");
        exit(1);
    } else {
        redisLog(REDIS_WARNING,"Warning: no config file specified, using the default config. In order to specify a config file use 'redis-server /path/to/redis.conf'");
    }
    initServer();
    if (server.daemonize) daemonize();
