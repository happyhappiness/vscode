static void
commDevPollRegisterWithCacheManager(void)
{
    CacheManager::GetInstance()->
    registerAction(
        "comm_devpoll_incoming",
        "comm_incoming() stats",
        commIncomingStats,
        0,
        1
    );
}