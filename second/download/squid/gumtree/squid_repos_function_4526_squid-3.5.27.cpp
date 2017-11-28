void
Ssl::PeerConnector::NegotiateSsl(int, void *data)
{
    PeerConnector *pc = static_cast<PeerConnector*>(data);
    // Use job calls to add done() checks and other job logic/protections.
    CallJobHere(83, 7, pc, Ssl::PeerConnector, negotiateSsl);
}