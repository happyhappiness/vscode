void
Comm::ConnOpener::closeFd()
{
    if (temporaryFd_ < 0)
        return;

    cleanFd();

    // comm_close() below uses COMMIO_FD_WRITECB(fd)->active() to clear Comm
    // "Select" state. It will not clear ours. XXX: It should always clear
    // because a callback may have been active but was called before comm_close
    // Update: we now do this in cleanFd()
    // Comm::SetSelect(temporaryFd_, COMM_SELECT_WRITE, NULL, NULL, 0);

    comm_close(temporaryFd_);
    temporaryFd_ = -1;
}