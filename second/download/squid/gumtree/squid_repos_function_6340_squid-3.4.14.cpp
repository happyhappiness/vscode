void
Ipc::ReadWriteLock::updateStats(ReadWriteLockStats &stats) const
{
    if (readers) {
        ++stats.readable;
        stats.readers += readers;
    } else if (writers) {
        ++stats.writeable;
        stats.writers += writers;
    } else {
        ++stats.idle;
    }
    ++stats.count;
}