const Ipc::QueueReader &
Ipc::FewToFewBiQueue::reader(const Group group, const int processId) const
{
    return readers->theReaders[readerIndex(group, processId)];
}