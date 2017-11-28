size_t
Ipc::OneToOneUniQueues::sharedMemorySize() const
{
    return sizeof(*this) + theCapacity * front().sharedMemorySize();
}