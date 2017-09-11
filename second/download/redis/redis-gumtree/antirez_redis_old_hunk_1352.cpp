        if (ftruncate(server.repl_transfer_fd,
            server.repl_transfer_read - REDIS_RUN_ID_SIZE) == -1)
        {
            redisLog(REDIS_WARNING,"Error truncating the RDB file received from the master for SYNC: %s", strerror(errno));
            goto error;
        }
    }
