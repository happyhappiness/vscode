int
Ipc::OneToOneUniQueue::Bytes2Items(const unsigned int maxItemSize, int size)
{
    assert(maxItemSize > 0);
    size -= sizeof(OneToOneUniQueue);
    return size >= 0 ? size / maxItemSize : 0;
}