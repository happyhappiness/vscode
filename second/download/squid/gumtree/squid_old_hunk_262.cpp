    if (WIN32_run_mode == _WIN_SQUID_RUN_MODE_SERVICE) {
        storeAppendPrintf(sentry,"\nRunning as %s Windows System Service on %s\n",
                          WIN32_Service_name, WIN32_OS_string);
        storeAppendPrintf(sentry,"Service command line is: %s\n", WIN32_Service_Command_Line);
    } else
        storeAppendPrintf(sentry,"Running on %s\n",WIN32_OS_string);

#endif

    storeAppendPrintf(sentry, "Start Time:\t%s\n",
                      mkrfc1123(squid_start.tv_sec));

    storeAppendPrintf(sentry, "Current Time:\t%s\n",
                      mkrfc1123(current_time.tv_sec));

    storeAppendPrintf(sentry, "Connection information for %s:\n",APP_SHORTNAME);

    storeAppendPrintf(sentry, "\tNumber of clients accessing cache:\t%u\n",
                      statCounter.client_http.clients);

    storeAppendPrintf(sentry, "\tNumber of HTTP requests received:\t%u\n",
                      statCounter.client_http.requests);

    storeAppendPrintf(sentry, "\tNumber of ICP messages received:\t%u\n",
                      statCounter.icp.pkts_recv);

    storeAppendPrintf(sentry, "\tNumber of ICP messages sent:\t%u\n",
                      statCounter.icp.pkts_sent);

    storeAppendPrintf(sentry, "\tNumber of queued ICP replies:\t%u\n",
                      statCounter.icp.replies_queued);

#if USE_HTCP

    storeAppendPrintf(sentry, "\tNumber of HTCP messages received:\t%u\n",
                      statCounter.htcp.pkts_recv);

    storeAppendPrintf(sentry, "\tNumber of HTCP messages sent:\t%u\n",
                      statCounter.htcp.pkts_sent);

#endif

    storeAppendPrintf(sentry, "\tRequest failure ratio:\t%5.2f\n",
                      request_failure_ratio);

    storeAppendPrintf(sentry, "\tAverage HTTP requests per minute since start:\t%.1f\n",
                      statCounter.client_http.requests / (runtime / 60.0));

    storeAppendPrintf(sentry, "\tAverage ICP messages per minute since start:\t%.1f\n",
                      (statCounter.icp.pkts_sent + statCounter.icp.pkts_recv) / (runtime / 60.0));

    storeAppendPrintf(sentry, "\tSelect loop called: %ld times, %0.3f ms avg\n",
                      statCounter.select_loops, 1000.0 * runtime / statCounter.select_loops);

    storeAppendPrintf(sentry, "Cache information for %s:\n",APP_SHORTNAME);

    storeAppendPrintf(sentry, "\tHits as %% of all requests:\t5min: %3.1f%%, 60min: %3.1f%%\n",
                      statRequestHitRatio(5),
                      statRequestHitRatio(60));

    storeAppendPrintf(sentry, "\tHits as %% of bytes sent:\t5min: %3.1f%%, 60min: %3.1f%%\n",
                      statByteHitRatio(5),
                      statByteHitRatio(60));

    storeAppendPrintf(sentry, "\tMemory hits as %% of hit requests:\t5min: %3.1f%%, 60min: %3.1f%%\n",
                      statRequestHitMemoryRatio(5),
                      statRequestHitMemoryRatio(60));

    storeAppendPrintf(sentry, "\tDisk hits as %% of hit requests:\t5min: %3.1f%%, 60min: %3.1f%%\n",
                      statRequestHitDiskRatio(5),
                      statRequestHitDiskRatio(60));

    storeAppendPrintf(sentry, "\tStorage Swap size:\t%lu KB\n",
                      store_swap_size);

    storeAppendPrintf(sentry, "\tStorage Swap capacity:\t%4.1f%% used, %4.1f%% free\n",
                      Math::doublePercent(store_swap_size, Store::Root().maxSize()),
                      Math::doublePercent((Store::Root().maxSize() - store_swap_size), Store::Root().maxSize()));


    storeAppendPrintf(sentry, "\tStorage Mem size:\t%lu KB\n",
                      (unsigned long)(mem_node::StoreMemSize() >> 10));

    double mFree = 0.0;
    if (mem_node::InUseCount() <= store_pages_max)
        mFree = Math::doublePercent((store_pages_max - mem_node::InUseCount()), store_pages_max);
    storeAppendPrintf(sentry, "\tStorage Mem capacity:\t%4.1f%% used, %4.1f%% free\n",
                      Math::doublePercent(mem_node::InUseCount(), store_pages_max),
                      mFree);

    storeAppendPrintf(sentry, "\tMean Object Size:\t%0.2f KB\n",
                      n_disk_objects ? (double) store_swap_size / n_disk_objects : 0.0);

    storeAppendPrintf(sentry, "\tRequests given to unlinkd:\t%ld\n",
                      (long)statCounter.unlink.requests);

    storeAppendPrintf(sentry, "Median Service Times (seconds)  5 min    60 min:\n");

    storeAppendPrintf(sentry, "\tHTTP Requests (All):  %8.5f %8.5f\n",
                      statPctileSvc(0.5, 5, PCTILE_HTTP) / 1000.0,
                      statPctileSvc(0.5, 60, PCTILE_HTTP) / 1000.0);

    storeAppendPrintf(sentry, "\tCache Misses:         %8.5f %8.5f\n",
                      statPctileSvc(0.5, 5, PCTILE_MISS) / 1000.0,
                      statPctileSvc(0.5, 60, PCTILE_MISS) / 1000.0);

    storeAppendPrintf(sentry, "\tCache Hits:           %8.5f %8.5f\n",
                      statPctileSvc(0.5, 5, PCTILE_HIT) / 1000.0,
                      statPctileSvc(0.5, 60, PCTILE_HIT) / 1000.0);

    storeAppendPrintf(sentry, "\tNear Hits:            %8.5f %8.5f\n",
                      statPctileSvc(0.5, 5, PCTILE_NH) / 1000.0,
                      statPctileSvc(0.5, 60, PCTILE_NH) / 1000.0);

    storeAppendPrintf(sentry, "\tNot-Modified Replies: %8.5f %8.5f\n",
                      statPctileSvc(0.5, 5, PCTILE_NM) / 1000.0,
                      statPctileSvc(0.5, 60, PCTILE_NM) / 1000.0);

    storeAppendPrintf(sentry, "\tDNS Lookups:          %8.5f %8.5f\n",
                      statPctileSvc(0.5, 5, PCTILE_DNS) / 1000.0,
                      statPctileSvc(0.5, 60, PCTILE_DNS) / 1000.0);

    storeAppendPrintf(sentry, "\tICP Queries:          %8.5f %8.5f\n",
                      statPctileSvc(0.5, 5, PCTILE_ICP_QUERY) / 1000000.0,
                      statPctileSvc(0.5, 60, PCTILE_ICP_QUERY) / 1000000.0);

    squid_getrusage(&rusage);

    cputime = rusage_cputime(&rusage);

    storeAppendPrintf(sentry, "Resource usage for %s:\n", APP_SHORTNAME);

    storeAppendPrintf(sentry, "\tUP Time:\t%.3f seconds\n", runtime);

    storeAppendPrintf(sentry, "\tCPU Time:\t%.3f seconds\n", cputime);

    storeAppendPrintf(sentry, "\tCPU Usage:\t%.2f%%\n",
                      Math::doublePercent(cputime, runtime));

    storeAppendPrintf(sentry, "\tCPU Usage, 5 minute avg:\t%.2f%%\n",
                      statCPUUsage(5));

    storeAppendPrintf(sentry, "\tCPU Usage, 60 minute avg:\t%.2f%%\n",
                      statCPUUsage(60));

#if HAVE_SBRK

    storeAppendPrintf(sentry, "\tProcess Data Segment Size via sbrk(): %lu KB\n",
                      (unsigned long) (((char *) sbrk(0) - (char *) sbrk_start) >> 10));

#endif

    storeAppendPrintf(sentry, "\tMaximum Resident Size: %ld KB\n",
                      (long)rusage_maxrss(&rusage));

    storeAppendPrintf(sentry, "\tPage faults with physical i/o: %ld\n",
                      (long)rusage_pagefaults(&rusage));

#if HAVE_MSTATS && HAVE_GNUMALLOC_H


    struct mstats ms = mstats();

    storeAppendPrintf(sentry, "Memory usage for %s via mstats():\n",APP_SHORTNAME);

    storeAppendPrintf(sentry, "\tTotal space in arena:  %6.0f KB\n",
                      static_cast<double>(ms.bytes_total / 1024));

    storeAppendPrintf(sentry, "\tTotal free:            %6.0f KB %.0f%%\n",
                      static_cast<double>(ms.bytes_free / 1024),
                      Math::doublePercent(static_cast<double>(ms.bytes_free), static_cast<double>(ms.bytes_total)));

#elif HAVE_MALLINFO && HAVE_STRUCT_MALLINFO

    struct mallinfo mp = mallinfo();

    storeAppendPrintf(sentry, "Memory usage for %s via mallinfo():\n",APP_SHORTNAME);

    storeAppendPrintf(sentry, "\tTotal space in arena:  %6.0f KB\n",
                      static_cast<double>(mp.arena / 1024));

    storeAppendPrintf(sentry, "\tOrdinary blocks:       %6.0f KB %6.0f blks\n",
                      static_cast<double>(mp.uordblks / 1024), static_cast<double>(mp.ordblks));

    storeAppendPrintf(sentry, "\tSmall blocks:          %6.0f KB %6.0f blks\n",
                      static_cast<double>(mp.usmblks / 1024), static_cast<double>(mp.smblks));

    storeAppendPrintf(sentry, "\tHolding blocks:        %6.0f KB %6.0f blks\n",
                      static_cast<double>(mp.hblkhd / 1024), static_cast<double>(mp.hblks));

    storeAppendPrintf(sentry, "\tFree Small blocks:     %6.0f KB\n",
                      static_cast<double>(mp.fsmblks / 1024));

    storeAppendPrintf(sentry, "\tFree Ordinary blocks:  %6.0f KB\n",
                      static_cast<double>(mp.fordblks / 1024));

    double t = mp.uordblks + mp.usmblks + mp.hblkhd;

    storeAppendPrintf(sentry, "\tTotal in use:          %6.0f KB %.0f%%\n",
                      (t / 1024), Math::doublePercent(t, static_cast<double>(mp.arena + mp.hblkhd)));

    t = mp.fsmblks + mp.fordblks;

    storeAppendPrintf(sentry, "\tTotal free:            %6.0f KB %.0f%%\n",
                      (t / 1024), Math::doublePercent(t, static_cast<double>(mp.arena + mp.hblkhd)));

    t = mp.arena + mp.hblkhd;

    storeAppendPrintf(sentry, "\tTotal size:            %6.0f KB\n", (t / 1024));

#if HAVE_STRUCT_MALLINFO_MXFAST

    storeAppendPrintf(sentry, "\tmax size of small blocks:\t%.0f\n", static_cast<double>(mp.mxfast));

    storeAppendPrintf(sentry, "\tnumber of small blocks in a holding block:\t%6.0f\n",
                      static_cast<double>(mp.nlblks));

    storeAppendPrintf(sentry, "\tsmall block rounding factor:\t%.0f\n", static_cast<double>(mp.grain));

    storeAppendPrintf(sentry, "\tspace (including overhead) allocated in ord. blks:\t%.0f\n",
                      static_cast<double>(mp.uordbytes));

    storeAppendPrintf(sentry, "\tnumber of ordinary blocks allocated:\t%.0f\n",
                      static_cast<double>(mp.allocated));

    storeAppendPrintf(sentry, "\tbytes used in maintaining the free tree:\t%.0f\n",
                      static_cast<double>(mp.treeoverhead));

#endif /* HAVE_STRUCT_MALLINFO_MXFAST */
#endif /* HAVE_MALLINFO */

    storeAppendPrintf(sentry, "Memory accounted for:\n");

#if !(HAVE_MSTATS && HAVE_GNUMALLOC_H) && HAVE_MALLINFO && HAVE_STRUCT_MALLINFO

    storeAppendPrintf(sentry, "\tTotal accounted:       %6.0f KB %.0f%%\n",
                      (statMemoryAccounted() / 1024), Math::doublePercent(statMemoryAccounted(), t));

#else

    storeAppendPrintf(sentry, "\tTotal accounted:       %6.0f KB\n",
                      (statMemoryAccounted() / 1024));

#endif
    {
        MemPoolGlobalStats mp_stats;
        memPoolGetGlobalStats(&mp_stats);
#if !(HAVE_MSTATS && HAVE_GNUMALLOC_H) && HAVE_MALLINFO && HAVE_STRUCT_MALLINFO

        storeAppendPrintf(sentry, "\tmemPool accounted:     %6.0f KB %.0f%%\n",
                          static_cast<double>(mp_stats.TheMeter->alloc.level / 1024),
                          Math::doublePercent(static_cast<double>(mp_stats.TheMeter->alloc.level), t));

        double iFree = 0;
        if (t >= mp_stats.TheMeter->alloc.level)
            iFree = Math::doublePercent((t - static_cast<double>(mp_stats.TheMeter->alloc.level)), t);
        storeAppendPrintf(sentry, "\tmemPool unaccounted:   %6.0f KB %.0f%%\n",
                          static_cast<double>((t - mp_stats.TheMeter->alloc.level) / 1024), iFree);
#endif

        storeAppendPrintf(sentry, "\tmemPoolAlloc calls: %9.0f\n",
                          mp_stats.TheMeter->gb_saved.count);
        storeAppendPrintf(sentry, "\tmemPoolFree calls:  %9.0f\n",
                          mp_stats.TheMeter->gb_freed.count);
    }

    storeAppendPrintf(sentry, "File descriptor usage for %s:\n", APP_SHORTNAME);
    storeAppendPrintf(sentry, "\tMaximum number of file descriptors:   %4d\n",
                      Squid_MaxFD);
    storeAppendPrintf(sentry, "\tLargest file desc currently in use:   %4d\n",
                      Biggest_FD);
    storeAppendPrintf(sentry, "\tNumber of file desc currently in use: %4d\n",
                      Number_FD);
    storeAppendPrintf(sentry, "\tFiles queued for open:                %4d\n",
                      Opening_FD);
    storeAppendPrintf(sentry, "\tAvailable number of file descriptors: %4d\n",
                      fdNFree());
    storeAppendPrintf(sentry, "\tReserved number of file descriptors:  %4d\n",
                      RESERVED_FD);
    storeAppendPrintf(sentry, "\tStore Disk files open:                %4d\n",
                      store_open_disk_fd);

    storeAppendPrintf(sentry, "Internal Data Structures:\n");
    storeAppendPrintf(sentry, "\t%6lu StoreEntries\n",
                      (unsigned long)StoreEntry::inUseCount());
    storeAppendPrintf(sentry, "\t%6lu StoreEntries with MemObjects\n",
                      (unsigned long)MemObject::inUseCount());
    storeAppendPrintf(sentry, "\t%6ld Hot Object Cache Items\n",
                      (long)hot_obj_count);
    storeAppendPrintf(sentry, "\t%6ld on-disk objects\n",
                      (long)n_disk_objects);

#if XMALLOC_STATISTICS

    xm_deltat = current_dtime - xm_time;
    xm_time = current_dtime;
    storeAppendPrintf(sentry, "\nMemory allocation statistics\n");
    storeAppendPrintf(sentry, "%12s %15s %6s %12s\n","Alloc Size","Count","Delta","Alloc/sec");
    malloc_statistics(info_get_mallstat, sentry);
#endif
}

static void
service_times(StoreEntry * sentry)
{
    int p;
    storeAppendPrintf(sentry, "Service Time Percentiles            5 min    60 min:\n");
    for (p = 5; p < 100; p += 5) {
        storeAppendPrintf(sentry, "\tHTTP Requests (All):  %2d%%  %8.5f %8.5f\n",
                          p,
                          statPctileSvc((double) p / 100.0, 5, PCTILE_HTTP) / 1000.0,
                          statPctileSvc((double) p / 100.0, 60, PCTILE_HTTP) / 1000.0);
    }
    for (p = 5; p < 100; p += 5) {
        storeAppendPrintf(sentry, "\tCache Misses:         %2d%%  %8.5f %8.5f\n",
                          p,
                          statPctileSvc((double) p / 100.0, 5, PCTILE_MISS) / 1000.0,
                          statPctileSvc((double) p / 100.0, 60, PCTILE_MISS) / 1000.0);
    }
    for (p = 5; p < 100; p += 5) {
        storeAppendPrintf(sentry, "\tCache Hits:           %2d%%  %8.5f %8.5f\n",
                          p,
                          statPctileSvc((double) p / 100.0, 5, PCTILE_HIT) / 1000.0,
                          statPctileSvc((double) p / 100.0, 60, PCTILE_HIT) / 1000.0);
    }
    for (p = 5; p < 100; p += 5) {
        storeAppendPrintf(sentry, "\tNear Hits:            %2d%%  %8.5f %8.5f\n",
                          p,
                          statPctileSvc((double) p / 100.0, 5, PCTILE_NH) / 1000.0,
                          statPctileSvc((double) p / 100.0, 60, PCTILE_NH) / 1000.0);
    }
    for (p = 5; p < 100; p += 5) {
        storeAppendPrintf(sentry, "\tNot-Modified Replies: %2d%%  %8.5f %8.5f\n",
                          p,
                          statPctileSvc((double) p / 100.0, 5, PCTILE_NM) / 1000.0,
                          statPctileSvc((double) p / 100.0, 60, PCTILE_NM) / 1000.0);
    }
    for (p = 5; p < 100; p += 5) {
        storeAppendPrintf(sentry, "\tDNS Lookups:          %2d%%  %8.5f %8.5f\n",
                          p,
                          statPctileSvc((double) p / 100.0, 5, PCTILE_DNS) / 1000.0,
                          statPctileSvc((double) p / 100.0, 60, PCTILE_DNS) / 1000.0);
    }
    for (p = 5; p < 100; p += 5) {
        storeAppendPrintf(sentry, "\tICP Queries:          %2d%%  %8.5f %8.5f\n",
                          p,
                          statPctileSvc((double) p / 100.0, 5, PCTILE_ICP_QUERY) / 1000000.0,
                          statPctileSvc((double) p / 100.0, 60, PCTILE_ICP_QUERY) / 1000000.0);
    }
}

#define XAVG(X) (dt ? (double) (f->X - l->X) / dt : 0.0)
static void
statAvgDump(StoreEntry * sentry, int minutes, int hours)
{
    StatCounters *f;
    StatCounters *l;
    double dt;
    double ct;
    double x;
    assert(N_COUNT_HIST > 1);
    assert(minutes > 0 || hours > 0);
    f = &CountHist[0];
    l = f;

    if (minutes > 0 && hours == 0) {
