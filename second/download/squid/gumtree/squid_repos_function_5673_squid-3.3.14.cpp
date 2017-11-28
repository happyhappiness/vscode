void
IpcIoFile::writeCompleted(WriteRequest *writeRequest,
                          const IpcIoMsg *const response)
{
    bool ioError = false;
    if (!response) {
        debugs(79, 3, HERE << "error: timeout");
        ioError = true; // I/O timeout does not warrant setting error_?
    } else if (response->xerrno) {
        debugs(79, DBG_IMPORTANT, HERE << "error: " << xstrerr(response->xerrno));
        ioError = error_ = true;
    } else if (response->len != writeRequest->len) {
        debugs(79, DBG_IMPORTANT, HERE << "problem: " << response->len << " < " << writeRequest->len);
        error_ = true;
    }

    if (writeRequest->free_func)
        (writeRequest->free_func)(const_cast<char*>(writeRequest->buf)); // broken API?

    if (!ioError) {
        debugs(79,5, HERE << "wrote " << writeRequest->len << " to disker" <<
               diskId << " at " << writeRequest->offset);
    }

    const ssize_t rlen = ioError ? 0 : (ssize_t)writeRequest->len;
    const int errflag = ioError ? DISK_ERROR :DISK_OK;
    ioRequestor->writeCompleted(errflag, rlen, writeRequest);
}