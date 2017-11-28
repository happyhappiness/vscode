const Ipc::OneToOneUniQueue &
Ipc::FewToFewBiQueue::outQueue(const int remoteProcessId) const
{
    return oneToOneQueue(theLocalGroup, theLocalProcessId,
                         remoteGroup(), remoteProcessId);
}