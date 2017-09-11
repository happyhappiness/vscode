        c = redisConnect(config.tcp.host, config.tcp.port);
    } else if (config.type == CONN_UNIX) {
        c = redisConnectUnix(config.unix.path);
    } else {
        assert(NULL);
    }

    if (c->err) {
        printf("Connection error: %s\n", c->errstr);
        exit(1);
    }
