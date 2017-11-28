void
DiskThreadsDiskFile::create(int flags, mode_t mode, RefCount<IORequestor> callback)
{
    statCounter.syscalls.disk.opens++;
#if !ASYNC_CREATE

    int fd = file_open(path_, flags);

    if (fd < 0) {
        debugs(79, 3, "DiskThreadsDiskFile::create: got failure (" << errno << ")");
        errorOccured = true;
        return;
    }

#endif
    Opening_FD++;

    ioRequestor = callback;

    ++inProgressIOs;

#if ASYNC_CREATE

    aioOpen(path_, flags, mode, DiskThreadsDiskFile::OpenDone, this);

#else

    openDone (fd, NULL, fd, 0);

#endif
}