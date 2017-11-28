void
Adaptation::DynamicServiceChain::Split(const ServiceFilter &filter,
                                       const String &ids, DynamicGroupCfg &current,
                                       DynamicGroupCfg &future)
{
    // walk the list of services and split it into two parts:
    // services that are applicable now and future services
    bool doingCurrent = true;
    const char *item = NULL;
    int ilen = 0;
    const char *pos = NULL;
    while (strListGetItem(&ids, ',', &item, &ilen, &pos)) {
        String id;
        id.limitInit(item, ilen);
        ServicePointer service = FindService(id);
        if (doingCurrent) {
            if (!service || // cannot tell or matches current location
                    (service->cfg().method == filter.method &&
                     service->cfg().point == filter.point)) {
                current.add(id);
                continue;
            } else {
                doingCurrent = false;
            }
        }

        if (!doingCurrent)
            future.add(id);
    }
}