void
BlockingFile::read(ReadRequest *aRequest)
{
    assert (fd > -1);
    assert (ioRequestor.getRaw());
    readRequest = aRequest;
    debugs(79, 3, HERE << aRequest->len << " for FD " << fd << " at " << aRequest->offset);
    file_read(fd, aRequest->buf, aRequest->len, aRequest->offset, ReadDone, this);
}