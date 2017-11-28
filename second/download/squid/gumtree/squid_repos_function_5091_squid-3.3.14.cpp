static void
commDevPollRegisterWithCacheManager(void)
{
    Mgr::RegisterAction(
        "comm_devpoll_incoming",
        "comm_incoming() stats",
        commIncomingStats,
        0,
        1
    );
}