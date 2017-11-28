mb_size_t MemBuf::potentialSpaceSize() const
{
    const mb_size_t terminatedSize = size + 1;
    return (terminatedSize < max_capacity) ? max_capacity - terminatedSize : 0;
}