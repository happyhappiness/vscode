void
Ipc::ReadWriteLock::unlockHeaders()
{
    AssertFlagIsSet(updating);
    updating.clear(std::memory_order_release);
    unlockShared();
}