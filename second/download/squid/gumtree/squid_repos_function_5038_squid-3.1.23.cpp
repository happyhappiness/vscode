void
DiskThreadsDiskFile::open(int flags, mode_t mode, RefCount<IORequestor> callback)
{
    statCounter.syscalls.disk.opens++;
#if !ASYNC_OPEN

    fd = file_open(path_, flags);

    if (fd < 0) {
        debugs(79, 3, "DiskThreadsDiskFile::open: got failure (" << errno << ")");
        errorOccured = true;
        return;
    }

#endif
    Opening_FD++;

    ioRequestor = callback;

    ++inProgressIOs;

#if ASYNC_OPEN

    aioOpen(path_, flags, mode, DiskThreadsDiskFile::OpenDone, this);

#else

    openDone(fd, NULL, fd, 0);

#endif
}