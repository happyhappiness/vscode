static void
commEPollRegisterWithCacheManager(void)
{
    Mgr::RegisterAction("comm_epoll_incoming",
                        "comm_incoming() stats",
                        commIncomingStats, 0, 1);
}