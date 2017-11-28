static void
statCountersCopy(StatCounters * dest, const StatCounters * orig)
{
    assert(dest && orig);
    /* this should take care of all the fields, but "special" ones */
    xmemcpy(dest, orig, sizeof(*dest));
    /* prepare space where to copy special entries */
    statCountersInitSpecial(dest);
    /* now handle special cases */
    /* note: we assert that histogram capacities do not change */
    statHistCopy(&dest->client_http.all_svc_time, &orig->client_http.all_svc_time);
    statHistCopy(&dest->client_http.miss_svc_time, &orig->client_http.miss_svc_time);
    statHistCopy(&dest->client_http.nm_svc_time, &orig->client_http.nm_svc_time);
    statHistCopy(&dest->client_http.nh_svc_time, &orig->client_http.nh_svc_time);
    statHistCopy(&dest->client_http.hit_svc_time, &orig->client_http.hit_svc_time);
    statHistCopy(&dest->icp.query_svc_time, &orig->icp.query_svc_time);
    statHistCopy(&dest->icp.reply_svc_time, &orig->icp.reply_svc_time);
    statHistCopy(&dest->dns.svc_time, &orig->dns.svc_time);
    statHistCopy(&dest->cd.on_xition_count, &orig->cd.on_xition_count);
    statHistCopy(&dest->comm_icp_incoming, &orig->comm_icp_incoming);
    statHistCopy(&dest->comm_http_incoming, &orig->comm_http_incoming);
    statHistCopy(&dest->select_fds_hist, &orig->select_fds_hist);
}