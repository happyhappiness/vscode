static void
commPollRegisterWithCacheManager(void)
{
    Mgr::RegisterAction("comm_poll_incoming",
                        "comm_incoming() stats",
                        commIncomingStats, 0, 1);
}