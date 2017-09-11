            mode, server.port,
            (long) getpid()
        );
        serverLogRaw(REDIS_NOTICE|REDIS_LOG_RAW,buf);
    }
    zfree(buf);
}
