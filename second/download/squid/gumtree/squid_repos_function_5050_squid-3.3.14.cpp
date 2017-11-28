static int
examine_select(fd_set * readfds, fd_set * writefds)
{
    int fd = 0;
    fd_set read_x;
    fd_set write_x;

    struct timeval tv;
    AsyncCall::Pointer ch = NULL;
    fde *F = NULL;

    struct stat sb;
    debugs(5, DBG_CRITICAL, "examine_select: Examining open file descriptors...");

    for (fd = 0; fd < Squid_MaxFD; ++fd) {
        FD_ZERO(&read_x);
        FD_ZERO(&write_x);
        tv.tv_sec = tv.tv_usec = 0;

        if (FD_ISSET(fd, readfds))
            FD_SET(fd, &read_x);
        else if (FD_ISSET(fd, writefds))
            FD_SET(fd, &write_x);
        else
            continue;

        ++ statCounter.syscalls.selects;
        errno = 0;

        if (!fstat(fd, &sb)) {
            debugs(5, 5, "FD " << fd << " is valid.");
            continue;
        }

        F = &fd_table[fd];
        debugs(5, DBG_CRITICAL, "FD " << fd << ": " << xstrerror());
        debugs(5, DBG_CRITICAL, "WARNING: FD " << fd << " has handlers, but it's invalid.");
        debugs(5, DBG_CRITICAL, "FD " << fd << " is a " << fdTypeStr[F->type] << " called '" << F->desc << "'");
        debugs(5, DBG_CRITICAL, "tmout:" << F->timeoutHandler << " read:" << F->read_handler << " write:" << F->write_handler);

        for (ch = F->closeHandler; ch != NULL; ch = ch->Next())
            debugs(5, DBG_CRITICAL, " close handler: " << ch);

        if (F->closeHandler != NULL) {
            commCallCloseHandlers(fd);
        } else if (F->timeoutHandler != NULL) {
            debugs(5, DBG_CRITICAL, "examine_select: Calling Timeout Handler");
            ScheduleCallHere(F->timeoutHandler);
        }

        F->closeHandler = NULL;
        F->timeoutHandler = NULL;
        F->read_handler = NULL;
        F->write_handler = NULL;
        FD_CLR(fd, readfds);
        FD_CLR(fd, writefds);
    }

    return 0;
}