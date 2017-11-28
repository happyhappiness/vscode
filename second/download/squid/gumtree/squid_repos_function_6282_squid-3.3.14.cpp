size_t
Ipc::OneToOneUniQueues::SharedMemorySize(const int capacity, const unsigned int maxItemSize, const int queueCapacity)
{
    const int queueSize =
        OneToOneUniQueue::Items2Bytes(maxItemSize, queueCapacity);
    return sizeof(OneToOneUniQueues) + queueSize * capacity;
}