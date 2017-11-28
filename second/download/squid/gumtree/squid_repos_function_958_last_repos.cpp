void
PeerPoolMgr::handleSecureClosure(const CommCloseCbParams &params)
{
    Must(closer != NULL);
    Must(securer != NULL);
    securer->cancel("conn closed by a 3rd party");
    securer = NULL;
    closer = NULL;
    // allow the closing connection to fully close before we check again
    Checkpoint(this, "conn closure while securing");
}