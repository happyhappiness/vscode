        if (errno == EAGAIN) {
            nwritten = 0;
        } else {
            serverLog(REDIS_VERBOSE,
                "Error writing to client: %s", strerror(errno));
            freeClient(c);
            return;
