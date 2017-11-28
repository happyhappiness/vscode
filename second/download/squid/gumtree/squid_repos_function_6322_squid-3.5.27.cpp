void
BlockingFile::write(WriteRequest *aRequest)
{
    debugs(79, 3, HERE << aRequest->len << " for FD " << fd << " at " << aRequest->offset);
    writeRequest = aRequest;
    file_write(fd,
               aRequest->offset,
               (char *)aRequest->buf,
               aRequest->len,
               WriteDone,
               this,
               aRequest->free_func);
}