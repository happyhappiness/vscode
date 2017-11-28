void
commCloseAllSockets(void)
{
    int fd;
    fde *F = NULL;

    for (fd = 0; fd <= Biggest_FD; fd++) {
        F = &fd_table[fd];

        if (!F->flags.open)
            continue;

        if (F->type != FD_SOCKET)
            continue;

        if (F->flags.ipc)	/* don't close inter-process sockets */
            continue;

        if (F->timeoutHandler != NULL) {
            AsyncCall::Pointer callback = F->timeoutHandler;
            F->timeoutHandler = NULL;
            debugs(5, 5, "commCloseAllSockets: FD " << fd << ": Calling timeout handler");
            ScheduleCallHere(callback);
        } else {
            debugs(5, 5, "commCloseAllSockets: FD " << fd << ": calling comm_reset_close()");
            comm_reset_close(fd);
        }
    }
}