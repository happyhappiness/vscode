static void
commPollRegisterWithCacheManager(void)
{
    CacheManager::GetInstance()->
    registerAction("comm_poll_incoming",
                   "comm_incoming() stats",
                   commIncomingStats, 0, 1);
}