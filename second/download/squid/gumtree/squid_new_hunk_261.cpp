{
    statObjectsStart(sentry, statObjectsOpenfdFilter);
}

#endif

#if XMALLOC_STATISTICS
static void
info_get_mallstat(int size, int number, int oldnum, void *data)
{
    StoreEntry *sentry = (StoreEntry *)data;

// format: "%12s %15s %6s %12s\n","Alloc Size","Count","Delta","Alloc/sec"
    if (number > 0)
        storeAppendPrintf(sentry, "%12d %15d %6d %.1f\n", size, number, number - oldnum, xdiv((number - oldnum), xm_deltat));
}

#endif

void
GetInfo(Mgr::InfoActionData& stats)
{

    struct rusage rusage;
    double cputime;
    double runtime;
#if HAVE_MSTATS && HAVE_GNUMALLOC_H

    struct mstats ms;
#elif HAVE_MALLINFO && HAVE_STRUCT_MALLINFO

    struct mallinfo mp;
#endif

    runtime = tvSubDsec(squid_start, current_time);

    if (runtime == 0.0)
        runtime = 1.0;

    stats.squid_start = squid_start;

    stats.current_time = current_time;

    stats.client_http_clients = statCounter.client_http.clients;

    stats.client_http_requests = statCounter.client_http.requests;

    stats.icp_pkts_recv = statCounter.icp.pkts_recv;

    stats.icp_pkts_sent = statCounter.icp.pkts_sent;

    stats.icp_replies_queued = statCounter.icp.replies_queued;

#if USE_HTCP

    stats.htcp_pkts_recv = statCounter.htcp.pkts_recv;

    stats.htcp_pkts_sent = statCounter.htcp.pkts_sent;

#endif

    stats.request_failure_ratio = request_failure_ratio;

    stats.avg_client_http_requests = statCounter.client_http.requests / (runtime / 60.0);

    stats.avg_icp_messages = (statCounter.icp.pkts_sent + statCounter.icp.pkts_recv) / (runtime / 60.0);

    stats.select_loops = statCounter.select_loops;
    stats.avg_loop_time = 1000.0 * runtime / statCounter.select_loops;

    stats.request_hit_ratio5 = statRequestHitRatio(5);
    stats.request_hit_ratio60 = statRequestHitRatio(60);

    stats.byte_hit_ratio5 = statByteHitRatio(5);
    stats.byte_hit_ratio60 = statByteHitRatio(60);

    stats.request_hit_mem_ratio5 = statRequestHitMemoryRatio(5);
    stats.request_hit_mem_ratio60 = statRequestHitMemoryRatio(60);

    stats.request_hit_disk_ratio5 = statRequestHitDiskRatio(5);
    stats.request_hit_disk_ratio60 = statRequestHitDiskRatio(60);

    Store::Root().getStats(stats.store);

    stats.unlink_requests = statCounter.unlink.requests;

    stats.http_requests5 = statPctileSvc(0.5, 5, PCTILE_HTTP);
    stats.http_requests60 = statPctileSvc(0.5, 60, PCTILE_HTTP);

    stats.cache_misses5 = statPctileSvc(0.5, 5, PCTILE_MISS);
    stats.cache_misses60 = statPctileSvc(0.5, 60, PCTILE_MISS);

    stats.cache_hits5 = statPctileSvc(0.5, 5, PCTILE_HIT);
    stats.cache_hits60 = statPctileSvc(0.5, 60, PCTILE_HIT);

    stats.near_hits5 = statPctileSvc(0.5, 5, PCTILE_NH);
    stats.near_hits60 = statPctileSvc(0.5, 60, PCTILE_NH);

    stats.not_modified_replies5 = statPctileSvc(0.5, 5, PCTILE_NM);
    stats.not_modified_replies60 = statPctileSvc(0.5, 60, PCTILE_NM);

    stats.dns_lookups5 = statPctileSvc(0.5, 5, PCTILE_DNS);
    stats.dns_lookups60 = statPctileSvc(0.5, 60, PCTILE_DNS);

    stats.icp_queries5 = statPctileSvc(0.5, 5, PCTILE_ICP_QUERY);
    stats.icp_queries60 = statPctileSvc(0.5, 60, PCTILE_ICP_QUERY);

    squid_getrusage(&rusage);
    cputime = rusage_cputime(&rusage);

    stats.up_time = runtime;
    stats.cpu_time = cputime;
    stats.cpu_usage = Math::doublePercent(cputime, runtime);
    stats.cpu_usage5 = statCPUUsage(5);
    stats.cpu_usage60 = statCPUUsage(60);

#if HAVE_SBRK

    stats.proc_data_seg = ((char *) sbrk(0) - (char *) sbrk_start);

#endif

    stats.maxrss = rusage_maxrss(&rusage);

    stats.page_faults = rusage_pagefaults(&rusage);

#if HAVE_MSTATS && HAVE_GNUMALLOC_H

    ms = mstats();

    stats.ms_bytes_total = ms.bytes_total;

    stats.ms_bytes_free = ms.bytes_free;

#elif HAVE_MALLINFO && HAVE_STRUCT_MALLINFO

    mp = mallinfo();

    stats.mp_arena = mp.arena;

    stats.mp_uordblks = mp.uordblks;
    stats.mp_ordblks = mp.ordblks;

    stats.mp_usmblks = mp.usmblks;
    stats.mp_smblks = mp.smblks;

    stats.mp_hblkhd = mp.hblkhd;
    stats.mp_hblks = mp.hblks;

    stats.mp_fsmblks = mp.fsmblks;

    stats.mp_fordblks = mp.fordblks;

#if HAVE_STRUCT_MALLINFO_MXFAST

    stats.mp_mxfast = mp.mxfast;

    stats.mp_nlblks = mp.nlblks;

    stats.mp_grain = mp.grain;

    stats.mp_uordbytes = mp.uordbytes;

    stats.mp_allocated = mp.allocated;

    stats.mp_treeoverhead = mp.treeoverhead;

#endif /* HAVE_STRUCT_MALLINFO_MXFAST */
#endif /* HAVE_MALLINFO */

    stats.total_accounted = statMemoryAccounted();

    {
        MemPoolGlobalStats mp_stats;
        memPoolGetGlobalStats(&mp_stats);
#if !(HAVE_MSTATS && HAVE_GNUMALLOC_H) && HAVE_MALLINFO && HAVE_STRUCT_MALLINFO

        stats.mem_pool_allocated = mp_stats.TheMeter->alloc.level;
#endif

        stats.gb_saved_count = mp_stats.TheMeter->gb_saved.count;
        stats.gb_freed_count = mp_stats.TheMeter->gb_freed.count;
    }

    stats.max_fd = Squid_MaxFD;
    stats.biggest_fd = Biggest_FD;
    stats.number_fd = Number_FD;
    stats.opening_fd = Opening_FD;
    stats.num_fd_free = fdNFree();
    stats.reserved_fd = RESERVED_FD;
}

void
DumpInfo(Mgr::InfoActionData& stats, StoreEntry* sentry)
{
    storeAppendPrintf(sentry, "Squid Object Cache: Version %s\n",
                      version_string);

#if _SQUID_WINDOWS_
    if (WIN32_run_mode == _WIN_SQUID_RUN_MODE_SERVICE) {
        storeAppendPrintf(sentry,"\nRunning as %s Windows System Service on %s\n",
                          WIN32_Service_name, WIN32_OS_string);
        storeAppendPrintf(sentry,"Service command line is: %s\n", WIN32_Service_Command_Line);
    } else
        storeAppendPrintf(sentry,"Running on %s\n",WIN32_OS_string);
