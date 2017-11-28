void
Ssl::PeerConnector::checkForPeekAndSpliceDone(allow_t answer)
{
    const Ssl::BumpMode finalAction = (answer.code == ACCESS_ALLOWED) ?
                                      static_cast<Ssl::BumpMode>(answer.kind):
                                      checkForPeekAndSpliceGuess();
    checkForPeekAndSpliceMatched(finalAction);
}