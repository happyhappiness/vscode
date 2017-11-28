static void
helperDispatchWriteDone(const Comm::ConnectionPointer &conn, char *buf, size_t len, comm_err_t flag, int xerrno, void *data)
{
    helper_server *srv = (helper_server *)data;

    srv->writebuf->clean();
    delete srv->writebuf;
    srv->writebuf = NULL;
    srv->flags.writing = 0;

    if (flag != COMM_OK) {
        /* Helper server has crashed */
        debugs(84, DBG_CRITICAL, "helperDispatch: Helper " << srv->parent->id_name << " #" << srv->index + 1 << " has crashed");
        return;
    }

    if (!srv->wqueue->isNull()) {
        srv->writebuf = srv->wqueue;
        srv->wqueue = new MemBuf;
        srv->flags.writing = 1;
        AsyncCall::Pointer call = commCbCall(5,5, "helperDispatchWriteDone",
                                             CommIoCbPtrFun(helperDispatchWriteDone, srv));
        Comm::Write(srv->writePipe, srv->writebuf->content(), srv->writebuf->contentSize(), call, NULL);
    }
}