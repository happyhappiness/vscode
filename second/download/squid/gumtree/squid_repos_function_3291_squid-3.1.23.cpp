static void
commSelectRegisterWithCacheManager(void)
{
    CacheManager::GetInstance()->
    registerAction("comm_select_incoming",
                   "comm_incoming() stats",
                   commIncomingStats, 0, 1);
}