
    data.read_pending = false;

    debugs(9, 3, HERE << "ftpDataRead: FD " << io.fd << " Read " << io.size << " bytes");

    if (io.size > 0) {
        kb_incr(&(statCounter.server.all.kbytes_in), io.size);
        kb_incr(&(statCounter.server.ftp.kbytes_in), io.size);
    }

    if (io.flag == COMM_ERR_CLOSING)
        return;

    assert(io.fd == data.conn->fd);

    if (EBIT_TEST(entry->flags, ENTRY_ABORTED)) {
        abortTransaction("entry aborted during dataRead");
        return;
    }

    if (io.flag == COMM_OK && io.size > 0) {
        debugs(9,5,HERE << "appended " << io.size << " bytes to readBuf");
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

    if (io.flag != COMM_OK) {
        debugs(50, ignoreErrno(io.xerrno) ? 3 : DBG_IMPORTANT,
               "ftpDataRead: read error: " << xstrerr(io.xerrno));

        if (ignoreErrno(io.xerrno)) {
            typedef CommCbMemFunT<FtpStateData, CommTimeoutCbParams> TimeoutDialer;
            AsyncCall::Pointer timeoutCall = JobCallback(9, 5,
                                             TimeoutDialer, this, FtpStateData::ftpTimeout);
            commSetConnTimeout(io.conn, Config.Timeout.read, timeoutCall);

            maybeReadVirginBody();
        } else {
            failed(ERR_READ_ERROR, 0);
            /* failed closes ctrl.conn and frees ftpState */
            return;
        }
    } else if (io.size == 0) {
        debugs(9,3, HERE << "Calling dataComplete() because io.size == 0");
        /*
         * DPW 2007-04-23
