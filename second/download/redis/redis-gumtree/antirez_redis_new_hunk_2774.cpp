}

void version() {
    printf("Redis server v=%s sha=%s:%d malloc=%s\n", REDIS_VERSION,
        redisGitSHA1(), atoi(redisGitDirty()) > 0, ZMALLOC_LIB);
    exit(0);
}

void usage() {
    fprintf(stderr,"Usage: ./redis-server [/path/to/redis.conf] [options]\n");
    fprintf(stderr,"       ./redis-server - (read config from stdin)\n");
    fprintf(stderr,"       ./redis-server -v or --version\n");
    fprintf(stderr,"       ./redis-server -h or --help\n");
    fprintf(stderr,"       ./redis-server --test-memory <megabytes>\n\n");
    fprintf(stderr,"Examples:\n");
    fprintf(stderr,"       ./redis-server (run the server with default conf)\n");
    fprintf(stderr,"       ./redis-server /etc/redis/6379.conf\n");
