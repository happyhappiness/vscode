void
commStopHalfClosedMonitor(int const fd)
{
    debugs(5, 5, HERE << "removing FD " << fd << " from " << *TheHalfClosed);

    // cancel the read if one was scheduled
    AsyncCall::Pointer reader = fd_table[fd].halfClosedReader;
    if (reader != NULL)
        Comm::ReadCancel(fd, reader);
    fd_table[fd].halfClosedReader = NULL;

    TheHalfClosed->del(fd);
}