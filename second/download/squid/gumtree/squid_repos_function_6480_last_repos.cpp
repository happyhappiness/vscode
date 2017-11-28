void
IpcIoFile::DiskerHandleRequest(const int workerId, IpcIoMsg &ipcIo)
{
    if (ipcIo.command != IpcIo::cmdRead && ipcIo.command != IpcIo::cmdWrite) {
        debugs(0, DBG_CRITICAL, "ERROR: " << DbName <<
               " should not receive " << ipcIo.command <<
               " ipcIo" << workerId << '.' << ipcIo.requestId);
        return;
    }

    debugs(47,5, HERE << "disker" << KidIdentifier <<
           (ipcIo.command == IpcIo::cmdRead ? " reads " : " writes ") <<
           ipcIo.len << " at " << ipcIo.offset <<
           " ipcIo" << workerId << '.' << ipcIo.requestId);

    if (ipcIo.command == IpcIo::cmdRead)
        diskerRead(ipcIo);
    else // ipcIo.command == IpcIo::cmdWrite
        diskerWrite(ipcIo);

    debugs(47, 7, HERE << "pushing " << SipcIo(workerId, ipcIo, KidIdentifier));

    try {
        if (queue->push(workerId, ipcIo))
            Notify(workerId); // must notify worker
    } catch (const Queue::Full &) {
        // The worker queue should not overflow because the worker should pop()
        // before push()ing and because if disker pops N requests at a time,
        // we should make sure the worker pop() queue length is the worker
        // push queue length plus N+1. XXX: implement the N+1 difference.
        debugs(47, DBG_IMPORTANT, "BUG: Worker I/O pop queue for " <<
               DbName << " overflow: " <<
               SipcIo(workerId, ipcIo, KidIdentifier)); // TODO: report queue len

        // the I/O request we could not push will timeout
    }
}