void
Ftp::Client::dataRead(const CommIoCbParams &io)
{
    int j;
    int bin;

    data.read_pending = false;

    debugs(9, 3, "FD " << io.fd << " Read " << io.size << " bytes");

    if (io.size > 0) {
        kb_incr(&(statCounter.server.all.kbytes_in), io.size);
        kb_incr(&(statCounter.server.ftp.kbytes_in), io.size);
    }

    if (io.flag == Comm::ERR_CLOSING)
        return;

    assert(io.fd == data.conn->fd);

    if (EBIT_TEST(entry->flags, ENTRY_ABORTED)) {
        abortOnData("entry aborted during dataRead");
        return;
    }

    if (io.flag == Comm::OK && io.size > 0) {
        debugs(9, 5, "appended " << io.size << " bytes to readBuf");
        data.readBuf->appended(io.size);
#if USE_DELAY_POOLS
        DelayId delayId = entry->mem_obj->mostBytesAllowed();
        delayId.bytesIn(io.size);
#endif
        ++ IOStats.Ftp.reads;

        for (j = io.size - 1, bin = 0; j; ++bin)
            j >>= 1;

        ++ IOStats.Ftp.read_hist[bin];
    }

    if (io.flag != Comm::OK) {
        debugs(50, ignoreErrno(io.xerrno) ? 3 : DBG_IMPORTANT,
               "FTP data read error: " << xstrerr(io.xerrno));

        if (ignoreErrno(io.xerrno)) {
            maybeReadVirginBody();
        } else {
            failed(ERR_READ_ERROR, 0);
            /* failed closes ctrl.conn and frees ftpState */
            return;
        }
    } else if (io.size == 0) {
        debugs(9, 3, "Calling dataComplete() because io.size == 0");
        /*
         * DPW 2007-04-23
         * Dangerous curves ahead.  This call to dataComplete was
         * calling scheduleReadControlReply, handleControlReply,
         * and then ftpReadTransferDone.  If ftpReadTransferDone
         * gets unexpected status code, it closes down the control
         * socket and our FtpStateData object gets destroyed.   As
         * a workaround we no longer set the 'buffered_ok' flag in
         * the scheduleReadControlReply call.
         */
        dataComplete();
    }

    processReplyBody();
}