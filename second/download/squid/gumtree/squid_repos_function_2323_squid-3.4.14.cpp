void
MemObject::trimUnSwappable()
{
    int64_t new_mem_lo = policyLowestOffsetToKeep(0);
    assert (new_mem_lo > 0);

    data_hdr.freeDataUpto(new_mem_lo);
    inmem_lo = new_mem_lo;
}