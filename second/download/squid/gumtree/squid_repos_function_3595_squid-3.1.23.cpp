void MemBuf::append(const char *newContent, mb_size_t sz)
{
    assert(sz >= 0);
    assert(buf || (0==capacity && 0==size));
    assert(!stolen); /* not frozen */

    PROF_start(MemBuf_append);
    if (sz > 0) {
        if (size + sz + 1 > capacity)
            grow(size + sz + 1);

        assert(size + sz <= capacity); /* paranoid */

        xmemcpy(space(), newContent, sz);

        appended(sz);
    }
    PROF_stop(MemBuf_append);
}