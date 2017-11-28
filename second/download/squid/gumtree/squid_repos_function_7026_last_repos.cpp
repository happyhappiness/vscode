void
Ipc::ReadWriteLock::switchExclusiveToShared()
{
    assert(writing);
    ++readLevel; // must be done before we release exclusive control
    ++readers;
    unlockExclusive();
}