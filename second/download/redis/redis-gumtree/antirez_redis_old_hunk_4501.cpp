    } else if (argc > 2) {
        fprintf(stderr,"Usage: ./redis-server [/path/to/redis.conf]\n");
        exit(1);
    }
    initServer();
    if (server.daemonize) daemonize();
