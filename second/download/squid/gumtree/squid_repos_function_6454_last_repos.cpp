void
IpcIoFile::read(ReadRequest *readRequest)
{
    debugs(79,3, HERE << "(disker" << diskId << ", " << readRequest->len << ", " <<
           readRequest->offset << ")");

    assert(ioRequestor != NULL);
    assert(readRequest->offset >= 0);
    Must(!error_);

    //assert(minOffset < 0 || minOffset <= readRequest->offset);
    //assert(maxOffset < 0 || readRequest->offset + readRequest->len <= (uint64_t)maxOffset);

    IpcIoPendingRequest *const pending = new IpcIoPendingRequest(this);
    pending->readRequest = readRequest;
    push(pending);
}