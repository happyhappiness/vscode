}

void version() {
    printf("Redis server v=%s sha=%s:%d malloc=%s\n", REDIS_VERSION,
        redisGitSHA1(), atoi(redisGitDirty()) > 0, ZMALLOC_LIB);
    exit(0);
}

