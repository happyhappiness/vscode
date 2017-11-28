void
Security::PeerConnector::start()
{
    AsyncJob::start();
    debugs(83, 5, "this=" << (void*)this);

    Security::SessionPointer tmp;
    if (prepareSocket() && initialize(tmp))
        negotiate();
    else
        mustStop("Security::PeerConnector TLS socket initialize failed");
}