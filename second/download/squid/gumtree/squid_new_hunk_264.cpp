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

/* add special cases here as they arrive */
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

/* add special cases here as they arrive */
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

static void
statCountersHistograms(StoreEntry * sentry)
{
    storeAppendPrintf(sentry, "client_http.allSvcTime histogram:\n");
    statCounter.client_http.allSvcTime.dump(sentry, NULL);
    storeAppendPrintf(sentry, "client_http.missSvcTime histogram:\n");
    statCounter.client_http.missSvcTime.dump(sentry, NULL);
    storeAppendPrintf(sentry, "client_http.nearMissSvcTime histogram:\n");
    statCounter.client_http.nearMissSvcTime.dump(sentry, NULL);
    storeAppendPrintf(sentry, "client_http.nearHitSvcTime histogram:\n");
    statCounter.client_http.nearHitSvcTime.dump(sentry, NULL);
    storeAppendPrintf(sentry, "client_http.hitSvcTime histogram:\n");
    statCounter.client_http.hitSvcTime.dump(sentry, NULL);
    storeAppendPrintf(sentry, "icp.querySvcTime histogram:\n");
    statCounter.icp.querySvcTime.dump(sentry, NULL);
    storeAppendPrintf(sentry, "icp.replySvcTime histogram:\n");
    statCounter.icp.replySvcTime.dump(sentry, NULL);
    storeAppendPrintf(sentry, "dns.svc_time histogram:\n");
    statCounter.dns.svcTime.dump(sentry, NULL);
    storeAppendPrintf(sentry, "select_fds_hist histogram:\n");
    statCounter.select_fds_hist.dump(sentry, NULL);
}

static void
statCountersDump(StoreEntry * sentry)
{
    Mgr::CountersActionData stats;
    GetCountersStats(stats);
    DumpCountersStats(stats, sentry);
}

void
GetCountersStats(Mgr::CountersActionData& stats)
{
    StatCounters *f = &statCounter;

    struct rusage rusage;
    squid_getrusage(&rusage);
    f->page_faults = rusage_pagefaults(&rusage);
    f->cputime = rusage_cputime(&rusage);

    stats.sample_time = f->timestamp;
    stats.client_http_requests = f->client_http.requests;
    stats.client_http_hits = f->client_http.hits;
    stats.client_http_errors = f->client_http.errors;
    stats.client_http_kbytes_in = f->client_http.kbytes_in.kb;
    stats.client_http_kbytes_out = f->client_http.kbytes_out.kb;
    stats.client_http_hit_kbytes_out = f->client_http.hit_kbytes_out.kb;

    stats.server_all_requests = f->server.all.requests;
    stats.server_all_errors = f->server.all.errors;
    stats.server_all_kbytes_in = f->server.all.kbytes_in.kb;
    stats.server_all_kbytes_out = f->server.all.kbytes_out.kb;

    stats.server_http_requests = f->server.http.requests;
    stats.server_http_errors = f->server.http.errors;
    stats.server_http_kbytes_in = f->server.http.kbytes_in.kb;
    stats.server_http_kbytes_out = f->server.http.kbytes_out.kb;

    stats.server_ftp_requests = f->server.ftp.requests;
    stats.server_ftp_errors = f->server.ftp.errors;
    stats.server_ftp_kbytes_in = f->server.ftp.kbytes_in.kb;
    stats.server_ftp_kbytes_out = f->server.ftp.kbytes_out.kb;

    stats.server_other_requests = f->server.other.requests;
    stats.server_other_errors = f->server.other.errors;
    stats.server_other_kbytes_in = f->server.other.kbytes_in.kb;
    stats.server_other_kbytes_out = f->server.other.kbytes_out.kb;

    stats.icp_pkts_sent = f->icp.pkts_sent;
    stats.icp_pkts_recv = f->icp.pkts_recv;
    stats.icp_queries_sent = f->icp.queries_sent;
    stats.icp_replies_sent = f->icp.replies_sent;
    stats.icp_queries_recv = f->icp.queries_recv;
    stats.icp_replies_recv = f->icp.replies_recv;
    stats.icp_query_timeouts = f->icp.query_timeouts;
    stats.icp_replies_queued = f->icp.replies_queued;
    stats.icp_kbytes_sent = f->icp.kbytes_sent.kb;
    stats.icp_kbytes_recv = f->icp.kbytes_recv.kb;
    stats.icp_q_kbytes_sent = f->icp.q_kbytes_sent.kb;
    stats.icp_r_kbytes_sent = f->icp.r_kbytes_sent.kb;
    stats.icp_q_kbytes_recv = f->icp.q_kbytes_recv.kb;
    stats.icp_r_kbytes_recv = f->icp.r_kbytes_recv.kb;

#if USE_CACHE_DIGESTS

    stats.icp_times_used = f->icp.times_used;
    stats.cd_times_used = f->cd.times_used;
    stats.cd_msgs_sent = f->cd.msgs_sent;
    stats.cd_msgs_recv = f->cd.msgs_recv;
    stats.cd_memory = f->cd.memory.kb;
    stats.cd_local_memory = store_digest ? store_digest->mask_size / 1024 : 0;
    stats.cd_kbytes_sent = f->cd.kbytes_sent.kb;
    stats.cd_kbytes_recv = f->cd.kbytes_recv.kb;
#endif

    stats.unlink_requests = f->unlink.requests;
    stats.page_faults = f->page_faults;
    stats.select_loops = f->select_loops;
    stats.cpu_time = f->cputime;
    stats.wall_time = tvSubDsec(f->timestamp, current_time);
    stats.swap_outs = f->swap.outs;
    stats.swap_ins = f->swap.ins;
    stats.swap_files_cleaned = f->swap.files_cleaned;
    stats.aborted_requests = f->aborted_requests;
}

void
DumpCountersStats(Mgr::CountersActionData& stats, StoreEntry* sentry)
{
    storeAppendPrintf(sentry, "sample_time = %d.%d (%s)\n",
                      (int) stats.sample_time.tv_sec,
                      (int) stats.sample_time.tv_usec,
                      mkrfc1123(stats.sample_time.tv_sec));
    storeAppendPrintf(sentry, "client_http.requests = %.0f\n",
                      stats.client_http_requests);
    storeAppendPrintf(sentry, "client_http.hits = %.0f\n",
                      stats.client_http_hits);
    storeAppendPrintf(sentry, "client_http.errors = %.0f\n",
                      stats.client_http_errors);
    storeAppendPrintf(sentry, "client_http.kbytes_in = %.0f\n",
                      stats.client_http_kbytes_in);
    storeAppendPrintf(sentry, "client_http.kbytes_out = %.0f\n",
                      stats.client_http_kbytes_out);
    storeAppendPrintf(sentry, "client_http.hit_kbytes_out = %.0f\n",
                      stats.client_http_hit_kbytes_out);

    storeAppendPrintf(sentry, "server.all.requests = %.0f\n",
                      stats.server_all_requests);
    storeAppendPrintf(sentry, "server.all.errors = %.0f\n",
                      stats.server_all_errors);
    storeAppendPrintf(sentry, "server.all.kbytes_in = %.0f\n",
                      stats.server_all_kbytes_in);
    storeAppendPrintf(sentry, "server.all.kbytes_out = %.0f\n",
                      stats.server_all_kbytes_out);

    storeAppendPrintf(sentry, "server.http.requests = %.0f\n",
                      stats.server_http_requests);
    storeAppendPrintf(sentry, "server.http.errors = %.0f\n",
                      stats.server_http_errors);
    storeAppendPrintf(sentry, "server.http.kbytes_in = %.0f\n",
                      stats.server_http_kbytes_in);
    storeAppendPrintf(sentry, "server.http.kbytes_out = %.0f\n",
                      stats.server_http_kbytes_out);

    storeAppendPrintf(sentry, "server.ftp.requests = %.0f\n",
                      stats.server_ftp_requests);
    storeAppendPrintf(sentry, "server.ftp.errors = %.0f\n",
                      stats.server_ftp_errors);
    storeAppendPrintf(sentry, "server.ftp.kbytes_in = %.0f\n",
                      stats.server_ftp_kbytes_in);
    storeAppendPrintf(sentry, "server.ftp.kbytes_out = %.0f\n",
                      stats.server_ftp_kbytes_out);

    storeAppendPrintf(sentry, "server.other.requests = %.0f\n",
                      stats.server_other_requests);
    storeAppendPrintf(sentry, "server.other.errors = %.0f\n",
                      stats.server_other_errors);
    storeAppendPrintf(sentry, "server.other.kbytes_in = %.0f\n",
                      stats.server_other_kbytes_in);
    storeAppendPrintf(sentry, "server.other.kbytes_out = %.0f\n",
                      stats.server_other_kbytes_out);

    storeAppendPrintf(sentry, "icp.pkts_sent = %.0f\n",
                      stats.icp_pkts_sent);
    storeAppendPrintf(sentry, "icp.pkts_recv = %.0f\n",
                      stats.icp_pkts_recv);
    storeAppendPrintf(sentry, "icp.queries_sent = %.0f\n",
                      stats.icp_queries_sent);
    storeAppendPrintf(sentry, "icp.replies_sent = %.0f\n",
                      stats.icp_replies_sent);
    storeAppendPrintf(sentry, "icp.queries_recv = %.0f\n",
                      stats.icp_queries_recv);
    storeAppendPrintf(sentry, "icp.replies_recv = %.0f\n",
                      stats.icp_replies_recv);
    storeAppendPrintf(sentry, "icp.query_timeouts = %.0f\n",
                      stats.icp_query_timeouts);
    storeAppendPrintf(sentry, "icp.replies_queued = %.0f\n",
                      stats.icp_replies_queued);
    storeAppendPrintf(sentry, "icp.kbytes_sent = %.0f\n",
                      stats.icp_kbytes_sent);
    storeAppendPrintf(sentry, "icp.kbytes_recv = %.0f\n",
                      stats.icp_kbytes_recv);
    storeAppendPrintf(sentry, "icp.q_kbytes_sent = %.0f\n",
                      stats.icp_q_kbytes_sent);
    storeAppendPrintf(sentry, "icp.r_kbytes_sent = %.0f\n",
                      stats.icp_r_kbytes_sent);
    storeAppendPrintf(sentry, "icp.q_kbytes_recv = %.0f\n",
                      stats.icp_q_kbytes_recv);
    storeAppendPrintf(sentry, "icp.r_kbytes_recv = %.0f\n",
                      stats.icp_r_kbytes_recv);

#if USE_CACHE_DIGESTS

    storeAppendPrintf(sentry, "icp.times_used = %.0f\n",
                      stats.icp_times_used);
    storeAppendPrintf(sentry, "cd.times_used = %.0f\n",
                      stats.cd_times_used);
    storeAppendPrintf(sentry, "cd.msgs_sent = %.0f\n",
                      stats.cd_msgs_sent);
    storeAppendPrintf(sentry, "cd.msgs_recv = %.0f\n",
                      stats.cd_msgs_recv);
    storeAppendPrintf(sentry, "cd.memory = %.0f\n",
                      stats.cd_memory);
    storeAppendPrintf(sentry, "cd.local_memory = %.0f\n",
                      stats.cd_local_memory);
    storeAppendPrintf(sentry, "cd.kbytes_sent = %.0f\n",
                      stats.cd_kbytes_sent);
    storeAppendPrintf(sentry, "cd.kbytes_recv = %.0f\n",
                      stats.cd_kbytes_recv);
#endif

    storeAppendPrintf(sentry, "unlink.requests = %.0f\n",
                      stats.unlink_requests);
    storeAppendPrintf(sentry, "page_faults = %.0f\n",
                      stats.page_faults);
    storeAppendPrintf(sentry, "select_loops = %.0f\n",
                      stats.select_loops);
    storeAppendPrintf(sentry, "cpu_time = %f\n",
                      stats.cpu_time);
    storeAppendPrintf(sentry, "wall_time = %f\n",
                      stats.wall_time);
    storeAppendPrintf(sentry, "swap.outs = %.0f\n",
                      stats.swap_outs);
    storeAppendPrintf(sentry, "swap.ins = %.0f\n",
                      stats.swap_ins);
    storeAppendPrintf(sentry, "swap.files_cleaned = %.0f\n",
                      stats.swap_files_cleaned);
    storeAppendPrintf(sentry, "aborted_requests = %.0f\n",
                      stats.aborted_requests);
}

void
statFreeMemory(void)
{
    int i;

    for (i = 0; i < N_COUNT_HIST; ++i)
        statCountersClean(&CountHist[i]);

    for (i = 0; i < N_COUNT_HOUR_HIST; ++i)
        statCountersClean(&CountHourHist[i]);
}

static void
statPeerSelect(StoreEntry * sentry)
{
