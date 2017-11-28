bool
Ipc::ReadWriteLock::lockShared()
{
    ++readLevel; // this locks "new" writers out
    if (!writeLevel || appending) { // nobody is writing, or sharing is OK
        ++readers;
        return true;
    }
    --readLevel;
    return false;
}