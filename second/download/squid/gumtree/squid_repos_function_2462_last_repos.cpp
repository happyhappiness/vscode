size_t
StoreEntry::bytesWanted (Range<size_t> const aRange, bool ignoreDelayPools) const
{
    if (mem_obj == NULL)
        return aRange.end;

#if URL_CHECKSUM_DEBUG

    mem_obj->checkUrlChecksum();

#endif

    if (!mem_obj->readAheadPolicyCanRead())
        return 0;

    return mem_obj->mostBytesWanted(aRange.end, ignoreDelayPools);
}