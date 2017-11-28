bool
Ipc::ReadWriteLock::lockHeaders()
{
    if (lockShared()) {
        if (!updating.test_and_set(std::memory_order_acquire))
            return true; // we got here first
        // the updating lock was already set by somebody else
        unlockShared();
    }
    return false;
}