DelayIdComposite::Pointer
VectorPool::id(CompositeSelectionDetails &details)
{
    if (rate()->restore_bps == -1)
        return new NullDelayId;

    /* non-IPv4 are not able to provide IPv4-bitmask for this pool type key. */
    if ( !details.src_addr.isIPv4() )
        return new NullDelayId;

    unsigned int key = makeKey(details.src_addr);

    if (keyAllocated(key))
        return new Id(this, buckets.findKeyIndex(key));

    unsigned char const resultIndex = buckets.insert(key);

    buckets.values[resultIndex].init(*rate());

    return new Id(this, resultIndex);
}