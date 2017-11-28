void
Ssl::PeekingPeerConnector::checkForPeekAndSpliceDone(allow_t answer)
{
    const Ssl::BumpMode finalAction = answer.allowed() ?
                                      static_cast<Ssl::BumpMode>(answer.kind):
                                      checkForPeekAndSpliceGuess();
    checkForPeekAndSpliceMatched(finalAction);
}