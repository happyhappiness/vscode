redisLog(REDIS_WARNING,"Exiting on short write while writing to "
                                   "the append-only file: %s (nwritten=%ld, "
                                   "expected=%ld)",
                                   strerror(errno),
                                   (long)nwritten,
                                   (long)sdslen(server.aof_buf));