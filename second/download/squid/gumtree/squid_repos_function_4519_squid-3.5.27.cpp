void
Ssl::PeerConnector::cbCheckForPeekAndSpliceDone(allow_t answer, void *data)
{
    Ssl::PeerConnector *peerConnect = (Ssl::PeerConnector *) data;
    // Use job calls to add done() checks and other job logic/protections.
    CallJobHere1(83, 7, CbcPointer<PeerConnector>(peerConnect), Ssl::PeerConnector, checkForPeekAndSpliceDone, answer);
}