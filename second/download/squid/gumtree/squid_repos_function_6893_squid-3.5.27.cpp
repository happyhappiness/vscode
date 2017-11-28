Ipc::OneToOneUniQueue &
Ipc::BaseMultiQueue::outQueue(const int remoteProcessId)
{
    const OneToOneUniQueue &queue =
        const_cast<const BaseMultiQueue *>(this)->outQueue(remoteProcessId);
    return const_cast<OneToOneUniQueue &>(queue);
}