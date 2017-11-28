int64_t
MemObject::policyLowestOffsetToKeep(bool swap) const
{
    /*
     * Careful.  lowest_offset can be greater than endOffset(), such
     * as in the case of a range request.
     */
    int64_t lowest_offset = lowestMemReaderOffset();

    if (endOffset() < lowest_offset ||
            endOffset() - inmem_lo > (int64_t)Config.Store.maxInMemObjSize ||
            (swap && !Config.onoff.memory_cache_first))
        return lowest_offset;

    return inmem_lo;
}