Mgr::ServiceTimesActionData&
Mgr::ServiceTimesActionData::operator += (const ServiceTimesActionData& stats)
{
    for (int i = 0; i < seriesSize; ++i) {
        http_requests5[i] += stats.http_requests5[i];
        http_requests60[i] += stats.http_requests60[i];

        cache_misses5[i] += stats.cache_misses5[i];
        cache_misses60[i] += stats.cache_misses60[i];

        cache_hits5[i] += stats.cache_hits5[i];
        cache_hits60[i] += stats.cache_hits60[i];

        near_hits5[i] += stats.near_hits5[i];
        near_hits60[i] += stats.near_hits60[i];

        not_modified_replies5[i] += stats.not_modified_replies5[i];
        not_modified_replies60[i] += stats.not_modified_replies60[i];

        dns_lookups5[i] += stats.dns_lookups5[i];
        dns_lookups60[i] += stats.dns_lookups60[i];

        icp_queries5[i] += stats.icp_queries5[i];
        icp_queries60[i] += stats.icp_queries60[i];
    }
    ++count;

    return *this;
}