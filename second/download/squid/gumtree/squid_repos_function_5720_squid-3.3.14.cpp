void
BlockingFile::writeDone(int rvfd, int errflag, size_t len)
{
    assert (rvfd == fd);
    debugs(79, 3, HERE << "FD " << fd << ", len " << len);

    WriteRequest::Pointer result = writeRequest;
    writeRequest = NULL;

    if (errflag) {
        debugs(79, DBG_CRITICAL, "storeUfsWriteDone: got failure (" << errflag << ")");
        doClose();
        ioRequestor->writeCompleted (DISK_ERROR,0, result);
        return;
    }

    ioRequestor->writeCompleted(DISK_OK, len, result);
}