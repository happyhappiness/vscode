                                   strerror(errno),
                                   (long)nwritten,
                                   (long)sdslen(server.aof_buf));
        }
        exit(1);
    }
