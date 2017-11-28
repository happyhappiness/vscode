void
IpcIoFile::write(WriteRequest *writeRequest)
{
    debugs(79,3, HERE << "(disker" << diskId << ", " << writeRequest->len << ", " <<
           writeRequest->offset << ")");

    assert(ioRequestor != NULL);
    assert(writeRequest->len > 0); // TODO: work around mmap failures on zero-len?
    assert(writeRequest->offset >= 0);
    Must(!error_);

    //assert(minOffset < 0 || minOffset <= writeRequest->offset);
    //assert(maxOffset < 0 || writeRequest->offset + writeRequest->len <= (uint64_t)maxOffset);

    IpcIoPendingRequest *const pending = new IpcIoPendingRequest(this);
    pending->writeRequest = writeRequest;
    push(pending);
}