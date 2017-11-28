void Adaptation::Icap::ServiceRep::noteConnectionFailed(const char *comment)
{
    debugs(93, 3, HERE << "Connection failed: " << comment);
    --theBusyConns;
}