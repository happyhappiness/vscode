void
Ipc::ReadWriteLock::unlockShared()
{
    assert(readers > 0);
    --readers;
    --readLevel;
}