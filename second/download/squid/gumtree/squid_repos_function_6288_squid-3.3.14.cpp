Ipc::OneToOneUniQueue &
Ipc::FewToFewBiQueue::oneToOneQueue(const Group fromGroup, const int fromProcessId, const Group toGroup, const int toProcessId)
{
    return (*queues)[oneToOneQueueIndex(fromGroup, fromProcessId, toGroup, toProcessId)];
}