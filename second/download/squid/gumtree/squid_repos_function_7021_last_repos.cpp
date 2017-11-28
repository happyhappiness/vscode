bool
Ipc::ReadWriteLock::lockExclusive()
{
    if (!writeLevel++) { // we are the first writer + lock "new" readers out
        if (!readLevel) { // no old readers and nobody is becoming one
            writing = true;
            return true;
        }
    }
    --writeLevel;
    return false;
}