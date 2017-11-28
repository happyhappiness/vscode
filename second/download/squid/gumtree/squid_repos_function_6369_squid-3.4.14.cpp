const Ipc::OneToOneUniQueue &
Ipc::OneToOneUniQueues::operator [](const int index) const
{
    Must(0 <= index && index < theCapacity);
    const size_t queueSize = index ? front().sharedMemorySize() : 0;
    const char *const queue =
        reinterpret_cast<const char *>(this) + sizeof(*this) + index * queueSize;
    return *reinterpret_cast<const OneToOneUniQueue *>(queue);
}