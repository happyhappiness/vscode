int Adaptation::Icap::ServiceRep::availableConnections() const
{
    if (theMaxConnections < 0)
        return -1;

    // we are available if we can open or reuse connections
    // in other words, if we will not create debt
    int available = max(0, theMaxConnections - theBusyConns);

    if (!available && !connOverloadReported) {
        debugs(93, DBG_IMPORTANT, "WARNING: ICAP Max-Connections limit " <<
               "exceeded for service " << cfg().uri << ". Open connections now: " <<
               theBusyConns + theIdleConns->count() << ", including " <<
               theIdleConns->count() << " idle persistent connections.");
        connOverloadReported = true;
    }

    if (cfg().onOverload == srvForce)
        return -1;

    return available;
}