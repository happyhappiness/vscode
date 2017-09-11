            redisLog(REDIS_WARNING,
                "I/O error reading bulk count from MASTER: %s",
                strerror(errno));
            replicationAbortSyncTransfer();
            return;
        }
        if (buf[0] == '-') {
            redisLog(REDIS_WARNING,
                "MASTER aborted replication with an error: %s",
                buf+1);
            replicationAbortSyncTransfer();
            return;
        } else if (buf[0] == '\0') {
            /* At this stage just a newline works as a PING in order to take
             * the connection live. So we refresh our last interaction
