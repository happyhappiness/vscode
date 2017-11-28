size_t
Ipc::QueueReaders::SharedMemorySize(const int capacity)
{
    return sizeof(QueueReaders) + sizeof(QueueReader) * capacity;
}