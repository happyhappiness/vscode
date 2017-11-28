void
BlockingFile::open(int flags, mode_t mode, RefCount<IORequestor> callback)
{
    /* Simulate async calls */
    fd = file_open(path_ , flags);
    ioRequestor = callback;

    if (fd < 0) {
        debugs(79, 3, "BlockingFile::open: got failure (" << errno << ")");
        error(true);
    } else {
        closed = false;
        ++store_open_disk_fd;
        debugs(79, 3, "BlockingFile::open: opened FD " << fd);
    }

    callback->ioCompletedNotification();
}