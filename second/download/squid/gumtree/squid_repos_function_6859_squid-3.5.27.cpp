void
Ipc::ReadWriteLock::updateStats(ReadWriteLockStats &stats) const
{
    if (readers) {
        ++stats.readable;
        stats.readers += readers;
    } else if (writing) {
        ++stats.writeable;
        ++stats.writers;
        stats.appenders += appending;
    } else {
        ++stats.idle;
    }
    ++stats.count;
}