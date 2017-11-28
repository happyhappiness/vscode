        return;
    }

    dt = tvSubDsec(l->timestamp, f->timestamp);
    ct = f->cputime - l->cputime;

    stats.sample_start_time = l->timestamp;
    stats.sample_end_time = f->timestamp;

    stats.client_http_requests = XAVG(client_http.requests);
    stats.client_http_hits = XAVG(client_http.hits);
    stats.client_http_errors = XAVG(client_http.errors);
    stats.client_http_kbytes_in = XAVG(client_http.kbytes_in.kb);
    stats.client_http_kbytes_out = XAVG(client_http.kbytes_out.kb);

    stats.client_http_all_median_svc_time = statHistDeltaMedian(l->client_http.allSvcTime,
                                            f->client_http.allSvcTime) / 1000.0;
    stats.client_http_miss_median_svc_time = statHistDeltaMedian(l->client_http.missSvcTime,
            f->client_http.missSvcTime) / 1000.0;
    stats.client_http_nm_median_svc_time = statHistDeltaMedian(l->client_http.nearMissSvcTime,
                                           f->client_http.nearMissSvcTime) / 1000.0;
    stats.client_http_nh_median_svc_time = statHistDeltaMedian(l->client_http.nearHitSvcTime,
                                           f->client_http.nearHitSvcTime) / 1000.0;
    stats.client_http_hit_median_svc_time = statHistDeltaMedian(l->client_http.hitSvcTime,
                                            f->client_http.hitSvcTime) / 1000.0;

    stats.server_all_requests = XAVG(server.all.requests);
    stats.server_all_errors = XAVG(server.all.errors);
    stats.server_all_kbytes_in = XAVG(server.all.kbytes_in.kb);
    stats.server_all_kbytes_out = XAVG(server.all.kbytes_out.kb);

    stats.server_http_requests = XAVG(server.http.requests);
    stats.server_http_errors = XAVG(server.http.errors);
    stats.server_http_kbytes_in = XAVG(server.http.kbytes_in.kb);
    stats.server_http_kbytes_out = XAVG(server.http.kbytes_out.kb);

    stats.server_ftp_requests = XAVG(server.ftp.requests);
    stats.server_ftp_errors = XAVG(server.ftp.errors);
    stats.server_ftp_kbytes_in = XAVG(server.ftp.kbytes_in.kb);
    stats.server_ftp_kbytes_out = XAVG(server.ftp.kbytes_out.kb);

    stats.server_other_requests = XAVG(server.other.requests);
    stats.server_other_errors = XAVG(server.other.errors);
    stats.server_other_kbytes_in = XAVG(server.other.kbytes_in.kb);
    stats.server_other_kbytes_out = XAVG(server.other.kbytes_out.kb);

    stats.icp_pkts_sent = XAVG(icp.pkts_sent);
    stats.icp_pkts_recv = XAVG(icp.pkts_recv);
    stats.icp_queries_sent = XAVG(icp.queries_sent);
    stats.icp_replies_sent = XAVG(icp.replies_sent);
    stats.icp_queries_recv = XAVG(icp.queries_recv);
    stats.icp_replies_recv = XAVG(icp.replies_recv);
    stats.icp_replies_queued = XAVG(icp.replies_queued);
    stats.icp_query_timeouts = XAVG(icp.query_timeouts);
    stats.icp_kbytes_sent = XAVG(icp.kbytes_sent.kb);
    stats.icp_kbytes_recv = XAVG(icp.kbytes_recv.kb);
    stats.icp_q_kbytes_sent = XAVG(icp.q_kbytes_sent.kb);
    stats.icp_r_kbytes_sent = XAVG(icp.r_kbytes_sent.kb);
    stats.icp_q_kbytes_recv = XAVG(icp.q_kbytes_recv.kb);
    stats.icp_r_kbytes_recv = XAVG(icp.r_kbytes_recv.kb);

    stats.icp_query_median_svc_time = statHistDeltaMedian(l->icp.querySvcTime,
                                      f->icp.querySvcTime) / 1000000.0;
    stats.icp_reply_median_svc_time = statHistDeltaMedian(l->icp.replySvcTime,
                                      f->icp.replySvcTime) / 1000000.0;
    stats.dns_median_svc_time = statHistDeltaMedian(l->dns.svcTime,
                                f->dns.svcTime) / 1000.0;

    stats.unlink_requests = XAVG(unlink.requests);
    stats.page_faults = XAVG(page_faults);
    stats.select_loops = XAVG(select_loops);
    stats.select_fds = XAVG(select_fds);
    stats.average_select_fd_period = f->select_fds > l->select_fds ?
                                     (f->select_time - l->select_time) / (f->select_fds - l->select_fds) : 0.0;

    stats.median_select_fds = statHistDeltaMedian(l->select_fds_hist, f->select_fds_hist);
    stats.swap_outs = XAVG(swap.outs);
    stats.swap_ins = XAVG(swap.ins);
    stats.swap_files_cleaned = XAVG(swap.files_cleaned);
    stats.aborted_requests = XAVG(aborted_requests);

    stats.syscalls_disk_opens = XAVG(syscalls.disk.opens);
    stats.syscalls_disk_closes = XAVG(syscalls.disk.closes);
    stats.syscalls_disk_reads = XAVG(syscalls.disk.reads);
    stats.syscalls_disk_writes = XAVG(syscalls.disk.writes);
    stats.syscalls_disk_seeks = XAVG(syscalls.disk.seeks);
    stats.syscalls_disk_unlinks = XAVG(syscalls.disk.unlinks);
    stats.syscalls_sock_accepts = XAVG(syscalls.sock.accepts);
    stats.syscalls_sock_sockets = XAVG(syscalls.sock.sockets);
    stats.syscalls_sock_connects = XAVG(syscalls.sock.connects);
    stats.syscalls_sock_binds = XAVG(syscalls.sock.binds);
    stats.syscalls_sock_closes = XAVG(syscalls.sock.closes);
    stats.syscalls_sock_reads = XAVG(syscalls.sock.reads);
    stats.syscalls_sock_writes = XAVG(syscalls.sock.writes);
    stats.syscalls_sock_recvfroms = XAVG(syscalls.sock.recvfroms);
    stats.syscalls_sock_sendtos = XAVG(syscalls.sock.sendtos);
    stats.syscalls_selects = XAVG(syscalls.selects);

    stats.cpu_time = ct;
    stats.wall_time = dt;
}

void
DumpAvgStat(Mgr::IntervalActionData& stats, StoreEntry* sentry)
{
    storeAppendPrintf(sentry, "sample_start_time = %d.%d (%s)\n",
                      (int)stats.sample_start_time.tv_sec,
                      (int)stats.sample_start_time.tv_usec,
                      mkrfc1123(stats.sample_start_time.tv_sec));
    storeAppendPrintf(sentry, "sample_end_time = %d.%d (%s)\n",
                      (int)stats.sample_end_time.tv_sec,
                      (int)stats.sample_end_time.tv_usec,
                      mkrfc1123(stats.sample_end_time.tv_sec));

    storeAppendPrintf(sentry, "client_http.requests = %f/sec\n",
                      stats.client_http_requests);
    storeAppendPrintf(sentry, "client_http.hits = %f/sec\n",
                      stats.client_http_hits);
    storeAppendPrintf(sentry, "client_http.errors = %f/sec\n",
                      stats.client_http_errors);
    storeAppendPrintf(sentry, "client_http.kbytes_in = %f/sec\n",
                      stats.client_http_kbytes_in);
    storeAppendPrintf(sentry, "client_http.kbytes_out = %f/sec\n",
                      stats.client_http_kbytes_out);

    double fct = stats.count > 1 ? stats.count : 1.0;
    storeAppendPrintf(sentry, "client_http.all_median_svc_time = %f seconds\n",
                      stats.client_http_all_median_svc_time / fct);
    storeAppendPrintf(sentry, "client_http.miss_median_svc_time = %f seconds\n",
                      stats.client_http_miss_median_svc_time / fct);
    storeAppendPrintf(sentry, "client_http.nm_median_svc_time = %f seconds\n",
                      stats.client_http_nm_median_svc_time / fct);
    storeAppendPrintf(sentry, "client_http.nh_median_svc_time = %f seconds\n",
                      stats.client_http_nh_median_svc_time / fct);
    storeAppendPrintf(sentry, "client_http.hit_median_svc_time = %f seconds\n",
                      stats.client_http_hit_median_svc_time / fct);

    storeAppendPrintf(sentry, "server.all.requests = %f/sec\n",
                      stats.server_all_requests);
    storeAppendPrintf(sentry, "server.all.errors = %f/sec\n",
                      stats.server_all_errors);
    storeAppendPrintf(sentry, "server.all.kbytes_in = %f/sec\n",
                      stats.server_all_kbytes_in);
    storeAppendPrintf(sentry, "server.all.kbytes_out = %f/sec\n",
                      stats.server_all_kbytes_out);

    storeAppendPrintf(sentry, "server.http.requests = %f/sec\n",
                      stats.server_http_requests);
    storeAppendPrintf(sentry, "server.http.errors = %f/sec\n",
                      stats.server_http_errors);
    storeAppendPrintf(sentry, "server.http.kbytes_in = %f/sec\n",
                      stats.server_http_kbytes_in);
    storeAppendPrintf(sentry, "server.http.kbytes_out = %f/sec\n",
                      stats.server_http_kbytes_out);

    storeAppendPrintf(sentry, "server.ftp.requests = %f/sec\n",
                      stats.server_ftp_requests);
    storeAppendPrintf(sentry, "server.ftp.errors = %f/sec\n",
                      stats.server_ftp_errors);
    storeAppendPrintf(sentry, "server.ftp.kbytes_in = %f/sec\n",
                      stats.server_ftp_kbytes_in);
    storeAppendPrintf(sentry, "server.ftp.kbytes_out = %f/sec\n",
                      stats.server_ftp_kbytes_out);

    storeAppendPrintf(sentry, "server.other.requests = %f/sec\n",
                      stats.server_other_requests);
    storeAppendPrintf(sentry, "server.other.errors = %f/sec\n",
                      stats.server_other_errors);
    storeAppendPrintf(sentry, "server.other.kbytes_in = %f/sec\n",
                      stats.server_other_kbytes_in);
    storeAppendPrintf(sentry, "server.other.kbytes_out = %f/sec\n",
                      stats.server_other_kbytes_out);

    storeAppendPrintf(sentry, "icp.pkts_sent = %f/sec\n",
                      stats.icp_pkts_sent);
    storeAppendPrintf(sentry, "icp.pkts_recv = %f/sec\n",
                      stats.icp_pkts_recv);
    storeAppendPrintf(sentry, "icp.queries_sent = %f/sec\n",
                      stats.icp_queries_sent);
    storeAppendPrintf(sentry, "icp.replies_sent = %f/sec\n",
                      stats.icp_replies_sent);
    storeAppendPrintf(sentry, "icp.queries_recv = %f/sec\n",
                      stats.icp_queries_recv);
    storeAppendPrintf(sentry, "icp.replies_recv = %f/sec\n",
                      stats.icp_replies_recv);
    storeAppendPrintf(sentry, "icp.replies_queued = %f/sec\n",
                      stats.icp_replies_queued);
    storeAppendPrintf(sentry, "icp.query_timeouts = %f/sec\n",
                      stats.icp_query_timeouts);
    storeAppendPrintf(sentry, "icp.kbytes_sent = %f/sec\n",
                      stats.icp_kbytes_sent);
    storeAppendPrintf(sentry, "icp.kbytes_recv = %f/sec\n",
                      stats.icp_kbytes_recv);
    storeAppendPrintf(sentry, "icp.q_kbytes_sent = %f/sec\n",
                      stats.icp_q_kbytes_sent);
    storeAppendPrintf(sentry, "icp.r_kbytes_sent = %f/sec\n",
                      stats.icp_r_kbytes_sent);
    storeAppendPrintf(sentry, "icp.q_kbytes_recv = %f/sec\n",
                      stats.icp_q_kbytes_recv);
    storeAppendPrintf(sentry, "icp.r_kbytes_recv = %f/sec\n",
                      stats.icp_r_kbytes_recv);
    storeAppendPrintf(sentry, "icp.query_median_svc_time = %f seconds\n",
                      stats.icp_query_median_svc_time / fct);
    storeAppendPrintf(sentry, "icp.reply_median_svc_time = %f seconds\n",
                      stats.icp_reply_median_svc_time / fct);
    storeAppendPrintf(sentry, "dns.median_svc_time = %f seconds\n",
                      stats.dns_median_svc_time / fct);
    storeAppendPrintf(sentry, "unlink.requests = %f/sec\n",
                      stats.unlink_requests);
    storeAppendPrintf(sentry, "page_faults = %f/sec\n",
                      stats.page_faults);
    storeAppendPrintf(sentry, "select_loops = %f/sec\n",
                      stats.select_loops);
    storeAppendPrintf(sentry, "select_fds = %f/sec\n",
                      stats.select_fds);
    storeAppendPrintf(sentry, "average_select_fd_period = %f/fd\n",
                      stats.average_select_fd_period / fct);
    storeAppendPrintf(sentry, "median_select_fds = %f\n",
                      stats.median_select_fds / fct);
    storeAppendPrintf(sentry, "swap.outs = %f/sec\n",
                      stats.swap_outs);
    storeAppendPrintf(sentry, "swap.ins = %f/sec\n",
                      stats.swap_ins);
    storeAppendPrintf(sentry, "swap.files_cleaned = %f/sec\n",
                      stats.swap_files_cleaned);
    storeAppendPrintf(sentry, "aborted_requests = %f/sec\n",
                      stats.aborted_requests);

#if USE_POLL
    storeAppendPrintf(sentry, "syscalls.polls = %f/sec\n", stats.syscalls_selects);
#elif defined(USE_SELECT) || defined(USE_SELECT_WIN32)
    storeAppendPrintf(sentry, "syscalls.selects = %f/sec\n", stats.syscalls_selects);
#endif

    storeAppendPrintf(sentry, "syscalls.disk.opens = %f/sec\n", stats.syscalls_disk_opens);
    storeAppendPrintf(sentry, "syscalls.disk.closes = %f/sec\n", stats.syscalls_disk_closes);
    storeAppendPrintf(sentry, "syscalls.disk.reads = %f/sec\n", stats.syscalls_disk_reads);
    storeAppendPrintf(sentry, "syscalls.disk.writes = %f/sec\n", stats.syscalls_disk_writes);
    storeAppendPrintf(sentry, "syscalls.disk.seeks = %f/sec\n", stats.syscalls_disk_seeks);
    storeAppendPrintf(sentry, "syscalls.disk.unlinks = %f/sec\n", stats.syscalls_disk_unlinks);
    storeAppendPrintf(sentry, "syscalls.sock.accepts = %f/sec\n", stats.syscalls_sock_accepts);
    storeAppendPrintf(sentry, "syscalls.sock.sockets = %f/sec\n", stats.syscalls_sock_sockets);
    storeAppendPrintf(sentry, "syscalls.sock.connects = %f/sec\n", stats.syscalls_sock_connects);
    storeAppendPrintf(sentry, "syscalls.sock.binds = %f/sec\n", stats.syscalls_sock_binds);
    storeAppendPrintf(sentry, "syscalls.sock.closes = %f/sec\n", stats.syscalls_sock_closes);
    storeAppendPrintf(sentry, "syscalls.sock.reads = %f/sec\n", stats.syscalls_sock_reads);
    storeAppendPrintf(sentry, "syscalls.sock.writes = %f/sec\n", stats.syscalls_sock_writes);
    storeAppendPrintf(sentry, "syscalls.sock.recvfroms = %f/sec\n", stats.syscalls_sock_recvfroms);
    storeAppendPrintf(sentry, "syscalls.sock.sendtos = %f/sec\n", stats.syscalls_sock_sendtos);

    storeAppendPrintf(sentry, "cpu_time = %f seconds\n", stats.cpu_time);
    storeAppendPrintf(sentry, "wall_time = %f seconds\n", stats.wall_time);
    storeAppendPrintf(sentry, "cpu_usage = %f%%\n", Math::doublePercent(stats.cpu_time, stats.wall_time));
}

static void
statRegisterWithCacheManager(void)
{
    Mgr::RegisterAction("info", "General Runtime Information",
                        &Mgr::InfoAction::Create, 0, 1);
    Mgr::RegisterAction("service_times", "Service Times (Percentiles)",
                        &Mgr::ServiceTimesAction::Create, 0, 1);
    Mgr::RegisterAction("filedescriptors", "Process Filedescriptor Allocation",
                        fde::DumpStats, 0, 1);
    Mgr::RegisterAction("objects", "All Cache Objects", stat_objects_get, 0, 0);
    Mgr::RegisterAction("vm_objects", "In-Memory and In-Transit Objects",
                        stat_vmobjects_get, 0, 0);
    Mgr::RegisterAction("io", "Server-side network read() size histograms",
                        &Mgr::IoAction::Create, 0, 1);
    Mgr::RegisterAction("counters", "Traffic and Resource Counters",
                        &Mgr::CountersAction::Create, 0, 1);
    Mgr::RegisterAction("peer_select", "Peer Selection Algorithms",
                        statPeerSelect, 0, 1);
    Mgr::RegisterAction("digest_stats", "Cache Digest and ICP blob",
                        statDigestBlob, 0, 1);
    Mgr::RegisterAction("5min", "5 Minute Average of Counters",
                        &Mgr::IntervalAction::Create5min, 0, 1);
    Mgr::RegisterAction("60min", "60 Minute Average of Counters",
                        &Mgr::IntervalAction::Create60min, 0, 1);
    Mgr::RegisterAction("utilization", "Cache Utilization",
                        statUtilization, 0, 1);
    Mgr::RegisterAction("histograms", "Full Histogram Counts",
                        statCountersHistograms, 0, 1);
    Mgr::RegisterAction("active_requests",
                        "Client-side Active Requests",
                        statClientRequests, 0, 1);
#if USE_AUTH
    Mgr::RegisterAction("username_cache",
                        "Active Cached Usernames",
                        Auth::User::UsernameCacheStats, 0, 1);
#endif
#if DEBUG_OPENFD
    Mgr::RegisterAction("openfd_objects", "Objects with Swapout files open",
                        statOpenfdObj, 0, 0);
#endif
#if STAT_GRAPHS
    Mgr::RegisterAction("graph_variables", "Display cache metrics graphically",
                        statGraphDump, 0, 1);
#endif
}


void
statInit(void)
{
    int i;
    debugs(18, 5, "statInit: Initializing...");

    for (i = 0; i < N_COUNT_HIST; ++i)
        statCountersInit(&CountHist[i]);

    for (i = 0; i < N_COUNT_HOUR_HIST; ++i)
        statCountersInit(&CountHourHist[i]);

    statCountersInit(&statCounter);

    eventAdd("statAvgTick", statAvgTick, NULL, (double) COUNT_INTERVAL, 1);

