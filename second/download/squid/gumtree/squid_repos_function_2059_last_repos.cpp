double
CacheDigest::usedMaskPercent() const
{
    CacheDigestStats stats;
    cacheDigestStats(this, &stats);
    return xpercent(stats.bit_on_count, stats.bit_count);
}