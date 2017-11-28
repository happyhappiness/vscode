void
PeerPoolMgr::closeOldConnections(const int howMany)
{
    debugs(48, 8, howMany);
    peer->standby.pool->closeN(howMany);
}