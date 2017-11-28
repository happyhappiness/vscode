void
BlockingFile::readDone(int rvfd, const char *buf, int len, int errflag)
{
    debugs(79, 3, "BlockingFile::readDone: FD " << rvfd);
    assert (fd == rvfd);

    ssize_t rlen;

    if (errflag) {
        debugs(79, 3, "BlockingFile::readDone: got failure (" << errflag << ")");
        rlen = -1;
    } else {
        rlen = (ssize_t) len;
    }

    if (errflag == DISK_EOF)
        errflag = DISK_OK;  /* EOF is signalled by len == 0, not errors... */

    ReadRequest::Pointer result = readRequest;

    readRequest = NULL;

    ioRequestor->readCompleted(buf, rlen, errflag, result);
}