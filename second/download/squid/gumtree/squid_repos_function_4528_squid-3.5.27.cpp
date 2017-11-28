void
Ssl::PeerConnector::bail(ErrorState *error)
{
    Must(error); // or the recepient will not know there was a problem

    // XXX: forward.cc calls peerConnectSucceeded() after an OK TCP connect but
    // we call peerConnectFailed() if SSL failed afterwards. Is that OK?
    // It is not clear whether we should call peerConnectSucceeded/Failed()
    // based on TCP results, SSL results, or both. And the code is probably not
    // consistent in this aspect across tunnelling and forwarding modules.
    if (CachePeer *p = serverConnection()->getPeer())
        peerConnectFailed(p);

    Must(callback != NULL);
    CbDialer *dialer = dynamic_cast<CbDialer*>(callback->getDialer());
    Must(dialer);
    dialer->answer().error = error;

    callBack();
    // Our job is done. The callabck recepient will probably close the failed
    // peer connection and try another peer or go direct (if possible). We
    // can close the connection ourselves (our error notification would reach
    // the recepient before the fd-closure notification), but we would rather
    // minimize the number of fd-closure notifications and let the recepient
    // manage the TCP state of the connection.
}