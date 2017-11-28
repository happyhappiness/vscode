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