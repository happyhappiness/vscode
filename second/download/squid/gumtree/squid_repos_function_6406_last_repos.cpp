void
SharedMemory::put(ssize_t offset)
{
    int i;
    assert(offset >= 0);
    assert(offset < nbufs * SHMBUF_BLKSZ);
    i = offset / SHMBUF_BLKSZ;
    assert(i < nbufs);
    assert(CBIT_TEST(inuse_map, i));
    CBIT_CLR(inuse_map, i);
    --diskd_stats.shmbuf_count;
}