bool Adaptation::Iterator::updatePlan(bool adopt)
{
    HttpRequest *r = theCause ? theCause : dynamic_cast<HttpRequest*>(theMsg);
    Must(r);

    Adaptation::History::Pointer ah = r->adaptHistory();
    if (!ah) {
        debugs(85,9, HERE << "no history to store a service-proposed plan");
        return false; // the feature is not enabled or is not triggered
    }

    String services;
    if (!ah->extractNextServices(services)) { // clears history
        debugs(85,9, HERE << "no service-proposed plan received");
        return false; // the service did not provide a new plan
    }

    if (!adopt) {
        debugs(85,3, HERE << "rejecting service-proposed plan");
        return false;
    }

    debugs(85,3, HERE << "retiring old plan: " << thePlan);

    Adaptation::ServiceFilter f = this->filter();
    DynamicGroupCfg current, future;
    DynamicServiceChain::Split(f, services, current, future);

    if (!future.empty()) {
        ah->setFutureServices(future);
        debugs(85,3, HERE << "noted future service-proposed plan: " << future);
    }

    // use the current config even if it is empty; we must replace the old plan
    theGroup = new DynamicServiceChain(current, f); // refcounted
    thePlan = ServicePlan(theGroup, f);
    debugs(85,3, HERE << "adopted service-proposed plan: " << thePlan);
    return true;
}