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