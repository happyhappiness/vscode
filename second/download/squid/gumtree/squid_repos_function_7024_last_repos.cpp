void
Ipc::ReadWriteLock::unlockExclusive()
{
    assert(writing);
    appending = false;
    writing = false;
    --writeLevel;
}