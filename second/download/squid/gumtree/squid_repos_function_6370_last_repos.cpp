void
MmappedFile::write(WriteRequest *aRequest)
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

    const ssize_t written =
        pwrite(fd, aRequest->buf, aRequest->len, aRequest->offset);
    if (written < 0) {
        debugs(79, DBG_IMPORTANT, HERE << "error: " << xstrerr(errno));
        error_ = true;
    } else if (static_cast<size_t>(written) != aRequest->len) {
        debugs(79, DBG_IMPORTANT, HERE << "problem: " << written << " < " << aRequest->len);
        error_ = true;
    }

    if (aRequest->free_func)
        (aRequest->free_func)(const_cast<char*>(aRequest->buf)); // broken API?

    if (!error_) {
        debugs(79,5, HERE << "wrote " << aRequest->len << " to FD " << fd << " at " << aRequest->offset);
    } else {
        doClose();
    }

    const ssize_t rlen = error_ ? 0 : (ssize_t)aRequest->len;
    const int errflag = error_ ? DISK_ERROR :DISK_OK;
    ioRequestor->writeCompleted(errflag, rlen, aRequest);
}