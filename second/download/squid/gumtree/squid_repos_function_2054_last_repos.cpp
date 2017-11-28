void
CacheDigest::updateCapacity(uint64_t newCapacity)
{
    safe_free(mask);
    init(newCapacity); // will re-init mask and mask_size
}