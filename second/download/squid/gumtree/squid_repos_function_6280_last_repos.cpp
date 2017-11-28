void
DiskThreadsDiskFile::write(WriteRequest * writeRequest)
{
    debugs(79, 3, "DiskThreadsDiskFile::write: FD " << fd);
    ++statCounter.syscalls.disk.writes;
    ++inProgressIOs;
#if ASYNC_WRITE

    aioWrite(fd, writeRequest->offset, (char *)writeRequest->buf, writeRequest->len, WriteDone, new IoResult<WriteRequest>(this, writeRequest),
             writeRequest->free_func);
#else

    file_write(fd, writeRequest->offset, (char *)writeRequest->buf, writeRequest->len, WriteDone, new IoResult<WriteRequest>(this, writeRequest),
               writeRequest->free_func);
#endif
}