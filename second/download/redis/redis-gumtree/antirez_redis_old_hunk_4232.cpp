    addReplySds(c,sdscatprintf(sdsempty(),"$%lu\r\n",(unsigned long)len));
}

static void acceptHandler(aeEventLoop *el, int fd, void *privdata, int mask) {
    int cport, cfd;
    char cip[128];
