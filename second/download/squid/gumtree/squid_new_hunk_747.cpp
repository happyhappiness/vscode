    const int false_count = stats->falseHits + stats->falseMisses;
    const int hit_count = stats->trueHits + stats->falseHits;
    const int miss_count = stats->trueMisses + stats->falseMisses;
    const int tot_count = true_count + false_count;

    assert(label);
    assert(tot_count == hit_count + miss_count);    /* paranoid */

    if (!tot_count) {
        storeAppendPrintf(sentry, "no guess stats for %s available\n", label);
        return;
    }

