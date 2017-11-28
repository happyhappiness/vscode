void
cacheDigestGuessStatsReport(const CacheDigestGuessStats * stats, StoreEntry * sentry, const char *label)
{
    const int true_count = stats->trueHits + stats->trueMisses;
    const int false_count = stats->falseHits + stats->falseMisses;
    const int hit_count = stats->trueHits + stats->falseHits;
    const int miss_count = stats->trueMisses + stats->falseMisses;
    const int tot_count = true_count + false_count;

    assert(label);
    assert(tot_count == hit_count + miss_count);	/* paranoid */

    if (!tot_count) {
        storeAppendPrintf(sentry, "no guess stats for %s available\n", label);
        return;
    }

    storeAppendPrintf(sentry, "Digest guesses stats for %s:\n", label);
    storeAppendPrintf(sentry, "guess\t hit\t\t miss\t\t total\t\t\n");
    storeAppendPrintf(sentry, " \t #\t %%\t #\t %%\t #\t %%\t\n");
    storeAppendPrintf(sentry, "true\t %d\t %.2f\t %d\t %.2f\t %d\t %.2f\n",
                      stats->trueHits, xpercent(stats->trueHits, tot_count),
                      stats->trueMisses, xpercent(stats->trueMisses, tot_count),
                      true_count, xpercent(true_count, tot_count));
    storeAppendPrintf(sentry, "false\t %d\t %.2f\t %d\t %.2f\t %d\t %.2f\n",
                      stats->falseHits, xpercent(stats->falseHits, tot_count),
                      stats->falseMisses, xpercent(stats->falseMisses, tot_count),
                      false_count, xpercent(false_count, tot_count));
    storeAppendPrintf(sentry, "all\t %d\t %.2f\t %d\t %.2f\t %d\t %.2f\n",
                      hit_count, xpercent(hit_count, tot_count),
                      miss_count, xpercent(miss_count, tot_count),
                      tot_count, xpercent(tot_count, tot_count));
    storeAppendPrintf(sentry, "\tclose_hits: %d ( %d%%) /* cd said hit, doc was in the peer cache, but we got a miss */\n",
                      stats->closeHits, xpercentInt(stats->closeHits, stats->falseHits));
}