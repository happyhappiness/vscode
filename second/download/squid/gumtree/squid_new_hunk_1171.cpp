    sum += refreshCountsStatsEntry(sentry, rc, STALE_FORCED_RELOAD, "Stale: request has no-cache directive");
    sum += refreshCountsStatsEntry(sentry, rc, STALE_EXCEEDS_REQUEST_MAX_AGE_VALUE, "Stale: age exceeds request max-age value");
    sum += refreshCountsStatsEntry(sentry, rc, STALE_EXPIRES, "Stale: expires time reached");
    sum += refreshCountsStatsEntry(sentry, rc, STALE_MAX_RULE, "Stale: refresh_pattern max age rule");
    sum += refreshCountsStatsEntry(sentry, rc, STALE_LMFACTOR_RULE, "Stale: refresh_pattern last-mod factor percentage");
    sum += refreshCountsStatsEntry(sentry, rc, STALE_DEFAULT, "Stale: by default");
    storeAppendPrintf(sentry, "\n");
}

static void
refreshStats(StoreEntry * sentry)
{
    // display per-rule counts of usage and tests
    storeAppendPrintf(sentry, "\nRefresh pattern usage:\n\n");
    storeAppendPrintf(sentry, "  Used      \tChecks    \t%% Matches\tPattern\n");
    for (const RefreshPattern *R = Config.Refresh; R; R = R->next) {
        storeAppendPrintf(sentry, "  %10" PRIu64 "\t%10" PRIu64 "\t%6.2f\t%s%s\n",
                          R->stats.matchCount,
                          R->stats.matchTests,
                          xpercent(R->stats.matchCount, R->stats.matchTests),
                          (R->pattern.flags&REG_ICASE ? "-i " : ""),
                          R->pattern.c_str());
    }

    int i;
    int total = 0;

    /* get total usage count */

    for (i = 0; i < rcCount; ++i)
