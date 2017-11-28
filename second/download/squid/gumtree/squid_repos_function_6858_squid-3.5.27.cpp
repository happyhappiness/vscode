void
Ipc::ReadWriteLock::startAppending()
{
    assert(writing);
    appending = true;
}