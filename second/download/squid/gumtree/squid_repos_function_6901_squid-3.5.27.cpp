const Ipc::OneToOneUniQueue &
Ipc::FewToFewBiQueue::inQueue(const int remoteProcessId) const
{
    return oneToOneQueue(remoteGroup(), remoteProcessId,
                         theLocalGroup, theLocalProcessId);
}