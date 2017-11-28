Adaptation::Initiate *
Adaptation::Ecap::ServiceRep::makeXactLauncher(HttpMsg *virgin,
        HttpRequest *cause, AccessLogEntry::Pointer &alp)
{
    Must(up());

    // register now because (a) we need EventLoop::Running and (b) we do not
    // want to add more main loop overheads unless an async service is used.
    static AsyncEngine *TheEngine = NULL;
    if (AsyncServices.size() && !TheEngine && EventLoop::Running) {
        TheEngine = new Engine;
        EventLoop::Running->registerEngine(TheEngine);
        debugs(93, 3, "asyncs: " << AsyncServices.size() << ' ' << TheEngine);
    }

    XactionRep *rep = new XactionRep(virgin, cause, alp, Pointer(this));
    XactionRep::AdapterXaction x(theService->makeXaction(rep));
    rep->master(x);
    return rep;
}