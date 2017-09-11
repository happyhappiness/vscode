
    if (fp == NULL) {
        if (errno == ENOENT) {
            return REDIS_ERR;
        } else {
            serverLog(REDIS_WARNING,
                "Loading the cluster node config from %s: %s",
