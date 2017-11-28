void
FwdState::serverClosed(int fd)
{
    // XXX: fd is often -1 here
    debugs(17, 2, "FD " << fd << " " << entry->url() << " after " <<
           (fd >= 0 ? fd_table[fd].pconn.uses : -1) << " requests");
    if (fd >= 0 && serverConnection()->fd == fd)
        fwdPconnPool->noteUses(fd_table[fd].pconn.uses);
    retryOrBail();
}