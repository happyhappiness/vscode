void MemBuf::terminate()
{
    assert(size < capacity);
    *space() = '\0';
}