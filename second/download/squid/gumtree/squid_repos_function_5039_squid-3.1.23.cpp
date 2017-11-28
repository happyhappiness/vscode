void
DiskThreadsDiskFile::read(ReadRequest * request)
{
    debugs(79, 3, "DiskThreadsDiskFile::read: " << this << ", size " << request->len);
    assert (fd > -1);
    assert (ioRequestor.getRaw());
    statCounter.syscalls.disk.reads++;
    ++inProgressIOs;
#if ASYNC_READ

    aioRead(fd, request->offset, request->len, ReadDone, new IoResult<ReadRequest>(this, request));
#else

    file_read(fd, request->buf, request->len, request->offset, ReadDone, new IoResult<ReadRequest>(this, request));
#endif
}