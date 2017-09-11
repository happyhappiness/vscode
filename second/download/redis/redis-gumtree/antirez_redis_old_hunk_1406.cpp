                server.tcp_backlog);
        }
        if (fds[*count] == ANET_ERR) {
            redisLog(REDIS_WARNING,
                "Creating Server TCP listening socket %s:%d: %s",
                server.bindaddr[j] ? server.bindaddr[j] : "*",
                port, server.neterr);
