
        if (nread <= 0) {
            /* I/O error... */
            serverLog(REDIS_DEBUG,"I/O error reading from node link: %s",
                (nread == 0) ? "connection closed" : strerror(errno));
            handleLinkIOError(link);
            return;
