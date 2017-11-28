size_t
Ipc::QueueReaders::sharedMemorySize() const
{
    return SharedMemorySize(theCapacity);
}