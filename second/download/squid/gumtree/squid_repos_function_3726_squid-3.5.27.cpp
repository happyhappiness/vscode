static void
refreshCountsStats(StoreEntry * sentry, struct RefreshCounts &rc)
{
    if (!rc.total)
        return;

    storeAppendPrintf(sentry, "\n\n%s histogram:\n", rc.proto);
    storeAppendPrintf(sentry, "Count\t%%Total\tCategory\n");

    int sum = 0;
    sum += refreshCountsStatsEntry(sentry, rc, FRESH_REQUEST_MAX_STALE_ALL, "Fresh: request max-stale wildcard");
    sum += refreshCountsStatsEntry(sentry, rc, FRESH_REQUEST_MAX_STALE_VALUE, "Fresh: request max-stale value");
    sum += refreshCountsStatsEntry(sentry, rc, FRESH_EXPIRES, "Fresh: expires time not reached");
    sum += refreshCountsStatsEntry(sentry, rc, FRESH_LMFACTOR_RULE, "Fresh: refresh_pattern last-mod factor percentage");
    sum += refreshCountsStatsEntry(sentry, rc, FRESH_MIN_RULE, "Fresh: refresh_pattern min value");
    sum += refreshCountsStatsEntry(sentry, rc, FRESH_OVERRIDE_EXPIRES, "Fresh: refresh_pattern override-expires");
    sum += refreshCountsStatsEntry(sentry, rc, FRESH_OVERRIDE_LASTMOD, "Fresh: refresh_pattern override-lastmod");
    sum += refreshCountsStatsEntry(sentry, rc, STALE_MUST_REVALIDATE, "Stale: response has must-revalidate");
    sum += refreshCountsStatsEntry(sentry, rc, STALE_RELOAD_INTO_IMS, "Stale: changed reload into IMS");
    sum += refreshCountsStatsEntry(sentry, rc, STALE_FORCED_RELOAD, "Stale: request has no-cache directive");
    sum += refreshCountsStatsEntry(sentry, rc, STALE_EXCEEDS_REQUEST_MAX_AGE_VALUE, "Stale: age exceeds request max-age value");
    sum += refreshCountsStatsEntry(sentry, rc, STALE_EXPIRES, "Stale: expires time reached");
    sum += refreshCountsStatsEntry(sentry, rc, STALE_MAX_RULE, "Stale: refresh_pattern max age rule");
    sum += refreshCountsStatsEntry(sentry, rc, STALE_LMFACTOR_RULE, "Stale: refresh_pattern last-mod factor percentage");
    sum += refreshCountsStatsEntry(sentry, rc, STALE_DEFAULT, "Stale: by default");

    storeAppendPrintf(sentry, "%6d\t%6.2f\tTOTAL\n", rc.total, xpercent(rc.total, sum));
    storeAppendPrintf(sentry, "\n");
}