static void
neighborsRegisterWithCacheManager()
{
    Mgr::RegisterAction("server_list",
                        "Peer Cache Statistics",
                        neighborDumpPeers, 0, 1);

    if (Comm::IsConnOpen(icpIncomingConn)) {
        Mgr::RegisterAction("non_peers",
                            "List of Unknown sites sending ICP messages",
                            neighborDumpNonPeers, 0, 1);
    }
}