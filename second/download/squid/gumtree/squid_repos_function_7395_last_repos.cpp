void
Security::PeerConnector::NegotiateSsl(int, void *data)
{
    PeerConnector *pc = static_cast<Security::PeerConnector *>(data);
    // Use job calls to add done() checks and other job logic/protections.
    CallJobHere(83, 7, pc, Security::PeerConnector, negotiate);
}