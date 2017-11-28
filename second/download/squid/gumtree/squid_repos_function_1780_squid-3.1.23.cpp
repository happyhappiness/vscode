static void
neighborsRegisterWithCacheManager()
{
    CacheManager *manager = CacheManager::GetInstance();
    manager->registerAction("server_list",
                            "Peer Cache Statistics",
                            neighborDumpPeers, 0, 1);

    if (theInIcpConnection >= 0) {
        manager->registerAction("non_peers",
                                "List of Unknown sites sending ICP messages",
                                neighborDumpNonPeers, 0, 1);
    }
}