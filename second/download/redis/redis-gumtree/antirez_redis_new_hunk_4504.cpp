    }
}

static void ttlCommand(redisClient *c) {
    time_t expire;
    int ttl = -1;

    expire = getExpire(c->db,c->argv[1]);
    if (expire != -1) {
        ttl = (int) (expire-time(NULL));
        if (ttl < 0) ttl = -1;
    }
    addReplySds(c,sdscatprintf(sdsempty(),":%d\r\n",ttl));
}

/* =============================== Replication  ============================= */

static int syncWrite(int fd, char *ptr, ssize_t size, int timeout) {
