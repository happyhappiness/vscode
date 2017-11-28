CachePeer *
Comm::Connection::getPeer() const
{
    if (cbdataReferenceValid(peer_))
        return peer_;

    return NULL;
}