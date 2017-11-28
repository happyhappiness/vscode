void
eventInit(void)
{
    CacheManager::GetInstance()->
    registerAction("events", "Event Queue", eventDump, 0, 1);
}