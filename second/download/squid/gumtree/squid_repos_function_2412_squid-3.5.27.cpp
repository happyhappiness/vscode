void
MemObject::trimUnSwappable()
{
    if (const int64_t new_mem_lo = policyLowestOffsetToKeep(false)) {
        assert (new_mem_lo > 0);
        data_hdr.freeDataUpto(new_mem_lo);
        inmem_lo = new_mem_lo;
    } // else we should not trim anything at this time
}