bool Adaptation::Iterator::updatePlan(bool adopt)
{
    HttpRequest *r = theCause ? theCause : dynamic_cast<HttpRequest*>(theMsg);
    Must(r);

    Adaptation::History::Pointer ah = r->adaptHistory();
    if (!ah)
        return false; // the feature is not enabled or is not triggered

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
    theGroup = new DynamicServiceChain(services, theGroup); // refcounted
    thePlan = ServicePlan(theGroup, filter());
    debugs(85,3, HERE << "adopted service-proposed plan: " << thePlan);
    return true;
}