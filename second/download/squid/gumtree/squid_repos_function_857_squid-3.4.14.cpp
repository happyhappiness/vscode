void
whoisStart(FwdState * fwd)
{
    WhoisState *p;
    char *buf;
    size_t l;
    CBDATA_INIT_TYPE(WhoisState);
    p = cbdataAlloc(WhoisState);
    p->request = fwd->request;
    p->entry = fwd->entry;
    p->fwd = fwd;
    p->dataWritten = false;

    p->entry->lock();
    comm_add_close_handler(fwd->serverConnection()->fd, whoisClose, p);

    l = p->request->urlpath.size() + 3;

    buf = (char *)xmalloc(l);

    String str_print=p->request->urlpath.substr(1,p->request->urlpath.size());
    snprintf(buf, l, SQUIDSTRINGPH"\r\n", SQUIDSTRINGPRINT(str_print));

    AsyncCall::Pointer writeCall = commCbCall(5,5, "whoisWriteComplete",
                                   CommIoCbPtrFun(whoisWriteComplete, p));
    Comm::Write(fwd->serverConnection(), buf, strlen(buf), writeCall, NULL);
    AsyncCall::Pointer readCall = commCbCall(5,4, "whoisReadReply",
                                  CommIoCbPtrFun(whoisReadReply, p));
    comm_read(fwd->serverConnection(), p->buf, BUFSIZ, readCall);
    AsyncCall::Pointer timeoutCall = commCbCall(5, 4, "whoisTimeout",
                                     CommTimeoutCbPtrFun(whoisTimeout, p));
    commSetConnTimeout(fwd->serverConnection(), Config.Timeout.read, timeoutCall);
}