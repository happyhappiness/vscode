const Ipc::QueueReader &
Ipc::FewToFewBiQueue::remoteReader(const int processId) const
{
    return readers->theReaders[readerIndex(remoteGroup(), processId)];
}