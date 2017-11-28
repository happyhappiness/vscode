static void
statCountersClean(StatCounters * C)
{
    assert(C);
    C->client_http.allSvcTime.clear();
    C->client_http.missSvcTime.clear();
    C->client_http.nearMissSvcTime.clear();
    C->client_http.nearHitSvcTime.clear();
    C->client_http.hitSvcTime.clear();
    C->icp.querySvcTime.clear();
    C->icp.replySvcTime.clear();
    C->dns.svcTime.clear();
    C->cd.on_xition_count.clear();
    C->comm_udp_incoming.clear();
    C->comm_dns_incoming.clear();
    C->comm_tcp_incoming.clear();
    C->select_fds_hist.clear();
}