}

void version() {
    printf("Redis server version %s (%s:%d)\n", REDIS_VERSION,
        redisGitSHA1(), atoi(redisGitDirty()) > 0);
    exit(0);
}

