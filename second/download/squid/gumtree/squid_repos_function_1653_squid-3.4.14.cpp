void
GetServiceTimesStats(Mgr::ServiceTimesActionData& stats)
{
    for (int i = 0; i < Mgr::ServiceTimesActionData::seriesSize; ++i) {
        double p = (i + 1) * 5 / 100.0;
        stats.http_requests5[i] = statPctileSvc(p, 5, PCTILE_HTTP);
        stats.http_requests60[i] = statPctileSvc(p, 60, PCTILE_HTTP);

        stats.cache_misses5[i] = statPctileSvc(p, 5, PCTILE_MISS);
        stats.cache_misses60[i] = statPctileSvc(p, 60, PCTILE_MISS);

        stats.cache_hits5[i] = statPctileSvc(p, 5, PCTILE_HIT);
        stats.cache_hits60[i] = statPctileSvc(p, 60, PCTILE_HIT);

        stats.near_hits5[i] = statPctileSvc(p, 5, PCTILE_NH);
        stats.near_hits60[i] = statPctileSvc(p, 60, PCTILE_NH);

        stats.not_modified_replies5[i] = statPctileSvc(p, 5, PCTILE_NM);
        stats.not_modified_replies60[i] = statPctileSvc(p, 60, PCTILE_NM);

        stats.dns_lookups5[i] = statPctileSvc(p, 5, PCTILE_DNS);
        stats.dns_lookups60[i] = statPctileSvc(p, 60, PCTILE_DNS);

        stats.icp_queries5[i] = statPctileSvc(p, 5, PCTILE_ICP_QUERY);
        stats.icp_queries60[i] = statPctileSvc(p, 60, PCTILE_ICP_QUERY);
    }
}