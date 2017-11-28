void
BlockingFile::read(ReadRequest *aRequest)
{
    assert (fd > -1);
    assert (ioRequestor.getRaw());
    readRequest = aRequest;
    file_read(fd, aRequest->buf, aRequest->len, aRequest->offset, ReadDone, this);
}