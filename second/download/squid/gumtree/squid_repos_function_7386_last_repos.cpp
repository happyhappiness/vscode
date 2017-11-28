void
Security::PeerConnector::connectionClosed(const char *reason)
{
    debugs(83, 5, reason << " socket closed/closing. this=" << (void*)this);
    mustStop(reason);
    callback = NULL;
}