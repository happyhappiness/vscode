void
MmappedFile::read(ReadRequest *aRequest)
{
    debugs(79,3, HERE << "(FD " << fd << ", " << aRequest->len << ", " <<
           aRequest->offset << ")");

    assert(fd >= 0);
    assert(ioRequestor != NULL);
    assert(aRequest->len > 0); // TODO: work around mmap failures on zero-len?
    assert(aRequest->offset >= 0);
    assert(!error_); // TODO: propagate instead?

    assert(minOffset < 0 || minOffset <= aRequest->offset);
    assert(maxOffset < 0 || static_cast<uint64_t>(aRequest->offset + aRequest->len) <= static_cast<uint64_t>(maxOffset));

    Mmapping mapping(fd, aRequest->len, PROT_READ, MAP_PRIVATE | MAP_NORESERVE,
                     aRequest->offset);

    bool done = false;
    if (void *buf = mapping.map()) {
        memcpy(aRequest->buf, buf, aRequest->len);
        done = mapping.unmap();
    }
    error_ = !done;

    const ssize_t rlen = error_ ? -1 : (ssize_t)aRequest->len;
    const int errflag = error_ ? DISK_ERROR :DISK_OK;
    ioRequestor->readCompleted(aRequest->buf, rlen, errflag, aRequest);
}