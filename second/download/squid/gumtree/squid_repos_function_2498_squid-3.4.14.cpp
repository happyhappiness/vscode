int
cacheDigestBitUtil(const CacheDigest * cd)
{
    CacheDigestStats stats;
    assert(cd);
    cacheDigestStats(cd, &stats);
    return xpercentInt(stats.bit_on_count, stats.bit_count);
}