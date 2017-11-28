bool
Ipc::ReadWriteLock::lockShared()
{
    ++readers; // this locks "new" writers out
    if (!writers) // there are no old writers
        return true;
    --readers;
    return false;
}