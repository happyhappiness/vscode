    // visit adapter-specific options (i.e., those not recognized by Squid)
    typedef Master::Extensions::const_iterator MECI;
    for (MECI i = master.extensions.begin(); i != master.extensions.end(); ++i)
        visitor.visit(Name(i->first), Area::FromTempString(i->second));
}

/* Adaptation::Ecap::Engine */

int
Adaptation::Ecap::Engine::checkEvents(int)
{
    // Start with the default I/O loop timeout, convert from milliseconds.
    static const struct timeval maxTimeout = {
        EVENT_LOOP_TIMEOUT/1000, // seconds
        (EVENT_LOOP_TIMEOUT % 1000)*1000
    }; // microseconds
    struct timeval timeout = maxTimeout;

    kickAsyncServices(timeout);
    if (timeout.tv_sec == maxTimeout.tv_sec && timeout.tv_usec == maxTimeout.tv_usec)
        return EVENT_IDLE;

    debugs(93, 7, "timeout: " << timeout.tv_sec << "s+" << timeout.tv_usec << "us");

    // convert back to milliseconds, avoiding int overflows
    if (timeout.tv_sec >= std::numeric_limits<int>::max()/1000 - 1000)
        return std::numeric_limits<int>::max();
    else
        return timeout.tv_sec*1000 + timeout.tv_usec/1000;
}

/// resumes async transactions (if any) and returns true if they set a timeout
void
Adaptation::Ecap::Engine::kickAsyncServices(timeval &timeout)
{
    if (AsyncServices.empty())
        return;

    debugs(93, 3, "async services: " << AsyncServices.size());

    // Activate waiting async transactions, if any.
    typedef AdapterServices::iterator ASI;
    for (ASI s = AsyncServices.begin(); s != AsyncServices.end(); ++s) {
        assert(s->second);
        s->second->resume(); // may call Ecap::Xaction::resume()
    }

    // Give services a chance to decrease the default timeout.
    for (ASI s = AsyncServices.begin(); s != AsyncServices.end(); ++s) {
        s->second->suspend(timeout);
    }
}

/* Adaptation::Ecap::ServiceRep */

Adaptation::Ecap::ServiceRep::ServiceRep(const ServiceConfigPointer &cfg):
/*AsyncJob("Adaptation::Ecap::ServiceRep"),*/ Adaptation::Service(cfg),
    isDetached(false)
{
}

Adaptation::Ecap::ServiceRep::~ServiceRep()
{
}
