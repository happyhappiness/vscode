
/* ============================== Append Only file ========================== */

static void feedAppendOnlyFile(struct redisCommand *cmd, int dictid, robj **argv, int argc) {
    sds buf = sdsempty();
    int j;
    ssize_t nwritten;
    time_t now;
    robj *tmpargv[3];

    /* The DB this command was targetting is not the same as the last command
