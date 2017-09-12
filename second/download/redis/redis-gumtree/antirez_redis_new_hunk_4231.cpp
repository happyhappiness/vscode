    char buf[128];
    size_t len;

    if (ul == 0) {
        addReply(c,shared.czero);
        return;
    } else if (ul == 1) {
        addReply(c,shared.cone);
        return;
    }
    len = snprintf(buf,sizeof(buf),":%lu\r\n",ul);
    addReplySds(c,sdsnewlen(buf,len));
}
