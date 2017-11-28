void FtpStateData::ftpReadControlReply(const CommIoCbParams &io)
{
    debugs(9, 3, "ftpReadControlReply: FD " << io.fd << ", Read " << io.size << " bytes");

    if (io.size > 0) {
        kb_incr(&statCounter.server.all.kbytes_in, io.size);
        kb_incr(&statCounter.server.ftp.kbytes_in, io.size);
    }

    if (io.flag == COMM_ERR_CLOSING)
        return;

    if (EBIT_TEST(entry->flags, ENTRY_ABORTED)) {
        abortTransaction("entry aborted during control reply read");
        return;
    }

    assert(ctrl.offset < ctrl.size);

    if (io.flag == COMM_OK && io.size > 0) {
        fd_bytes(io.fd, io.size, FD_READ);
    }

    if (io.flag != COMM_OK) {
        debugs(50, ignoreErrno(io.xerrno) ? 3 : DBG_IMPORTANT,
               "ftpReadControlReply: read error: " << xstrerr(io.xerrno));

        if (ignoreErrno(io.xerrno)) {
            scheduleReadControlReply(0);
        } else {
            failed(ERR_READ_ERROR, io.xerrno);
            /* failed closes ctrl.fd and frees ftpState */
        }
        return;
    }

    if (io.size == 0) {
        if (entry->store_status == STORE_PENDING) {
            failed(ERR_FTP_FAILURE, 0);
            /* failed closes ctrl.fd and frees ftpState */
            return;
        }

        /* XXX this may end up having to be serverComplete() .. */
        abortTransaction("zero control reply read");
        return;
    }

    unsigned int len =io.size + ctrl.offset;
    ctrl.offset = len;
    assert(len <= ctrl.size);
    handleControlReply();
}