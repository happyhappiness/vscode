void MemBuf::appended(mb_size_t sz)
{
    assert(size + sz <= capacity);
    size += sz;
    terminate();
}