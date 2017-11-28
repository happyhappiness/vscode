static void
statCountersInitSpecial(StatCounters * C)
{
    /*
     * HTTP svc_time hist is kept in milli-seconds; max of 3 hours.
     */
    C->client_http.allSvcTime.logInit(300, 0.0, 3600000.0 * 3.0);
    C->client_http.missSvcTime.logInit(300, 0.0, 3600000.0 * 3.0);
    C->client_http.nearMissSvcTime.logInit(300, 0.0, 3600000.0 * 3.0);
    C->client_http.nearHitSvcTime.logInit(300, 0.0, 3600000.0 * 3.0);
    C->client_http.hitSvcTime.logInit(300, 0.0, 3600000.0 * 3.0);
    /*
     * ICP svc_time hist is kept in micro-seconds; max of 1 minute.
     */
    C->icp.querySvcTime.logInit(300, 0.0, 1000000.0 * 60.0);
    C->icp.replySvcTime.logInit(300, 0.0, 1000000.0 * 60.0);
    /*
     * DNS svc_time hist is kept in milli-seconds; max of 10 minutes.
     */
    C->dns.svcTime.logInit(300, 0.0, 60000.0 * 10.0);
    /*
     * Cache Digest Stuff
     */
    C->cd.on_xition_count.enumInit(CacheDigestHashFuncCount);
    C->comm_udp_incoming.enumInit(INCOMING_UDP_MAX);
    C->comm_dns_incoming.enumInit(INCOMING_DNS_MAX);
    C->comm_tcp_incoming.enumInit(INCOMING_TCP_MAX);
    C->select_fds_hist.enumInit(256);	/* was SQUID_MAXFD, but it is way too much. It is OK to crop this statistics */
}