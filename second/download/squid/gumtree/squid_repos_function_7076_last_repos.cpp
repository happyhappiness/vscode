const Ipc::QueueReader &
Ipc::MultiQueue::reader(const int processId) const
{
    assert(validProcessId(processId));
    const int index = processId - metadata->theProcessIdOffset;
    return readers->theReaders[index];
}