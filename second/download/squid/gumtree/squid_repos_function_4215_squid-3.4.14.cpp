Adaptation::Initiate *
Adaptation::Icap::ServiceRep::makeXactLauncher(HttpMsg *virgin,
        HttpRequest *cause)
{
    return new Adaptation::Icap::ModXactLauncher(virgin, cause, this);
}