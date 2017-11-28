void
checkTimeouts(void)
{
    int fd;
    fde *F = NULL;
    AsyncCall::Pointer callback;

    for (fd = 0; fd <= Biggest_FD; ++fd) {
        F = &fd_table[fd];

        if (writeTimedOut(fd)) {
            // We have an active write callback and we are timed out
            debugs(5, 5, "checkTimeouts: FD " << fd << " auto write timeout");
            Comm::SetSelect(fd, COMM_SELECT_WRITE, NULL, NULL, 0);
            COMMIO_FD_WRITECB(fd)->finish(COMM_ERROR, ETIMEDOUT);
        } else if (AlreadyTimedOut(F))
            continue;

        debugs(5, 5, "checkTimeouts: FD " << fd << " Expired");

        if (F->timeoutHandler != NULL) {
            debugs(5, 5, "checkTimeouts: FD " << fd << ": Call timeout handler");
            callback = F->timeoutHandler;
            F->timeoutHandler = NULL;
            ScheduleCallHere(callback);
        } else {
            debugs(5, 5, "checkTimeouts: FD " << fd << ": Forcing comm_close()");
            comm_close(fd);
        }
    }
}