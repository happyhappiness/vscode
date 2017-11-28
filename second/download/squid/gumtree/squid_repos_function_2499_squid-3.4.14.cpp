void
cacheDigestGuessStatsUpdate(CacheDigestGuessStats * stats, int real_hit, int guess_hit)
{
    assert(stats);

    if (real_hit) {
        if (guess_hit)
            ++stats->trueHits;
        else
            ++stats->falseMisses;
    } else {
        if (guess_hit)
            ++stats->falseHits;
        else
            ++stats->trueMisses;
    }
}