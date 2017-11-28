                              entry->mem_obj ? entry->mem_obj->request : NULL,
                              delta);
    ++ refreshCounts[rcCDigest].total;
    ++ refreshCounts[rcCDigest].status[reason];
    return (reason < 200) ? 0 : 1;
}

#endif

time_t
getMaxAge(const char *url)
{
    const RefreshPattern *R;
    debugs(22, 3, "getMaxAge: '" << url << "'");

    if ((R = refreshLimits(url)))
        return R->max;
    else
        return REFRESH_DEFAULT_MAX;
}

static void

refreshCountsStats(StoreEntry * sentry, struct RefreshCounts *rc)
{
    int sum = 0;
    int tot = rc->total;

    storeAppendPrintf(sentry, "\n\n%s histogram:\n", rc->proto);
    storeAppendPrintf(sentry, "Count\t%%Total\tCategory\n");

#define refreshCountsStatsEntry(code,desc) { \
	storeAppendPrintf(sentry, "%6d\t%6.2f\t%s\n", \
	    rc->status[code], xpercent(rc->status[code], tot), desc); \
    sum += rc->status[code]; \
}

    refreshCountsStatsEntry(FRESH_REQUEST_MAX_STALE_ALL,
                            "Fresh: request max-stale wildcard");
    refreshCountsStatsEntry(FRESH_REQUEST_MAX_STALE_VALUE,
                            "Fresh: request max-stale value");
    refreshCountsStatsEntry(FRESH_EXPIRES,
                            "Fresh: expires time not reached");
    refreshCountsStatsEntry(FRESH_LMFACTOR_RULE,
                            "Fresh: refresh_pattern last-mod factor percentage");
    refreshCountsStatsEntry(FRESH_MIN_RULE,
                            "Fresh: refresh_pattern min value");
    refreshCountsStatsEntry(FRESH_OVERRIDE_EXPIRES,
                            "Fresh: refresh_pattern override expires");
    refreshCountsStatsEntry(FRESH_OVERRIDE_LASTMOD,
                            "Fresh: refresh_pattern override lastmod");
    refreshCountsStatsEntry(STALE_MUST_REVALIDATE,
                            "Stale: response has must-revalidate");
    refreshCountsStatsEntry(STALE_RELOAD_INTO_IMS,
                            "Stale: changed reload into IMS");
    refreshCountsStatsEntry(STALE_FORCED_RELOAD,
                            "Stale: request has no-cache directive");
    refreshCountsStatsEntry(STALE_EXCEEDS_REQUEST_MAX_AGE_VALUE,
                            "Stale: age exceeds request max-age value");
    refreshCountsStatsEntry(STALE_EXPIRES,
                            "Stale: expires time reached");
    refreshCountsStatsEntry(STALE_MAX_RULE,
                            "Stale: refresh_pattern max age rule");
    refreshCountsStatsEntry(STALE_LMFACTOR_RULE,
                            "Stale: refresh_pattern last-mod factor percentage");
    refreshCountsStatsEntry(STALE_DEFAULT,
                            "Stale: by default");

    tot = sum;			/* paranoid: "total" line shows 100% if we forgot nothing */
    storeAppendPrintf(sentry, "%6d\t%6.2f\tTOTAL\n",
                      rc->total, xpercent(rc->total, tot));
    \
    storeAppendPrintf(sentry, "\n");
}

static void
refreshStats(StoreEntry * sentry)
{
