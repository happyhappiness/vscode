const Ipc::OneToOneUniQueue &
Ipc::MultiQueue::inQueue(const int remoteProcessId) const
{
    return oneToOneQueue(remoteProcessId, theLocalProcessId);
}