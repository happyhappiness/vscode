bool
PeerPoolMgr::doneAll() const
{
    return !(validPeer() && peer->standby.limit) && AsyncJob::doneAll();
}