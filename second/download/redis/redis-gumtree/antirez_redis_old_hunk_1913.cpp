 * to the current length, that is much faster. */
void aofUpdateCurrentSize(void) {
    struct redis_stat sb;

    if (redis_fstat(server.aof_fd,&sb) == -1) {
        redisLog(REDIS_WARNING,"Unable to obtain the AOF file length. stat: %s",
            strerror(errno));
    } else {
        server.aof_current_size = sb.st_size;
    }
}

/* A background append only file rewriting (BGREWRITEAOF) terminated its work.
