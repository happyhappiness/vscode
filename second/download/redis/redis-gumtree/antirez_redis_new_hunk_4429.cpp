            redisLog(REDIS_WARNING,"Aborting on short write while writing to the append-only file: %s",strerror(errno));
         }
         abort();
    }
    now = time(NULL);
    if (server.appendfsync == APPENDFSYNC_ALWAYS ||
        (server.appendfsync == APPENDFSYNC_EVERYSEC &&
         now-server.lastfsync > 1))
    {
        fsync(server.appendfd); /* Let's try to get this data on the disk */
        server.lastfsync = now;
    }
}

static void processInputBuffer(redisClient *c) {
