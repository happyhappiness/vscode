static void
service_times(StoreEntry * sentry)
{
    int p;
    storeAppendPrintf(sentry, "Service Time Percentiles            5 min    60 min:\n");
    for (p = 5; p < 100; p += 5) {
        storeAppendPrintf(sentry, "\tHTTP Requests (All):  %2d%%  %8.5f %8.5f\n",
                          p,
                          statPctileSvc((double) p / 100.0, 5, PCTILE_HTTP) / 1000.0,
                          statPctileSvc((double) p / 100.0, 60, PCTILE_HTTP) / 1000.0);
    }
    for (p = 5; p < 100; p += 5) {
        storeAppendPrintf(sentry, "\tCache Misses:         %2d%%  %8.5f %8.5f\n",
                          p,
                          statPctileSvc((double) p / 100.0, 5, PCTILE_MISS) / 1000.0,
                          statPctileSvc((double) p / 100.0, 60, PCTILE_MISS) / 1000.0);
    }
    for (p = 5; p < 100; p += 5) {
        storeAppendPrintf(sentry, "\tCache Hits:           %2d%%  %8.5f %8.5f\n",
                          p,
                          statPctileSvc((double) p / 100.0, 5, PCTILE_HIT) / 1000.0,
                          statPctileSvc((double) p / 100.0, 60, PCTILE_HIT) / 1000.0);
    }
    for (p = 5; p < 100; p += 5) {
        storeAppendPrintf(sentry, "\tNear Hits:            %2d%%  %8.5f %8.5f\n",
                          p,
                          statPctileSvc((double) p / 100.0, 5, PCTILE_NH) / 1000.0,
                          statPctileSvc((double) p / 100.0, 60, PCTILE_NH) / 1000.0);
    }
    for (p = 5; p < 100; p += 5) {
        storeAppendPrintf(sentry, "\tNot-Modified Replies: %2d%%  %8.5f %8.5f\n",
                          p,
                          statPctileSvc((double) p / 100.0, 5, PCTILE_NM) / 1000.0,
                          statPctileSvc((double) p / 100.0, 60, PCTILE_NM) / 1000.0);
    }
    for (p = 5; p < 100; p += 5) {
        storeAppendPrintf(sentry, "\tDNS Lookups:          %2d%%  %8.5f %8.5f\n",
                          p,
                          statPctileSvc((double) p / 100.0, 5, PCTILE_DNS) / 1000.0,
                          statPctileSvc((double) p / 100.0, 60, PCTILE_DNS) / 1000.0);
    }
    for (p = 5; p < 100; p += 5) {
        storeAppendPrintf(sentry, "\tICP Queries:          %2d%%  %8.5f %8.5f\n",
                          p,
                          statPctileSvc((double) p / 100.0, 5, PCTILE_ICP_QUERY) / 1000000.0,
                          statPctileSvc((double) p / 100.0, 60, PCTILE_ICP_QUERY) / 1000000.0);
    }
}