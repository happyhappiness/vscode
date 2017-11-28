void
IpcIoFile::open(int flags, mode_t mode, RefCount<IORequestor> callback)
{
    ioRequestor = callback;
    Must(diskId < 0); // we do not know our disker yet

    if (!queue.get())
        queue.reset(new Queue(ShmLabel, IamWorkerProcess() ? Queue::groupA : Queue::groupB, KidIdentifier));

    if (IamDiskProcess()) {
        error_ = !DiskerOpen(SBuf(dbName.termedBuf()), flags, mode);
        if (error_)
            return;

        diskId = KidIdentifier;
        const bool inserted =
            IpcIoFiles.insert(std::make_pair(diskId, this)).second;
        Must(inserted);

        queue->localRateLimit().store(config.ioRate);

        Ipc::HereIamMessage ann(Ipc::StrandCoord(KidIdentifier, getpid()));
        ann.strand.tag = dbName;
        Ipc::TypedMsgHdr message;
        ann.pack(message);
        SendMessage(Ipc::Port::CoordinatorAddr(), message);

        ioRequestor->ioCompletedNotification();
        return;
    }

    Ipc::StrandSearchRequest request;
    request.requestorId = KidIdentifier;
    request.tag = dbName;

    Ipc::TypedMsgHdr msg;
    request.pack(msg);
    Ipc::SendMessage(Ipc::Port::CoordinatorAddr(), msg);

    WaitingForOpen.push_back(this);

    eventAdd("IpcIoFile::OpenTimeout", &IpcIoFile::OpenTimeout,
             this, Timeout, 0, false); // "this" pointer is used as id
}