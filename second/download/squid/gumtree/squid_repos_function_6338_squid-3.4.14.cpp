void
Ipc::ReadWriteLock::unlockExclusive()
{
    assert(writers-- > 0);
}