void
DumpServiceTimesStats(Mgr::ServiceTimesActionData& stats, StoreEntry* sentry)
{
    storeAppendPrintf(sentry, "Service Time Percentiles            5 min    60 min:\n");
    double fct = stats.count > 1 ? stats.count * 1000.0 : 1000.0;
    for (int i = 0; i < Mgr::ServiceTimesActionData::seriesSize; ++i) {
        storeAppendPrintf(sentry, "\tHTTP Requests (All):  %2d%%  %8.5f %8.5f\n",
                          (i + 1) * 5,
                          stats.http_requests5[i] / fct,
                          stats.http_requests60[i] / fct);
    }
    for (int i = 0; i < Mgr::ServiceTimesActionData::seriesSize; ++i) {
        storeAppendPrintf(sentry, "\tCache Misses:         %2d%%  %8.5f %8.5f\n",
                          (i + 1) * 5,
                          stats.cache_misses5[i] / fct,
                          stats.cache_misses60[i] / fct);
    }
    for (int i = 0; i < Mgr::ServiceTimesActionData::seriesSize; ++i) {
        storeAppendPrintf(sentry, "\tCache Hits:           %2d%%  %8.5f %8.5f\n",
                          (i + 1) * 5,
                          stats.cache_hits5[i] / fct,
                          stats.cache_hits60[i] / fct);
    }
    for (int i = 0; i < Mgr::ServiceTimesActionData::seriesSize; ++i) {
        storeAppendPrintf(sentry, "\tNear Hits:            %2d%%  %8.5f %8.5f\n",
                          (i + 1) * 5,
                          stats.near_hits5[i] / fct,
                          stats.near_hits60[i] / fct);
    }
    for (int i = 0; i < Mgr::ServiceTimesActionData::seriesSize; ++i) {
        storeAppendPrintf(sentry, "\tNot-Modified Replies: %2d%%  %8.5f %8.5f\n",
                          (i + 1) * 5,
                          stats.not_modified_replies5[i] / fct,
                          stats.not_modified_replies60[i] / fct);
    }
    for (int i = 0; i < Mgr::ServiceTimesActionData::seriesSize; ++i) {
        storeAppendPrintf(sentry, "\tDNS Lookups:          %2d%%  %8.5f %8.5f\n",
                          (i + 1) * 5,
                          stats.dns_lookups5[i] / fct,
                          stats.dns_lookups60[i] / fct);
    }
    fct = stats.count > 1 ? stats.count * 1000000.0 : 1000000.0;
    for (int i = 0; i < Mgr::ServiceTimesActionData::seriesSize; ++i) {
        storeAppendPrintf(sentry, "\tICP Queries:          %2d%%  %8.5f %8.5f\n",
                          (i + 1) * 5,
                          stats.icp_queries5[i] / fct,
                          stats.icp_queries60[i] / fct);
    }
}