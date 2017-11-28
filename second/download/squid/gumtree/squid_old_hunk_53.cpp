        if (serv) {
            writeableCfg().port = htons(serv->s_port);
        } else {
            writeableCfg().port = 1344;
        }
    }
}

void Adaptation::Icap::ServiceRep::noteFailure()
{
    ++theSessionFailures;
    debugs(93,4, HERE << " failure " << theSessionFailures << " out of " <<
           TheConfig.service_failure_limit << " allowed " << status());

    if (isSuspended)
        return;

    if (TheConfig.service_failure_limit >= 0 &&
            theSessionFailures > TheConfig.service_failure_limit)
        suspend("too many failures");

    // TODO: Should bypass setting affect how much Squid tries to talk to
    // the ICAP service that is currently unusable and is likely to remain
    // so for some time? The current code says "no". Perhaps the answer
    // should be configurable.
}

void Adaptation::Icap::ServiceRep::suspend(const char *reason)
{
    if (isSuspended) {
        debugs(93,4, HERE << "keeping suspended, also for " << reason);
    } else {
        isSuspended = reason;
