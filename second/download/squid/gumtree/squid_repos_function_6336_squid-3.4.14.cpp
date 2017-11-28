bool
Ipc::ReadWriteLock::lockExclusive()
{
    if (!writers++) { // we are the first writer + this locks "new" readers out
        if (!readers) // there are no old readers
            return true;
    }
    --writers;
    return false;
}