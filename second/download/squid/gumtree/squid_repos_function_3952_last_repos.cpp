Ssl::BumpMode
Ssl::PeekingPeerConnector::checkForPeekAndSpliceGuess() const
{
    if (const ConnStateData *csd = request->clientConnectionManager.valid()) {
        const Ssl::BumpMode currentMode = csd->sslBumpMode;
        if (currentMode == Ssl::bumpStare) {
            debugs(83,5, "default to bumping after staring");
            return Ssl::bumpBump;
        }
        debugs(83,5, "default to splicing after " << currentMode);
    } else {
        debugs(83,3, "default to splicing due to missing info");
    }

    return Ssl::bumpSplice;
}