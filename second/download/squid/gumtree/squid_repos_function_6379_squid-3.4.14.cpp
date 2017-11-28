Ipc::QueueReader &
Ipc::FewToFewBiQueue::reader(const Group group, const int processId)
{
    return readers->theReaders[readerIndex(group, processId)];
}