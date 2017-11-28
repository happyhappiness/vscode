void
cacheDigestClear(CacheDigest * cd)
{
    assert(cd);
    cd->count = cd->del_count = 0;
    memset(cd->mask, 0, cd->mask_size);
}