void MemBuf::truncate(mb_size_t tailSize)
{
    const mb_size_t cSize = contentSize();
    assert(0 <= tailSize && tailSize <= cSize);
    assert(!stolen); /* not frozen */
    size -= tailSize;
}