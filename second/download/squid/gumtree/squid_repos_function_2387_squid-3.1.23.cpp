void
cacheDigestGuessStatsUpdate(cd_guess_stats * stats, int real_hit, int guess_hit)
{
    assert(stats);

    if (real_hit) {
        if (guess_hit)
            stats->true_hits++;
        else
            stats->false_misses++;
    } else {
        if (guess_hit)
            stats->false_hits++;
        else
            stats->true_misses++;
    }
}