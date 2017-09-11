        c = redisConnect(config.tcp.host, config.tcp.port);
    } else if (config.type == CONN_UNIX) {
        c = redisConnectUnix(config.unix.path);
    } else if (config.type == CONN_FD) {
        /* Create a dummy connection just to get an fd to inherit */
        redisContext *dummy_ctx = redisConnectUnix(config.unix.path);
        if (dummy_ctx) {
            int fd = disconnect(dummy_ctx, 1);
            printf("Connecting to inherited fd %d\n", fd);
            c = redisConnectFd(fd);
        }
    } else {
        assert(NULL);
    }

    if (c == NULL) {
        printf("Connection error: can't allocate redis context\n");
        exit(1);
    } else if (c->err) {
        printf("Connection error: %s\n", c->errstr);
        exit(1);
    }
