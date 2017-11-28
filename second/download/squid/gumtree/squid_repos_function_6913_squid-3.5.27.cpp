const Ipc::OneToOneUniQueue &
Ipc::MultiQueue::outQueue(const int remoteProcessId) const
{
    return oneToOneQueue(theLocalProcessId, remoteProcessId);
}