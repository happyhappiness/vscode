void
GetAvgStat(Mgr::IntervalActionData& stats, int minutes, int hours)
{
    StatCounters *f;
    StatCounters *l;
    double dt;
    double ct;
    assert(N_COUNT_HIST > 1);
    assert(minutes > 0 || hours > 0);
    f = &CountHist[0];
    l = f;

    if (minutes > 0 && hours == 0) {
        /* checking minute readings ... */

        if (minutes > N_COUNT_HIST - 1)
            minutes = N_COUNT_HIST - 1;

        l = &CountHist[minutes];
    } else if (minutes == 0 && hours > 0) {
        /* checking hour readings ... */

        if (hours > N_COUNT_HOUR_HIST - 1)
            hours = N_COUNT_HOUR_HIST - 1;

        l = &CountHourHist[hours];
    } else {
        debugs(18, DBG_IMPORTANT, "statAvgDump: Invalid args, minutes=" << minutes << ", hours=" << hours);
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