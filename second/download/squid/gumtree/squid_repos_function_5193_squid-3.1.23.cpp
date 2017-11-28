void
BlockingFile::write(WriteRequest *aRequest)
{
    debugs(79, 3, "storeUfsWrite: FD " << fd);
    writeRequest = aRequest;
    file_write(fd,
               aRequest->offset,
               (char *)aRequest->buf,
               aRequest->len,
               WriteDone,
               this,
               aRequest->free_func);
}