mb_size_t MemBuf::spaceSize() const
{
    const mb_size_t terminatedSize = size + 1;
    return (terminatedSize < capacity) ? capacity - terminatedSize : 0;
}