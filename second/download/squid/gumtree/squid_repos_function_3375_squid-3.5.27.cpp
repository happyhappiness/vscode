void
PconnPool::notifyManager(const char *reason)
{
    if (mgr.valid())
        PeerPoolMgr::Checkpoint(mgr, reason);
}