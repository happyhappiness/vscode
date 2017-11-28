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
    assert(isOpen(fd));

    assert(F->type != FD_FILE);

    PROF_start(comm_close);

    F->flags.close_request = 1;

    AsyncCall::Pointer startCall=commCbCall(5,4, "comm_close_start",
                                            CommCloseCbPtrFun(comm_close_start, NULL));
    typedef CommCloseCbParams Params;
    Params &startParams = GetCommParams<Params>(startCall);
    startParams.fd = fd;
    ScheduleCallHere(startCall);

    // a half-closed fd may lack a reader, so we stop monitoring explicitly
    if (commHasHalfClosedMonitor(fd))
        commStopHalfClosedMonitor(fd);
    commSetTimeout(fd, -1, NULL, NULL);

    // notify read/write handlers
    if (commio_has_callback(fd, IOCB_WRITE, COMMIO_FD_WRITECB(fd))) {
        commio_finish_callback(fd, COMMIO_FD_WRITECB(fd), COMM_ERR_CLOSING, errno);
    }
    if (commio_has_callback(fd, IOCB_READ, COMMIO_FD_READCB(fd))) {
        commio_finish_callback(fd, COMMIO_FD_READCB(fd), COMM_ERR_CLOSING, errno);
    }

    // notify accept handlers
    fdc_table[fd].notify(-1, COMM_ERR_CLOSING, 0, ConnectionDetail());

    commCallCloseHandlers(fd);

    if (F->pconn.uses)
        F->pconn.pool->count(F->pconn.uses);

    comm_empty_os_read_buffers(fd);


    AsyncCall::Pointer completeCall=commCbCall(5,4, "comm_close_complete",
                                    CommCloseCbPtrFun(comm_close_complete, NULL));
    Params &completeParams = GetCommParams<Params>(completeCall);
    completeParams.fd = fd;
    // must use async call to wait for all callbacks
    // scheduled before comm_close() to finish
    ScheduleCallHere(completeCall);

    PROF_stop(comm_close);
}