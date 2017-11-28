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