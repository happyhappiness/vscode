const Ipc::QueueReader &
Ipc::MultiQueue::remoteReader(const int processId) const
{
    return reader(processId);
}