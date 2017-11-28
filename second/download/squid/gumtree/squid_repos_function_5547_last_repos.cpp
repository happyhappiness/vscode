time_t
Comm::Connection::connectTimeout(const time_t fwdStart) const
{
    // a connection opening timeout (ignoring forwarding time limits for now)
    const CachePeer *peer = getPeer();
    const time_t ctimeout = peer ? peerConnectTimeout(peer) : Config.Timeout.connect;

    // time we have left to finish the whole forwarding process
    const time_t fwdTimeLeft = FwdState::ForwardTimeout(fwdStart);

    // The caller decided to connect. If there is no time left, to protect
    // connecting code from trying to establish a connection while a zero (i.e.,
    // "immediate") timeout notification is firing, ensure a positive timeout.
    // XXX: This hack gives some timed-out forwarding sequences more time than
    // some sequences that have not quite reached the forwarding timeout yet!
    const time_t ftimeout = fwdTimeLeft ? fwdTimeLeft : 5; // seconds

    return min(ctimeout, ftimeout);
}