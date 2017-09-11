        redisLog(REDIS_WARNING,"Unable to check the AOF length: %s",
            strerror(errno));
    } else {
        server.aof_current_size = sb.st_size;
    }
}

