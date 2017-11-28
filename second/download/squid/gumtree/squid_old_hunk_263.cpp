        return;
    }

    dt = tvSubDsec(l->timestamp, f->timestamp);
    ct = f->cputime - l->cputime;

    storeAppendPrintf(sentry, "sample_start_time = %d.%d (%s)\n",
                      (int) l->timestamp.tv_sec,
                      (int) l->timestamp.tv_usec,
                      mkrfc1123(l->timestamp.tv_sec));
    storeAppendPrintf(sentry, "sample_end_time = %d.%d (%s)\n",
                      (int) f->timestamp.tv_sec,
                      (int) f->timestamp.tv_usec,
                      mkrfc1123(f->timestamp.tv_sec));

    storeAppendPrintf(sentry, "client_http.requests = %f/sec\n",
                      XAVG(client_http.requests));
    storeAppendPrintf(sentry, "client_http.hits = %f/sec\n",
                      XAVG(client_http.hits));
    storeAppendPrintf(sentry, "client_http.errors = %f/sec\n",
                      XAVG(client_http.errors));
    storeAppendPrintf(sentry, "client_http.kbytes_in = %f/sec\n",
                      XAVG(client_http.kbytes_in.kb));
    storeAppendPrintf(sentry, "client_http.kbytes_out = %f/sec\n",
                      XAVG(client_http.kbytes_out.kb));

    x = statHistDeltaMedian(&l->client_http.all_svc_time,
                            &f->client_http.all_svc_time);
    storeAppendPrintf(sentry, "client_http.all_median_svc_time = %f seconds\n",
                      x / 1000.0);
    x = statHistDeltaMedian(&l->client_http.miss_svc_time,
                            &f->client_http.miss_svc_time);
    storeAppendPrintf(sentry, "client_http.miss_median_svc_time = %f seconds\n",
                      x / 1000.0);
    x = statHistDeltaMedian(&l->client_http.nm_svc_time,
                            &f->client_http.nm_svc_time);
    storeAppendPrintf(sentry, "client_http.nm_median_svc_time = %f seconds\n",
                      x / 1000.0);
    x = statHistDeltaMedian(&l->client_http.nh_svc_time,
                            &f->client_http.nh_svc_time);
    storeAppendPrintf(sentry, "client_http.nh_median_svc_time = %f seconds\n",
                      x / 1000.0);
    x = statHistDeltaMedian(&l->client_http.hit_svc_time,
                            &f->client_http.hit_svc_time);
    storeAppendPrintf(sentry, "client_http.hit_median_svc_time = %f seconds\n",
                      x / 1000.0);

    storeAppendPrintf(sentry, "server.all.requests = %f/sec\n",
                      XAVG(server.all.requests));
    storeAppendPrintf(sentry, "server.all.errors = %f/sec\n",
                      XAVG(server.all.errors));
    storeAppendPrintf(sentry, "server.all.kbytes_in = %f/sec\n",
                      XAVG(server.all.kbytes_in.kb));
    storeAppendPrintf(sentry, "server.all.kbytes_out = %f/sec\n",
                      XAVG(server.all.kbytes_out.kb));

    storeAppendPrintf(sentry, "server.http.requests = %f/sec\n",
                      XAVG(server.http.requests));
    storeAppendPrintf(sentry, "server.http.errors = %f/sec\n",
                      XAVG(server.http.errors));
    storeAppendPrintf(sentry, "server.http.kbytes_in = %f/sec\n",
                      XAVG(server.http.kbytes_in.kb));
    storeAppendPrintf(sentry, "server.http.kbytes_out = %f/sec\n",
                      XAVG(server.http.kbytes_out.kb));

    storeAppendPrintf(sentry, "server.ftp.requests = %f/sec\n",
                      XAVG(server.ftp.requests));
    storeAppendPrintf(sentry, "server.ftp.errors = %f/sec\n",
                      XAVG(server.ftp.errors));
    storeAppendPrintf(sentry, "server.ftp.kbytes_in = %f/sec\n",
                      XAVG(server.ftp.kbytes_in.kb));
    storeAppendPrintf(sentry, "server.ftp.kbytes_out = %f/sec\n",
                      XAVG(server.ftp.kbytes_out.kb));

    storeAppendPrintf(sentry, "server.other.requests = %f/sec\n",
                      XAVG(server.other.requests));
    storeAppendPrintf(sentry, "server.other.errors = %f/sec\n",
                      XAVG(server.other.errors));
    storeAppendPrintf(sentry, "server.other.kbytes_in = %f/sec\n",
                      XAVG(server.other.kbytes_in.kb));
    storeAppendPrintf(sentry, "server.other.kbytes_out = %f/sec\n",
                      XAVG(server.other.kbytes_out.kb));

    storeAppendPrintf(sentry, "icp.pkts_sent = %f/sec\n",
                      XAVG(icp.pkts_sent));
    storeAppendPrintf(sentry, "icp.pkts_recv = %f/sec\n",
                      XAVG(icp.pkts_recv));
    storeAppendPrintf(sentry, "icp.queries_sent = %f/sec\n",
                      XAVG(icp.queries_sent));
    storeAppendPrintf(sentry, "icp.replies_sent = %f/sec\n",
                      XAVG(icp.replies_sent));
    storeAppendPrintf(sentry, "icp.queries_recv = %f/sec\n",
                      XAVG(icp.queries_recv));
    storeAppendPrintf(sentry, "icp.replies_recv = %f/sec\n",
                      XAVG(icp.replies_recv));
    storeAppendPrintf(sentry, "icp.replies_queued = %f/sec\n",
                      XAVG(icp.replies_queued));
    storeAppendPrintf(sentry, "icp.query_timeouts = %f/sec\n",
                      XAVG(icp.query_timeouts));
    storeAppendPrintf(sentry, "icp.kbytes_sent = %f/sec\n",
                      XAVG(icp.kbytes_sent.kb));
    storeAppendPrintf(sentry, "icp.kbytes_recv = %f/sec\n",
                      XAVG(icp.kbytes_recv.kb));
    storeAppendPrintf(sentry, "icp.q_kbytes_sent = %f/sec\n",
                      XAVG(icp.q_kbytes_sent.kb));
    storeAppendPrintf(sentry, "icp.r_kbytes_sent = %f/sec\n",
                      XAVG(icp.r_kbytes_sent.kb));
    storeAppendPrintf(sentry, "icp.q_kbytes_recv = %f/sec\n",
                      XAVG(icp.q_kbytes_recv.kb));
    storeAppendPrintf(sentry, "icp.r_kbytes_recv = %f/sec\n",
                      XAVG(icp.r_kbytes_recv.kb));
    x = statHistDeltaMedian(&l->icp.query_svc_time, &f->icp.query_svc_time);
    storeAppendPrintf(sentry, "icp.query_median_svc_time = %f seconds\n",
                      x / 1000000.0);
    x = statHistDeltaMedian(&l->icp.reply_svc_time, &f->icp.reply_svc_time);
    storeAppendPrintf(sentry, "icp.reply_median_svc_time = %f seconds\n",
                      x / 1000000.0);
    x = statHistDeltaMedian(&l->dns.svc_time, &f->dns.svc_time);
    storeAppendPrintf(sentry, "dns.median_svc_time = %f seconds\n",
                      x / 1000.0);
    storeAppendPrintf(sentry, "unlink.requests = %f/sec\n",
                      XAVG(unlink.requests));
    storeAppendPrintf(sentry, "page_faults = %f/sec\n",
                      XAVG(page_faults));
    storeAppendPrintf(sentry, "select_loops = %f/sec\n",
                      XAVG(select_loops));
    storeAppendPrintf(sentry, "select_fds = %f/sec\n",
                      XAVG(select_fds));
    storeAppendPrintf(sentry, "average_select_fd_period = %f/fd\n",
                      f->select_fds > l->select_fds ?
                      (f->select_time - l->select_time) / (f->select_fds - l->select_fds)
                      : 0.0);
    x = statHistDeltaMedian(&l->select_fds_hist, &f->select_fds_hist);
    storeAppendPrintf(sentry, "median_select_fds = %f\n", x);
    storeAppendPrintf(sentry, "swap.outs = %f/sec\n",
                      XAVG(swap.outs));
    storeAppendPrintf(sentry, "swap.ins = %f/sec\n",
                      XAVG(swap.ins));
    storeAppendPrintf(sentry, "swap.files_cleaned = %f/sec\n",
                      XAVG(swap.files_cleaned));
    storeAppendPrintf(sentry, "aborted_requests = %f/sec\n",
                      XAVG(aborted_requests));

#if USE_POLL
    storeAppendPrintf(sentry, "syscalls.polls = %f/sec\n", XAVG(syscalls.selects));
#elif defined(USE_SELECT) || defined(USE_SELECT_WIN32)
    storeAppendPrintf(sentry, "syscalls.selects = %f/sec\n", XAVG(syscalls.selects));
#endif

    storeAppendPrintf(sentry, "syscalls.disk.opens = %f/sec\n", XAVG(syscalls.disk.opens));
    storeAppendPrintf(sentry, "syscalls.disk.closes = %f/sec\n", XAVG(syscalls.disk.closes));
    storeAppendPrintf(sentry, "syscalls.disk.reads = %f/sec\n", XAVG(syscalls.disk.reads));
    storeAppendPrintf(sentry, "syscalls.disk.writes = %f/sec\n", XAVG(syscalls.disk.writes));
    storeAppendPrintf(sentry, "syscalls.disk.seeks = %f/sec\n", XAVG(syscalls.disk.seeks));
    storeAppendPrintf(sentry, "syscalls.disk.unlinks = %f/sec\n", XAVG(syscalls.disk.unlinks));
    storeAppendPrintf(sentry, "syscalls.sock.accepts = %f/sec\n", XAVG(syscalls.sock.accepts));
    storeAppendPrintf(sentry, "syscalls.sock.sockets = %f/sec\n", XAVG(syscalls.sock.sockets));
    storeAppendPrintf(sentry, "syscalls.sock.connects = %f/sec\n", XAVG(syscalls.sock.connects));
    storeAppendPrintf(sentry, "syscalls.sock.binds = %f/sec\n", XAVG(syscalls.sock.binds));
    storeAppendPrintf(sentry, "syscalls.sock.closes = %f/sec\n", XAVG(syscalls.sock.closes));
    storeAppendPrintf(sentry, "syscalls.sock.reads = %f/sec\n", XAVG(syscalls.sock.reads));
    storeAppendPrintf(sentry, "syscalls.sock.writes = %f/sec\n", XAVG(syscalls.sock.writes));
    storeAppendPrintf(sentry, "syscalls.sock.recvfroms = %f/sec\n", XAVG(syscalls.sock.recvfroms));
    storeAppendPrintf(sentry, "syscalls.sock.sendtos = %f/sec\n", XAVG(syscalls.sock.sendtos));

    storeAppendPrintf(sentry, "cpu_time = %f seconds\n", ct);
    storeAppendPrintf(sentry, "wall_time = %f seconds\n", dt);
    storeAppendPrintf(sentry, "cpu_usage = %f%%\n", Math::doublePercent(ct, dt));
}

static void
statRegisterWithCacheManager(void)
{
    CacheManager *manager = CacheManager::GetInstance();
    manager->registerAction("info", "General Runtime Information",
                            info_get, 0, 1);
    manager->registerAction("service_times", "Service Times (Percentiles)",
                            service_times, 0, 1);
    manager->registerAction("filedescriptors", "Process Filedescriptor Allocation",
                            fde::DumpStats, 0, 1);
    manager->registerAction("objects", "All Cache Objects", stat_objects_get, 0, 0);
    manager->registerAction("vm_objects", "In-Memory and In-Transit Objects",
                            stat_vmobjects_get, 0, 0);
    manager->registerAction("io", "Server-side network read() size histograms",
                            stat_io_get, 0, 1);
    manager->registerAction("counters", "Traffic and Resource Counters",
                            statCountersDump, 0, 1);
    manager->registerAction("peer_select", "Peer Selection Algorithms",
                            statPeerSelect, 0, 1);
    manager->registerAction("digest_stats", "Cache Digest and ICP blob",
                            statDigestBlob, 0, 1);
    manager->registerAction("5min", "5 Minute Average of Counters",
                            statAvg5min, 0, 1);
    manager->registerAction("60min", "60 Minute Average of Counters",
                            statAvg60min, 0, 1);
    manager->registerAction("utilization", "Cache Utilization",
                            statUtilization, 0, 1);
    manager->registerAction("histograms", "Full Histogram Counts",
                            statCountersHistograms, 0, 1);
    manager->registerAction("active_requests",
                            "Client-side Active Requests",
                            statClientRequests, 0, 1);
#if DEBUG_OPENFD
    manager->registerAction("openfd_objects", "Objects with Swapout files open",
                            statOpenfdObj, 0, 0);
#endif
#if STAT_GRAPHS
    manager->registerAction("graph_variables", "Display cache metrics graphically",
                            statGraphDump, 0, 1);
#endif
}


void
statInit(void)
{
    int i;
    debugs(18, 5, "statInit: Initializing...");

    for (i = 0; i < N_COUNT_HIST; i++)
        statCountersInit(&CountHist[i]);

    for (i = 0; i < N_COUNT_HOUR_HIST; i++)
        statCountersInit(&CountHourHist[i]);

    statCountersInit(&statCounter);

    eventAdd("statAvgTick", statAvgTick, NULL, (double) COUNT_INTERVAL, 1);

