int
Ipc::OneToOneUniQueue::Items2Bytes(const unsigned int maxItemSize, const int size)
{
    assert(size >= 0);
    return sizeof(OneToOneUniQueue) + maxItemSize * size;
}