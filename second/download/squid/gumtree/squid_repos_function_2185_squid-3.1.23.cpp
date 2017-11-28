void
MemObject::trimUnSwappable()
{
    int64_t new_mem_lo = policyLowestOffsetToKeep();
    assert (new_mem_lo > 0);

    data_hdr.freeDataUpto(new_mem_lo);
    inmem_lo = new_mem_lo;
}