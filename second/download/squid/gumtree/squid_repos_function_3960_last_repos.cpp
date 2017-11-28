void
Ssl::PeekingPeerConnector::tunnelInsteadOfNegotiating()
{
    Must(callback != NULL);
    CbDialer *dialer = dynamic_cast<CbDialer*>(callback->getDialer());
    Must(dialer);
    dialer->answer().tunneled = true;
    debugs(83, 5, "The SSL negotiation with server aborted");
}