void
MmappedFile::open(int flags, mode_t, RefCount<IORequestor> callback)
{
    assert(fd < 0);

    /* Simulate async calls */
    fd = file_open(path_ , flags);
    ioRequestor = callback;

    if (fd < 0) {
        int xerrno = errno;
        debugs(79,3, "open error: " << xstrerr(xerrno));
        error_ = true;
    } else {
        ++store_open_disk_fd;
        debugs(79,3, "FD " << fd);

        // setup mapping boundaries
        struct stat sb;
        if (fstat(fd, &sb) == 0)
            maxOffset = sb.st_size; // we do not expect it to change
    }

    callback->ioCompletedNotification();
}