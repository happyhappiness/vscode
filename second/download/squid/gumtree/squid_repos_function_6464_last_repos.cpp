void
IpcIoFile::handleResponse(IpcIoMsg &ipcIo)
{
    const int requestId = ipcIo.requestId;
    debugs(47, 7, HERE << "popped disker response: " <<
           SipcIo(KidIdentifier, ipcIo, diskId));

    Must(requestId);
    if (IpcIoPendingRequest *const pending = dequeueRequest(requestId)) {
        pending->completeIo(&ipcIo);
        delete pending; // XXX: leaking if throwing
    } else {
        debugs(47, 4, HERE << "LATE disker response to " << ipcIo.command <<
               "; ipcIo" << KidIdentifier << '.' << requestId);
        // nothing we can do about it; completeIo() has been called already
    }
}