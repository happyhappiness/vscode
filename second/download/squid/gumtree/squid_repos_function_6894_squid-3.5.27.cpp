Ipc::QueueReader &
Ipc::BaseMultiQueue::localReader()
{
    const QueueReader &reader =
        const_cast<const BaseMultiQueue *>(this)->localReader();
    return const_cast<QueueReader &>(reader);
}