static void
commEPollRegisterWithCacheManager(void)
{
    CacheManager::GetInstance()->
    registerAction("comm_epoll_incoming",
                   "comm_incoming() stats",
                   commIncomingStats, 0, 1);
}