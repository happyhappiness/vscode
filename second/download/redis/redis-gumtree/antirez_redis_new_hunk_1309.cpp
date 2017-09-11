        if (errno == EAGAIN) {
            return;
        } else {
            serverLog(REDIS_VERBOSE, "Reading from client: %s",strerror(errno));
            freeClient(c);
            return;
        }
    } else if (nread == 0) {
        serverLog(REDIS_VERBOSE, "Client closed connection");
        freeClient(c);
        return;
    }
