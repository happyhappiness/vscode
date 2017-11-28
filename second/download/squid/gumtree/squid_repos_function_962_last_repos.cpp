void
PeerPoolMgr::Checkpoint(const Pointer &mgr, const char *reason)
{
    CallJobHere1(48, 5, mgr, PeerPoolMgr, checkpoint, reason);
}