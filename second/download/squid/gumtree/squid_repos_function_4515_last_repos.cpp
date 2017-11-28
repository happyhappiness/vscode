static int64_t
objectSizeForDirSelection(const StoreEntry &entry)
{
    // entry.objectLen() is negative here when we are still STORE_PENDING
    int64_t minSize = entry.mem_obj->expectedReplySize();

    // If entry size is unknown, use already accumulated bytes as an estimate.
    // Controller::accumulateMore() guarantees that there are enough of them.
    if (minSize < 0)
        minSize = entry.mem_obj->endOffset();

    assert(minSize >= 0);
    minSize += entry.mem_obj->swap_hdr_sz;
    return minSize;
}