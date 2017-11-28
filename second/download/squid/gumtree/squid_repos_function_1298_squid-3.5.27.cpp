bool
PeerPoolMgr::validPeer() const
{
    return peer && cbdataReferenceValid(peer) && peer->standby.pool;
}