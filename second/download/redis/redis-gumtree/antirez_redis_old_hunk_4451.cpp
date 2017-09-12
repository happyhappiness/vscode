    addReplySds(c,sdscatprintf(sdsempty(),":%d\r\n",ttl));
}

/* =============================== Replication  ============================= */

static int syncWrite(int fd, char *ptr, ssize_t size, int timeout) {
