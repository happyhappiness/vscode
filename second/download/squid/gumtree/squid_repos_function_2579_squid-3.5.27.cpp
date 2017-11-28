CacheDigest *
cacheDigestClone(const CacheDigest * cd)
{
    CacheDigest *clone;
    assert(cd);
    clone = cacheDigestCreate(cd->capacity, cd->bits_per_entry);
    clone->count = cd->count;
    clone->del_count = cd->del_count;
    assert(cd->mask_size == clone->mask_size);
    memcpy(clone->mask, cd->mask, cd->mask_size);
    return clone;
}