                                   strerror(errno),
                                   (long)nwritten,
                                   (long)sdslen(server.aof_buf));

            if (ftruncate(server.aof_fd, server.aof_current_size) == -1) {
                redisLog(REDIS_WARNING, "Could not remove short write "
                         "from the append-only file.  Redis may refuse "
                         "to load the AOF the next time it starts.  "
                         "ftruncate: %s", strerror(errno));
            }
        }
        exit(1);
    }
