int64_t
MemObject::policyLowestOffsetToKeep() const
{
    /*
     * Careful.  lowest_offset can be greater than endOffset(), such
     * as in the case of a range request.
     */
    int64_t lowest_offset = lowestMemReaderOffset();

    if (endOffset() < lowest_offset ||
            endOffset() - inmem_lo > (int64_t)Config.Store.maxInMemObjSize)
        return lowest_offset;

    return inmem_lo;
}