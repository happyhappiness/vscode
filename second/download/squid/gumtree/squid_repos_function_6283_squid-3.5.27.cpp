void
IpcIoFile::push(IpcIoPendingRequest *const pending)
{
    // prevent queue overflows: check for responses to earlier requests
    // warning: this call may result in indirect push() recursion
    HandleResponses("before push");

    debugs(47, 7, HERE);
    Must(diskId >= 0);
    Must(pending);
    Must(pending->readRequest || pending->writeRequest);

    IpcIoMsg ipcIo;
    try {
        if (++lastRequestId == 0) // don't use zero value as requestId
            ++lastRequestId;
        ipcIo.requestId = lastRequestId;
        ipcIo.start = current_time;
        if (pending->readRequest) {
            ipcIo.command = IpcIo::cmdRead;
            ipcIo.offset = pending->readRequest->offset;
            ipcIo.len = pending->readRequest->len;
        } else { // pending->writeRequest
            Must(pending->writeRequest->len <= Ipc::Mem::PageSize());
            if (!Ipc::Mem::GetPage(Ipc::Mem::PageId::ioPage, ipcIo.page)) {
                ipcIo.len = 0;
                throw TexcHere("run out of shared memory pages for IPC I/O");
            }
            ipcIo.command = IpcIo::cmdWrite;
            ipcIo.offset = pending->writeRequest->offset;
            ipcIo.len = pending->writeRequest->len;
            char *const buf = Ipc::Mem::PagePointer(ipcIo.page);
            memcpy(buf, pending->writeRequest->buf, ipcIo.len); // optimize away
        }

        debugs(47, 7, HERE << "pushing " << SipcIo(KidIdentifier, ipcIo, diskId));

        if (queue->push(diskId, ipcIo))
            Notify(diskId); // must notify disker
        trackPendingRequest(ipcIo.requestId, pending);
    } catch (const Queue::Full &) {
        debugs(47, DBG_IMPORTANT, "ERROR: worker I/O push queue for " <<
               dbName << " overflow: " <<
               SipcIo(KidIdentifier, ipcIo, diskId)); // TODO: report queue len
        // TODO: grow queue size

        pending->completeIo(NULL);
        delete pending;
    } catch (const TextException &e) {
        debugs(47, DBG_IMPORTANT, "ERROR: " << dbName << " exception: " << e.what());
        pending->completeIo(NULL);
        delete pending;
    }
}