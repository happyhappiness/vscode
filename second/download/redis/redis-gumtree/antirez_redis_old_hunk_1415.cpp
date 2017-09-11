            mode, server.port,
            (long) getpid()
        );
        redisLogRaw(REDIS_NOTICE|REDIS_LOG_RAW,buf);
    }
    zfree(buf);
}
