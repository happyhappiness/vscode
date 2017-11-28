Adaptation::Initiate *
Adaptation::Icap::ServiceRep::makeXactLauncher(HttpMsg *virgin,
        HttpRequest *cause, AccessLogEntry::Pointer &alp)
{
    return new Adaptation::Icap::ModXactLauncher(virgin, cause, alp, this);
}