void
cacheDigestChangeCap(CacheDigest * cd, uint64_t new_cap)
{
    assert(cd);
    cacheDigestClean(cd);
    cacheDigestInit(cd, new_cap, cd->bits_per_entry);
}