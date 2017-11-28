void
DiskThreadsDiskFile::openDone(int unused, const char *unused2, int anFD, int errflag)
{
    debugs(79, 3, "DiskThreadsDiskFile::openDone: FD " << anFD << ", errflag " << errflag);
    --Opening_FD;

    fd = anFD;

    if (errflag || fd < 0) {
        errno = errflag;
        debugs(79, DBG_CRITICAL, "DiskThreadsDiskFile::openDone: " << xstrerror());
        debugs(79, DBG_IMPORTANT, "\t" << path_);
        errorOccured = true;
    } else {
        ++store_open_disk_fd;
        commSetCloseOnExec(fd);
        fd_open(fd, FD_FILE, path_);
    }

    IORequestor::Pointer t = ioRequestor;
    --inProgressIOs;
    t->ioCompletedNotification();

    debugs(79, 3, "DiskThreadsDiskFile::openDone: exiting");
}