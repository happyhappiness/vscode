const Ipc::OneToOneUniQueue &
Ipc::MultiQueue::oneToOneQueue(const int fromProcessId, const int toProcessId) const
{
    assert(validProcessId(fromProcessId));
    assert(validProcessId(toProcessId));
    const int fromIndex = fromProcessId - metadata->theProcessIdOffset;
    const int toIndex = toProcessId - metadata->theProcessIdOffset;
    const int index = fromIndex * metadata->theProcessCount + toIndex;
    return (*queues)[index];
}