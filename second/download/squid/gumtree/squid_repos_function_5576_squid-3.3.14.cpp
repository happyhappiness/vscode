void
MmappedFile::open(int flags, mode_t mode, RefCount<IORequestor> callback)
{
    assert(fd < 0);

    /* Simulate async calls */
    fd = file_open(path_ , flags);
    ioRequestor = callback;

    if (fd < 0) {
        debugs(79,3, HERE << "open error: " << xstrerror());
        error_ = true;
    } else {
        ++store_open_disk_fd;
        debugs(79,3, HERE << "FD " << fd);

        // setup mapping boundaries
        struct stat sb;
        if (fstat(fd, &sb) == 0)
            maxOffset = sb.st_size; // we do not expect it to change
    }

    callback->ioCompletedNotification();
}