DelayIdComposite::Pointer
ClassCHostPool::id(CompositeSelectionDetails &details)
{
    if (rate()->restore_bps == -1)
        return new NullDelayId;

    /* non-IPv4 are not able to provide IPv4-bitmask for this pool type key. */
    if ( !details.src_addr.IsIPv4() )
        return new NullDelayId;

    unsigned int key = makeKey (details.src_addr);

    unsigned char host = makeHostKey (details.src_addr);

    unsigned char hostIndex;

    unsigned char netIndex;

    if (keyAllocated (key))
        netIndex = buckets.findKeyIndex(key);
    else
        netIndex = buckets.insert (key);

    hostIndex = buckets.values[netIndex].hostPosition (*rate(), host);

    return new Id (this, netIndex, hostIndex);
}