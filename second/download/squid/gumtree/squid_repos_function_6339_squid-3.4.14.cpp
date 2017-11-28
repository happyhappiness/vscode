void
Ipc::ReadWriteLock::switchExclusiveToShared()
{
    ++readers; // must be done before we release exclusive control
    unlockExclusive();
}