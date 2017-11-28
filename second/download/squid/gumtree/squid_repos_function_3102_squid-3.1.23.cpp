void
errorSend(int fd, ErrorState * err)
{
    HttpReply *rep;
    debugs(4, 3, "errorSend: FD " << fd << ", err=" << err);
    assert(fd >= 0);
    /*
     * ugh, this is how we make sure error codes get back to
     * the client side for logging and error tracking.
     */

    if (err->request)
        err->request->errType = err->type;

    /* moved in front of errorBuildBuf @?@ */
    err->flags.flag_cbdata = 1;

    rep = err->BuildHttpReply();

    MemBuf *mb = rep->pack();
    comm_write_mbuf(fd, mb, errorSendComplete, err);
    delete mb;

    delete rep;
}