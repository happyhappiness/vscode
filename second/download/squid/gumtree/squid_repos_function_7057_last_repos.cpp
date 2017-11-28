Ipc::OneToOneUniQueue &
Ipc::BaseMultiQueue::inQueue(const int remoteProcessId)
{
    const OneToOneUniQueue &queue =
        const_cast<const BaseMultiQueue *>(this)->inQueue(remoteProcessId);
    return const_cast<OneToOneUniQueue &>(queue);
}