void
Adaptation::History::setFutureServices(const DynamicGroupCfg &services)
{
    if (!theFutureServices.empty())
        debugs(93,3, HERE << "old future services: " << theFutureServices);
    debugs(93,3, HERE << "new future services: " << services);
    theFutureServices = services; // may be empty
}