Adaptation::Initiate *
Adaptation::Ecap::ServiceRep::makeXactLauncher(HttpMsg *virgin,
        HttpRequest *cause)
{
    Must(up());
    XactionRep *rep = new XactionRep(virgin, cause, Pointer(this));
    XactionRep::AdapterXaction x(theService->makeXaction(rep));
    rep->master(x);
    return rep;
}