        if (errno == ENOENT) {
            return C_ERR;
        } else {
            serverLog(REDIS_WARNING,
                "Loading the cluster node config from %s: %s",
                filename, strerror(errno));
            exit(1);
