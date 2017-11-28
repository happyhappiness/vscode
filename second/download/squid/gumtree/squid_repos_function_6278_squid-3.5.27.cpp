void
IpcIoFile::readCompleted(ReadRequest *readRequest,
                         IpcIoMsg *const response)
{
    bool ioError = false;
    if (!response) {
        debugs(79, 3, HERE << "error: timeout");
        ioError = true; // I/O timeout does not warrant setting error_?
    } else {
        if (response->xerrno) {
            debugs(79, DBG_IMPORTANT, "ERROR: " << dbName << " read: " <<
                   xstrerr(response->xerrno));
            ioError = error_ = true;
        } else if (!response->page) {
            debugs(79, DBG_IMPORTANT, "ERROR: " << dbName << " read ran " <<
                   "out of shared memory pages");
            ioError = true;
        } else {
            const char *const buf = Ipc::Mem::PagePointer(response->page);
            memcpy(readRequest->buf, buf, response->len);
        }

        Ipc::Mem::PutPage(response->page);
    }

    const ssize_t rlen = ioError ? -1 : (ssize_t)readRequest->len;
    const int errflag = ioError ? DISK_ERROR :DISK_OK;
    ioRequestor->readCompleted(readRequest->buf, rlen, errflag, readRequest);
}