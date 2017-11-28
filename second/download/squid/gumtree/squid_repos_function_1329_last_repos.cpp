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
                        Auth::User::CredentialsCacheStats, 0, 1);
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