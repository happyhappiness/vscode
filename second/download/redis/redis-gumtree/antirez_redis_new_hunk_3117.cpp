    unlink(tmpfile);
}

/* Update the server.appendonly_current_size filed explicitly using stat(2)
 * to check the size of the file. This is useful after a rewrite or after
 * a restart, normally the size is updated just adding the write length
 * to the current lenght, that is much faster. */
void aofUpdateCurrentSize(void) {
    struct redis_stat sb;

    if (redis_fstat(server.appendfd,&sb) == -1) {
        redisLog(REDIS_WARNING,"Unable to check the AOF length: %s",
            strerror(errno));
    } else {
        server.appendonly_current_size = sb.st_size;
    }
}

/* A background append only file rewriting (BGREWRITEAOF) terminated its work.
 * Handle this. */
void backgroundRewriteDoneHandler(int exitcode, int bysignal) {
