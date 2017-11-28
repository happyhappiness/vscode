void
Ssl::PeekingPeerConnector::cbCheckForPeekAndSpliceDone(allow_t answer, void *data)
{
    Ssl::PeekingPeerConnector *peerConnect = (Ssl::PeekingPeerConnector *) data;
    // Use job calls to add done() checks and other job logic/protections.
    CallJobHere1(83, 7, CbcPointer<PeekingPeerConnector>(peerConnect), Ssl::PeekingPeerConnector, checkForPeekAndSpliceDone, answer);
}