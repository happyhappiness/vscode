void
whoisStart(FwdState * fwd)
{
    WhoisState *p;
    int fd = fwd->server_fd;
    char *buf;
    size_t l;
    CBDATA_INIT_TYPE(WhoisState);
    p = cbdataAlloc(WhoisState);
    p->request = fwd->request;
    p->entry = fwd->entry;
    p->fwd = fwd;
    p->dataWritten = false;

    p->entry->lock();
    comm_add_close_handler(fd, whoisClose, p);

    l = p->request->urlpath.size() + 3;

    buf = (char *)xmalloc(l);

    String str_print=p->request->urlpath.substr(1,p->request->urlpath.size());
    snprintf(buf, l, SQUIDSTRINGPH"\r\n", SQUIDSTRINGPRINT(str_print));

    comm_write(fd, buf, strlen(buf), whoisWriteComplete, p, NULL);
    comm_read(fd, p->buf, BUFSIZ, whoisReadReply, p);
    commSetTimeout(fd, Config.Timeout.read, whoisTimeout, p);
}