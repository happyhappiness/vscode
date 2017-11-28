static void
statCountersCopy(StatCounters * dest, const StatCounters * orig)
{
    assert(dest && orig);
    /* this should take care of all the fields, but "special" ones */
    memcpy(dest, orig, sizeof(*dest));
    /* prepare space where to copy special entries */
    statCountersInitSpecial(dest);
    /* now handle special cases */
    /* note: we assert that histogram capacities do not change */
    dest->client_http.allSvcTime=orig->client_http.allSvcTime;
    dest->client_http.missSvcTime=orig->client_http.missSvcTime;
    dest->client_http.nearMissSvcTime=orig->client_http.nearMissSvcTime;
    dest->client_http.nearHitSvcTime=orig->client_http.nearHitSvcTime;

    dest->client_http.hitSvcTime=orig->client_http.hitSvcTime;
    dest->icp.querySvcTime=orig->icp.querySvcTime;
    dest->icp.replySvcTime=orig->icp.replySvcTime;
    dest->dns.svcTime=orig->dns.svcTime;
    dest->cd.on_xition_count=orig->cd.on_xition_count;
    dest->comm_udp_incoming=orig->comm_udp_incoming;
    dest->comm_dns_incoming=orig->comm_dns_incoming;
    dest->comm_tcp_incoming=orig->comm_tcp_incoming;
    dest->select_fds_hist=orig->select_fds_hist;
}