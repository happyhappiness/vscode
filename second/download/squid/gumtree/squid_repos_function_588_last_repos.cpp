void
_comm_close(int fd, char const *file, int line)
{
    debugs(5, 3, "comm_close: start closing FD " << fd);
    assert(fd >= 0);
    assert(fd < Squid_MaxFD);

    fde *F = &fd_table[fd];
    fdd_table[fd].close_file = file;
    fdd_table[fd].close_line = line;

    if (F->closing())
        return;

    /* XXX: is this obsolete behind F->closing() ? */
    if ( (shutting_down || reconfiguring) && (!F->flags.open || F->type == FD_FILE))
        return;

    /* The following fails because ipc.c is doing calls to pipe() to create sockets! */
    if (!isOpen(fd)) {
        debugs(50, DBG_IMPORTANT, HERE << "BUG 3556: FD " << fd << " is not an open socket.");
        // XXX: do we need to run close(fd) or fd_close(fd) here?
        return;
    }

    assert(F->type != FD_FILE);

    PROF_start(comm_close);

    F->flags.close_request = true;

    if (F->ssl) {
        AsyncCall::Pointer startCall=commCbCall(5,4, "commStartTlsClose",
                                                FdeCbPtrFun(commStartTlsClose, nullptr));
        FdeCbParams &startParams = GetCommParams<FdeCbParams>(startCall);
        startParams.fd = fd;
        ScheduleCallHere(startCall);
    }

    // a half-closed fd may lack a reader, so we stop monitoring explicitly
    if (commHasHalfClosedMonitor(fd))
        commStopHalfClosedMonitor(fd);
    commUnsetFdTimeout(fd);

    // notify read/write handlers after canceling select reservations, if any
    if (COMMIO_FD_WRITECB(fd)->active()) {
        Comm::SetSelect(fd, COMM_SELECT_WRITE, NULL, NULL, 0);
        COMMIO_FD_WRITECB(fd)->finish(Comm::ERR_CLOSING, errno);
    }
    if (COMMIO_FD_READCB(fd)->active()) {
        Comm::SetSelect(fd, COMM_SELECT_READ, NULL, NULL, 0);
        COMMIO_FD_READCB(fd)->finish(Comm::ERR_CLOSING, errno);
    }

#if USE_DELAY_POOLS
    if (ClientInfo *clientInfo = F->clientInfo) {
        if (clientInfo->selectWaiting) {
            clientInfo->selectWaiting = false;
            // kick queue or it will get stuck as commWriteHandle is not called
            clientInfo->kickQuotaQueue();
        }
    }
#endif

    commCallCloseHandlers(fd);

    comm_empty_os_read_buffers(fd);

    AsyncCall::Pointer completeCall=commCbCall(5,4, "comm_close_complete",
                                    FdeCbPtrFun(comm_close_complete, NULL));
    FdeCbParams &completeParams = GetCommParams<FdeCbParams>(completeCall);
    completeParams.fd = fd;
    // must use async call to wait for all callbacks
    // scheduled before comm_close() to finish
    ScheduleCallHere(completeCall);

    PROF_stop(comm_close);
}