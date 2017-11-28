void
Ftp::Client::readControlReply(const CommIoCbParams &io)
{
    debugs(9, 3, "FD " << io.fd << ", Read " << io.size << " bytes");

    if (io.size > 0) {
        kb_incr(&(statCounter.server.all.kbytes_in), io.size);
        kb_incr(&(statCounter.server.ftp.kbytes_in), io.size);
    }

    if (io.flag == Comm::ERR_CLOSING)
        return;

    if (EBIT_TEST(entry->flags, ENTRY_ABORTED)) {
        if (abortOnData("entry aborted during control reply read"))
            return;
    }

    assert(ctrl.offset < ctrl.size);

    if (io.flag == Comm::OK && io.size > 0) {
        fd_bytes(io.fd, io.size, FD_READ);
    }

    if (io.flag != Comm::OK) {
        debugs(50, ignoreErrno(io.xerrno) ? 3 : DBG_IMPORTANT,
               "FTP control reply read error: " << xstrerr(io.xerrno));

        if (ignoreErrno(io.xerrno)) {
            scheduleReadControlReply(0);
        } else {
            failed(ERR_READ_ERROR, io.xerrno);
            /* failed closes ctrl.conn and frees ftpState */
        }
        return;
    }

    if (io.size == 0) {
        if (entry->store_status == STORE_PENDING) {
            failed(ERR_FTP_FAILURE, 0);
            /* failed closes ctrl.conn and frees ftpState */
            return;
        }

        /* XXX this may end up having to be serverComplete() .. */
        abortAll("zero control reply read");
        return;
    }

    unsigned int len =io.size + ctrl.offset;
    ctrl.offset = len;
    assert(len <= ctrl.size);
    if (Comm::IsConnOpen(ctrl.conn))
        commUnsetConnTimeout(ctrl.conn); // we are done waiting for ctrl reply
    handleControlReply();
}