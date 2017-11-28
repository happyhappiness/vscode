Comm::ConnectionPointer
Comm::Connection::copyDetails() const
{
    ConnectionPointer c = new Comm::Connection;

    c->setAddrs(local, remote);
    c->peerType = peerType;
    c->tos = tos;
    c->nfmark = nfmark;
    c->flags = flags;
    c->startTime_ = startTime_;

    // ensure FD is not open in the new copy.
    c->fd = -1;

    // ensure we have a cbdata reference to peer_ not a straight ptr copy.
    c->peer_ = cbdataReference(getPeer());

    return c;
}