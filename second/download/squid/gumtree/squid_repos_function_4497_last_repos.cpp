bool
Store::Disk::canStore(const StoreEntry &e, int64_t diskSpaceNeeded, int &load) const
{
    debugs(47,8, HERE << "cache_dir[" << index << "]: needs " <<
           diskSpaceNeeded << " <? " << max_objsize);

    if (EBIT_TEST(e.flags, ENTRY_SPECIAL))
        return false; // we do not store Squid-generated entries

    if (!objectSizeIsAcceptable(diskSpaceNeeded))
        return false; // does not satisfy size limits

    if (flags.read_only)
        return false; // cannot write at all

    if (currentSize() > maxSize())
        return false; // already overflowing

    /* Return 999 (99.9%) constant load; TODO: add a named constant for this */
    load = 999;
    return true; // kids may provide more tests and should report true load
}