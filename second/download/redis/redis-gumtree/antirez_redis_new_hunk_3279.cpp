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
    zfree(buf);
}

int main(int argc, char **argv) {
    long long start;

