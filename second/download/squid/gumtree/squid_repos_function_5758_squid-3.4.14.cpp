void
IpcIoFile::openCompleted(const Ipc::StrandSearchResponse *const response)
{
    Must(diskId < 0); // we do not know our disker yet

    if (!response) {
        debugs(79, DBG_IMPORTANT, HERE << "error: timeout");
        error_ = true;
    } else {
        diskId = response->strand.kidId;
        if (diskId >= 0) {
            const bool inserted =
                IpcIoFiles.insert(std::make_pair(diskId, this)).second;
            Must(inserted);
        } else {
            error_ = true;
            debugs(79, DBG_IMPORTANT, HERE << "error: no disker claimed " << dbName);
        }
    }

    ioRequestor->ioCompletedNotification();
}