int64_t
SwapDir::maxObjectSize() const
{
    // per-store max-size=N value is authoritative
    if (max_objsize > -1)
        return max_objsize;

    // store with no individual max limit is limited by configured maximum_object_size
    // or the total store size, whichever is smaller
    return min(static_cast<int64_t>(maxSize()), Config.Store.maxObjectSize);
}