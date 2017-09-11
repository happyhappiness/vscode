    fprintf(stderr,"       ./redis-server /etc/redis/6379.conf\n");
    fprintf(stderr,"       ./redis-server --port 7777\n");
    fprintf(stderr,"       ./redis-server --port 7777 --slaveof 127.0.0.1 8888\n");
    fprintf(stderr,"       ./redis-server /etc/myredis.conf --loglevel verbose\n");
    exit(1);
}

void redisAsciiArt(void) {
#include "asciilogo.h"
    char *buf = zmalloc(1024*16);

    snprintf(buf,1024*16,ascii_logo,
        REDIS_VERSION,
        redisGitSHA1(),
        strtol(redisGitDirty(),NULL,10) > 0,
        (sizeof(long) == 8) ? "64" : "32",
        server.cluster_enabled ? "cluster" : "stand alone",
        server.port,
        (long) getpid()
    );
    redisLogRaw(REDIS_NOTICE|REDIS_LOG_RAW,buf);
