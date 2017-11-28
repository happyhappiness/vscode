bool Adaptation::History::extractFutureServices(DynamicGroupCfg &value)
{
    if (theFutureServices.empty())
        return false;

    value = theFutureServices;
    theFutureServices.clear();
    return true;
}