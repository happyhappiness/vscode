Ipc::MultiQueue::Owner *
Ipc::MultiQueue::Init(const String &id, const int processCount, const int processIdOffset, const unsigned int maxItemSize, const int capacity)
{
    return new Owner(id, processCount, processIdOffset, maxItemSize, capacity);
}