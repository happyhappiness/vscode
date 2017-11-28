bool
Adaptation::AccessCheck::usedDynamicRules()
{
    Adaptation::History::Pointer ah = filter.request->adaptHistory();
    if (!ah)
        return false; // dynamic rules not enabled or not triggered

    DynamicGroupCfg services;
    if (!ah->extractFutureServices(services)) { // clears history
        debugs(85,9, HERE << "no service-proposed rules stored");
        return false; // earlier service did not plan for the future
    }

    debugs(85,3, HERE << "using stored service-proposed rules: " << services);

    ServiceGroupPointer g = new DynamicServiceChain(services, filter);
    callBack(g);
    Must(done());
    return true;
}