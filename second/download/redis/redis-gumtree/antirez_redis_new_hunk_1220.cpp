        if (errno == ENOENT) {
            return REDIS_ERR;
        } else {
            serverLog(REDIS_WARNING,
                "Loading the cluster node config from %s: %s",
                filename, strerror(errno));
            exit(1);
