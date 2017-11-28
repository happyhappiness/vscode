Ipc::QueueReader &
Ipc::BaseMultiQueue::remoteReader(const int remoteProcessId)
{
    const QueueReader &reader =
        const_cast<const BaseMultiQueue *>(this)->remoteReader(remoteProcessId);
    return const_cast<QueueReader &>(reader);
}