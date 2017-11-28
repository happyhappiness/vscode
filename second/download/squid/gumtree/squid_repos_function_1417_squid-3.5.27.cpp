void
SBufStatsAction::RegisterWithCacheManager()
{
    Mgr::RegisterAction("sbuf", "String-Buffer statistics", &SBufStatsAction::Create, 0 , 1);
}