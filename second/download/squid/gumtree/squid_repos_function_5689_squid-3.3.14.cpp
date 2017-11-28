void
IpcIoPendingRequest::completeIo(IpcIoMsg *const response)
{
    if (readRequest)
        file->readCompleted(readRequest, response);
    else if (writeRequest)
        file->writeCompleted(writeRequest, response);
    else {
        Must(!response); // only timeouts are handled here
        file->openCompleted(NULL);
    }
}