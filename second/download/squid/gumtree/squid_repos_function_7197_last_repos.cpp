void
Ipc::MemMapSlot::set(const unsigned char *aKey, const void *block, size_t blockSize, time_t expireAt)
{
    memcpy(key, aKey, sizeof(key));
    if (block)
        memcpy(p, block, blockSize);
    pSize = blockSize;
    expire = expireAt;
}